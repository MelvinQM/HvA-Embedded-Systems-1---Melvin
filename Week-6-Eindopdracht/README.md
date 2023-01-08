# ![alt text](assets/pictures/em1_markdown_header.png)

## Git repository onderhouden door: Melvin Moes, 500905603

## Pong Eindopdracht

## Gemaakt door: Melvin Moes, 500905603

For my end assignment I chose the project "Pong". The way I've done this is by using a ledbar and two buttons. Every button represents a player that tries to bounce back the light moving across the ledbar using their respective led they light up with the button. This gives the illusion that the led that lights up using the button is physically pushing back the moving led.

Here you can see the wiring schematic and physical wiring schematic
![alt text](assets/pictures/pong_schema.png)
![alt text](assets/pictures/pong_foto.png)

Below are all the libraries used in the program.
```python
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <string.h>
```

All the variables that are needed for the codes are defined here and can easily be changed if needed.
```python
//Defining power levels
#define HIGH 1
#define LOW 0
#define STACK_SIZE 5000

//Defining buffer size for uart
#define BUF_SIZE (1024)

//Defining the button pins for the two players (The pins are the physical pins)
#define PLAYER_ONE 38
#define PLAYER_TWO 45

//All delay variables
#define gameloopDelay 300
#define lifeLostBlink 250
#define countdownDelay 500
#define penaltyDelay 250

//Defining all led pins on the ledbar and gamemechanic variables
int LED_PIN[10] = {3, 8, 18, 17, 16, 15, 7, 6, 5, 4};
bool slideright = true;
bool direction;
int waarde = 0b000000001;


//Variables for the status of the player
bool pOneStatus;
bool pTwoStatus;
int pOneLives = 5;
int pTwoLives = 5;
char pOneName[BUF_SIZE];
char pTwoName[BUF_SIZE];
bool nameIsGiven = false;
//Boolean for the direction of the game to check which player should block the puck

/* Defining a data structure and defining the different instances of 
the datastructure for both players. Using 3 and 4 for the pins because 
array index isn't a constant.*/
typedef struct {
    int player;
    int pin;
} PlayerData;
PlayerData player1_data = {.player = PLAYER_ONE, .pin = 3};
PlayerData player2_data = {.player = PLAYER_TWO, .pin = 4};
```

2 functions are determined ahead of the function itself so that the parameters are known in advance for some other parts of the code.

The function player deals with the button control of the game it uses a boolean to detect if it is pressed this boolean is used in multiple places in the program.
```python
void life_display(int lives, int player);
void move_light();
void player(void *pvParameters) {
    //Function that is used to make 2 different tasks for both players

    // Cast the void pointer back to a struct type.
    PlayerData *data = (PlayerData *) pvParameters;
    int player = data->player;
    int pin = data->pin;
    //Checking if the instance of this function is player one or two
    bool isPlayerOne = false;
    if (pin == 3){
        isPlayerOne = true;
    }
    while (true){   
        if(gpio_get_level(player)){
            //An indicator if button is pressed
            if (isPlayerOne){
                pOneStatus = true;
            } else {
                pTwoStatus = true;
            }
            gpio_set_level(pin, HIGH);
            vTaskDelay(gameloopDelay / portTICK_PERIOD_MS);
            if (isPlayerOne){
                pOneStatus = false;
            } else {
                pTwoStatus = false;
            }
            gpio_set_level(pin, LOW);
            vTaskDelay(penaltyDelay / portTICK_PERIOD_MS);
        }
    }
}
```
![alt text](assets/gifs/buttonpress_gif.gif)

The setup required like the gpio powerdirection, UART initialization etc
```python
void setup(){
    //Uart setup
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    /*Setting the power direction for the buttons so 
    that it can receive a signal to see if the button is pressed*/
    gpio_set_direction(PLAYER_ONE, GPIO_MODE_INPUT);
    gpio_set_direction(PLAYER_TWO, GPIO_MODE_INPUT);

    //Setting the power direction for the ledbar
    for (size_t i = 0; i < 10; i++){
        gpio_set_direction(LED_PIN[i], GPIO_MODE_OUTPUT);
    }
}
```

The function displayed below handles the creation of the tasks. What these do is basically make a seperate thread that runs alongside the main thread. This is needed so the delays placed on these functions don't interfere with each other.

The first two tasks created are both using the same function to do this I've created a data structure with 2 different instances that are used respectively in the creation of the taks. 

The final task made is the gameplay task which I will describe in below.
```python
void task_function( void ){
    //Function for making 2 different tasks for both players to run independetly the main task
    TaskHandle_t xHandle = NULL;
    /* Create the task, storing the handle. */
    xTaskCreate(
        player,             /* Function that implements the task. */
        "Player 1 Input",   /* Text name for the task. */
        STACK_SIZE,         /* Stack size in words, not bytes. */
        &player1_data,      /* Parameter passed into the task. */
        tskIDLE_PRIORITY,   /* Priority at which the task is created. */
        &xHandle );
    
    xTaskCreate(
        player,             /* Function that implements the task. */
        "Player 2 Input",   /* Text name for the task. */
        STACK_SIZE,         /* Stack size in words, not bytes. */
        &player2_data,      /* Parameter passed into the task. */
        tskIDLE_PRIORITY,   /* Priority at which the task is created. */
        &xHandle );         /* Used to pass out the created task's handle. */

    xTaskCreate(
        gameplay,             /* Function that implements the task. */
        "Game Loop",   /* Text name for the task. */
        STACK_SIZE,         /* Stack size in words, not bytes. */
        NULL,      /* Parameter passed into the task. */
        tskIDLE_PRIORITY,   /* Priority at which the task is created. */
        &xHandle );         /* Used to pass out the created task's handle. */
}
```

The code below handles together with the function move_light and the function life_display the movement and interaction of the leds across the ledbar. It also handles the display of the amount of lives remaining the way it shows this is by blinking the amount of lights on the respective players side. It does this only when a life is lost.
```Python
void gameplay(){
    //While both players have atleast 1 live remaining, continue game.
    while (pOneLives >= 1 && pTwoLives >= 1){
        for (size_t i = 0; i < 10; i++){
            vTaskDelay(gameloopDelay / portTICK_PERIOD_MS);
            //Deciding which way to go based on the boolean
            if (slideright){
                //Initial direction
                direction = true;
                move_light();
                //Making sure the last led only turns on once
                if (i < 9){
                    waarde = waarde << 1;
                }               
            } else {
                //Reverse direction boolean to indicate which direction its going
                direction = false;
                move_light();
                //Making sure the last led only turns on once
                if (i < 9){
                    waarde = waarde >> 1;
                }
            }
        }
        /*According to the direction that is taken see which 
        player needs to save the puck, if direction = true than its player one etc*/
        if (direction){
            if (pTwoStatus){
                printf("Bounce!\n");
            } else {
                pTwoLives--;
                life_display(pTwoLives, 2);
                printf("BOOM %s lives remaining: %d\n", pTwoName, pTwoLives);
            }
        } else {
            if (pOneStatus){
                printf("Bounce!\n");
            } else {
                pOneLives--;
                life_display(pOneLives, 1);
                printf("BOOM %s lives remaining: %d\n", pOneName, pOneLives);
            }
        }
        //Reverse the direction
        slideright = !slideright;
    }
}
void move_light(){
    //Code to check all 10 led's
    for (size_t i = 0; i < 10; i++){   
    if ((waarde >> i) & 1){
        gpio_set_level(LED_PIN[i], HIGH);
    } else {
        gpio_set_level(LED_PIN[i], LOW);
    }
    }
}
void life_display(int lives, int player){
    //Parameter given through function call determines which player should show a lifelost animation
    if (player == 1){
        for (size_t i = 0; i < 5; i++){
            for (size_t i = 0; i < lives; i++){
                gpio_set_level(LED_PIN[i], HIGH);
            }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
            for (size_t i = 0; i < lives; i++){
                gpio_set_level(LED_PIN[i], LOW);
            }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
        }
    } else if (player == 2){
        for (size_t i = 0; i < 5; i++){
            for (size_t i = 0; i < lives; i++){
                gpio_set_level(LED_PIN[9-i], HIGH);
                }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
            for (size_t i = 0; i < lives; i++){
                gpio_set_level(LED_PIN[9-i], LOW);
            }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
        }        
    }
    //Checking which player won
    if (pOneLives == 0 || pTwoLives == 0){
        if (pOneLives == 0){
            printf("GAME OVER %s won!\n", pTwoName);
        } else {
            printf("GAME OVER %s won!\n", pOneName);
        }
        //Gameover animation
        for (size_t i = 0; i < 10; i++){
            for (size_t i = 0; i < 10; i++){
                gpio_set_level(LED_PIN[i], HIGH);
            }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
            for (size_t i = 0; i < 10; i++){
                gpio_set_level(LED_PIN[i], LOW);
            }
            vTaskDelay(lifeLostBlink / portTICK_PERIOD_MS);
        }
    }
}
```
![alt text](assets/gifs/life_display_gif.gif)

Finally a function to make a countdown animationa and the input for the players name. This way it can show the scores alongside the player names. The game doesn't start until the players names have been inputted.
```Python
void countdown(){
    /*Function for the initial countdown to the start of the game
    It starts by turning on all led's then turning them off one by one*/
    int countdown = 0b1111111111;
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j++){   
        if ((countdown >> j) & 1){
            gpio_set_level(LED_PIN[j], HIGH);
        } else {
            gpio_set_level(LED_PIN[j], LOW);
        } 
    }
    countdown = countdown >> 1;
    vTaskDelay(countdownDelay / portTICK_PERIOD_MS);
    }
    gpio_set_level(LED_PIN[0], LOW);
    vTaskDelay(countdownDelay / portTICK_PERIOD_MS);
}
void nameInput(char *pName){
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    memset(data, 0, BUF_SIZE);
    int nameLen = 0;
    while (!nameIsGiven)
    {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_0, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        //Data is an array of the inputted chars
        data[len] = '\0';
        //If input is received execute code
        if (len) {
            //Display for input
            printf("> %s\n", data);
            //Putting the storing of the input in the else statement to prevent the enter getting added to the name
            if (data[0] == '\r'){
                nameIsGiven = true;
            } else {
                // Store the input from the UART in the pOneName char array
                for (int i = 0; i < len; i++) {
                    pName[nameLen] = data[i];
                    nameLen++;
                }
            }

        }
    }

    // Add a null terminator to the end of the pOneName char array
    pName[nameLen] = '\0';

    //Incase another name needs to be inputted make nameIsGiven false
    nameIsGiven = false;
}
void app_main(){
    setup();

    printf("Player 1 enter name: (press enter to confirm)\n");
    nameInput(pOneName);
    printf("%s\n",pOneName);
    printf("Player 2 enter name: (press enter to confirm)\n");
    nameInput(pTwoName);
    printf("%s\n",pTwoName);

    printf("THE GAME IS STARTING SOON GET READY\n");
    countdown();
    task_function(); 
}
```
![alt text](assets/gifs/nameinput_gif.gif)
![alt text](assets/gifs/countdown_gif.gif)
