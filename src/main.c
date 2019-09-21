/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "defines.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "xmem.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "pwm0.h"
#include "delay.h"
#include "buzzer.h"

#include "songs/nyan_cat.h"

void heartbeat_init()
{
    DDRB |= 1 << DDB0;
}

void heartbeat()
{
    PORTB ^= 1 << PB0;
}


int main(void) {
    heartbeat_init();
    uart_init(); // So we can communicate with the terminal connected via JTAG
    xmem_init();
    adc_init();
    joystick_init();
    touch_init();
    pwm0_init();

    printf("All inits ran successfully!\n");

    buzzer_play_song_P(nyan_cat_melody, nyan_cat_note_types, NYAN_CAT_LENGTH);


    while (1)
    {
	    printf("Loop!\n");
        _delay_ms(100);
    }
}
