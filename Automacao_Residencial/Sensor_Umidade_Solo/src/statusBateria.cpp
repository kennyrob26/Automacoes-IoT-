#include "statusBateria.h"

/*No caso dos valores setados, a bateria está ligada a um divisor de tensão, onde:

    [GND] ---- {R1 22K} -- [GPIO] ---- {R2 14.7K} ---- [VCC BATERIA]

    onde:

    GPIO é o pino que monitora a bateria
    R1 e R2 são os resistores do divisor de tensão.
    GND é o GND do ESP e da placa solar
    VCC da bateria é o + da bateria.

*/

//Devem ser definidas de acordo com a bateria utilizada
//tMinima é a tensão minima da bateria em   0% (no geral 2.7V ~ 3.0V)
//tMaxima é a tensão maxima da bateria em 100% (no geral 3.8V ~ 4.2V)

/*=======================--- Variáveis ---=====================*/

float  tMinima    = 3.0,                 //0%   - 3.0V
       tMaxima    = 4.2,                 //100% - 4.20V
       tensaoBat  = 0.0;                 //Armazena a tensão da bateria

unsigned short int pinBat      = 0,      //Pino que faz a leitura da tensão da bateria 
                   porcentBat  = 0;      //Armazena a porcentagem da bateria

unsigned long int leituraPin   = 0;      //Vai armazenar a soma de 500 amostras


/*=======================--- Funções ---=====================*/

void pinoBateria(int pinoBateria)
{
    pinMode(pinoBateria, INPUT);
    pinBat = pinoBateria;
}

void leituraPinoBateria(){
    //Vamos trabalhar com amostras 500 amostras por leitura, para garantir maior consistência dos dados
    const int quantAmostras = 500;
    //Soma as amostras na variável leituraPin
    for(int i=0; i<quantAmostras; i++)
    {
        leituraPin += analogRead(pinBat);
    }
    //Divide a soma das amostras pela quantidade de amostras
    leituraPin = leituraPin/quantAmostras;
    

    leituraPin = map(leituraPin, 2110, 2751, 3230, 4120);
    
    //Armazena a tensão da bateria
    tensaoBat   = (float) leituraPin / 1000.0;
    
    //Armazena a porcentagem da bateria
    porcentBat = (int) map(leituraPin, (tMinima * 1000), (tMaxima * 1000), 0, 100);

}

//Retorna a ultima tensão armazenada em tensaoBateria
float tensaoBateria()
{
    //tensaoBat = analogRead(pinBat);
    return tensaoBat;
}

//Retorna a ultima porcentagem armazenada em porcentBat
int porcentBateria()
{
    if(tensaoBateria() <= tMinima)
    {
        porcentBat = 0;
    }
    else if (tensaoBateria() >= tMaxima )
    {
        porcentBat = 100;
    }

    //Está implicito que se nenhuma das condições for verdadedeira a porcentagem não muda
    //Ou seja, será retornada a porcentagem setada em leituraPinoBateria (valor entre 1 e 99)

    return porcentBat;
}