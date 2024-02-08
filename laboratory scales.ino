#define SENSOR_PIN A0
#define BTN_PIN 2
#define DATA_PIN   10
#define SCLK_PIN   11
#define LOAD_PIN   12

#include <GyverSegment.h>


const int dataMin = 0;
const int dataMax = 1023;
const int massMin = 0;
const int massMax = 10000;

int tara = 0;

Disp595Static<4> disp(DATA_PIN, SCLK_PIN, LOAD_PIN);

void setup() {
  pinMode(BTN_PIN, INPUT);
  Serial.begin(9600);
  disp.setCursor(0);
  disp.print("helo");
  disp.update();
  disp.delay(3000);

  Serial.println("Начало работы");
}

void loop() {
  int data = analogRead(SENSOR_PIN);
  int weight = map(data, dataMin, dataMax, massMin, massMax);
  bool btnPressed = digitalRead(BTN_PIN);
  if (btnPressed)
  {
    tara = weight;
  }
  int m = weight-tara;
  Serial.println(m);

  disp.clear();
  disp.setCursor(0);
  if ((m > 9999) or (m < -999))
  {
    float message = float(weight-tara) / 1000.0f;
    disp.print(message);
  } else { 
    disp.print(m);
  }
  disp.update();
  disp.tick();
  delay(500);
}
