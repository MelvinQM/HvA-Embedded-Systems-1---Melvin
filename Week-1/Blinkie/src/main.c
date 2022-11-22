//Importing gpio drivers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pin 
#define LED_PIN 16
#define HIGH 1
#define LOW 0
#define DELAY 1000 // 1000 milliseconde = 1 seconde
#define SMALL_DELAY 100

//Main code
void app_main() {
    //Setting power direction
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    while (true){
    //Turning Led on and off in quick succession
    gpio_set_level(LED_PIN, HIGH);
    vTaskDelay(SMALL_DELAY / portTICK_PERIOD_MS); 
    gpio_set_level(LED_PIN, LOW);
    vTaskDelay(SMALL_DELAY / portTICK_PERIOD_MS);
    gpio_set_level(LED_PIN, HIGH);
    vTaskDelay(SMALL_DELAY / portTICK_PERIOD_MS);
    
    //Turning Led off
    gpio_set_level(LED_PIN, LOW);
    //Adding delay after turning it off
    vTaskDelay(DELAY / portTICK_PERIOD_MS);
    }  
}