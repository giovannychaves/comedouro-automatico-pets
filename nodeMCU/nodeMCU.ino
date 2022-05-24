#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define pinBotao1 12 

const char* SSID = "testemobile";                
const char* PASSWORD = "teste123";  
WiFiClient wifiClient;                        
 
const char* BROKER_MQTT = "mqtt.eclipseprojects.io"; 
int BROKER_PORT = 1883;                    

#define ID_MQTT  "PbNodeMCU"             
#define TOPIC_PUBLISH "ComedouroIoT"    
PubSubClient MQTT(wifiClient);       

void mantemConexoes(); 
void conectaWiFi();    
void conectaMQTT();   
void enviaPacote();   

void setup() {
  pinMode(pinBotao1, INPUT_PULLUP);         

  Serial.begin(115200);

  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
}

void loop() {
  mantemConexoes();
  enviaValores();
  MQTT.loop();
}

void mantemConexoes() {
    if (!MQTT.connected()) {
       conectaMQTT(); 
    }
    
    conectaWiFi();
}

void conectaWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
     return;
  }
        
  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");

  WiFi.begin(SSID, PASSWORD); 
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(SSID);  
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP()); 
}

void conectaMQTT() { 
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado ao Broker com sucesso!");
        } 
        else {
            Serial.println("Noo foi possivel se conectar ao broker.");
            Serial.println("Nova tentatica de conexao em 10s");
            delay(10000);
        }
    }
}

void enviaValores() {
static bool estadoBotao1 = HIGH;
static bool estadoBotao1Ant = HIGH;
static unsigned long debounceBotao1;

  estadoBotao1 = digitalRead(pinBotao1);
  if (  (millis() - debounceBotao1) > 30 ) { 
     if (!estadoBotao1 && estadoBotao1Ant) {

        MQTT.publish(TOPIC_PUBLISH, "1");
        Serial.println("Botao1 APERTADO. Payload enviado.");
        
        debounceBotao1 = millis();
     } else if (estadoBotao1 && !estadoBotao1Ant) {

        MQTT.publish(TOPIC_PUBLISH, "0");
        Serial.println("Botao1 SOLTO. Payload enviado.");
        
        debounceBotao1 = millis();
     }
     
  }
  estadoBotao1Ant = estadoBotao1;
}
