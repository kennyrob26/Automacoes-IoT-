/*=====================================================

        *Contém 2 funções muito simples
        *uma das funções retorna a umidade 
            e a outra a temperatura do ambuiente

======================================================*/

#include "statusSensorDHT.h"

/*=======================--- Variáveis ---=====================*/

//São salvos na memória RTC pois é necessário utilizar após o ESP acordar
RTC_DATA_ATTR float temperatura = 0.0;
RTC_DATA_ATTR float umidadeAmb = 0.0;

/*=================--- Instanciando Objeto ---=================*/

DHT dht(DHTPino, DHTTYPE);

/*=======================--- Funções ---=====================*/

//Retorna a temperatura do ambiente
float temperaturaAmbiente()
{   
    float bufferTemperatura = dht.readTemperature();

    //Valida se o valor recebido está dentro da faixa de operação do sensor
    if(bufferTemperatura >= 0 && bufferTemperatura <= 50 )
        temperatura = bufferTemperatura;

    //Se o valor não for válido retorna o ultimo valor lido
    return temperatura;
}

//Retorna a leitura do ambiente
float umidadeAmbiente()
{   
    
    float bufferUmidade = dht.readHumidity();

    //Valida se o valor da umidade é válido (entre 0 e 100)
    if(bufferUmidade >=0  && bufferUmidade <= 100)
        umidadeAmb = bufferUmidade;

    //Se o valor não for válido retorna a ultima medição válida
    return umidadeAmb;
}

