/*===================--- INCLUDE ---=============================*/

#include <Arduino.h>
#include "main.h"


/*===================--- VARIAVEIS ---============================*/

//pinos utilizados
#define pino_BOTAO_2       4
#define pino_SENSOR_1     35
#define pino_BATERIA      32
#define pino_PLACA_SOLAR  33
#define TEMPO_EM_SLEEP    60


unsigned long tempoAnt      =    0;
unsigned long tempoPausa    = 2000;
unsigned long tempoAtual    =    0;


/*================--- Instanciando Objetos ---=====================*/

SensorUmidade sensor1(35);

/*=======================--- SETUP ---=============================*/

void setup() {
  Serial.begin(115200);

  tempoAnt = millis();

  /*------  Definição dos pinos -------*/

  pinoBateria(pino_BATERIA);
  pinoPlacaSolar(pino_PLACA_SOLAR);
  pinoBotao2(pino_BOTAO_2);

  //Imprime no monitor serial o que despertou o ESP
  imprirMotivoDespertou();

  //Define por quanto tempo o esp dormirá (em segundos)
  defineTempoSono(TEMPO_EM_SLEEP);

  //Faz toda a configuração de WiFi e MQTT
  conectWifi();

  //Função que inicia o Arduino OTA
  configArduinoOTA();


  
}//end setup

/*=========================--- LOOP ---===============================*/

void loop() {
  //Conecta ao nosso server MQTT

  ArduinoOTA.handle();

  conectServerMqtt();

  //Verifica o botão 2, 
  //se pressionado por mais de 4 segundos reseta as configurações
  resetarConfiguracoes();

  tempoAtual = millis();

  //Verifica se o ESP está conectado a uma rede ou em modo AP
  if(!isModoAP() && digitalRead(pino_BOTAO_2))
  { 
    //Por algum motivo é necessário esse delay de 2 segundos, 
    //Caso contrário o sensor DHT retorna dados inconsistentes
    if((tempoAtual - tempoAnt) > tempoPausa)
    {

      Serial.println("===== ---Sensores--- ======\n");

      publicaUmidadeAtual(sensor1);

      leituraPinoBateria();

      publicaTensaoBat();
      
      publicaPorcentBat();

      publicaTensaoPlaca();

      publicaTemperaturaAmbiente();

      publicaUmidadeAmbiente();

      tempoAnt = tempoAtual;

      espDormir();
      //lembre-se disso
      //Tudo que estiver abaixo do sleep mode não será rodado
      
    }
  }
  
}//end loop
