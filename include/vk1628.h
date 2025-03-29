
#ifndef VK1628_H
#define VK1628_H

#define PIN_STB 4
#define PIN_CLK 15
#define PIN_DIO 2

#define CMD_DISPLAY_MODE 0x0
#define DISPLAY_MODE_4_13 0x0
#define DISPLAY_MODE_5_12 0x1
#define DISPLAY_MODE_6_11 0x2
#define DISPLAY_MODE_7_10 0x3
#define CMD_DATA_SETTING 0x40
#define DATA_SETTING_READ_KEY 0x2
#define DATA_SETTING_FIXED 0x4
#define DATA_SETTING_TEST 0x8

#define CMD_DISPLAY_CONTROL 0x80
#define DISPLAY_CONTROL_1_16 0x0
#define DISPLAY_CONTROL_2_16 0x1
#define DISPLAY_CONTROL_4_16 0x2
#define DISPLAY_CONTROL_10_16 0x3
#define DISPLAY_CONTROL_11_16 0x4
#define DISPLAY_CONTROL_12_16 0x5
#define DISPLAY_CONTROL_13_16 0x6
#define DISPLAY_CONTROL_14_16 0x7
#define DISPLAY_CONTROL_ON 0x8
#define DISPLAY_CONTROL_OFF 0x0
#define CMD_ADDRESS_SETTING 0xC0

#define PW_CLK 5

#include <stdint.h>

void vk1628_init();
void vk1628_write_command(uint8_t command);
void vk1628_write_command_and_data(uint8_t command, uint8_t *data, int n);

#endif // VK1628_H