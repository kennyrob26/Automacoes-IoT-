/*==============================================================

        *Aqui estão presentes todas as configurações de sono profundo do es,
    desde a informação do que despertou o ESP, até definição do tempo e a 
    função que de fato coloca o esp para 'dormir'

================================================================*/

#include "Arduino.h"
#include "configDeepSleep.h"

#define SEGUNDO_PARA_MICROSSEGUNDOS 1000000

unsigned long segundos = 0;

void imprirMotivoDespertou()
{
    esp_sleep_wakeup_cause_t motivo_despertou;
    motivo_despertou = esp_sleep_get_wakeup_cause();

    switch (motivo_despertou)
    {
        case ESP_SLEEP_WAKEUP_EXT0 :
            Serial.println("Despertado pelo botão");
            break;

        case ESP_SLEEP_WAKEUP_TIMER:
            Serial.println("Despertado por conta do tempo");
            break;

        default:
            Serial.printf("Não foi despertado pelo sono profundo: %d\n", motivo_despertou);
            break;
    } 

}
//recebe tempo em segundos
void defineTempoSono(unsigned long tempo)
{   
    segundos = tempo;
    //Configura o tempo
    esp_sleep_enable_timer_wakeup(tempo * SEGUNDO_PARA_MICROSSEGUNDOS);

    //Configura o GPIO 4 (botao)
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0);

}

void espDormir()
{
    Serial.printf("O ESP irá dormir por: %ds\n", segundos );

    Serial.println("Indo dormir");
    delay(1000);
    Serial.flush();

    //Coloca o ESP em sono profundo
    esp_deep_sleep_start();
}