/**
 * @file star_wars_picture_128x32.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Star Wars logo implemented as a paged picture that can be printed to
 *        the OLED screen. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef STAR_WARS_PICTURE_128X32_H
#define STAR_WARS_PICTURE_128X32_H

#include <avr/pgmspace.h>
#include <stdint.h>

#define STAR_WARS_PICTURE_PAGES 4
#define STAR_WARS_PICTURE_COLUMNS  128

const uint8_t starwars_picture_128x32[STAR_WARS_PICTURE_PAGES][STAR_WARS_PICTURE_COLUMNS] PROGMEM = 
{
    {
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x8, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xcf,
        0x8f, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0, 0xc0,
        0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0xf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xf8, 0xe0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
    },

    {
        0x0, 0x0, 0x0, 0x0, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
        0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7d, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f,
        0x3f, 0x1f, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        0x7f, 0x7f, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x7c, 0x7f, 0x7f,
        0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x3f, 0x7f,
        0x7f, 0x7f, 0x7f, 0x7f, 0x7c, 0x70, 0x40, 0x0, 0x0, 0x0, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        0x7f, 0x7f, 0x7f, 0x3, 0x7, 0x7, 0xf, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7d,
        0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x0, 0x0, 0x0, 0x0
    },

    {
        0x0, 0x0, 0x0, 0x0, 0x2, 0xe, 0x3e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf0, 0xe0,
        0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0xe0, 0xf0, 0xfc,
        0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x1e, 0x6, 0x0, 0x0, 0x0, 0xc0, 0xf0, 0xfc, 0xfe, 0xfe,
        0xfe, 0xfe, 0xfe, 0xfe, 0x3e, 0x1e, 0x7e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0xe0, 0x80, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x9e,
        0x9e, 0x8e, 0x8e, 0x9e, 0x9e, 0x9e, 0x9e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x7c, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
        0x9e, 0x9e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x0, 0x0, 0x0, 0x0
    },

    {
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x3f, 0xf, 0x3, 0x1, 0x7, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x7f, 0x1f, 0x7, 0x1, 0x0, 0x0, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
        0x3f, 0x3f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3d, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
        0xf8, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7,
        0xf, 0xf, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf8, 0xf8,
        0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf9, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x7f, 0x7f, 0x7f, 0x3e, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
    }
};

#endif  // STAR_WARS_PICTURE_128X32_H