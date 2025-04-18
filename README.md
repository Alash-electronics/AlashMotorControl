# Библиотека AlashMotorControl от Alash electronics

Добро пожаловать! Alash electronics с гордостью представляет библиотеку **AlashMotorControl**, разработанную в Казахстане для легкого и эффективного управления двигателями постоянного тока (DC моторами) с помощью платформы Arduino.

Эта библиотека создана для упрощения взаимодействия с популярными драйверами моторов, такими как L298N и TA6586 (ZK-5AD), предоставляя интуитивно понятный интерфейс для ваших робототехнических и DIY проектов.

Мы также предлагаем вариант **AlashMotorControlX2**, который позволяет управлять двумя моторами с помощью одного экземпляра библиотеки, идеально подходя для создания двухколесных роботов или других механизмов с несколькими двигателями. **AlashMotorControlX2** — это не новая версия модуля, а удобная обертка для управления двумя моторами одновременно с использованием базовых функций AlashMotorControl.

## 🇰🇿 Сделано в Казахстане

Мы рады внести свой вклад в развитие технологической экосистемы Казахстана, предоставляя разработчикам и энтузиастам удобные инструменты для реализации их идей.

## Ключевые особенности

* **Простота использования:** Интуитивно понятные методы для управления скоростью и направлением.
* **Поддержка разных драйверов:** Совместимость с L298N (с пином Enable и без него) и TA6586 (управление ШИМ через пины IN).
* **Управление скоростью:** Поддержка ШИМ (PWM) для плавной регулировки скорости (для драйверов с EN или TA6586).
* **Timed-функции:** Возможность запускать мотор на определенное время.
* **Функции обратного вызова (Callbacks):** Выполнение пользовательского кода после завершения движения на заданное время.
* **Два мотора (AlashMotorControlX2):** Удобное управление двумя моторами через один объект.
* **Разные типы остановки:** Поддержка плавной остановки (`stop()`) и резкого торможения (`HardStop()`).

## Установка библиотеки

1.  **Скачайте репозиторий:** Загрузите последнюю версию библиотеки [с GitHub](https://github.com/Alash-electronics/AlashMotorControl) как ZIP-архив (`Code` -> `Download ZIP`).
2.  **Установите в Arduino IDE:**
    * Откройте Arduino IDE.
    * Перейдите в меню `Скетч` -> `Подключить библиотеку` -> `Добавить .ZIP библиотеку...`.
    * Выберите скачанный ZIP-файл.
    * Библиотека будет установлена и готова к использованию.

## Подключение библиотеки к проекту

Добавьте соответствующую строку `#include` в начало вашего скетча:

```cpp
// Для управления одним мотором
#include <AlashMotorControl.h>
C++

// Для управления двумя моторами одновременно
#include <AlashMotorControlX2.h>
Инициализация (Создание экземпляра)
Для одного мотора (AlashMotorControl):

C++

#include <AlashMotorControl.h>

// --- Варианты инициализации ---

// 1. Драйвер L298N с пином Enable (EN подключен к PWM пину Arduino)
// AlashMotorControl motor(PIN_IN1, PIN_IN2, PIN_EN);
AlashMotorControl motor1(7, 8, 9); // Пример: IN1=7, IN2=8, EN=9

// 2. Драйвер L298N без пина Enable (перемычка EN установлена, мотор всегда на полной скорости)
// AlashMotorControl motor(PIN_IN1, PIN_IN2);
// или явно указать тип драйвера (по умолчанию L298N)
// AlashMotorControl motor(PIN_IN1, PIN_IN2, DRIVER_L298N);
AlashMotorControl motor2(4, 5); // Пример: IN1=4, IN2=5

// 3. Драйвер TA6586 (ZK-5AD) (пины IN1/IN2 управляют и направлением, и скоростью через ШИМ)
// AlashMotorControl motor(PIN_IN1, PIN_IN2, DRIVER_TA6586);
AlashMotorControl motor3(10, 11, DRIVER_TA6586); // Пример: IN1=10(PWM), IN2=11(PWM)

void setup() {
  // Код инициализации
}

void loop() {
  // Управление моторами motor1, motor2, motor3
}
PIN_IN1, PIN_IN2: Цифровые пины Arduino, подключенные к входам IN1 и IN2 драйвера. Для TA6586 эти пины должны поддерживать ШИМ (PWM).
PIN_EN: Пин Arduino с поддержкой ШИМ (PWM), подключенный к пину Enable (ENA или ENB) драйвера L298N.
DRIVER_L298N, DRIVER_TA6586: Константы для явного указания типа драйвера (необязательно для L298N, но рекомендуется для ясности).
Для двух моторов (AlashMotorControlX2):

Инициализация аналогична, но вы указываете пины для обоих моторов (A и B).

C++

#include <AlashMotorControlX2.h>

// Пример: Два драйвера L298N с пинами Enable
#define IN1_A 7
#define IN2_A 8
#define EN_A  9 // PWM
#define IN1_B 4
#define IN2_B 5
#define EN_B  6 // PWM

AlashMotorControlX2 motors_l298_en(IN1_A, IN2_A, EN_A, IN1_B, IN2_B, EN_B);

// Пример: Два драйвера TA6586
#define IN1_A_TA 10 // PWM
#define IN2_A_TA 11 // PWM
#define IN1_B_TA 2  // PWM
#define IN2_B_TA 3  // PWM

AlashMotorControlX2 motors_ta6586(IN1_A_TA, IN2_A_TA, IN1_B_TA, IN2_B_TA, DRIVER_TA6586, DRIVER_TA6586);

// Пример: Смешанные драйверы (Мотор A - L298N с EN, Мотор B - TA6586)
// AlashMotorControlX2 mixed_motors(IN1_A, IN2_A, EN_A, // Мотор A (L298N)
//                                 IN1_B_TA, IN2_B_TA, // Мотор B (TA6586)
//                                 DRIVER_L298N,      // Тип драйвера A
//                                 DRIVER_TA6586);     // Тип драйвера B


void setup() {
  // Код инициализации
}

void loop() {
  // Управление моторами через motors_l298_en или motors_ta6586
}
Основные методы AlashMotorControl
Метод	Параметры	Описание
setSpeed	int speedVal (0-255)	Устанавливает скорость мотора. Эффективно для L298N с PIN_EN или для TA6586.
getSpeed	нет	Возвращает текущую установленную скорость (0-255). Возвращает 0, если мотор остановлен.
forward	нет	Запускает мотор в прямом направлении (конкретное направление зависит от подключения) с текущей установленной скоростью.
backward	нет	Запускает мотор в обратном направлении с текущей установленной скоростью.
run	AlashMotorControl::Direction direction	Запускает мотор в указанном направлении (FORWARD, BACKWARD) или останавливает (STOP).
controlBySpeed	int speedVal (-255 до 255)	Управляет направлением и скоростью одним значением. Положительное значение - вперед, отрицательное - назад, 0 - остановка (stop).
forwardFor	unsigned long delay	Запускает мотор вперед на delay миллисекунд, затем останавливает (stop).
forwardFor	unsigned long delay, CallBackFunction callback	Запускает мотор вперед на delay мс, затем останавливает и вызывает функцию callback.
backwardFor	unsigned long delay	Запускает мотор назад на delay миллисекунд, затем останавливает (stop).
backwardFor	unsigned long delay, CallBackFunction callback	Запускает мотор назад на delay мс, затем останавливает и вызывает функцию callback.
runFor	unsigned long delay, Direction direction	Запускает мотор в указанном направлении на delay мс, затем останавливает (stop).
runFor	unsigned long delay, Direction direction, CallBackFunction callback	Запускает мотор в указанном направлении на delay мс, останавливает и вызывает callback.
stop	нет	Останавливает мотор, позволяя ему вращаться по инерции (Coast stop). Устанавливает LOW на пинах IN1/IN2 (и EN, если используется). Для TA6586 устанавливает PWM 0 на IN1/IN2.
HardStop	нет	Резко тормозит мотор (Brake stop). Устанавливает HIGH на пинах IN1/IN2 (и держит EN HIGH, если используется).
reset	нет	Сбрасывает внутренний таймер и флаг для функций *For, позволяя им быть вызванными снова.
isMoving	нет	Возвращает true, если мотор в данный момент должен двигаться (согласно последней команде), false в противном случае.
getDirection	нет	Возвращает текущее установленное направление (FORWARD, BACKWARD или STOP).
getDriverType	нет	Возвращает тип драйвера, указанный при инициализации (DRIVER_L298N или DRIVER_TA6586).

Экспортировать в Таблицы
Константы направления (Direction):

AlashMotorControl::FORWARD
AlashMotorControl::BACKWARD
AlashMotorControl::STOP
Типы драйверов (MotorDriverType):

DRIVER_L298N
DRIVER_TA6586
Важно для timed-функций (*For):

Для корректной работы функций forwardFor, backwardFor, runFor необходимо постоянно вызывать соответствующую функцию внутри loop(). Библиотека проверяет истекшее время только при вызове этих методов.

C++

void loop() {
  // Если вы запустили motor.forwardFor(5000, myCallback); в setup() или ранее в loop()
  // Нужно продолжать вызывать его здесь, чтобы он мог проверить время:
  motor.forwardFor(5000, myCallback);

  // Ваш остальной код...
}
Методы AlashMotorControlX2
Экземпляр AlashMotorControlX2 предоставляет доступ ко всем методам AlashMotorControl для каждого мотора отдельно, добавляя суффикс A или B:

setSpeedA(speed), setSpeedB(speed)
forwardA(), forwardB()
backwardForA(delay, callback), backwardForB(delay, callback)
stopA(), stopB()
HardStopA(), HardStopB()
isMovingA(), isMovingB()
и так далее...
Также доступны методы без суффиксов, которые влияют на оба мотора одновременно:

setSpeed(speed): Устанавливает одинаковую скорость для обоих моторов.
forward(): Запускает оба мотора вперед.
backward(): Запускает оба мотора назад.
run(direction): Запускает оба мотора в указанном направлении.
forwardFor(delay, callback): Запускает оба мотора вперед на delay, затем останавливает оба и вызывает callback один раз.
backwardFor(delay, callback): Аналогично для движения назад.
runFor(delay, direction, callback): Аналогично для указанного направления.
stop(): Останавливает оба мотора (Coast Stop).
HardStop(): Тормозит оба мотора (Brake Stop).
reset(): Сбрасывает таймеры и флаги для обоих моторов.
Примеры использования
Вы можете найти готовые примеры скетчей в папке examples данного репозитория. Если вы установили библиотеку через Arduino IDE, примеры доступны через меню Файл -> Примеры -> AlashMotorControl.

Simple: Базовое управление - вперед, назад, стоп.
Fade: Плавное изменение скорости мотора (требуется PWM управление скоростью).
Callback: Использование функций обратного вызова с timed-функциями.
SimpleX2: Базовое управление двумя моторами с AlashMotorControlX2.
ControlBySpeed: Демонстрация метода controlBySpeed.
HardStop: Демонстрация разницы между stop() и HardStop().
Схемы подключения
Принципиальные схемы подключения для разных конфигураций драйверов находятся в папке schema репозитория или посмотрите изображения ниже:

L298N (Один мотор)
С пином Enable

Без пина Enable (с перемычкой)


L298N (Два мотора - для AlashMotorControlX2)
С пинами Enable

Без пинов Enable (с перемычками)


(Примечание: Схемы для TA6586 аналогичны схемам без пинов Enable, но пины IN1/IN2 должны быть подключены к PWM-выходам Arduino)

Лицензия
Библиотека распространяется под лицензией MIT. См. файл LICENSE для получения дополнительной информации.

Поддержка и Контакты
Если у вас возникли вопросы, предложения или вы нашли ошибку, пожалуйста, создайте Issue на странице GitHub репозитория.

Спасибо за использование продукции Alash electronics!
