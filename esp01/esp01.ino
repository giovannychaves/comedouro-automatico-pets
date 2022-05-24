  #include <ESP8266WiFi.h> 
#include <PubSubClient.h>

#define pinRele 2 

const char* SSID = "jacquegio";                
const char* PASSWORD = "Santso10@";  
WiFiClient wifiClient;                        
 
const char* BROKER_MQTT = "mqtt.eclipseprojects.io"; 
int BROKER_PORT = 1883;                      

#define ID_MQTT  "ArduinoEspComedouro"             
#define TOPIC_SUBSCRIBE "ComedouroIoT"  
PubSubClient MQTT(wifiClient);       

void mantemConexoes();  
void conectaWiFi();     
void conectaMQTT();     
void recebePacote(char* topic, byte* payload, unsigned int length);

void setup() {
  pinMode(pinRele, OUTPUT);         

  Serial.begin(115200);

  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);  
  MQTT.setCallback(recebePacote); 
}

void loop() {
  mantemConexoes();
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
            MQTT.subscribe(TOPIC_SUBSCRIBE);
        } 
        else {
            Serial.println("Noo foi possivel se conectar ao broker.");
            Serial.println("Nova tentatica de conexao em 10s");
            delay(10000);
        }
    }
}

void recebePacote(char* topic, byte* payload, unsigned int length) 
{
    String msg;

    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }

    if (msg == "0") {
       digitalWrite(pinRele, LOW);
    }

    if (msg == "1") {
       digitalWrite(pinRele, HIGH);
    }
}
