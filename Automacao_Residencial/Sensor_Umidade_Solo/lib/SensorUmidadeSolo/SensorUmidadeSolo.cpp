#include "SensorUmidadeSolo.h"

SensorUmidade::SensorUmidade(int pinoSensor, int valorMinimo, int valorMaximo, int numAmostras)
{
    this->pinoSensor  = pinoSensor;
    this->valorMin    = valorMinimo;
    this->valorMax    = valorMaximo;
    this->numAmostras = numAmostras;

    pinMode(pinoSensor, INPUT);
}

SensorUmidade::SensorUmidade(int pinoSensor) : SensorUmidade(pinoSensor, 1000, 2600, 500)
{
    //Construtor auxiliar que chama o contrutor principal
    //é util apenas se o usuário desejar definir apenas o pino do sensor
}

unsigned short int SensorUmidade::umidadeAtual()
{ 
    unsigned int leituraPino = 0;

    for(int i = 0; i < numAmostras; i++)
    {
        leituraPino += analogRead(pinoSensor);
    }

    //Faz a media das amostras
    leituraPino = (int)leituraPino/numAmostras;
    //Serial.print(leituraPino);

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