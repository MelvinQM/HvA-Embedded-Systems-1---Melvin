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

    //Making the configuration for the Red LED
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

    //Making the configuration for the Yellow LED
    ledc_channel_config_t ledc_channel_2 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_Y,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_2));

    //Making the configuration for the Green LED
    ledc_channel_config_t ledc_channel_3 = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_G,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_3));
}

void app_main(void)
{
    // Set the LEDC peripheral configuration
    example_ledc_init();
    /*
    All 3 led's are on the same channel 0 so since the code is directing 
    the dutycycle to the channel all 3 will dimm and brighten in sync
    */
    while (true){
        for (size_t i = 0; i < MAX_DUTY; i++)
    {
        //Change dutycycle
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, i);
        // Update duty to apply the new value
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(10 / portTICK_PERIOD_MS); 
    }
        for (size_t i = MAX_DUTY; i > 0; i--)
    {
        //Change dutycycle
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, i);
        // Update duty to apply the new value
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(10 / portTICK_PERIOD_MS); 
    }
    }
}