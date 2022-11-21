## Blinkie opdracht 1
## Gemaakt door: Melvin Moes, 500905603, 17-11-2022

```
//Importing gpio drivers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pin 
#define LED_PIN 21

//Main code
void app_main() {
    //Setting power direction
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    //Turning Led on
    gpio_set_level(LED_PIN, HIGH);
    //Adding a delay between turning the Led on and off
    vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
    //Turning Led off
    gpio_set_level(LED_PIN, LOW);
}
```


