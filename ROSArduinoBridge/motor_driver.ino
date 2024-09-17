#include <Arduino.h>
#include "motor_driver.h"

#ifdef USE_BASE

#ifdef YOUR_MOTOR_DRIVER

void initMotorController() {
    // Configura os pinos como saídas
    pinMode(LEFT_MOTOR_PWM, OUTPUT);
    pinMode(LEFT_MOTOR_DIR, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM, OUTPUT);
    pinMode(RIGHT_MOTOR_DIR, OUTPUT);

    // Inicializa o PWM para 0 e direção para frente
    analogWrite(LEFT_MOTOR_PWM, PWM_MIN);
    digitalWrite(LEFT_MOTOR_DIR, HIGH); // Assume que HIGH é para frente
    analogWrite(RIGHT_MOTOR_PWM, PWM_MIN);
    digitalWrite(RIGHT_MOTOR_DIR, HIGH); // Assume que HIGH é para frente
}

void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;

    if (spd < 0) {
        spd = -spd;
        reverse = 1;
    }
    if (spd > PWM_MAX) {
        spd = PWM_MAX;
    }

    if (i == LEFT) {
        analogWrite(LEFT_MOTOR_PWM, spd);
        digitalWrite(LEFT_MOTOR_DIR, reverse ? LOW : HIGH);
    } else if (i == RIGHT) {
        analogWrite(RIGHT_MOTOR_PWM, spd);
        digitalWrite(RIGHT_MOTOR_DIR, reverse ? LOW : HIGH);
    }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
}

#else
  #error A motor driver must be selected!
#endif

#endif
