# ![alt text](assets/pictures/em1_markdown_header.png)

## Stoplicht Commandos Opdracht 4

## Gemaakt door: Melvin Moes, 500905603

```python
/*
Melvin Moes
28-12-2022
Code that received Input through UART using putty to control a traffic light
*/
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define BUF_SIZE (1024)
#define HIGH                    (1)
#define LOW                     (0)
#define LEDC_OUTPUT_IO_R        (47)
#define LEDC_OUTPUT_IO_Y        (21)
#define LEDC_OUTPUT_IO_G        (20)


//Function to turn all leds off
void reset() {
    gpio_set_level(LEDC_OUTPUT_IO_R, LOW);
    gpio_set_level(LEDC_OUTPUT_IO_Y, LOW);
    gpio_set_level(LEDC_OUTPUT_IO_G, LOW);
}

//Setups for Uart and GPIO
void setup(){
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

    //GPIO setup
    gpio_set_direction(LEDC_OUTPUT_IO_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDC_OUTPUT_IO_Y, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDC_OUTPUT_IO_G, GPIO_MODE_OUTPUT);
}

void app_main() {
    setup();
    reset();

    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (true) {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_0, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        //Data is an array of the inputted chars
        data[len] = '\0';
        //If input is received execute code
        if (len) {
            printf("> %s\n", data);
            //If input is 1 turn off all leds and turn on RED led same applies for the else ifs but for the other LEDs
            if (data[0] == '1'){
                reset();
                printf("1 IS INPUTTED\n");
                gpio_set_level(LEDC_OUTPUT_IO_R, HIGH);
            } else if (data[0] == '2'){
                reset();
                printf("2 IS INPUTTED\n");
                gpio_set_level(LEDC_OUTPUT_IO_Y, HIGH);     
            } else if (data[0] == '3'){
                reset();
                gpio_set_level(LEDC_OUTPUT_IO_G, HIGH);
                printf("3 IS INPUTTED\n");
            } else if (data[0] == 'A'){
                reset();
                printf("A IS INPUTTED PRESS ANY KEY TO INTERRUPT\n");
                while (true){
                    // Read data from the UART if data is inputted interrupt the blinking of the led
                    int len = uart_read_bytes(UART_NUM_0, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
                    if (len) {
                        printf("A IS INTERUPTED\n");
                        break;
                    }
                    gpio_set_level(LEDC_OUTPUT_IO_Y, HIGH);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(LEDC_OUTPUT_IO_Y, LOW);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                }
            } else {
            printf("Wrong input\n");
            }
        }
    }
}
```

![alt text](assets/pictures/Stoplicht_commando_schema.png)
![alt text](assets/gifs/commandos_gif.gif)

## Week 4 vragen
