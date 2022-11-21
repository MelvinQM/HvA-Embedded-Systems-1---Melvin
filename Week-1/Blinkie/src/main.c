//Importing gpio drivers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pin 
#define LED_PIN 16
#define HIGH 1
#define LOW 0

//Main code
void app_main() {
    //Setting power direction
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    while (true){
    //Turning Led on and off in quick succession
    gpio_set_level(LED_PIN, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
    gpio_set_level(LED_PIN, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LED_PIN, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    //Turning Led off
    gpio_set_level(LED_PIN, LOW);
    //Adding delay after turning it off
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }  
}