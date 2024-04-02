
#include <SPI.h>  // Подключаем библиотеку для работы с SPI-интерфейсом
#include <nRF24L01.h> // Подключаем файл конфигурации из библиотеки RF24
#include <RF24.h> // Подключаем библиотеку для работа для работы с модулем NRF24L01
#define PIN_LED 3  // Номер пина Arduino, к которому подключен светодиод
#define PIN_CE  9  // Номер пина Arduino, к которому подключен вывод CE радиомодуля
#define PIN_CSN 10 // Номер пина Arduino, к которому подключен вывод CSN радиомодуля
RF24 radio(PIN_CE, PIN_CSN); // Создаём объект radio с указанием выводов CE и CSN

int potValue[1]; // Создаём массив для приёма значений потенциометра

void setup() {
  Serial.begin(9600);

  pinMode(A0, OUTPUT); 
  pinMode(A1, OUTPUT); 
  digitalWrite(A1,0);

  radio.begin();  // Инициализация модуля NRF24L01
  radio.setChannel(5); // Обмен данными будет вестись на пятом канале (2,405 ГГц)
  radio.setDataRate (RF24_250KBPS); // Скорость обмена данными 1 Мбит/сек
  radio.setPALevel(RF24_PA_LOW); // Выбираем высокую мощность передатчика (-6dBm)
  radio.openReadingPipe (1, 0x7878787878LL); // Открываем трубу ID передатчика
  radio.startListening(); // Начинаем прослушивать открываемую трубу
}

void loop() {
  if(radio.available()){ // Если в буфер приёмника поступили данные
    radio.read(&potValue, sizeof(potValue)); // Читаем показания потенциометра
    Serial.println(potValue[0]);
    digitalWrite(A0, potValue[0]>200); // Регулируем яркость диода
  }
}


