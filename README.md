# UWBike 
## Sistema de Mapeamento de Motos nos Pátios da Mottu com ESP32 + UWB

# Integrantes:
 - Vinicius Leandro de Araujo Bernardes RM554728 TURMA 2TDSPY
 - Edvan Davi Murilo Santos do Nascimento RM554733 TURMA 2TDSPZ
- Rafael Romanini de Oliveira RM554637 TURMA 2TDSPZ

 O UWBike será um sistema de localização precisa de motos nos pátios da mottu. A ideia consiste em implantar 3 esp32 com uwb nos cantos do pátio, colocar etiquetas uwb nas motos e, quando a etiqueta da moto estiver ativa
 ela enviara sinais para os receptores(esp32) que pegaram no formato double a distancia da moto de cada receptor e enviaram para uma API JAVA
 A API então chama uma função responsável por calcular a posição exata da moto no pátio usando essas três distâncias e as coordenadas conhecidas das âncoras.
 Esse cálculo é feito através de um método chamado trilateração, que é uma técnica matemática usada para determinar uma posição no espaço a partir de três pontos de referência. A ideia é encontrar o ponto (x, y) que satisfaz as três distâncias medidas a partir das âncoras.



## Procedimentos para rodar a simulação:
- ### descompacte a pasta UWBike-iot-java, abra a pasta UWBike dentro dela no Intellij
- ### Altere as configurações de login e senha do banco(ou utilize a que esta) no application.properties
- ### Execute o projeto java pelo Intellij
- ### Caso tenha alterado as credenciais do oracle para a sua: 
 - - utilize o git bash para rodar estes curls:
 
 curl -X POST "http://localhost:8080/api/patio" \
-H "Content-Type: application/json" \
-d '{
  "logradouro": "Av. Prof. Celestino Bourroul",
  "numero": 363,
  "complemento": "Em frente ao EMEI Nelson Mandela",
  "cep": "02710-000",
  "cidade": "São Paulo",
  "uf": "SP",
  "pais": "Brasil",
  "lotacao": 200
}'

curl -X POST "http://localhost:8080/api/moto" \
-H "Content-Type: application/json" \
-d '{
  "modelo": "MottuSport",
  "placa": "FQBE303",
  "chassi": "7AD111010T2003890"
}'

curl -X POST "http://localhost:8080/api/moto-patio" \
-H "Content-Type: application/json" \
-d '{
  "idMoto": 1,
  "idPatio": 1
}'
- ### Tenha uma conta no wokwi
- ### Instale as extensões Wokwi Simulator e PlatformIO IDE
- ### Rode os comandos no terminal dentro da pasta raiz do projeto:
- - pip install platformio
  - pio run -e ancora1
  - pio run -e ancora2
  - pio run -e ancora3
- ### Abra cada pasta ancora em uma janela diferente no vscode
- ### Abra ou rode com live server a pagina index.html do projeto
 ### Pronto, agora você verá um dashboard trazendo as informações da distancia da moto de cada âncora(atualmente simulada) + um mini mapa demonstração de um patio de 200m2 com as âncoras posicionadas.  

 ## Resultados:

 ### Âncoras sendo simuladas:

![diagramasrodando](https://github.com/user-attachments/assets/bf8982d4-dd99-4c8c-ac7d-542feb1a66b1)

### Página web recendo as distancias por requisição MQTT:

![iotweb](https://github.com/user-attachments/assets/7c05676f-6e9a-41d0-aa43-90fab62e8771)


## Tecnologias Utilizadas :
⚙️ Hardware Simulado

    ESP32: Microcontrolador principal usado para simular as âncoras (receptores).


💻 Ambiente de Desenvolvimento

    PlatformIO: Ambiente de desenvolvimento baseado em VS Code, usado para compilar, programar e simular os ESP32.

    Wokwi: Ferramenta online que simula eletrônica, incluindo ESP32 e sensores, usada para criar e rodar os diagramas de simulação (diagram.json, wokwi.toml).

📡 Comunicação

    MQTT: Protocolo leve de mensagens utilizado para enviar as distâncias medidas pelas âncoras para um broker.

    Broker MQTT (HiveMQ público): Usado como ponto central de troca de mensagens entre as âncoras e o sistema externo.

🌐 Frontend Web

    HTML + JavaScript: Painel web simples para exibir em tempo real as distâncias recebidas de cada âncora via MQTT.

    MQTT.js: Biblioteca JavaScript usada no navegador para se conectar ao broker MQTT e escutar mensagens dos tópicos.
