/*
Melvin Moes
2-12-2022
Binary button press counting program with leds
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pins
int LED_PIN[10] = {4, 5, 6, 7, 15, 16, 3, 46, 9, 10};
int BUTTON_UP = 41;
int BUTTON_DOWN = 40;

#define HIGH 1
#define LOW 0
#define DELAY 1000 // 1000 milliseconde = 1 seconde

//Main code
void app_main() {
    //NOT TESTED!!!!!!!!!!!!!!!!!!!!!!!!!!
    int length = sizeof(LED_PIN) / sizeof(LED_PIN[0]);
    //Setting power direction for every single led
    for (size_t i = 0; i < length; i++)
    {
        gpio_set_direction(LED_PIN[i], GPIO_MODE_OUTPUT);
    }

    gpio_set_direction(BUTTON_UP, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_DOWN, GPIO_MODE_INPUT);
    int telGetal = 0;
    
    while (true)
    {
        int upButtonState = gpio_get_level(BUTTON_UP);
        int downButtonState = gpio_get_level(BUTTON_DOWN);
        //Checking if the on button is pressed(This makes the tel)
        if (upButtonState == 1){
            printf("Teller Omhoog\n");
            telGetal++;
        }
        if (downButtonState == 1){
            printf("Teller Omlaag\n");
            telGetal--;
        }

        for (size_t i = 0; i < length; i++)
        {
            //TO DO: NEXT TIME PRINT CALCULATION RESULT BELOW IN VAR TO SEE IF IT PRINTS NUMBER HIGHER THAN 1
            if (((1 << i) & telGetal) >= 1)
            {
                gpio_set_level(LED_PIN[i], HIGH);
            } else {
                gpio_set_level(LED_PIN[i], LOW);
            }
        }
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}  