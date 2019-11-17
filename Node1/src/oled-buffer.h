/*
    General OLED-buffer (given 8-bit column height)
*/
#ifndef OLED_BUFFER_H
#define OLED_BUFFER_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

// Low level functions
void oled_buffer_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *buffer);

bool oled_buffer_get_pixel(uint8_t x, uint8_t y, uint8_t *buffer);

void oled_buffer_set_page_column(int page, int column, uint8_t data, uint8_t *buffer);

// System functions
void oled_buffer_clear_page(uint8_t page, uint8_t *buffer);

void oled_buffer_clear_screen(uint8_t *buffer);

// Text functions
enum TEXT_SIZE
{
    SMALL = 4,
    MEDIUM = 5,
    LARGE = 8
};

void oled_buffer_print_char(char c, enum TEXT_SIZE size, uint8_t page, uint8_t column, uint8_t *buffer);

void oled_buffer_print_string(char *s, enum TEXT_SIZE size, uint8_t page, uint8_t *buffer);

// Drawing functions
void oled_buffer_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *buffer);

void oled_buffer_draw_picture(uint8_t columns, uint8_t pages, 
                              const uint8_t picture_P[pages][columns], 
                              uint8_t column_offset, uint8_t page_offset,
                              uint8_t *buffer);
#endif /* OLED_BUFFER_H */