#ifndef _SENSOR_DHT_
    #define _SENSOR_DHT11_
    #include "Arduino.h"
    #include "DHT.h"
    

    #define DHTTYPE DHT11
    #define DHTPino 19

        
    float temperaturaAmbiente();    //retorna qual a temperatura ambiente
    float umidadeAmbiente();        //retorna qual a umidade do ambiente

#endif