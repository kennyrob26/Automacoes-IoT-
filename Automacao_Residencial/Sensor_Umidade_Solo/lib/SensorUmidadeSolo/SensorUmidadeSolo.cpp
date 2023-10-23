#include "SensorUmidadeSolo.h"

//Construtor padrão
//Aceita 4 parâmetros
//valor minimo e máximo estã relacionados a leitura analógia
//Os valores pré setado geraram bons resultados, mas podem ser modificados

SensorUmidade::SensorUmidade(int pinoSensor, int valorMinimo, int valorMaximo, int numAmostras)
{
    this->pinoSensor  = pinoSensor;
    this->valorMin    = valorMinimo;
    this->valorMax    = valorMaximo;
    this->numAmostras = numAmostras;

    pinMode(pinoSensor, INPUT);
}

//Utiliza valores pré setados (sobrecarga do construtor padrão) , 
//exigindo apenas a definição do pino

SensorUmidade::SensorUmidade(int pinoSensor) : SensorUmidade(pinoSensor, 1000, 2600, 500)
{
    //Construtor auxiliar que chama o contrutor principal
    //é util apenas se o usuário desejar definir apenas o pino do sensor
}

// Faz a leitura de várias amostras e tira a média aritmética
// A função retorna o resultado dessa média de amostras

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