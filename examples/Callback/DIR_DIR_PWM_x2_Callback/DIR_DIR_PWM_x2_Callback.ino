/*
  Author    : Alash engineer
  Site      : https://alash-electronics.kz
  Source    : https://github.com/Alash-electronics/AlashMotorControl

  Этот код демонстрирует использование функции обратного вызова с двумя моторами, управляемыми библиотекой AlashMotorControlX2.
  
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
const unsigned int IN1_LEFT = 4;
const unsigned int IN2_LEFT = 5;
const unsigned int EN_LEFT = 6;


const unsigned int IN1_RIGHT = 7;
const unsigned int IN2_RIGHT = 8;
const unsigned int EN_RIGHT = 9;

// Инициализация двух моторов
AlashMotorControlX2 motors(IN1_LEFT, IN2_LEFT, EN_LEFT, IN1_RIGHT, IN2_RIGHT, EN_RIGHT);

// Начальная скорость
unsigned short SpeedLeft = 55;
unsigned short SpeedRight = 255;

// Отслеживание направления
unsigned int direction = 1;

void setup() {
  Serial.begin(9600);  // Инициализация последовательного порта для отображения информации
  while (!Serial) {    // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
  Serial.println(F("Движение обоих моторов в течение 4 секунд с последующей печатью информации."));
  motors.setSpeedA(SpeedLeft);  // Установка начальной скорости для левого мотора
  motors.setSpeedB(SpeedRight); // Установка начальной скорости для правого мотора
  printInfo();  // Печать начальной информации
}

void loop() {
  if (direction) {
    motors.forwardFor(4000, callback);  // Движение обоих моторов вперед в течение 4 секунд с вызовом функции обратного вызова
  } else {
    motors.backwardFor(4000, callback); // Движение обоих моторов назад в течение 4 секунд с вызовом функции обратного вызова
  }
}

/*
  Функция обратного вызова: увеличивает скорость левого мотора и уменьшает скорость правого, затем сбрасывает оба мотора.
*/
void callback() {
  if (SpeedLeft > 255 && SpeedRight < 55) {
    direction = !direction;  // Смена направления
    Serial.println("Смена направления движения.");
  }
  if (SpeedLeft <= 255) {
    SpeedLeft += 25;  // Увеличение скорости левого мотора
  } else {
    SpeedLeft = 55;   // Сброс скорости левого мотора
  }
  if (SpeedRight >= 55) {
    SpeedRight -= 25; // Уменьшение скорости правого мотора
  } else {
    SpeedRight = 255; // Сброс скорости правого мотора
  }
  motors.setSpeedA(SpeedLeft);  // Установка новой скорости для левого мотора
  motors.setSpeedB(SpeedRight); // Установка новой скорости для правого мотора
  motors.reset();  // Повторное включение движения обоих моторов
  printInfo();     // Печать информации
}

// Функция для вывода информации о моторах в Serial Monitor
void printInfo() {
  Serial.print("Скорость мотора A = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Скорость мотора B = ");
  Serial.println(motors.getSpeedB());
}
