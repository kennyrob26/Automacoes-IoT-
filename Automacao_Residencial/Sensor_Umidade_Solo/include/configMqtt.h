#ifndef _CONFIG_MQTT_
    #define _CONFIG_MQTT_

    #include <Arduino.h>
    #include <PubSubClient.h>
    #include "configWifi.h"
    #include "statusBateria.h"
    #include "statusPlacaSolar.h"
    #include "statusSensorUmidade.h"
    #include "SensorUmidadeSolo.h"
    #include "statusSensorDHT.h"


    void    defineServerMqtt(const char* ipServidorMqtt, int portaMqtt);
    void    conectServerMqtt();
    void    callback(char* topico, byte* mensagem, unsigned int tamanho); 
    boolean reconectar();
    void    teste();
    void    publicaTensaoBat();
    void    publicaPorcentBat();
    void    publicaTensaoPlaca();
    void    publicaUmidadeAtual(SensorUmidade sensor);
    void    publicaTemperaturaAmbiente();
    void    publicaUmidadeAmbiente();
    void    botao1();
    void    botao2();

#endif