# Comedouro-automatico-pets
Comedouro automático para pets

## Funcionamento

Esse projeto consiste em um comedouro inteligente totalmente automatizado e com funcionalidades remotas. Sua estrutura é construída em PVC e MDF, e seu controle é feito por uma placa Arduino Uno R3, alimentada por uma fonte 12V e com uma bateria auxiliar de também 12V. Possui dois relés que fazem o chaveamente da bateria para o Arduino e do Arduino para o motor DC de 3,3V. O Arduino carrega um script feito em C onde o usuário irá configurar os horários em que o sistema todo irá funcionar e por quanto tempo o motor irá funcionar, determinando a quantidade de ração irá despejar no pote do pet. O projeto possui também um controle de acionamento remoto, assim ao apertar o botão, um dispostivo NodeMCU junto com um ESP8266 irá enviar "mensagens" via internet através do protocolo MQTT, que através de um Broker irá redirecionar essas mensagens para o ESP8266 do comedouro, acionando assim todo o sistema enquanto o botão estiver sendo pressionado.


