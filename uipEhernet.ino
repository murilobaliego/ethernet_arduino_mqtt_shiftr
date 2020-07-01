#include <UIPEthernet.h>
#include <MQTT.h>

//#include <FastLED.h>
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define MACADDRESS 0x00,0x01,0x02,0x03,0x04,0x05
#define MYIPADDR 192,168,0,75
#define MYIPMASK 255,255,255,0
#define MYDNS 189,7,48,61
#define MYGW 192,168,0,1

//CRGB leds[30];
boolean connected = false;
boolean myinit = true;
unsigned long lastMillis = 0;

EthernetClient ethClient;
MQTTClient client;

void setup() {
  // setup serial communication
  Serial.begin(115200);
  connected = false;
  
  // setup ethernet communication using DHCP
  uint8_t mac[6] = {MACADDRESS};
  uint8_t myIP[4] = {MYIPADDR};
  uint8_t myMASK[4] = {MYIPMASK};
  uint8_t myDNS[4] = {MYDNS};
  uint8_t myGW[4] = {MYGW};
  Ethernet.begin(mac,myIP,myDNS,myGW,myMASK);

  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.subnetMask());
  Serial.println(Ethernet.gatewayIP());
  Serial.println(Ethernet.dnsServerIP());
  // setup mqtt client
  delay(1000);
  client.begin("broker.shiftr.io", ethClient);
  client.onMessage(messageReceived);
  connect();
  Serial.println(("MQTT client configured"));
}

void connect() {
  Serial.println("Connecting with MQTT");
  while (!client.connect("UnoMQTT2", "user", "password")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("/1wae-client");
  connected = true;
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
  delay(200);
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.print(" - ");
  Serial.println();
  //int index = payload.indexOf(':');
  //String st = payload.substring(index);
  //Serial.println(st);
//    for( int i = 0; i < 30; i++) {
//        leds[i] =  14893620;
//   }
}

void loop() {
  client.loop();
    if (!client.connected()) {
    connect();
  }
  if (myinit){
      //FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds, 30).setCorrection( TypicalLEDStrip );
      myinit = false;
  }  
  if (connected){
//      FastLED.setBrightness(  64 );
//      FastLED.show();
//      FastLED.delay(100);
  }
    
 }
