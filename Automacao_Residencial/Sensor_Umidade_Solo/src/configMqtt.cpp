#include "configMqtt.h"

    WiFiClient espClient;
    PubSubClient client(espClient);
    long lastMsg = 0;
    char msg[50];
    int value = 0;

    //Variável de tempo
    long ultimaReconexao = 0;
    
    unsigned short botaoPressionou = 0;

void defineServerMqtt(const char* ipServidorMqtt, int portaMqtt)
{
    client.setServer(ipServidorMqtt, portaMqtt);
    client.setCallback(callback);

}
void conectServerMqtt()
{   

    if(!client.connected())
    {
        long tempo = millis();
        if(tempo - ultimaReconexao > 5000)
        {
            ultimaReconexao = tempo;
            if(reconectar())
            {
                ultimaReconexao = 0;
            } //end if reconectar
        }// end if tempo
    }//end if externo
    else
    {
        client.loop();
    }
    
}
void callback(char* topico, byte* mensagem, unsigned int tamanho)
{
    return;
    //Não recebe nada por enquanto, apenas envia
}
boolean reconectar()
{
    if(client.connect("Sensor_umidade_solo"))
    {
        client.subscribe("horta/sensor_umidade");
    }
    return client.connected();
}

void publicaTensaoBat()
{
    char tensao[4];
    sprintf(tensao, "%.2f", tensaoBateria());
    client.publish("sensor_umidade/tensao_bateria", tensao);
    Serial.printf("Tensao da Bateria:\t%sV \n", tensao);
}

void publicaPorcentBat()
{
    char porcentagem[3];
    sprintf(porcentagem, "%d", porcentBateria());
    client.publish("sensor_umidade/porcentagem_bateria", porcentagem);
    Serial.printf("Porcentagem da bateria:\t%s%% \n", porcentagem);
}

void publicaTensaoPlaca()
{
    char tensao[4];
    sprintf(tensao, "%.2f", tensaoPlacaSolar());
    client.publish("sensor_umidade/tensao_placa", tensao);
    Serial.printf("Tensão da Placa:\t%sV \n", tensao);
}

void publicaUmidadeAtual(SensorUmidade sensor)
{
    char umidadeA[4];
    sprintf(umidadeA, "%d", sensor.umidadeAtual());
    client.publish("sensor_umidade/umidade_do_solo", umidadeA);
    Serial.printf("Umidade Atual:\t\t%s%% \n", umidadeA);
}

void publicaTemperaturaAmbiente()
{
    char temperatura[5];
    sprintf(temperatura, "%.2f", temperaturaAmbiente());
    client.publish("sensor_umidade/temperatura_ambiente", temperatura);
    Serial.printf("Temperatura Ambiente: %.2f °C \n", temperatura);
}
void publicaUmidadeAmbiente()
{
    char umidade[4];
    sprintf(umidade, "%.1f", umidadeAmbiente());
    client.publish("sensor_umidade/umidade_ambiente", umidade);
    Serial.printf("Umidade Ambiente: %.1f%% \n", umidade);
}

/*Apenas alguns testes, no momento não estão sendo mais utilizados
    mas preferi deixa-los no código caso encontre a necessidade de
    algum teste pontual    
*/

void botao1()
{
    if(botaoPressionou == 0)
    {
        botaoPressionou = 1;
    }
    else
    {
        botaoPressionou = 0;
    }

    char estadoBotao[4];
    sprintf(estadoBotao, "%d", botaoPressionou);

    client.publish("sensor_umidade/botao1", estadoBotao);
}

void botao2()
{

}
void teste()
{
    char payload[] = "ON";
    char payload2[] = "2";
    client.publish("horta/sensor_umidade", payload);
    client.publish("horta/sensor_umidade2", payload2);
}


