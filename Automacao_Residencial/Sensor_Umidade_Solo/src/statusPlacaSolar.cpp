/*No caso dos valores setados, a placa está ligada a um divisor de tensão, onde:

    [GND] ---- {R1 10K} -- [GPIO] ---- {R2 14.7K} ---- [VCC Placa solar]

    onde:

    GPIO é o pino que monitora a placa solar
    R1 e R2 são os resistores do divisor de tensão.
    GND é o GND do ESP e da placa solar
    VCC da placa solar é o + da placa solar.

*/

#include "statusPlacaSolar.h"

/*=======================--- Variáveis ---=====================*/

float         tensaoPlaca = 0.0;
unsigned int  pinoPlaca   = 0  ;


/*=======================--- Funções ---=====================*/

//Define o pino utilizado
void pinoPlacaSolar(int pinoPlacaSolar)
{
    pinMode(pinoPlacaSolar, INPUT);
    pinoPlaca = pinoPlacaSolar;
}

//Retorna a tensão da placa solar
float tensaoPlacaSolar()
{
    //Vamos trabalhar com amostras 500 amostras por leitura, para garantir maior consistência dos dados
    const int quantAmostras = 500;
    unsigned long leituraPino = 0;
    //Soma as amostras na variável leituraPin
    for(int i=0; i<quantAmostras; i++)
    {
        leituraPino += analogRead(pinoPlaca);
    }
    //Divide a soma das amostras pela quantidade de amostras
    leituraPino = leituraPino/quantAmostras;
    //tensaoPlaca = leituraPino;
    
    leituraPino = map(leituraPino, 783, 2958, 1850, 6090);
    tensaoPlaca = (float) leituraPino / 1000.00;
    
    
    return tensaoPlaca;
}