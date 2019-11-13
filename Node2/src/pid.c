#include "pid.h"
#include <avr/interrupt.h>
#include "../../lib/inc/defines.h"

#include <stdio.h>


void pid_init(pid_t *pid, float kp, float ki, float kd, float timestep, float output_maximum, float output_minimum) {
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->T  = timestep;
    
    pid->measurement = 0;
    pid->setpoint    = 0;

    pid->current_error = 0;
    pid->previous_error = 0;
    pid->cumulative_error = 0;

    pid->output = 0;
    pid->output_maximum = output_maximum;
    pid->output_minimum = output_minimum;


    // Setup timer
    // CTC mode with TOP = OCR5A, disconnected pin
    TCCR5B |= (1 << WGM02) | (1 << CS51) | (1 << CS50);
    TCCR5A = 0;

    uint32_t ocr = (uint32_t)F_CPU * timestep / (2UL * 64UL);
    OCR5A = (uint16_t)ocr;

    TIMSK5 |= (1 << OCIE5A);
    sei();
}


void pid_next_output(pid_t *pid) {
    pid->previous_error = pid->current_error;
    pid->current_error = pid->setpoint - pid->measurement;
    pid->cumulative_error += pid->current_error * pid->T;

    pid->output = pid->Kp * pid->current_error
                + pid->Ki * pid->cumulative_error
                + pid->Kd / pid->T * (pid->current_error - pid->previous_error);

    if (pid->output_maximum >= 0) {
        if (pid->output >= pid->output_maximum)
            pid->output = pid->output_maximum;
        else if (pid->output <= -pid->output_maximum)
            pid->output = -pid->output_maximum;
    }
    else if (pid->output_minimum >= 0) {
        if (pid->output <= pid->output_minimum && pid->output >= -pid->output_minimum)
            pid->output = 0;
    }


}


