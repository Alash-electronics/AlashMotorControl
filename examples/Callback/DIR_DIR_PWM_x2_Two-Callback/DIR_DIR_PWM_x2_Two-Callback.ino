/*
  Author  : Alash engineer
  Site    : https://alash-electronics.kz
  Source  : https://github.com/Alash-electronics/AlashMotorControl

  Этот пример показывает, как работать с двумя моторами, каждый из которых имеет свой собственный коллбэк.
  AlashMotorControlX2 - это не новая версия модуля или ИС, а двойная реализация библиотеки AlashMotorControl.
  С помощью AlashMotorControlX2 можно инициализировать два мотора одновременно.
  Диапазон скоростей от 0 до 255, по умолчанию 100.
  Используйте setSpeed(speed) для изменения скорости обоих моторов,
  setSpeedA(speed) или setSpeedB(speed) для индивидуальных изменений.
  Схема подключения в файле "AlashMotorControlX2 - Schema_with_EN_pin.png".
  Код написан для Alash engineering.
*/
#include <AlashMotorControlX2.h>
// Определение пинов
const unsigned int EN_A = 6;
const unsigned int IN1_A = 4;
const unsigned int IN2_A = 5;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;
// Инициализация обоих моторов
AlashMotorControlX2 motors(IN1_A, IN2_A, EN_A, IN1_B, IN2_B, EN_B);
void setup() {
  Serial.begin(9600); // Инициализация последовательного порта для отображения информации
  while (!Serial) {
    // ничего не делаем, ждем открытия Serial Monitor
  }
  motors.setSpeedA(120); // Установка скорости для мотора A
  motors.setSpeedB(80);  // Установка скорости для мотора B
  printInfo(); // Печать начальной информации
}
int stepA = 1;
unsigned long delayA = 3000;
int directionA = AlashMotorControl::FORWARD;

unsigned long delayB = 3000;
int directionB = AlashMotorControl::BACKWARD;

void loop() {
  motors.runForA(delayA, directionA, callbackA); // Управление мотором A
  motors.runForB(delayB, directionB, callbackB); // Управление мотором B
  // Другие задачи...
}
//Функция callbackA: на основе текущего шага выполняет изменения для мотора A.
void callbackA() {
  switch (stepA) {
    case 1:
      delayA = 10000;
      directionA = AlashMotorControl::BACKWARD;
      motors.setSpeedA(90);
      motors.resetA();
      break;
    case 2:
      delayA = 5000;
      directionA = AlashMotorControl::FORWARD;
      motors.setSpeedA(130);
      motors.resetA();
      break;
    case 3:
      delayA = 10000;
      directionA = AlashMotorControl::STOP;
      motors.setSpeedA(90);
      motors.resetA();
      break;
    case 4:
      delayA = 10000;
      directionA = AlashMotorControl::BACKWARD;
      motors.setSpeedA(90);
      motors.resetA();
      break;
    case 5:
      delayA = 5000;
      directionA = AlashMotorControl::FORWARD;
      motors.setSpeedA(200);
      motors.resetA();
      break;
  }
  stepA = (stepA < 4) ? stepA + 1 : 1;
  printInfo();
}
//Функция callbackB: при каждом вызове меняет направление для мотора B.
void callbackB() {
  directionB = !directionB;
  motors.resetB();
}
// Функция для печати информации о моторах в Serial Monitor
void printInfo() {
  Serial.print("Motor A | Speed = ");
  Serial.print(motors.getSpeedA());
  Serial.print(" | Direction = ");
  Serial.print(motors.getDirectionA());
  Serial.print(" | Next step = ");
  Serial.println(stepA);

  Serial.print("Motor B | Speed = ");
  Serial.print(motors.getSpeedB());
  Serial.print(" | Direction = ");
  Serial.println(motors.getDirectionB());
}
