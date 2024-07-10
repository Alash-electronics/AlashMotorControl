/*
Author  : Alash engineer
Site    : https://alash-electronics.kz
Source  : https://github.com/Alash-electronics/AlashMotorControl
Этот пример демонстрирует, как работать в стандартной конфигурации без необходимости использования пина Enable.
Убедитесь, что на вашем модуле установлен джампер.
AlashMotorControlX2 - это не новая версия модуля или ИС, а двойная реализация библиотеки AlashMotorControl.
С помощью AlashMotorControlX2 можно инициализировать два мотора одновременно.
Когда у AlashMotorControl установлен джампер вместо пина Enable, скорость всегда равна 255.
Схема подключения в файле "AlashMotorControlX2 - Schema_without_EN_pin.png".
Код написан для Alash engineering.
*/
#include <AlashMotorControlX2.h>
// Определение пинов
const unsigned int IN1_A = 4;
const unsigned int IN2_A = 5;
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
// Инициализация обоих моторов
AlashMotorControlX2 motors(IN1_A, IN2_A, IN1_B, IN2_B);
void setup(){
  Serial.begin(9600); // Инициализация последовательного порта для отображения информации
  // Ожидание открытия Serial Monitor
  while (!Serial) {
    // ничего не делаем
  }
}
void loop(){
  motors.forward(); // Оба мотора движутся вперед (может зависеть от вашего подключения)
  // Альтернативный метод:
  // motors.run(AlashMotorControl::FORWARD);
  printMyInfo(); // Печать статуса моторов в Serial Monitor
  delay(3000);
  motors.stop(); // Остановка моторов
  // Альтернативный метод:
  // motors.run(AlashMotorControl::STOP);
  printMyInfo();
  delay(3000);
  motors.backwardA(); // Мотор A движется назад (может зависеть от вашего подключения)
  // Альтернативный метод:
  // motors.runA(AlashMotorControl::BACKWARD);
  motors.backwardB(); // Мотор B движется назад (может зависеть от вашего подключения)
  // Альтернативный метод:
  // motors.runB(AlashMotorControl::BACKWARD);
  printMyInfo();
  delay(3000);
  motors.stop(); // Остановка моторов
  printMyInfo();
  delay(3000);
}
//Функция для вывода информации о моторах в Serial Monitor
void printMyInfo(){
  Serial.print("Мотор A движется = ");
  Serial.println(motors.isMovingA() ? "ДА" : "НЕТ");
  Serial.print("Мотор B движется = ");
  Serial.println(motors.isMovingB() ? "ДА" : "НЕТ");
}
