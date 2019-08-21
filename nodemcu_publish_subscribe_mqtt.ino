#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Change this part using your WIFI Configuration
const char* ssid = "guetmantapo";         //name WIFI accespoint 
const char* password = "mokopujiok";      //WIFI password


const char* mqtt_server = "postman.cloudmqtt.com";    // Address your MQTT Server/Broker

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // Connectiong to WIFI
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Get data from MQTT Server/broker (Subscribe mode)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ["); 
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED ON
    Serial.println("LED ON");
  } else {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED OFF
    Serial.println("LED OFF");
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),"ylfxubjy","Bo3U7GcN5NAF")) {
      Serial.println("connected");
      client.subscribe("/subscribeNodeMCU");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the D0 pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 14843);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
  String messagetoPublish="from NodeMCU";
  Serial.print("Publish message: ");
  Serial.println(messagetoPublish.c_str());
  client.publish("/publishNodeMCU", messagetoPublish.c_str());   //publish to MQTT Server/Broker
  }
}
