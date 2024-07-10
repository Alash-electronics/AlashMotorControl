/*
  Автор    : Alash engineer
  Сайт     : https://alash-electronics.kz
  Исходник : https://github.com/Alash-electronics/AlashMotorControl

  В этом примере показано, как работать с опцией обратного вызова.
  Каждые пять секунд вызывается функция обратного вызова, увеличивая скорость.
  Когда достигается максимальная скорость, начинается снова с нуля.
  В это время ваш цикл loop никогда не блокируется.
  Диапазон скоростей от 0 до 255, по умолчанию 100.
  Используйте setSpeed(speed) для изменения.
  Иногда при низкой скорости моторы могут не работать.
  Это нормально и зависит от мотора и блока питания.
  Схема подключения в файле "AlashMotorControl - Schema_with_EN_pin.png".
*/
#include <AlashMotorControl.h>  // Подключаем библиотеку
// Определяем пины для подключения мотора
const unsigned int PIN_FORWARD = 4;
const unsigned int PIN_BACKWARD = 5;
const unsigned int PIN_ENABLE = 6;

// Создаем экземпляр класса AlashMotorControl
AlashMotorControl motor(PIN_FORWARD, PIN_BACKWARD, PIN_ENABLE);
unsigned short motorSpeed = 0;// Начальная скорость
void setup() {
  motor.setSpeed(motorSpeed);  // Устанавливаем начальную скорость мотора
}
void loop() {
  motor.forwardFor(5000, speedCallback);  // Двигаем мотор вперед на 5 секунд, затем вызываем функцию обратного вызова
  // Более гибкий способ:
  // motor.runFor(5000, AlashMotorControl::FORWARD, speedCallback);
}
/*Функция обратного вызова вызывается каждый раз для увеличения скорости мотора или сброса до 0.
  Эта функция может называться как угодно.*/
void speedCallback() {
  // Если скорость больше 255, увеличиваем
  if (motorSpeed <= 255) {
    motorSpeed += 25;
  } else {
    motorSpeed = 0;
  }
  /*Каждый раз при вызове функции обратного вызова
    мотор находится в состоянии "не двигаться".
    Для восстановления его работы используйте метод reset().*/
  motor.reset();
  motor.setSpeed(motorSpeed);  // Устанавливаем новую скорость
}
