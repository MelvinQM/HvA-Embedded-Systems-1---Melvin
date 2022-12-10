/*
Melvin Moes
08-12-2022
A code that dims and brightens 3 LED's using PWM
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html
*/
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON                  (40)
#define HIGH                    (1)
#define LOW                     (0)

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO_R        (47)
#define LEDC_OUTPUT_IO_Y        (21)
#define LEDC_OUTPUT_IO_G        (20)
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_8_BIT // Set duty resolution to 8 bits
#define LEDC_FREQUENCY          (1000) // Frequency in Hertz. Set frequency at 1 kHz
#define MAX_DUTY                (255)

//Configures the ledc parameters
static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    //Making the configuration for the Orange LED
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_R,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void reset(int LED1, int LED2, int LED3) {
    gpio_set_level(LED1, LOW);
    gpio_set_level(LED2, LOW);
    gpio_set_level(LED3, LOW);
}

void app_main() {
    example_ledc_init();
    reset(LEDC_OUTPUT_IO_R, LEDC_OUTPUT_IO_Y, LEDC_OUTPUT_IO_G);

    gpio_set_direction(LEDC_OUTPUT_IO_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDC_OUTPUT_IO_Y, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDC_OUTPUT_IO_G, GPIO_MODE_OUTPUT);

    int CMD_1 = 0x01;
    int CMD_2 = 0x02;
    int CMD_3 = 0x03;
    int CMD_A = 0x0A;
    int command;

    while (true){
        // Clear the input buffer
        fflush(stdin);

        printf("Enter commando: ");
        scanf("%x", &command); // Read user input from the terminal
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        if (command == CMD_1){
            gpio_set_level(LEDC_OUTPUT_IO_R, HIGH);
        } else if (command == CMD_2){
            gpio_set_level(LEDC_OUTPUT_IO_Y, HIGH);
        } else if (command == CMD_3){
            gpio_set_level(LEDC_OUTPUT_IO_G, HIGH);
        } else if (command == CMD_A){

        } else {
        printf("Wrong input");
        }

    }
}