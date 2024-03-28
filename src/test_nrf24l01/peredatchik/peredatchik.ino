// https://3d-diy.ru/wiki/arduino-moduli/radio-modul-nrf24l01/
// https://роботехника18.рф/nrf24l01-ардуино/

#include <SPI.h>  // Подключаем библиотеку для работы с SPI-интерфейсом
#include <nRF24L01.h> // Подключаем файл конфигурации из библиотеки RF24
#include <RF24.h> // Подключаем библиотеку для работа для работы с модулем NRF24L01
#define PIN_POT A7  // Номер пина Arduino, к которому подключен потенциометр
#define PIN_CE  9  // Номер пина Arduino, к которому подключен вывод CE радиомодуля
#define PIN_CSN 10 // Номер пина Arduino, к которому подключен вывод CSN радиомодуля
RF24 radio(PIN_CE, PIN_CSN); // Создаём объект radio с указанием выводов CE и CSN

int potValue[1]; // Создаём массив для передачи значений потенциометра

void setup() {
  radio.begin();  // Инициализация модуля NRF24L01
  radio.setChannel(5); // Обмен данными будет вестись на пятом канале (2,405 ГГц)
  radio.setDataRate (RF24_1MBPS); // Скорость обмена данными 1 Мбит/сек
  radio.setPALevel(RF24_PA_HIGH); // Выбираем высокую мощность передатчика (-6dBm)
  radio.openWritingPipe(0x7878787878LL); // Открываем трубу с уникальным ID
}

void loop() {
  potValue[0] = analogRead(PIN_POT); // Считываем показания потенциометра
  radio.write(potValue, 1); // Отправляем считанные показания по радиоканалу
}
