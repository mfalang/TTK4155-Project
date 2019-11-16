
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../../lib/inc/defines.h"

#include <avr/interrupt.h>
#include <avr/io.h>             // For led toggle

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "oled-menu.h"
#include "joystick.h"
#include "touch.h"
#include "oled-buffer.h"
#include "oled.h"
#include "game.h"
#include "highscore.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/message_defs.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define NUM_MAIN_MENU_ELEMENTS 3
#define NUM_HIGHSCORE_ELEMENTS NUM_HIGHSCORES // From "highscore.h". 
// Should not try to print more than 7 highscores with the 8 page OLED.
#define NUM_SONG_MENU_ELEMENTS 2
#define NUM_DIFFICULTY_MENU_ELEMENTS 3

////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////

static oled_menu_t *p_current_menu;
static oled_menu_t main_menu;
static oled_menu_t highscore_menu;
static oled_menu_t settings_menu;
static oled_menu_t difficulty_menu;
static oled_menu_el_t main_menu_elements[NUM_MAIN_MENU_ELEMENTS];
static oled_menu_el_t highscore_menu_elements[NUM_HIGHSCORE_ELEMENTS];
static oled_menu_el_t difficulty_menu_elements[NUM_DIFFICULTY_MENU_ELEMENTS];
static oled_menu_el_t song_menu_elements[NUM_SONG_MENU_ELEMENTS];

static joy_btn_dir_t prev_dir; 
static bool _menu_is_locked = false;
static uint16_t prev_score = 0;

////////////////////////////////////////////////////////////////////////////////
// Private function declarations
////////////////////////////////////////////////////////////////////////////////

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer);

void _menu_init_menus(void);
oled_menu_action_t _menu_get_empty_action(void);
oled_menu_action_t _menu_create_menu_ptr_action(oled_menu_t *p_menu);
oled_menu_action_t _menu_create_func_ptr_action(void *p_func);
oled_menu_el_t _menu_create_element(char *text, oled_menu_action_t action);
void _menu_perform_action(oled_menu_action_t action);
void _update_highscores_menu(void);
void _insert_new_highscore_test(void);

void _toggle_led(void);
void _start_game(uint8_t difficulty);
void _stop_game(void);
void _print_score_to_oled_buffer();

const static can_msg_t _calibrate_msg = { .sid = CALIBRATE_SID, .length = 0 };

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void oled_menu_init(void)
{
    _menu_init_menus();
    p_current_menu = &main_menu;

    prev_dir = NEUTRAL;

    draw_oled_menu(p_current_menu, OLED_BUFFER_BASE);
    oled_draw_screen(OLED_BUFFER_BASE);
}

void oled_menu_update(void)
{
    if (!_menu_is_locked) {
        joy_btn_dir_t dir = joystick_get_direction();

        if (dir == prev_dir) {
            return;
        }

        switch (dir)
        {
        case RIGHT:
            _menu_perform_action(
                p_current_menu->elements[p_current_menu->selected_idx].select_action);
            break;
        case LEFT:
            _menu_perform_action(p_current_menu->back_action);
            break;
        case UP:
            if (p_current_menu->selected_idx > 0)
            {
                --p_current_menu->selected_idx;
            }
            else
            {
                p_current_menu->selected_idx = p_current_menu->num_elements - 1;
            }
            break;
        case DOWN:
            if (p_current_menu->selected_idx < p_current_menu->num_elements - 1)
            {
                ++p_current_menu->selected_idx;
            }
            else
            {
                p_current_menu->selected_idx = 0;
            }
            break;
        }

        prev_dir = dir;
        if (!_menu_is_locked) {
            // The menu might be locked when doing an action, should only draw menu
            // if it is not
            draw_oled_menu(p_current_menu, OLED_BUFFER_BASE);
        }
    } else {
        // Menu is locked e.g. while playing
        // user can unlock by pressing left touch button

        // Print the score
        uint16_t new_score = game_get_score();

        if (prev_score != new_score) {
            // Avoid doing expensive buffer writing if not needed
            prev_score = new_score;
            _print_score_to_oled_buffer();
        }

        touch_btn_t buttons = touch_read_btns();

        if (buttons.left && buttons.right) {
            _stop_game();
        }

    }

    oled_draw_screen(OLED_BUFFER_BASE);
}


void oled_menu_lock(void) {
    _menu_is_locked = true;
}

void oled_menu_unlock(void) {
    _menu_is_locked = false;
}


////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

// Action functions

void _toggle_led(void)
{
    PORTE ^= 1 << PE0;
}

void _start_game(uint8_t difficulty) {
    _menu_is_locked = true;
    printf("Locking menu\n");
    game_start(difficulty);
    oled_buffer_clear_screen(OLED_BUFFER_BASE);
    oled_buffer_print_string("Playing...", LARGE, 0, OLED_BUFFER_BASE);
    _print_score_to_oled_buffer();
}


// TODO: Add typedefs instead of magic numbers
void _start_game_easy(void) {
    _start_game(0);
}

void _start_game_medium(void) {
    _start_game(1);
}

void _start_game_hard(void) {
    _start_game(2);
}

void _stop_game(void) {
    game_stop();
    _menu_is_locked = false;
    printf("Unlocking menu\n");
}

void _print_score_to_oled_buffer() {
    // Prints the score to the OLED buffer. 
    // Assumes the header is already printed in _start_game
    char score_string[15] = "";
    sprintf(score_string, "Score: %i", game_get_score());
    // strcpy(score_string, "asdf");
    printf(score_string);
    printf("\n");
    oled_buffer_print_string((char * ) score_string, MEDIUM, 2, OLED_BUFFER_BASE);
}

void _print_test(void) {

}

void _insert_new_highscore_test(void) {
    highscore_nominate(highscore_get(1) + 1);
    _update_highscores_menu();
}

void _send_calibrate(void) {
    can_send(&_calibrate_msg);
}

// Menu functions

void _menu_init_menus(void)
{
    // Set up main menu
    _menu_is_locked = false;
    main_menu.num_elements = 3;
    strcpy(main_menu.header_string, "Main Menu");
    main_menu.selected_idx = 0;
    main_menu.back_action = _menu_get_empty_action();

    main_menu_elements[0] = _menu_create_element("Play Game", _menu_create_menu_ptr_action(&difficulty_menu));
    main_menu_elements[1] = _menu_create_element("Highscores", _menu_create_menu_ptr_action(&highscore_menu));
    main_menu_elements[2] = _menu_create_element("Settings", _menu_create_menu_ptr_action(&settings_menu));
    main_menu.elements = main_menu_elements;

    // Set up submenus
    // Set up highscores "menu"
    strcpy(highscore_menu.header_string, "Highscores");
    highscore_menu.num_elements = NUM_HIGHSCORE_ELEMENTS;
    highscore_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    highscore_menu.selected_idx = 0;

    for (uint8_t i = 0; i < NUM_HIGHSCORE_ELEMENTS; ++i) {
        // Should not do anything when "selecting a score"
        highscore_menu_elements[i] = _menu_create_element("asdf", _menu_get_empty_action()); 
    }
    _update_highscores_menu(); // Generates strings and prints them to the menu
    highscore_menu.elements = highscore_menu_elements;

    // Set up settings menu
    strcpy(settings_menu.header_string, "Settings");
    settings_menu.num_elements = 2;
    settings_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    settings_menu.selected_idx = 0;

    song_menu_elements[0] = _menu_create_element("Calibrate position", _menu_create_func_ptr_action(&_send_calibrate));
    song_menu_elements[1] = _menu_create_element("Reset highscores", _menu_create_func_ptr_action(&highscore_reset));
    settings_menu.elements = song_menu_elements;

    // Set up difficulties menu
    strcpy(difficulty_menu.header_string, "Difficulty");
    difficulty_menu.num_elements = NUM_DIFFICULTY_MENU_ELEMENTS;
    difficulty_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    difficulty_menu.selected_idx = 0;

    difficulty_menu_elements[0] = _menu_create_element("Easy", _menu_create_func_ptr_action(&_start_game_easy));
    difficulty_menu_elements[1] = _menu_create_element("Medium", _menu_create_func_ptr_action(&_start_game_medium));
    difficulty_menu_elements[2] = _menu_create_element("Hard", _menu_create_func_ptr_action(&_start_game_hard));

    difficulty_menu.elements = difficulty_menu_elements;
}

void _update_highscores_menu(void) {
    for (uint8_t i = 0; i < NUM_HIGHSCORE_ELEMENTS; ++i) {
        highscore_print_score((char *) highscore_menu_elements[i].element_text, i+1);
    }
}

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer)
{
    // Clear the buffer
    oled_buffer_clear_screen(buffer);

    // Draw the header
    oled_buffer_print_string(menu->header_string, LARGE, 0, buffer);

    // Draw the elements
    char row_string[32] = "";

    const char *selected_marker = "> ";
    const char *not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        strcpy(row_string, "");

        bool is_selected = menu->selected_idx == i;
        if (is_selected)
        {
            // Add "> " before the string
            strcat(row_string, selected_marker);
        }
        else
        {
            // Add "  " before the string
            strcat(row_string, not_selected_marker);
        }

        strcat(row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string(row_string, MEDIUM, i + 1, buffer);
    }
}

oled_menu_action_t _menu_get_empty_action(void)
{
    // Returns an empty action
    oled_menu_action_t action;
    action.ptr.p_menu = NULL;
    action.is_func_ptr = false;

    return action;
}

oled_menu_action_t _menu_create_menu_ptr_action(oled_menu_t *p_menu)
{
    oled_menu_action_t action;

    action.is_func_ptr = false;
    action.ptr.p_menu = p_menu;

    return action;
}

oled_menu_action_t _menu_create_func_ptr_action(void *p_func)
{
    oled_menu_action_t action;
    action.is_func_ptr = true;
    action.ptr.p_menu = p_func;

    return action;
}

oled_menu_el_t _menu_create_element(char *text, oled_menu_action_t action)
{
    oled_menu_el_t element;

    strcpy(element.element_text, text);
    element.select_action = action;

    return element;
}

void _menu_perform_action(oled_menu_action_t action)
{
    if (action.is_func_ptr && action.ptr.p_func != NULL)
    {
        // Call function in function pointer
        action.ptr.p_func();
    }
    else if (action.ptr.p_menu != NULL)
    {
        // Change current menu to the pointer in the performed action if it is not NULL
        p_current_menu = action.ptr.p_menu;
    }
}