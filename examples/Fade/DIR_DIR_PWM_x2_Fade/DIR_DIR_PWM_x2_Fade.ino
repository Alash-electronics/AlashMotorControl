/*
Author  : Alash engineer
Site    : https://alash-electronics.kz
Source  : https://github.com/Alash-electronics/AlashMotorControl

Этот код демонстрирует использование функции плавного изменения скорости моторов с использованием библиотеки AlashMotorControlX2.

AlashMotorControlX2 - это не новая версия модуля или ИС, а реализация библиотеки AlashMotorControl для управления двумя моторами одновременно.

Диапазон скоростей от 0 до 255, по умолчанию 100.
Используйте setSpeed(speed) для изменения скорости обоих моторов,
setSpeedA(speed) или setSpeedB(speed) для индивидуального изменения скорости.

Иногда на низкой скорости моторы могут не работать.
Это нормально и может зависеть от мотора и источника питания.

Схема подключения в файле "AlashMotorControlX2 - Schema_with_EN_pin.png".

Код написан для Alash engineering.
*/

#include <AlashMotorControlX2.h>
// Определение пинов для моторов
const unsigned int EN_A = 6;
const unsigned int IN1_A = 4;
const unsigned int IN2_A = 5;
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;
// Инициализация двух моторов
AlashMotorControlX2 motors(IN1_A, IN2_A, EN_A, IN1_B, IN2_B, EN_B);
int speedness = 0;
int speedAmount = 1;
void setup() {
  Serial.begin(9600);  // Инициализация последовательного порта для отображения информации
  while (!Serial) {    // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
}
void loop() {
  motors.setSpeed(speedness);  // Применение текущей скорости к обоим моторам
  motors.forwardA();  // Вращение левого мотора вперед
  motors.backwardB(); // Вращение правого мотора назад
  printMyInfo();  // Печать информации о статусе моторов
  speedness += speedAmount;  // Изменение скорости для следующей итерации
  if (speedness <= 0 || speedness >= 255) {
    speedAmount = -speedAmount;  // Обратное изменение скорости при достижении границ
  }
  delay(30);  // Задержка для визуализации изменения скорости
}
// Функция для вывода информации о моторах в Serial Monitor
void printMyInfo() {
  Serial.print("Motor A is moving = ");
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedB());
}
