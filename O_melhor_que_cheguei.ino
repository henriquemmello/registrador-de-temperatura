#include <Arduino.h>
#include <MAX6675.h> //SENSOR DE TEMPERATURA
#include <Wire.h>
#include <Keyboard.h> //OBJETO PARA EMULADOR DE TECLADO (ARDUINO LEONARDO OU COMPATIVEL)
#include <RTClib.h>

//PINAGEM DO CIRCUITO
#define pinSO 8   //Pino Digital (SO)
#define pinCS 9   //Pino Digital (CS)
#define pinSCK 10 //Pino Digital (CLK / SCK)

MAX6675 sensorTemp(pinSCK, pinCS, pinSO);
RTC_DS1307 rtc; //OBJETO RELÓGIO

char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};  //VARIAVEIS GLOBAIS

void setup() //EXECUTADO QUANDO O ARDUINO FOR LIGADO
{
  Serial.begin(9600); 
  Wire.begin();
  Keyboard.begin(); //INICIO DO EMULADOR DE TECLADO
  sensorTemp.begin();

   if (! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Keyboard.println("DS1307 não encontrado"); //IMPRIME O TEXTO
        while(1); //SEMPRE ENTRE NO LOOP
  }
  if (! rtc.isrunning()) { //SE RTC NÃO ESTIVER SENDO EXECUTADO
    Keyboard.println("DS1307 rodando!"); //IMPRIME O TEXTO
       //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
  }
  delay(100);
  }

//EXECUTADO REPETIDAMENTE APÓS A EXECUCAO DO SETUP
void loop()
{
  DateTime now = rtc.now();

  Keyboard.print(daysOfTheWeek[now.dayOfTheWeek()]);
  teclaTAB();

  Keyboard.print(now.hour());
  Keyboard.print(':');
  Keyboard.print(now.minute());
  Keyboard.print(':');
  Keyboard.print(now.second());
  teclaTAB();

  Keyboard.print(now.day());
  Keyboard.print('/');
  Keyboard.print(now.month());
  Keyboard.print('/');
  Keyboard.print(now.year());
  teclaTAB();

  Keyboard.print(sensorTemp.getTemperature());
  delay(500);
  teclaEnter();

  delay(2000);
}

//FUNCAO PARA ENVIAR O APERTO DE UM ENTER
void teclaEnter()
{
  Keyboard.press(KEY_RETURN);   // PRESSIONA O ENTER
  delay(50);                   // ESPERA 100 MILISSEGUNDOS
  Keyboard.release(KEY_RETURN); // SOLTA O ENTER
}

//FUNCAO PARA ENVIAR O APERTO DE UM TAB
void teclaTAB()
{
  Keyboard.press(KEY_TAB);   // PRESSIONA O TAB
  delay(50);                // ESPERA 100 MILISSEGUNDOS
  Keyboard.release(KEY_TAB); // SOLTA O TAB
}