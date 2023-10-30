/*===================--- INCLUDE ---=============================*/

#include <Arduino.h>
#include "main.h"

/*=====================--- PINOS ---==============================*/

#define pino_BOTAO_2       4
#define pino_SENSOR_1     35
#define pino_BATERIA      32
#define pino_PLACA_SOLAR  33


/*===================--- VARIAVEIS ---============================*/
//Quanto tempo o esp dorme (segundos)
#define TEMPO_EM_SLEEP    60

unsigned long tempoAnt      =    0;
unsigned long tempoAtual    =    0;

//Tempo que o esp fica acordado
unsigned long tempoPausa    = 2000;

/*================--- Instanciando Objetos ---=====================*/

//Recebe o pino do sensor
SensorUmidade sensor1(35);

/*=======================--- SETUP ---=============================*/

void setup() {

  Serial.begin(115200);

  //Começa a contar tempo acordado
  tempoAnt = millis();


  /*======--  Definição dos pinos --=====*/

  pinoBateria(pino_BATERIA);
  pinoPlacaSolar(pino_PLACA_SOLAR);
  pinoBotao2(pino_BOTAO_2);

  /*======--======================--======*/


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

  //Função padrão do OTA
  ArduinoOTA.handle();

  //Conecta ao nosso server MQTT
  conectServerMqtt();

  //Verifica o botão 2, 
  //se pressionado por mais de 4 segundos reseta as configurações
  resetarConfiguracoes();

  tempoAtual = millis();

  //Verifica se o ESP está em modo AP
  //Verifica se o botão 2 está pressionado
  //Em ambos os casos o ESP não pode dormir
  if(!isModoAP() && digitalRead(pino_BOTAO_2))
  { 
    //É necessário esse delay de 2 segundos, 
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

      //IMPORTANTE
      //Tudo que estiver abaixo do sleep mode não será executado
      
    }
  }
  
}//end loop
