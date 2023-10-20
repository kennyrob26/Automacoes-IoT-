/*==============--- INCLUDE ---====================*/

#include <Arduino.h>
#include "main.h"

/*=============--- VARIAVEIS ---===================*/

//Lembre-se de definir qual o DHT utilizado DHT11, DHT12..


unsigned long tempoAnt      =    0;
unsigned long tempoDesejado = 5000;
unsigned long tempoAtual    =    0;

//Variáveis que serão modificadas durante a interrupção
volatile unsigned long tempoInicialBotao  = 0,        //É o momento em que o botão foi pressionado
                       tempoPressionado   = 0;        // quanto tempo o botão ficou pressionado

volatile bool estadoBotao   = true;

/*=========--- Interrupções ISR ---================*/

void IRAM_ATTR mudaStatusBotao()
{
  tempoAtual = xTaskGetTickCount(); //Substitui o millis()
  //Para evitar acionamento acidental
  if((tempoAtual - tempoInicialBotao) > 1000)
  {
    //Quando o botão for de HIGH para LOW 
    //Será armazenado em tempoPressionado quanto tempo o botão ficou pressionado.
    if(!estadoBotao)
      tempoPressionado = tempoAtual - tempoInicialBotao;
    
    //Nunca esquercer de resetar o tempo anterior
    tempoInicialBotao = tempoAtual;
    //Inverte o valor de estado do botão
    estadoBotao = !estadoBotao;
    

  } 
}

//Instânciando os objetos

SensorUmidade sensor1(35);

/*===============--- SETUP ---=====================*/

void setup() {
  Serial.begin(115200);

  pinMode(5, INPUT);


  attachInterrupt(digitalPinToInterrupt(5), mudaStatusBotao, CHANGE);       //Na bordade de subida e descida

  conectWifi();
  //defineServerMqtt("10.0.0.114", 1883);

  //Função que inicia o Arduino OTA
  configArduinoOTA();

  //Define os pinos utilizados
  pinoBateria(32);
  pinoPlacaSolar(33);
  
}//end setup

/*==============--- LOOP ---====================*/

void loop() {
  
  ArduinoOTA.handle();

  //Conecta ao nosso server MQTT
  conectServerMqtt();

  //Verifica se o usuário pressionou o botão 1 por mais de 4 segundos
  //Em caso afirmativo redefine O SSID e SENHA WiFi
  if(tempoPressionado > 4000)
  {
    resetarWifi();
    tempoPressionado = 0;
    Serial.println("O SSID e Senha WiFi foram resetados!!");
    Serial.println("Reiniciando O ESP32");

    //Delay de 3 segundos para dar tempo de ler o monitor serial
    delay(3000);
    ESP.restart();
  }

  
  unsigned long tempo = millis();
  if(tempo - tempoAnt > tempoDesejado)
  {
    tempoAnt = tempo;

  
    Serial.println("===== ---Sensores--- ======\n");

    publicaUmidadeAtual(sensor1);

    leituraPinoBateria();

    publicaTensaoBat();
    
    publicaPorcentBat();

    publicaTensaoPlaca();

    publicaTemperaturaAmbiente();

    publicaUmidadeAmbiente();

  /*
    Serial.printf ("Temperatura Ambiente: %.2f \n", temperaturaAmbiente());
    Serial.printf("Umidade Ambiente: %.2f \n", umidadeAmbiente());

    Serial.println("==========================\n");
  */
  }
  

}//end loop
