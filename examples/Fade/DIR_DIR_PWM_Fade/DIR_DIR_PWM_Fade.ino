/*
  Автор    : Alash engineer
  Сайт     : https://alash-electronics.kz
  Исходник : https://github.com/Alash-electronics/AlashMotorControl

  Основано на примере Arduino Basic Fade.
  Диапазон скоростей от 0 до 255, по умолчанию 100.
  Используйте setSpeed(speed) для изменения.
  Иногда при низкой скорости моторы могут не работать.
  Это нормально и зависит от мотора и блока питания.
  Схема подключения в файле "AlashMotorControl - Schema_with_EN_pin.png".
  Код написан для Alash engineering.
*/
#include <AlashMotorControl.h>  // Подключаем библиотеку
// Определяем пины для подключения мотора
const unsigned int PIN_FORWARD = 4;
const unsigned int PIN_BACKWARD = 5;
const unsigned int PIN_ENABLE = 6;
// Создаем экземпляр класса AlashMotorControl
AlashMotorControl motor(PIN_FORWARD, PIN_BACKWARD, PIN_ENABLE);
// Начальная скорость и величина изменения скорости
int currentSpeed = 0;
int speedIncrement = 1;
void setup() {
  Serial.begin(9600);    // Инициализация последовательного порта для отображения информации
  while (!Serial) {     // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
}
void loop() {
  motor.setSpeed(currentSpeed);  // Применение скорости с эффектом затухания
  motor.forward();  // Двигаем мотор вперед (может зависеть от вашей схемы подключения)
  printMotorInfo();  // Выводим статус мотора в Serial Monitor
  currentSpeed += speedIncrement;  // Изменение текущей скорости для следующей итерации
  if (currentSpeed <= 0 || currentSpeed >= 255) {
    speedIncrement = -speedIncrement;  // Изменение направления изменения скорости при достижении пределов
  }
  delay(30);  // Задержка 30 миллисекунд для визуализации эффекта затухания
}
// Функция для вывода информации о моторе в Serial Monitor
void printMotorInfo() {
  Serial.print("Motor is moving = ");   // Выводим, движется ли мотор
  Serial.print(motor.isMoving() ? "YES" : "NO");
  Serial.print(" at speed = ");         // Выводим текущую скорость мотора
  Serial.println(motor.getSpeed());
}
