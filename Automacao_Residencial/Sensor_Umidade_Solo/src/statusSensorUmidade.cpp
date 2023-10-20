#include "statusSensorUmidade.h"

unsigned short int umidade    = 0,
                   pinoSensor = 0;

//Define o pino que será utilizado para a leitura do sensor
void pinoSensorUmidade(const short int pino)
{
    pinMode(pino, INPUT);
    pinoSensor = pino;
}

//retorna a umidade atual
unsigned short int umidadeAtual()
{
    const int numAmostras = 500;   
    unsigned int leituraPino = 0;

    for(int i = 0; i < numAmostras; i++)
    {
        leituraPino += analogRead(pinoSensor);
    }

    //Faz a media das amostras
    leituraPino = (int)leituraPino/numAmostras;
    Serial.print(leituraPino);

    int valorMin = 1000,
        valorMax = 2600;
    //Converte para porcentagem
    if(leituraPino > valorMax)
    {
        umidade = 0;
    }
    else if(leituraPino > valorMin)
    {
        umidade = map(leituraPino, 1000, 2600, 100, 0);
    }
    else
    {
        umidade = 100;
    }
    return umidade;
}