/*
Melvin Moes
20-12-2022
Lightrider
*/
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

//Defining the Led Pins and variables
int LED_PIN[10] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3};
int waarde = 0b000000001;
bool slideright = true;
int delay;
#define DELAY_DIVISION 4
#define HIGH 1
#define LOW 0
#define DELAY 1000 // 1000 milliseconde = 1 seconde

//Function for the movement of the ledbar
void move_light(int waarde){
    for (size_t j = 0; j < 10; j++){   
    if ((waarde >> j) & 1){
        gpio_set_level(LED_PIN[j], HIGH);
    } else {
        gpio_set_level(LED_PIN[j], LOW);
    }
}
}

void app_main() {
    //Config for adc
    adc1_config_width(10);
    adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);

    //Setting power direction for every single led
    for (size_t i = 0; i < 10; i++)
    {
        gpio_set_direction(LED_PIN[i], GPIO_MODE_OUTPUT);
    }

    //Main ledbar movement code
    while (true)
    {
        for (size_t i = 0; i < 10; i++)
        {
            //Read value from potentiometer and add it as delay
            delay = adc1_get_raw(ADC1_CHANNEL_1);
            //Adding 5 to the delay so the delay is never 0 to prevent hardware issues
            vTaskDelay((delay/DELAY_DIVISION + 5) / portTICK_PERIOD_MS);
            printf("Potentiometer value: %d\n", delay);
            
            //Deciding which way to go based on the boolean
            if (slideright){
                //Initial direction
                move_light(waarde);
                //Making sure the last led doesnt turn on and off
                if (i < 9){
                    waarde = waarde << 1;
                }
            } else {
                //Reverse direction
                move_light(waarde);
                //Making sure the last led doesnt turn on and off
                if (i < 9){
                    waarde = waarde >> 1;
                }
            }
        }
        //Reverse the direction
        slideright = !slideright;
    }
}  