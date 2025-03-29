#ifndef CLOCK_TP_BOARD_H
#define CLOCK_TP_BOARD_H
#include <time.h>
#include <stdint.h>
#include <stdbool.h>


void show_time(struct tm *timeinfo);
void set_number(uint8_t index, uint8_t number);
void set_colon(bool show);
void set_slash(bool show);
void set_week(uint8_t week);
void show_display();
void show_left(bool show);
void show_right(bool show);

#endif