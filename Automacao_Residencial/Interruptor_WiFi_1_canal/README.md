# Interruptor WiFI de 1 Canal
## Uma breve descrição do projeto
    Um simples interruptor WiFI utilizando o microcontrolador ESP01, a placa desenvolvida para esse projeto é capaz de ler o 
estado de um botão e mudar o estado de uma lâmpada/carga, como estado queremos dizer ligado ou desligado.
    O projeto está sendo utilizado a pouco mais de 1 mês em meu quarto de estudos, onde ele é responsável pelo controle da
lâmpada do ambiente e até então estou contente com o resultado alcançado.  


## Ferramentas utilizadas no projeto
    Pensando em automações futuras, optei em utilizar a plataforma node-Red para a centralização de futuros sensores e atuadores. Sendo assim, o node-Red fica responsável por gerar uma pequena página Web utilizando os nós de dashboards, na página existe um switch que muda de estado quando a lampada tem seu estado alterado, e se alterarmos o estado do switch a lampada também mudará de estado.  
    Para a programação no ESP01 preferi utilizar o arduino IDE, por conta da quantidade imensa de bibliotecas disponíveis. O controle da lâmpada e monitoramento do interruptor é feito pelo próprio microcontrolador, o principal motivo para isso é que se toda a parte de controle fosse jogada para o node-Red em uma eventual falha no mesmo (queda da conexão ou algo do tipo) a lâmpada deixaria de funcionar.  
    O código presente no ESP também é independente da conexão MQTT, mas infelizmente quando ele não consegue se conectar ao servidor existe um pequeno delay de 3 a 4 segundo para o acionamento da Lâmpada, ao contrário de quando existe a conexão, onde neste cenário a lampada acende instantâneamente ao mudar o estado do botão.  

## O Hardware do Projeto
    Um dos maiores desafios do projeto foi conseguir chegar em uma PCI (placa de circuito impresso) que atenderia os requisitos, e também pequena o suficiente para servir em uma caixa de luz 4x2. Então a versão atual do projeto se baseia no esquema elétrico a baixo:  

***COLOCAR IMAGEM DO ESQUEMA ELÉTRICO***

### Visão geral dos componentes utilizados:

1. **Alimentação (fonte):** Basicamente nós temos uma **fonte Hi-link de 3.3V** que é mais do que o suficiente para a alimentação do projeto.
2. **Microcontrolador:** Como já dito anteriormente o **ESP01** foi o microcontrolador escolhido e ele é quem monitora e controla tudo na placa. 
3. **Transistor PNP:**O **BC558** é um transistor PNP, e este é um ponto muito importante, as **GPIOs 0 e 2 sempre devem iniciar com um nivel lógico alto**, e por isso você sempre deve **utilizar transistores PNP**. Sua função é basicamente excitar o FotoTriac.
4. **Foto-Triac:** O **Foto-Triac MOC3052** é o responsável por acionar a lâmpada, ele trabalha com uma **corrente máxima de 1A**, então é sempre importante estar atento ao tipo de carga, a depender será necessário o uso de TRIACs ou até mesmo um Relé.
5. **Capacitor eletrolítico:** O capacitor em paralelo com o interruptor é para evitar cliques acidentais, **ele é opcional** e em meus teste apenas o delay no código foi o bastante.  

### Conexões:
1. **P1:** é a entrada da rede, que aceita tensões entre 100-240V
2. **P2:** é a **saída em série com a carga** (Ou seja elá tem um funcionamento semelhante ao de um interruptor, em série com a carga), que no nosso caso é uma lâmpada.
3. **P3:** é o interruptor utilizado no projeto

### Layout da placa:
    A placa de circuito impresso segue o layout a seguir:  
***Colocar a imagem do layout da placa***   
    A placa tem aproximadamente 40x47mm, sendo assim, ela cabe tranquilamente em uma caixa 4x2.
	
## O código (ESP01)
### Alterações obrigatórias
    Em geral o código é muito simples e está presente em um único arquivo (Interruptor_WiFi_1_canal_OTA.ino), logo no inicio nos deparamos com o seguinte trecho de código:  
```
const char* ssid = "SSID DA REDE";  //nome da sua rede WiFI
const char* senha = "SENHA";        //sua senha WiFI
```
    Aqui nós apenas substituimos SSID DA REDE e SENHA pelos respectivos nome e a senha da rede WiFi utilizada.  
    Para definir qual será o **IP do Servidor MQTT** utilizado devemos alterar o trecho de código:  
```
const char* mqtt_server = "10.0.0.146"
```
    Substituindo o 10.0.0.146 pelo IP do seu servidor MQTT.  
    No geral, podemos dizer que a definição da rede WiFI, e definir o IP do Broker são os passos obrigatórios para a utilização do código, o restante é importante entender para ter uma melhor noção do funcionamento do projeto, e também adaptar para onde ele será utilizado.  

###Entendendo o funcionamento de cada função
1. setup_wifi: é uma função padrão em quase todo código que se conecta a uma rede WiFi. Basicamente ela recebe o ssid e a senha que definimos anteriormente e tenta conectar a rede. Quando a conexão é efetuada é exibido no monitor serial qual a rede em que conectamos, e qual o IP que recebemos.






















