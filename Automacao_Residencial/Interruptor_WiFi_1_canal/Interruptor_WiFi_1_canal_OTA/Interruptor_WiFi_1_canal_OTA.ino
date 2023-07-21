/*
  Este é um código que envolve diversas tecnologias, e tem como foco
  controlar lampadas/cargas utlizando o esp01 e a plataforma node-Red
  Como no estado atual do projeto ele está instalado em uma lampada, 
  preferi utilizar também o ArduinoOTA para manter o projeto atualizado
  sem a necessidade de retirar o projeto a cada atualização.
*/



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <Arduino.h>


//nome e senha da rede utilizada pelo ESP32
const char* ssid = "SSID DA REDE";  //nome da sua rede WiFI
const char* senha = "SENHA";        //sua senha WiFI

//Aqui colocamos o IP do nosso Broker
//No linux pode ser obtido com o comando "hostname -I"
const char* mqtt_server = "10.0.0.146";

//Código padrão para pubsub
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Definição das GPIO
const int interruptor = 3;  //O pino 3 é o RX, que é mais estável que o GPIO 2
const int lampada = 0;


//Como vamos trabalhar com tempo utilizando o millis(), 
//precisamos dessas duas variáveis:
long tempoAnterior = 0;
long ultimaReconexao = 0;

//Váriaveis que guardam estado (on/off)
int pressionado = 1;
bool lampadaEstado = 1;



//==================== SETUP ====================================

void setup() {
  Serial.begin(115200, SERIAL_8N1);
  pinMode(lampada, OUTPUT);
  pinMode(interruptor, INPUT);


  //É uma função que configura/conecta ao wifi, criada logo abaixo
  setup_wifi();

  //Função do Arduino OTA
  arduinoOta();
  //Ou seja, é o IP do broker e a porta utilizada
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ultimaReconexao = 0;
}

//===================== LOOP =====================================

void loop() {
  if(!client.connected()){
    long tempo = millis();
    if(tempo - ultimaReconexao > 5000){
      ultimaReconexao = tempo;
      if(reconnect()){
        ultimaReconexao = 0;
      }
    }
  }else{
    client.loop();
  }

  ArduinoOTA.handle();
  checaInterruptor();
  digitalWrite(lampada, lampadaEstado);
}



//=================== FUNCOES ==============================



//------------------   SETUP WIFI ----------------------
//Código padrão para conexão wifi

void setup_wifi(){
  delay(10);
  Serial.print("Tentado conectar a rede: ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado ao WiFi");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

}

//------------------- ARDUINO OTA --------------------------
//código recomentado pela biblioteca

void arduinoOta(){
   ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//---------------- CALLBACK() --------------------------------------

//Essa função é muito IMPORTANTE
//Ela trata de todos os callback

void callback(char* topic, byte* message, unsigned int length){
  Serial.print("Uma nova mensagem do tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");

  //É quem armazena o conteúdo da mensagem, algo como um buffer
  String messageTemp;

  //apenas coloca a informação de message dentro de messageTemp
  for (int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);

  //lê a mensagem, se "onOff" muda o estado da lampada

  if(String(topic) == "quarto/lampada"){
    

    if(messageTemp == "onOff"){
      lampadaEstado = !lampadaEstado;
      estadoLampada();
    }
  }
}

//-------------- RECONNECT() --------------------------

//Função responsável por conetar ao MQTT
//é Aqui quem definimos as subscrições

boolean reconnect(){
  if(client.connect("Lampada_Quarto")){
    client.subscribe("quarto/lampada");
  }
  return client.connected();


}

//---------------- CHECABOTAO() ---------------

//É a função que verfica periodicamente alterações no Interruptor

void checaInterruptor(){

  long tempo = millis();

  //Basicamente mudamos o estado da lampada (on /off)
  //Perceba que existe um "delay" de 300 milis para evitar duplos cliques acidentais

  if((pressionado != digitalRead(interruptor)) && (tempo - tempoAnterior > 300)){
    pressionado = digitalRead(interruptor);
    tempoAnterior = tempo;
    lampadaEstado = !lampadaEstado;
    estadoLampada();
  }
}

//---------------------- ESTADOLAMPADA() -------------------------------------------

//função resposável por manter o estado da lampada atualizado no node-Red
void estadoLampada(){
  char payload[3];
  if(!lampadaEstado){
    char on[] = "on_";
    strcpy(payload, on);
  }else{
    char off[] = "off";
    strcpy(payload, off);
  }
  client.publish("quarto/interruptor", payload);
}

































