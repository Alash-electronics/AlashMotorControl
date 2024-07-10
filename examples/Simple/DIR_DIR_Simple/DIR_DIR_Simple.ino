/*
  Автор    : Alash engineer
  Сайт     : https://alash-electronics.kz
  Исходник : https://github.com/Alash-electronics/AlashMotorControl
  В этом примере показано, как работать в обычной конфигурации без необходимости использования пина Enable.
  Убедитесь, что на вашем модуле установлен джампер.
  Если в AlashMotorControl используется джампер вместо пина Enable, скорость всегда равна 255.
  Схема подключения в файле "AlashMotorControl - Schema_without_EN_pin.png".
  Код написан для Alash engineering.
*/
#include <AlashMotorControl.h>  // Подключаем библиотеку
// Определяем пины для подключения мотора
const unsigned int PIN_FORWARD = 4;
const unsigned int PIN_BACKWARD = 5;
// Создаем экземпляр класса AlashMotorControl
AlashMotorControl motor(PIN_FORWARD, PIN_BACKWARD);
void setup() {
  Serial.begin(9600);    // Инициализация последовательного порта для отображения информации
  while (!Serial) {      // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
}
void loop() {
  motor.forward();  // Двигаем мотор вперед (может зависеть от вашей схемы подключения)
  Serial.print("Is moving = ");  // Выводим статус мотора в Serial Monitor
  Serial.println(motor.isMoving());
  delay(3000);  // Задержка 3 секунды

  motor.stop();  // Останавливаем мотор
  Serial.print("Is moving = ");  // Выводим статус мотора в Serial Monitor
  Serial.println(motor.isMoving());
  delay(3000);  // Задержка 3 секунды

  motor.backward();  // Двигаем мотор назад (может зависеть от вашей схемы подключения)
  Serial.print("Is moving = ");  // Выводим статус мотора в Serial Monitor
  Serial.println(motor.isMoving());
  delay(3000);  // Задержка 3 секунды

  motor.stop();  // Останавливаем мотор
  Serial.print("Is moving = ");  // Выводим статус мотора в Serial Monitor
  Serial.println(motor.isMoving());
  delay(3000);  // Задержка 3 секунды
}
