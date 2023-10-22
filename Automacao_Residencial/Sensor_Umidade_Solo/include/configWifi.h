#ifndef _CONFIG_WIFI_
    #define _CONFIG_WIFI_

    #include <Arduino.h>
    #include <WiFi.h>
    #include "manipulacaoDeArquivos.h"
    #include "AsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #include "configMqtt.h"

    bool iniciarWiFi();

    void conectWifi();
    void resetarWifi();
    bool isModoAP();


#endif