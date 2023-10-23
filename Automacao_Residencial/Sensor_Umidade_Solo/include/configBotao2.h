#ifndef _CONFIG_BOTAO1_
    #define _CONFIG_BOTAO1_

    #include "Arduino.h"
    #include "configWifi.h"


    void pinoBotao2(unsigned short pino);
    void IRAM_ATTR mudaStatusBotao();
    void resetarConfiguracoes();

#endif