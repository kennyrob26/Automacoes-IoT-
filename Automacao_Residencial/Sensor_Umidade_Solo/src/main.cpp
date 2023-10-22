/*==============--- INCLUDE ---====================*/

#include <Arduino.h>
#include "main.h"


/*=============--- VARIAVEIS ---===================*/

//pinos utilizados
#define pino_BOTAO_2       4
#define pino_SENSOR_1     35
#define pino_BATERIA      32
#define pino_PLACA_SOLAR  33


unsigned long tempoAnt      =    0;
unsigned long tempoDesejado = 5000;
unsigned long tempoAtual    =    0;

//Variáveis que serão modificadas durante a interrupção
volatile unsigned long tempoInicialBotao  = 0,   //É o momento em que o botão foi pressionado
                       tempoPressionado   = 0;   // quanto tempo o botão ficou pressionado

volatile bool estadoBotao   = true;

/*=========--- Interrupções ISR ---================*/

void IRAM_ATTR mudaStatusBotao()
{
  tempoAtual = xTaskGetTickCount();     //Substitui o millis()

  //Para evitar acionamento acidental 
  if((tempoAtual - tempoInicialBotao) > 1000)
  {
    //Quando o botão for de HIGH para LOW (o usuário parar de pressionar)
    //Será armazenado em "tempoPressionado" quanto tempo o botão ficou pressionado.
    if(estadoBotao)
      tempoPressionado = tempoAtual - tempoInicialBotao;
    
    //Nunca esquercer de resetar o tempo inicial
    tempoInicialBotao = tempoAtual;
    //Inverte o valor de estado do botão
    estadoBotao = !estadoBotao;
    

  } 
}


/*===========--- Instanciando Objetos ---=========*/

SensorUmidade sensor1(35);

/*===============--- SETUP ---=====================*/

void setup() {
  Serial.begin(115200);

  //Define os pinos utilizados
  pinoBateria(pino_BATERIA);
  pinoPlacaSolar(pino_PLACA_SOLAR);
  pinMode(pino_BOTAO_2, INPUT);

  //Monitora a borda de subida e descida
  attachInterrupt(digitalPinToInterrupt(pino_BOTAO_2), mudaStatusBotao, CHANGE);       

  //Imprime no monitor serial o que despertou o ESP
  imprirMotivoDespertou();

  //Define por quanto tempo o esp dormirá em segundos
  defineTempoSono(5);

  //Faz toda a configuração de WiFi e MQTT
  conectWifi();

  //Função que inicia o Arduino OTA
  configArduinoOTA();


  
}//end setup

/*==============--- LOOP ---====================*/

void loop() {
  
  ArduinoOTA.handle();

  //Conecta ao nosso server MQTT
  conectServerMqtt();

  //Verifica se o usuário pressionou o botão 2 por mais de 4 segundos
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

  //Verifica se o ESP está conectado a uma rede ou em modo AP
  if(!isModoAP() && digitalRead(pino_BOTAO_2))
  {
    Serial.println("===== ---Sensores--- ======\n");

    publicaUmidadeAtual(sensor1);

    leituraPinoBateria();

    publicaTensaoBat();
    
    publicaPorcentBat();

    publicaTensaoPlaca();

    publicaTemperaturaAmbiente();

    publicaUmidadeAmbiente();

    Serial.println(estadoBotao);

    espDormir();
  }
  

  /*
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

  }*/
  

}//end loop
