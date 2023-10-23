/*=================================================================================

      * A lógica é que quando o usuário segura o botão, será detectada
  uma borda de descida (botão está em pull-up) e então nós começamos a contar

      * Quando o usuário solta o botão é detectada uma borda de subida,
  Dessa forma é só tirarmos a diferença entre quando o usuário pressionou
  e quando ele soltou o botão para saber quanto tempo o botão ficou pressionado

  (instante que soltou botão) - (instante que pressionou botão) = tempo que ficou pressionado

      * E então sabendo quanto tempo o botão ficou pressionado, caso o usuário
  tenha pressionado por mais de 4 segundo as configurações serão restadas (zeradas)
  Se o tempo for menor não fará nada

=======================================================================================*/

#include "configBotao2.h"

//Variáveis que serão modificadas durante a interrupção
volatile unsigned long tempoInicialBotao  = 0;   //É o momento em que o botão foi pressionado
volatile unsigned long tempoPressionado   = 0;   // quanto tempo o botão ficou pressionado

volatile bool estadoBotao   = true;

void pinoBotao2(unsigned short pino)
{
  pinMode(pino, INPUT);
  //Monitora a borda de subida e descida
  attachInterrupt(digitalPinToInterrupt(pino), mudaStatusBotao, CHANGE);
}


void IRAM_ATTR mudaStatusBotao()
{
  unsigned long tempoAtual = xTaskGetTickCount();     //Substitui o millis()

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

void resetarConfiguracoes()
{
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
}