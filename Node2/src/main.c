
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include <avr/interrupt.h>

#include "ir.h"
#include "pid.h"
#include "dac.h"
#include "motor.h"
#include "enocder.h"
#include "solenoid.h"
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"
#include "pwm.h"

// pid_t motor_vel_pid;
// float kp = 1;
// float ki = 0;
// float kd = 0.2;
float t  = 0.01;  // sample time of pid
// float output_limit = 60;

pid_t motor_pos_pid;
int16_t pos = 0;

int16_t enc = 0;


int main(void) {
    uart_init();
    ir_init();
    dac_init();
    motor_init();
    encoder_init();
    solenoid_init();
    can_init(MODE_NORMAL);
    pwm_init();

    // pid_init(&motor_vel_pid, kp, ki, kd, t, output_limit);
    // motor_vel_pid.setpoint = 0;

    pid_init(&motor_pos_pid, 0.05, 0.01, 0, t, -1);

    printf("All inits ran successfully!\n");

    const can_msg_t *recvmsg;

    int solenoid_cmd_prev = 0;

    while (1) {
        if (can_new_msg()) {
            recvmsg = can_get_recv_msg();

            /* for (int i = 0; i < recvmsg->length; ++i) {
                printf("%.2X ", recvmsg->data[i]);
            } */
            // printf("\tu: %d\n", (int)(motor_vel_pid.output));

            // int16_t r = recvmsg->data[1] - 51;
            // motor_vel_pid.setpoint = r;

            // fire solenoid once when joystick is pointed up
            if (recvmsg->data[0] == 2 && solenoid_cmd_prev != recvmsg->data[0]) {
                solenoid_cmd_prev = recvmsg->data[0];
                solenoid_give_pulse();
            }
            else if (recvmsg->data[0] != 2) {
                solenoid_cmd_prev = recvmsg->data[0];
            }

            // Control position
            int16_t pos_ref = recvmsg->data[5] * -80;
            motor_pos_pid.setpoint = pos_ref;
            printf("R: %d\tPos: %d\tU: %d\te: %d\n", (int)pos_ref, 
                        (int)motor_pos_pid.measurement, (int)motor_pos_pid.output, 
                        (int)motor_pos_pid.current_error);


            // Turn the servo using the touch sliders
            // int16_t degrees = 180 - (int16_t)(recvmsg->data[6] * 1.8);
            // printf("deg: %i\n", degrees);

            // pwm_set_duty_cycle(degrees);
        }
    }

    return 0;
}   


ISR(TIMER5_COMPA_vect) {
    // pid_next_output(&motor_vel_pid);
    // motor_vel_pid.measurement = encoder_read();

    // Control pos
    pid_next_output(&motor_pos_pid);
    enc = encoder_read_raw();
    motor_pos_pid.measurement += enc;
    motor_set_speed(motor_pos_pid.output);
}

