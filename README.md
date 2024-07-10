```markdown
# Библиотека AlashMotorControl

Легкая в использовании библиотека AlashMotorControl для управления двигателями постоянного тока с помощью Arduino.

Для инициализации обоих моторов сразу используйте вариант библиотеки AlashMotorControlX2.

AlashMotorControlX2 - это не новая версия модуля или микросхемы, а двойная реализация библиотеки AlashMotorControl.

## УСТАНОВКА БИБЛИОТЕКИ

Скачайте этот репозиторий в виде .zip файла и в Arduino IDE выберите _Скетч -> Подключить библиотеку -> Добавить библиотеку из ZIP-файла_.

## ИМПОРТ

Вы можете импортировать библиотеку в свой код, используя Arduino IDE, выбрав _Скетч -> Подключить библиотеку -> AlashMotorControl_ или напрямую добавив строку include в ваш код:

```cpp
// Для одного мотора
#include <AlashMotorControl.h>
```

```cpp
// Для двух моторов
#include <AlashMotorControlX2.h>
```

## СОЗДАНИЕ ЭКЗЕМПЛЯРА МОДУЛЯ

Для управления мотором первым шагом является создание экземпляра библиотеки.

```cpp
// С пином Enable для управления скоростью
AlashMotorControl myMotor(IN1, IN2, EN); //DIR_DIR_PWM
```

```cpp
// Без пина Enable, с установленным джампером
AlashMotorControl myMotor(IN1, IN2);  //DIR_DIR
```

- EN = Пин Arduino (требуется PWM пин), подключенный к пину Enable модуля
- IN1 и IN2 - два цифровых пина, подключенные к IN1 и IN2 пинам модуля

### То же самое для варианта AlashMotorControlX2

```cpp
// С пином Enable для управления скоростью

                                    мотор A            мотор B
                            |------------------||------------------|
AlashMotorControlX2 myMotors(IN1_A, IN2_A, EN_A, IN1_B, IN2_B, EN_B);
```

```cpp
// Без пина Enable и с установленным джампером

                                 мотор A      мотор B
                            |------------||------------|
AlashMotorControlX2 myMotors(IN1_A, IN2_A, IN1_B, IN2_B);
```

## Методы AlashMotorControl

| Метод           | Параметры                                                                 | Описание                                                                                                                                       |
| :-------------- | :------------------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------------------------- |
| **setSpeed**    | unsigned short pwmVal                                                      | Устанавливает значение PWM для определения скорости мотора. Значение от 0 до 255.                                                              |
| **getSpeed**    | нет                                                                       | Возвращает ранее установленную скорость.                                                                                                       |
| **forward**     | нет                                                                       | Запускает мотор в прямом направлении (зависит от подключения).                                                                                 |
| **forwardFor**  | unsigned long delay                                                        | Запускает мотор в прямом направлении на время, указанное в delay.                                                                               |
| **forwardFor**  | unsigned long delay, CallBackFunction callback                             | Запускает мотор в прямом направлении на время, указанное в delay, после завершения вызывает функцию обратного вызова.                          |
| **backward**    | нет                                                                       | Запускает мотор в обратном направлении (зависит от подключения).                                                                                |
| **backwardFor** | unsigned long delay                                                        | Запускает мотор в обратном направлении на время, указанное в delay.                                                                             |
| **backwardFor** | unsigned long delay, CallBackFunction callback                             | Запускает мотор в обратном направлении на время, указанное в delay, после завершения вызывает функцию обратного вызова.                         |
| **run**         | uint8_t direction                                                          | Запускает мотор. Для указания направления используйте _AlashMotorControl::FORWARD_, _AlashMotorControl::BACKWARD_ или _AlashMotorControl::STOP_.|
| **runFor**      | unsigned long delay, AlashMotorControl::Direction direction                | Как _forwardFor_ или _backwardFor_, но более гибкий. Для указания направления используйте _AlashMotorControl::FORWARD_, _AlashMotorControl::BACKWARD_ или _AlashMotorControl::STOP_. |
| **runFor**      | unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback | Как предыдущий метод с возможностью выполнения функции обратного вызова.                                                                         |
| **stop**        | нет                                                                       | Останавливает мотор.                                                                                                                            |
| **reset**       | нет                                                                       | Используется для повторного включения движения мотора после использования методов _runFor_, _forwardFor_ или _backwardFor_.                      |
| **isMoving**    | нет                                                                       | Возвращает логическое значение, указывающее, работает ли мотор или нет.                                                                          |
| **getDirection**| нет                                                                       | Возвращает текущее направление **AlashMotorControl::Direction**.                                                                                |

#### Направление

| Константа      | Значение |
| :------------- | :-------:|
| AlashMotorControl::FORWARD  |     0     |
| AlashMotorControl::BACKWARD |     1     |
| AlashMotorControl::STOP     |    -1     |

## Методы AlashMotorControlX2

AlashMotorControlX2 имеет те же методы, что и AlashMotorControl, но с суффиксами A или B для управления каждым мотором. Например, setSpeed для мотора A это setSpeedA, а для мотора B - setSpeedB.

Методы без суффиксов влияют на оба мотора.

| Метод       | Параметры                                                                 |
| :---------- | :------------------------------------------------------------------------- |
| setSpeed    | unsigned short pwmVal                                                      |
| forward     | нет                                                                       |
| forwardFor  | unsigned long delay, CallBackFunction callback                             |
| forwardFor  | unsigned long delay                                                        |
| backward    | нет                                                                       |
| backwardFor | unsigned long delay, CallBackFunction callback                             |
| backwardFor | unsigned long delay                                                        |
| run         | uint8_t direction                                                          |
| runFor      | unsigned long delay, AlashMotorControl::Direction direction                |
| runFor      | unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback |
| stop        | нет                                                                       |
| reset       | нет                                                                       |

## Примеры

Примеры можно найти в папке examples или, если библиотека установлена в Arduino IDE, через меню _Файл -> Примеры -> AlashMotorControl_.

Схемы подключения можно найти в папке _schema_.

![L298NX2 - Schema_without_EN_pins](https://github.com/Alash-electronics/AlashMotorControl/assets/171731850/f49d3a24-c0d8-404a-8e69-5fe0ca60e0a0)
![L298NX2 - Schema_with_EN_pins](https://github.com/Alash-electronics/AlashMotorControl/assets/171731850/2b4a2df4-fa63-4a6c-85e1-2228c47fe866)
![L298N - Schema_without_EN_pin](https://github.com/Alash-electronics/AlashMotorControl/assets/171731850/d424b0ec-7fcf-4ec8-a628-932d95376f11)
![L298N - Schema_with_EN_pin](https://github.com/Alash-electronics/AlashMotorControl/assets/171731850/c291277b-08c3-4a9e-8740-f5b6128b6df4)
