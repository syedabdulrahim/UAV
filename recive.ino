#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "shaolin";//your ssid name
const char* password = "Password@#password";//ssid password
#define mqtt_server  "192.168.1.4"
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  } 
  Serial.println();
  
}


void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
     //client.connect("clientId");// user name and password is provided by mqtt broker and repalce the topics with your one.
     client.connect("clientId");
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
       //client.publish("/taditarun123@gmail.com/tarun",data);

      // ... and resubscribe
      client.subscribe("rud");
      client.subscribe("thr");
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
  // pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  //pinMode(12,OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //  client.setCallback(callback);
}

void loop() {

  if (!client.connected())
  {
    reconnect();
    
  }
  
 


 
  client.loop();
client.setCallback(callback);
 
}
