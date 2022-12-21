/*
Melvin Moes
20-12-2022
Lightrider
*/
//Importing gpio drivers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pins
int LED_PIN[10] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3};
int POT_PIN = 2 //Phys 1 ADC 1_1
#define HIGH 1
#define LOW 0
#define DELAY 1000 // 1000 milliseconde = 1 seconde

//Main code
void app_main() {

    //Setting power direction for every single led
    for (size_t i = 0; i < 10; i++)
    {
        gpio_set_direction(LED_PIN[i], GPIO_MODE_OUTPUT);
    }

    //Max number it can count to using 10 leds
    int waarde = 0b000000001;

    while (true){
    //Initial direction
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {   
            //De waarde is 
            if ((waarde >> j) & 1){
                gpio_set_level(LED_PIN[j], HIGH);
            } else {
                gpio_set_level(LED_PIN[j], LOW);
            }
        }
        if (i < 9){
            waarde = waarde << 1;
        }
        vTaskDelay(DELAY / portTICK_PERIOD_MS);
    }

    //Opposite direction
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {   
            //De waarde is 
            if ((waarde >> j) & 1){
                gpio_set_level(LED_PIN[j], HIGH);
            } else {
                gpio_set_level(LED_PIN[j], LOW);
            }
        }
        if (i < 9){
            waarde = waarde >> 1;
        }
        vTaskDelay(DELAY / portTICK_PERIOD_MS);
    }
    }
    
    
}  
