#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// Definições dos pinos para PWM e direção
const int LEFT_MOTOR_PWM = 9;      // Pino PWM para o motor esquerdo
const int LEFT_MOTOR_DIR = 8;      // Pino de direção para o motor esquerdo
const int RIGHT_MOTOR_PWM = 10;    // Pino PWM para o motor direito
const int RIGHT_MOTOR_DIR = 11;    // Pino de direção para o motor direito

// Constantes de controle do motor
const int PWM_MAX = 255;           // Valor máximo para PWM
const int PWM_MIN = 0;             // Valor mínimo para PWM

// Definições de motor
#define LEFT 0
#define RIGHT 1

// Funções para controle do motor
void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);

#endif // MOTOR_DRIVER_H
