#include "statusSensorDHT.h"

float temperatura = 0.0;
float umidadeAmb = 0.0;

DHT dht(DHTPino, DHTTYPE);

float temperaturaAmbiente()
{   
    float bufferTemperatura = dht.readTemperature();

    //Valida se o valor recebido está dentro da faixa de operação do sensor
    if(bufferTemperatura >= 0 && bufferTemperatura <= 50 )
        temperatura = bufferTemperatura;

    //Se o valor não for válido retorna o ultimo valor lido
    return temperatura;
}

float umidadeAmbiente()
{   
    
    float bufferUmidade = dht.readHumidity();

    //Valida se o valor da umidade é válido (entre 0 e 100)
    if(bufferUmidade >=0  && bufferUmidade <= 100)
        umidadeAmb = bufferUmidade;

    //Se o valor não for válido retorna a ultima medição válida
    return umidadeAmb;
}

