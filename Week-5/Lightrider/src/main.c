/*
Melvin Moes
20-12-2022
Lightrider
*/
//Importing gpio drivers
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

//Defining the Led Pins
int LED_PIN[10] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3};
#define HIGH 1
#define LOW 0
#define DELAY 1000 // 1000 milliseconde = 1 seconde

//Main code
void app_main() {
    //Config for adc
    adc1_config_width(10);
    adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);

    //Setting power direction for every single led
    for (size_t i = 0; i < 10; i++)
    {
        gpio_set_direction(LED_PIN[i], GPIO_MODE_OUTPUT);
    }

    //Max number it can count to using 10 leds
    int waarde = 0b000000001;

    while (true){
        int delay;
        //Initial direction
        for (size_t i = 0; i < 10; i++)
        {
            //Read value from potentiometer and add it as delay
            delay = adc1_get_raw(ADC1_CHANNEL_1);
            vTaskDelay(delay / portTICK_PERIOD_MS);
            for (size_t j = 0; j < 10; j++)
            {   
                printf("Potentiometer value: %d\n", delay);
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
        }
        //Opposite direction
        for (size_t i = 0; i < 10; i++)
        {
            //Read value from potentiometer and add it as delay
            delay = adc1_get_raw(ADC1_CHANNEL_1);
            vTaskDelay(delay / portTICK_PERIOD_MS);

            for (size_t j = 0; j < 10; j++)
            {   
                printf("Potentiometer value: %d\n", delay);
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
            
        }
    }
    
    
}  
