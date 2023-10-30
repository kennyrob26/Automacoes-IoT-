/*=======================================================

    Aqui estão todas as configurações MQTT
    A funções de configurações podem ser encontradas aqui
    E TODAS as FUNÇÕES de publicar MQTT

==========================================================*/

#include "configMqtt.h"

//Instancia os objetos
WiFiClient espClient;
PubSubClient client(espClient);

/*====================--- Variáveis ---================== */

//Configurações mqtt
long lastMsg = 0;
char msg[50];
int value = 0;

//Variável de tempo
long ultimaReconexao = 0;

unsigned short botaoPressionou = 0;

/*====================--- FUNÇÕES ---==========================*/

//Recebe o IP do host e a porta MQTT
void defineServerMqtt(const char* ipServidorMqtt, int portaMqtt)
{
    client.setServer(ipServidorMqtt, portaMqtt);
    client.setCallback(callback);

}

//Tenta conectar ao servidor
void conectServerMqtt()
{   
    if(!client.connected())
    {
        reconectar();
 
    }
    client.loop();
    
}

//Recebe as mensagens MQTT
void callback(char* topico, byte* mensagem, unsigned int tamanho)
{
    return;
    //Não recebe nada por enquanto, apenas envia
}

//Mantém a conexão com o servidor MQTT
boolean reconectar()
{
    if(client.connect("Sensor_umidade_solo"))
    {
        client.subscribe("horta/sensor_umidade");
    }
    return client.connected();
}

//Publica a tensão da bateria
void publicaTensaoBat()
{
    char tensao[4];
    sprintf(tensao, "%.2f", tensaoBateria());
    client.publish("sensor_umidade/tensao_bateria", tensao);
    Serial.printf("Tensao da Bateria:\t%sV \n", tensao);
}

//Publica a porcentagem da bateria
void publicaPorcentBat()
{
    char porcentagem[3];
    sprintf(porcentagem, "%d", porcentBateria());
    client.publish("sensor_umidade/porcentagem_bateria", porcentagem);
    Serial.printf("Porcentagem da bateria:\t%s%% \n", porcentagem);
}

//Publica a tensão da placa
void publicaTensaoPlaca()
{
    char tensao[4];
    sprintf(tensao, "%.2f", tensaoPlacaSolar());
    client.publish("sensor_umidade/tensao_placa", tensao);
    Serial.printf("Tensão da Placa:\t%sV \n", tensao);
}

//Publica a Umidade atual do solo
void publicaUmidadeAtual(SensorUmidade sensor)
{
    char umidadeA[4];
    sprintf(umidadeA, "%d", sensor.umidadeAtual());
    client.publish("sensor_umidade/umidade_do_solo", umidadeA);
    Serial.printf("Umidade Atual:\t\t%s%% \n", umidadeA);
}

//Publica a Temperatura atual do ambiente
void publicaTemperaturaAmbiente()
{
    char temperatura[5];
    sprintf(temperatura, "%.2f", temperaturaAmbiente());
    client.publish("sensor_umidade/temperatura_ambiente", temperatura);
    Serial.printf("Temperatura Ambiente: %.2f °C \n", temperatura);
}

//Publica a umidade atual do ambiente
void publicaUmidadeAmbiente()
{
    char umidade[4];
    sprintf(umidade, "%.1f", umidadeAmbiente());
    client.publish("sensor_umidade/umidade_ambiente", umidade);
    Serial.printf("Umidade Ambiente: %.1f%% \n", umidade);
}




