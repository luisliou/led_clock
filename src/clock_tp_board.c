
#include "vk1628.h"
#include "clock_tp_board.h"
#include <stdint.h>
#include <stdbool.h>

uint8_t NUM_BYTE[] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};

uint8_t display_memory[14] = {0};


void show_time(struct tm *timeinfo)
{
    set_number(0, timeinfo->tm_hour / 10);
    set_number(1, timeinfo->tm_hour % 10);

    set_number(2, timeinfo->tm_min / 10);
    set_number(3, timeinfo->tm_min % 10);
}

void set_number(uint8_t index, uint8_t number)
{
    uint8_t address_map[5] = {0x0, 0x2, 0x4, 0x6, 0x8};
    uint8_t data = NUM_BYTE[number % sizeof(NUM_BYTE)];
    display_memory[address_map[index]] = data;
}

void set_colon(bool show)
{
    display_memory[8] = (display_memory[8] & 0x7F) | ((show > 0) << 7);
}

void set_slash(bool show)
{
    display_memory[10] = (display_memory[10] & 0x7F) | ((show > 0) << 7);
}
void set_week(uint8_t week)
{
    display_memory[10] = 1 << (week - 1 % 7);
}

void show_display()
{
    vk1628_write_command(CMD_ADDRESS_SETTING);
    vk1628_write_command_and_data(CMD_DATA_SETTING, display_memory, sizeof(display_memory));
}

void show_left(bool show)
{
    display_memory[12] = (display_memory[12] & 0xF7) | ((show > 0) << 3);
}

void show_right(bool show)
{
    display_memory[12] = (display_memory[12] & 0xEF) | ((show > 0) << 4);
}

int i = 0;

void test_loop()
{
    set_number(0, i);
    set_number(1, i + 1);
    set_number(2, i + 2);
    set_number(3, i + 3);
    set_number(4, i + 4);
    set_colon((i + 1) % 2);
    set_week(i);
    set_slash(i % 2);
    show_left(i % 2);
    show_right((i + 1) % 2);
    show_display();
    i++;
}
