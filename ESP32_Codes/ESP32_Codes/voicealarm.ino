#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 23

const char* ssid = "MUHAMMED97";    
const char* password = "1234543210"; 
const char* mqtt_server = "16.16.192.226"; 
const char* n_topic = "esp32/notify";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert the payload to a String
  String msg = String((char*)payload).substring(0, length);

  // Print the received message
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(msg); 
  
  
  if (msg == "1") {
    digitalWrite(LED_PIN, HIGH); 
  } else if (msg == "0") {
    digitalWrite(LED_PIN, LOW); 
  }
}

void reconnect() {
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ClientID")) {
      Serial.println("connected");
      
      client.subscribe(n_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
