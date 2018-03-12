#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "connected";//your ssid name
const char* password = "anvesh1998";//ssid password
#define mqtt_server  "192.168.0.4"

WiFiClient espClient;
PubSubClient client(espClient);

int rec_thr,rec_rud,rec_ail,rec_ele,rec_aux;
int thr,rud,ail,ele,aux;
char aail[5],aele[5],athr[5],arud[5],aaux[5];
void setup_wifi()
{

  delay(10);
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
  
  
}


void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
     client.connect("clientId","username","password");// user name and password is provided by mqtt broker and repalce the topics with your one.
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
client.publish("ail",aail);
client.publish("ele",aele);
client.publish("thr",athr);
client.publish("rud",arud);
client.publish("aux",aaux);
      

      // ... and resubscribe
      //client.subscribe("inTopic");
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
  

Serial.begin(9600);
setup_wifi();
  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  if (!client.connected())
  {
    reconnect();
    
  }
 
rec_thr = pulseIn(0, HIGH, 40000); 
  rec_rud = pulseIn(12, HIGH, 40000);
  rec_ail=pulseIn(5,HIGH,40000);
  rec_ele=pulseIn(4,HIGH,40000);
  rec_aux=pulseIn(13,HIGH,40000);

      thr = rec_thr;
    rud = rec_rud;
    ail=rec_ail;
    ele=rec_ele;
  aux=rec_aux;
  Serial.print(rec_ail);
  Serial.print("\t");
  Serial.print(rec_ele);
  Serial.print("\t");
  Serial.print(rec_thr);
  Serial.print("\t");
  Serial.print(rec_rud);
  Serial.print("\t");
  Serial.print(rec_aux);
  Serial.println("\t");
 client.loop(); 
snprintf(aail,5,"%d",ail);
snprintf(aele,5,"%d",ele);
snprintf(athr,5,"%d",thr);
snprintf(arud,5,"%d",rud);
snprintf(aaux,5,"%d",aux);

client.setCallback(callback);
client.publish("ail",aail);
client.publish("ele",aele);
client.publish("thr",athr);
client.publish("rud",arud);
client.publish("aux",aaux);


}
