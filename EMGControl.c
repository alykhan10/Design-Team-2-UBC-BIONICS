#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define KP 1.0
#define KI 0.1
#define KD 0.05

double pid(double setpoint, double measured, double *prev_error, double *integral) {
    double error = setpoint - measured;
    *integral += error;
    double derivative = error - *prev_error;

    *prev_error = error;

    return KP * error + KI * (*integral) + KD * derivative;
}

// Simulated encoder position (replace with real reading)
int readPosition() {
    return rand() % 180;  // Simulated angle (0–180°)
}

// Simulated motor control output
void applyMotorPWM(double control_signal) {
    printf("Motor PWM signal: %.2f\n", control_signal);
}

int main() {
    wiringPiSetup();

    double setpoint = 90;  // Target angle
    double integral = 0.0;
    double prev_error = 0.0;

    while (1) {
        int current_position = readPosition();
        double control = pid(setpoint, current_position, &prev_error, &integral);

        applyMotorPWM(control);
        delay(100);
    }

    return 0;
}