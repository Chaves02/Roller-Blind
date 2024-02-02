/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL5veuuJEUo"
#define BLYNK_TEMPLATE_NAME "RollerBlindControl"
#define BLYNK_AUTH_TOKEN "SUOaPm6F-FYiG6ra5dU_tclbo2_CqzwI"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MEO-CHAVES";
char pass[] = "**********";

#define IN1a 5
#define IN2a 15
#define IN3a 4
#define IN4a 2

#define UP 12
#define STOP 13
#define DOWN 14

int MAXPOSITION = 1000;

int delayTime = 2;
int position = 0;

bool Down_Roller;
bool Up_Roller;
bool Stop_Roller;
bool Config_mais;
bool Config_menos;

BLYNK_WRITE(V0){
  Down_Roller = param.asInt();
}
BLYNK_WRITE(V1){
  Up_Roller = param.asInt();
}
BLYNK_WRITE(V2){
  Stop_Roller = param.asInt();
}

BLYNK_WRITE(V3){
  Config_menos = param.asInt();
}
BLYNK_WRITE(V4){
  Config_mais = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(IN1a, OUTPUT);
  pinMode(IN2a, OUTPUT);
  pinMode(IN3a, OUTPUT);
  pinMode(IN4a, OUTPUT);

  pinMode(UP, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  if(Config_menos){
    MAXPOSITION-=50;
    Serial.println(MAXPOSITION);
    delay(500);
  }
    
  if(Config_mais){
    MAXPOSITION+=50;
    Serial.println(MAXPOSITION);
    delay(500);
  }
    

  if(Down_Roller || !digitalRead(DOWN)){
    if(position < MAXPOSITION) {
      Serial.println("DOWN ROLLER BLIND");
      while(1){
        backwardMotor();
        position++;
        Blynk.run();
        if(!digitalRead(STOP) || Stop_Roller || position == MAXPOSITION)
          break;
      }      
    }
  }
  if(Up_Roller || !digitalRead(UP)){
    if(position > 0) {
      Serial.println("UP ROLLER BLIND");
      while(1){
        forwardMotor();
        position--;
        Blynk.run();
        if(!digitalRead(STOP) || Stop_Roller || position == 0)
          break;
      } 
    }
  }

  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, LOW);
}

void forwardMotor(void) {
  digitalWrite(IN4a, HIGH);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, HIGH);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, HIGH);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, HIGH);
  delay(delayTime);
}

void backwardMotor(void) {
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, HIGH);
  delay(delayTime);
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, HIGH);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
  digitalWrite(IN4a, LOW);
  digitalWrite(IN3a, HIGH);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
  digitalWrite(IN4a, HIGH);
  digitalWrite(IN3a, LOW);
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1a, LOW);
  delay(delayTime);
}
