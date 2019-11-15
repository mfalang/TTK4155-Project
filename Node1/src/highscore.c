#include "highscore.h"

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////
static uint16_t _highscores[NUM_HIGHSCORES];

////////////////////////////////////////////////////////////////////////////////
// Private function declarations
////////////////////////////////////////////////////////////////////////////////
void _insert_score(uint8_t place, uint16_t score);

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////
void highscore_init(void) {
    _highscores[0] = 25;
    _highscores[1] = 20;
    _highscores[2] = 15;
    _highscores[3] = 10;
    _highscores[4] = 5;
}

uint16_t highscore_get(uint8_t place) {
    if (1 <= place && place <= NUM_HIGHSCORES) {
        return _highscores[place - 1];
    }
    return 0;
};

void highscore_print_score(char * out, uint8_t place) {
    uint16_t score = highscore_get(place);

    if (score){
        sprintf(out, "#%d: %d", place, score);
    }
};

uint8_t highscore_nominate(uint16_t score) {
    // Assumes the highscore list is already sorted 
    for (uint8_t p = 1; p <= NUM_HIGHSCORES; ++p) { // p for place
        if (score > highscore_get(p)) {
            _insert_score(p, score);
            return highscore_get(p);
        }
    }
    return 0; // Score not good enough
}

////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////
void _insert_score(uint8_t place, uint16_t score) {
    // Inserts the score at the given position, discarding the last element
    // Note that place is not zero-indexed

    // EXAMPLE:
    // _highscores before:
    // [15, 10, 5]
    // _highscores after _insert_score(13)
    // [15, 13, 10]

    for (uint8_t i = NUM_HIGHSCORES - 1; i >= place - 1; --i) {
        _highscores[i] = _highscores[i-1];
    }
    _highscores[place - 1] = score;
}
