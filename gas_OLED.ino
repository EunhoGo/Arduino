// 가스 농도 측정해서 OLED에 표시, 농도가 일정 수준 이상이면 LED 및 buzzer로 알림 후 relay로 공기청정기 가동


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int Gas = 27;
const int LED_R = 7;
const int LED_G = 10;
const int LED_B = 11;
const int Relay = 22;
const int buzzer = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Relay,OUTPUT);
  pinMode(Gas,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
  
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  if(analogRead(Gas) >= 100) {
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Gas: ");
    display.println(analogRead(Gas));
    display.display();
    delay(2000);
    
    digitalWrite(LED_R, 0);
    tone(buzzer, 300);
    delay(1000);
    noTone(buzzer);
    delay(1000);
    digitalWrite(Relay, LOW);
  }
  else {
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Gas: ");
    display.println(analogRead(Gas));
    display.println("Clean air");
    display.display();
    delay(2000);
    
    digitalWrite(LED_R, 1);
    digitalWrite(LED_G, 1);
    digitalWrite(LED_B, 1);
    digitalWrite(Relay, HIGH);
  }
}
