#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_sntp.h"
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "vk1628.h"

void vk1628_write_byte(uint8_t data)
{
    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = data & 0x1;
        gpio_set_level(PIN_DIO, bit);
        data = data >> 1;
        // generate a rising edge
        gpio_set_level(PIN_CLK, 0);
        ets_delay_us(PW_CLK);
        gpio_set_level(PIN_CLK, 1);
        ets_delay_us(PW_CLK);
        ets_delay_us(1);
    }
}

void vk1628_write_command(uint8_t command)
{
    gpio_set_level(PIN_STB, 0); // begin to write
    ets_delay_us(1);
    vk1628_write_byte(command);
    gpio_set_level(PIN_STB, 1);
    ets_delay_us(1);
}
void vk1628_write_command_and_data(uint8_t command, uint8_t *data, int n)
{
    gpio_set_level(PIN_STB, 0); // begin to write
    ets_delay_us(1);
    vk1628_write_byte(command);
    for (int i = 0; i < n; i++)
    {
        vk1628_write_byte(data[i]);
    }
    gpio_set_level(PIN_STB, 1);
    ets_delay_us(1);
}

void vk1628_init()
{
    // Configure GPIO pins
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIN_STB) | (1ULL << PIN_CLK) | (1ULL << PIN_DIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(PIN_CLK, 0);
    uint8_t data[14] = {0};
    vk1628_write_command_and_data(CMD_DATA_SETTING, data, sizeof(data));
    vk1628_write_command(CMD_ADDRESS_SETTING);
    vk1628_write_command(CMD_DISPLAY_MODE | DISPLAY_MODE_7_10);
    vk1628_write_command(CMD_DISPLAY_CONTROL | DISPLAY_CONTROL_14_16 | DISPLAY_CONTROL_OFF);
    vk1628_write_command(CMD_DISPLAY_MODE | DISPLAY_MODE_7_10);
    vk1628_write_command(CMD_DISPLAY_CONTROL | DISPLAY_CONTROL_1_16 | DISPLAY_CONTROL_ON);
}
