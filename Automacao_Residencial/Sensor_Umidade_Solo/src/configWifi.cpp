# include "configWifi.h"
/*
void conectWifi(char* ssid, char* senha)
{
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
*/

//Verifica se existem ceredenciais salvas, 
//caso não tenha, inicia um servidor assincrono para que o usuário as insira


    AsyncWebServer server(80);

    const char* SSID       = "ssid";
    const char* SENHA      = "senha";
    const char* MQTT       = "brokerMQTT";
    const char* PORTA_MQTT = "portaMQTT";

    //variáveis que vão receber o conteúdo do formulário HTML
    String ssid       = "";
    String senha      = "";
    String brokerMQTT = "";
    String portaMQTT  = "";

    //Arquivo onde serão armazenado as configurações
    const char* arquivoSSID      = "/ssid.txt";
    const char* arquivoSENHA     = "/senha.txt";
    const char* arquivoMQTT      = "/brokerMQTT.txt";
    const char* arquivoPortaMQTT = "/portaMQTT.txt";

    //Variáveis de tempo
    unsigned long tempoAnterior = 0,
                  tempoMaximo   = 10000;  //Tempo limite para tentar conectar ao WiFi

void conectWifi()
{
    iniciairSPIFFS();

    ssid       = lerArquivo(SPIFFS, arquivoSSID);
    senha      = lerArquivo(SPIFFS, arquivoSENHA);
    brokerMQTT = lerArquivo(SPIFFS, arquivoMQTT);
    portaMQTT  = lerArquivo(SPIFFS, arquivoPortaMQTT);

    Serial.println(ssid);
    Serial.println(senha);
    Serial.println(brokerMQTT);
    Serial.println(portaMQTT);

    //A função iniciarWiFi retorna true caso consiga se conectar
    if(!iniciarWiFi())
    {
        Serial.println("Definindo um ponto de acesso");
        //SSID e senha do ponto de acesso, nesse caso não terá senha (NULL)
        WiFi.softAP("ESP_CONFIGURAR_WIFI", NULL);

        IPAddress IP = WiFi.softAPIP();
        Serial.print("IP do ponto de acesso: ");
        Serial.println(IP);

        //Iniciando o servidor Web
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
        });

        server.serveStatic("/", SPIFFS, "/");

        server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
        //quantidade de parametros recebidos (inputs preenchidos)
        int parametros = request->params();
        for(int i=0; i < parametros; i++)
        {
            AsyncWebParameter* p = request->getParam(i);
            if(p->isPost())
            {
            //O valor de SSID preenchido
            if(p->name() == SSID)
            {
                ssid = p->value().c_str();
                Serial.print("O SSID recebido é: ");
                Serial.println(ssid);

                //Escreve no arquivo ssid.txt
                escreverArquivo(SPIFFS, arquivoSSID, ssid.c_str());

            }//end if ssid
            if(p->name() == SENHA)
            {
                senha = p->value().c_str();
                Serial.print("A senha recebida é: ");
                Serial.println(senha);

                //Escreve no arquivo senha.txt
                escreverArquivo(SPIFFS, arquivoSENHA, senha.c_str());
            }
            if(p->name() == MQTT)
            {
                brokerMQTT = p->value().c_str();
                Serial.print("O endereço do broker recebido é: ");
                Serial.println(brokerMQTT);
                
                if(brokerMQTT != "")
                    //Escreve no arquivo brokerMQTT.txt
                    escreverArquivo(SPIFFS, arquivoMQTT, brokerMQTT.c_str());
            }
            if(p->name() == PORTA_MQTT)
            {
                portaMQTT = p->value().c_str();
                Serial.print("A porta MQTT recebida foi: ");
                Serial.println(portaMQTT);

                if(portaMQTT != "")
                    //Escreve no arquivo portaMQTT.txt
                    escreverArquivo(SPIFFS, arquivoPortaMQTT, portaMQTT.c_str());
            }

            }//end if is post
        }//end for
        request->send(200, "text/plain", "O ESP será reiniado e tentará se conectar a rede ");
        delay(3000);
        ESP.restart();
        });//end server.on

        server.begin();
    
    }//end IF mais externo
}

//Função que de fato irá tentar se conectar ao WiFi
bool iniciarWiFi()
{
    //Verifica se existe um SSID, caso não já retona false

    if(ssid=="" || brokerMQTT=="")
    {
        Serial.println("O SSID ou Broker não foi definido");
        return false;
    }

    //Tenta conectar a rede salva na SPIFFS
    Serial.print("Tentado conectar a rede: ");
    Serial.println(ssid);

    WiFi.begin(ssid.c_str(), senha.c_str());

    //Define qual o IP/url do broker e qual a porta será utilizada
    defineServerMqtt(brokerMQTT.c_str(), portaMQTT.toInt());
    

    unsigned long tempoAtual = millis();
    tempoAnterior = tempoAtual;

    while (WiFi.status() != WL_CONNECTED){
        tempoAtual = millis();
        if((tempoAtual - tempoAnterior) >= tempoMaximo)
        {
        Serial.println("Não foi poossível conectar a rede");
        return false;
        }
    }
    Serial.println("Conectado a rede:" + ssid);
    return true;
}

void resetarWifi()
{
    escreverArquivo(SPIFFS, arquivoSSID, "");
    escreverArquivo(SPIFFS, arquivoSENHA, "");
}