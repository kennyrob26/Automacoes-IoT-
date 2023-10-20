#ifndef _SENSOR_UMIDADE_INCLUDED_
    #define _SENSOR_UMIDADE_INCLUDED_

    #include <Arduino.h>

    class SensorUmidade
    {
        public:
            SensorUmidade(int pinoSensor, int valorMinimo, int ValorMaximo, int quantAmostras);
            SensorUmidade(int pinoSensor);
            unsigned short int umidadeAtual();
        
        private:
            unsigned short int umidade     = 0,
                               numAmostras = 0,
                               pinoSensor  = 0,
                               valorMin    = 0,
                               valorMax    = 0;
    };

#endif