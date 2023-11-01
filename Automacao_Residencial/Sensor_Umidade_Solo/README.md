# Sensor de Irrigação
## :mag_right: Conhecendo o Projeto
Este projeto consiste em um simples sensor de Irrigação utilizando o microcontrolador ESP32. A placa desenvolvida permite a conexão de até 4 sensores capacitivos do solo, uma bateria 18650 é responsável por alimentar toda a placa, e uma placa solar de 5V/1w mantém a bateria carregada.  
Toda a comunicação do projeto é realizada utilizando o protocolo MQTT, a placa envia os dados coletados de tempo em tempo dependendo da necessiade do usuário. Atualmente a placa **coleta e envia os seguintes dados:**  

* **Umidade do Solo:** obtida utilizando sensores capacitivo de umidade do solo
* **Umidade do Ambeiente:** foi utilizado um sensor DHT11
* **Temperatura do Ambiente:** também coletada pelo DHT11
* **Tensão da Bateria:** Mensurada atrávés de um divisor resistivo
* **Porcentagem da Bateria** é baseada na tensão da bateria
* **Tensão da Placa Solar** também utiliza um divisor resistivo

## :wrench: Status de Desenvolvimento

- Status do Projeto: Em desenvolvimento :warning:
- Versão de lançamento: <img src = "https://img.shields.io/static/v1?label=vers%C3%A3o_lan%C3%A7amento&message=v0.1&color=blue&style=for-the-plastic"/>
- Versão atual: <img src="https://img.shields.io/static/v1?label=vers%C3%A3o&message=v0.1&color=blue&style=for-the-plastic"/>

### Oque é esperado, e oque já foi desenvolvido:
- [X] Desenvolver um hardware que suporte o projeto
- [X] A solução é capaz de coletar a umidade do solo
- [X] A solução é capaz de coletar a temperatura e umidade do ambiente
- [X] A solução é capaz de monitorar o status da bateria e placa solar
- [ ] A solução é capaz de se manter sem a necessidade de utilizar a alimetação da rede elétrica, de tal forma que o conjunto bateria + placa solar seja suficiente.
- [ ] A solução pode ser 100% configurada por uma interface web amigável.
- [X] As configurações de rede WiFi podem ser executadas utilizando uma interface web.
- [X] Configurar o Host do broker MQTT e sua porta através da interface Web.
- [ ] É possível configurar as credenciais do broker MQTT através da interface web.
- [ ] É possível definir todos os tópicos MQTT através da interface web.
- [ ] A placa não necessita de interferência alguma para ser atualizada para uma nova versão, esta busca por atualizações automáticamente.
- [ ] Desenvolver uma versão utilizando rádio LoRa, visando o longo alcance
