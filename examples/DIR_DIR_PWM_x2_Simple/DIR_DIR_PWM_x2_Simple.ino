/*
  Автор    : Alash engineer
  Сайт     : https://alash-electronics.kz
  Исходник : https://github.com/Alash-electronics/AlashMotorControl
  В этом примере показано, как работать с двумя моторами с использованием AlashMotorControlX2.
  AlashMotorControlX2 не является новой версией библиотеки,
  а представляет собой двойную реализацию библиотеки AlashMotorControl.
  С помощью AlashMotorControlX2 можно инициализировать сразу два мотора.
  Диапазон скоростей от 0 до 255, по умолчанию 100.
  Используйте setSpeed(speed) для изменения скорости обоих моторов,
  setSpeedA(speed) или setSpeedB(speed) для индивидуальных изменений.
  Иногда на низкой скорости моторы могут не работать.
  Это нормально и может зависеть от мотора и источника питания.
  Схема подключения в файле "AlashMotorControlX2 - Schema_with_EN_pin.png".
  Код написан для Alash engineering.
*/
// Подключаем библиотеку
#include <AlashMotorControlX2.h>
// Определение пинов для моторов
const unsigned int PIN_FORWARD_LEFT = 4;
const unsigned int PIN_BACKWARD_LEFT = 5;
const unsigned int PIN_ENABLE_LEFT = 6;

const unsigned int PIN_FORWARD_RIGHT = 7;
const unsigned int PIN_BACKWARD_RIGHT = 8;
const unsigned int PIN_ENABLE_RIGHT = 9;
// Инициализация двух моторов
AlashMotorControlX2 motors(PIN_FORWARD_LEFT, PIN_BACKWARD_LEFT, PIN_ENABLE_LEFT, PIN_FORWARD_RIGHT, PIN_BACKWARD_RIGHT, PIN_ENABLE_RIGHT);
void setup(){
  Serial.begin(9600);  // Инициализация последовательного порта для отображения информации
  while (!Serial) {    // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
  motors.setSpeed(80);  // Установка начальной скорости для обоих моторов
}
void loop(){
  motors.forward();  // Двигаем оба мотора вперед (может зависеть от вашей схемы подключения)
  // Альтернативный метод:
  // motors.run(AlashMotorControl::FORWARD);
  // Выводим статус моторов в Serial Monitor
  printMotorInfo();
  delay(3000);  // Задержка 3 секунды
  motors.stop();  // Останавливаем моторы
  // Альтернативный метод:
  // motors.run(AlashMotorControl::STOP);
  printMotorInfo();
  delay(3000);  // Задержка 3 секунды
  // Изменение скорости индивидуально
  motors.setSpeedA(255);
  motors.setSpeedB(90);
  motors.backwardA();  // Двигаем мотор A назад (может зависеть от вашей схемы подключения)
  // Альтернативный метод:
  // motors.runA(AlashMotorControl::BACKWARD);
  motors.backwardB();  // Двигаем мотор B назад (может зависеть от вашей схемы подключения)
  // Альтернативный метод:
  // motors.runB(AlashMotorControl::BACKWARD);
  printMotorInfo();
  delay(3000);  // Задержка 3 секунды
  motors.stop();  // Останавливаем моторы
  printMotorInfo();
  // Изменение скорости индивидуально
  motors.setSpeedA(90);
  motors.setSpeedB(255);
  motor.сontrolBySpeed
  delay(3000);  // Задержка 3 секунды
}
// Функция для вывода информации о моторах в Serial Monitor
void printMotorInfo() {
  Serial.print("Motor A is moving = ");  // Выводим, движется ли мотор A
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");          // Выводим текущую скорость мотора A
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");  // Выводим, движется ли мотор B
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");          // Выводим текущую скорость мотора B
  Serial.println(motors.getSpeedB());
}
