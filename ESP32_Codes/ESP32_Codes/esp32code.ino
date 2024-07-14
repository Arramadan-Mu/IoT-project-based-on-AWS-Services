#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11
#define LED_PIN 23

const char* ssid = "MUHAMMED97";        
const char* password = "1234543210"; 
const char* mqtt_server = "16.16.192.226"; 
const char* temp_topic = "esp32/temperature";
const char* hum_topic = "esp32/humidity";
const char* thresh_topic = "esp32/put_t_threshould";

WiFiClient espClient;
PubSubClient client1(espClient);
DHT dht(DHTPIN, DHTTYPE);

float temperatureThreshold = 30.0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  setup_wifi();
  client1.setServer(mqtt_server, 1883);
  client1.setCallback(callback);
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
  String msg = String((char*)payload).substring(0, length);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(msg);
  if (strcmp(topic, thresh_topic) == 0) {
    temperatureThreshold = msg.toFloat();
    Serial.print("Updated temperature threshold: ");
    Serial.println(temperatureThreshold);
  } 
}

void reconnect() {
  while (!client1.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client1.connect("DHT11ESP32")) {
      Serial.println("connected");
      client1.subscribe(thresh_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client1.connected()) {
    reconnect();
  }
  client1.loop();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!, Randomly numbers are choosen!!");
    h = random(-100, 0);
    t = random(-100, 0);
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
  
  client1.publish(temp_topic, String(t).c_str(), true);
  client1.publish(hum_topic, String(h).c_str(), true);

  // Check if the temperature exceeds the threshold and control the LED accordingly
  if (t > temperatureThreshold) {
    digitalWrite(LED_PIN, HIGH);  // Turn the LED on
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn the LED off
  }
  
  delay(5000);
}
