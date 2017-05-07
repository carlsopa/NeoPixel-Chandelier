#include "pattern.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ESP8266WiFi.h>

#define WLAN_SSID   "*****"
#define WLAN_PASS   "*****"
#define MQTT_SERVER "***.***.*.***"
#define MQTT_PORT   1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

void BottomRingComplete();
void OutsideBottomComplete();
void OutsideTopComplete();
void CenterComplete();
void TopRingComplete();
void MQTT_connect();
char *load;
int itv = 0;
int TstArray[10];
const int sze = 5;
int pin;
int r1;
int g1;
int b1;
int r2;
int g2;
int b2;
enum state {SETUP,CONTROL,ANIMATE,RCYCLE,RAINBOW,RCHASE,TCHASE,COLORWIPE,FDE,DIM,DANCE,SET};

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);
Adafruit_MQTT_Subscribe Control = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/Apartment/LivingRoom/Chandelier");

ChanLevels BottomRing(60, 14, NEO_RGBW + NEO_KHZ800);
ChanLevels OutsideBottom(60, 15, NEO_GRB + NEO_KHZ800);
ChanLevels OutsideTop(60, 12, NEO_GRB + NEO_KHZ800);
ChanLevels Center(1, 0, NEO_GRB + NEO_KHZ800);
ChanLevels TopRing(6, 13, NEO_GRB + NEO_KHZ800);
ChanLevels ChandelierArray[sze]={BottomRing,Center,OutsideBottom,OutsideTop,TopRing};


void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  mqtt.subscribe(&Control);
}

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(500))){
    if (subscription == &Control) {
      load = (char *)Control.lastread;
    }
    state state;
    char *token = strtok(load, ":");
    if(token[0] == 'c'){
      state = CONTROL;
    }
    else if(token[0] == 'a'){
      state = ANIMATE;
    }
    while(token){
      token = strtok(NULL, ":");
      if (token != NULL){
        String t = String(token);
        switch(state){
          case CONTROL: {
            if (t == "on"){
              token = strtok(NULL,":");
              String t = String(token);
              if(t == "all"){
                for (int i = 0; i<sze; ++i){
                  ChandelierArray[i].TurnOn();
                }
              }
              else{
                ChandelierArray[t.toInt()].TurnOn();
              }
            }
            if (t == "off"){
              token = strtok(NULL, ":");
              String t = String(token);
              if(t == "all"){
                for (int i = 0; i<sze; ++i){
                  ChandelierArray[i].TurnOff();
                }
              }
              else{
                ChandelierArray[t.toInt()].TurnOff();
              }
            }
            break;
          }//end control case
          case ANIMATE: {
            if(t == "rbc"){//rainbowcycle
              state = RCYCLE;
            }
            if(t == "rb"){//rainbow
              state = RAINBOW;
            }
            if(t == "tcr"){//theaterchaserainbow
              state = RCHASE;
            }
            if(t == "tc"){//theaterchase
              state = TCHASE;
            }
            if(t == "cw"){//colorwipe
              state = COLORWIPE;                
            }
            if(t == "fd"){//fade
              state = FDE;
            }
            if(t == "dm"){//dim
              state = DIM;
            }
            if(t == "dn"){//dance
              state = DANCE;
              //return;
            }
            if(t == "set"){
              state = SET;
            }
            continue;
            break;
          }
          case TCHASE: {
            int i = 0;
            TstArray[i] = String(token).toInt();
            i++;
            while(token){
              String t = String(token = strtok(NULL, ":"));
              if (token != NULL){
                TstArray[i] = t.toInt();
                i++;
              }
            }
            pin = TstArray[0];
            r1 = TstArray[1];
            g1 = TstArray[2];
            b1 = TstArray[3];
            r2 = TstArray[4];
            g2 = TstArray[5];
            b2 = TstArray[6];
            ChandelierArray[pin].TheaterChase(ChandelierArray[pin].Color(r1,g1,b1),ChandelierArray[pin].Color(r2,g2,b2),100);
            break;
          }//End Theater Chase
          case RCYCLE: {
            int i = 0;
            TstArray[i] = String(token).toInt();
            i++;
            while(token){
              String t = String(token = strtok(NULL, ":"));
              if (token != NULL){
                TstArray[i] = t.toInt();
                i++;
              }
            }
            pin = TstArray[0];
            itv = TstArray[1];
            ChandelierArray[pin].RainbowCycle(i);
            break;
          }//End Rainbow Cycle
          case FDE: {
            int i = 0;
            TstArray[i] = String(token).toInt();
            i++;
            while(token){
              String t = String(token = strtok(NULL, ":"));
              if (token != NULL){
                TstArray[i] = t.toInt();
                i++;
              }
            }
            pin = TstArray[0];
            r1 = TstArray[1];
            g1 = TstArray[2];
            b1 = TstArray[3];
            r2 = TstArray[4];
            g2 = TstArray[5];
            b2 = TstArray[6];
            ChandelierArray[pin].Fade(ChandelierArray[pin].Color(r1,g1,b1),ChandelierArray[pin].Color(r2,g2,b2),20,100);
            break;
          }//End Fade
          case SET: {
            int i = 0;
            TstArray[i] = String(token).toInt();
            i++;
            while(token){
              String t = String(token = strtok(NULL,":"));
              if (token != NULL){
                TstArray[i] = t.toInt();
                i++;
              }
            }
            pin = TstArray[0];
            r1 = TstArray[1];
            g1 = TstArray[2];
            b1 = TstArray[3];
            ChandelierArray[pin].SetColor(r1,g1,b1);
            break;
          }// end color set
        }
      }
    }
  }
  for(int i = 0; i<sze; ++i){
    ChandelierArray[i].Update();
  }
}
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
