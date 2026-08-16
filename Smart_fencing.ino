#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "fencing"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// WiFi
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Pins
#define TRIG 5
#define ECHO 18
#define FENCE 23
#define LED1 22
#define LED2 19
#define BUZZER 21
#define SERVO_PIN 12

float distance;
bool intrusionDetected = false;
bool systemActive = true;  

// SERVO
Servo camServo;
int servoAngle = 30;
int servoDirection = 4;     // fast but smooth
bool servoPaused = false;

// BLYNK SYSTEM CONTROL 
BLYNK_WRITE(V3)
{
  int value = param.asInt();

  if (value == 1)
  {
    systemActive = true;
    servoPaused = false;

    Blynk.virtualWrite(V0, "SYSTEM IS ACTIVE");
    Serial.println("SYSTEM ACTIVATED");
  }
  else
  {
    systemActive = false;
    intrusionDetected = false;

    digitalWrite(FENCE, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    noTone(BUZZER);

    servoPaused = true;

    Blynk.virtualWrite(V0, "SYSTEM IS OFF");
    Serial.println("SYSTEM OFF");
  }
}

//  Auto-sync when Blynk app opens
BLYNK_CONNECTED()
{
  Blynk.virtualWrite(V3, 1);   // force system ON
}

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(FENCE, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(FENCE, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  camServo.attach(SERVO_PIN);
  camServo.write(servoAngle);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Blynk.virtualWrite(V0, "SYSTEM IS ACTIVE");
  //Display ESP32 Local IP address in Blynk if required 

  Serial.println("System Ready");
}

//  ULTRASONIC 
float getDistance()
{
  long duration;
  float total = 0;
  int validReadings = 0;

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration = pulseIn(ECHO, HIGH, 20000);
    float d = duration * 0.0343 / 2;

    if (d > 2 && d < 100)
    {
      total += d;
      validReadings++;
    }
    delay(20);
  }

  if (validReadings == 0) return 999;
  return total / validReadings;
}

// SERVO SCAN 
void scanServo()
{
  if (servoPaused) return;

  camServo.write(servoAngle);
  servoAngle += servoDirection;

  if (servoAngle >= 150) servoDirection = -4;
  if (servoAngle <= 30)  servoDirection = 4;

  delay(5);
}

void loop()
{
  Blynk.run();
  scanServo();

  if (!systemActive) return;

  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 24 && !intrusionDetected)
  {
    intrusionDetected = true;

    digitalWrite(FENCE, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    tone(BUZZER, 1000);

    servoPaused = true;

    Blynk.virtualWrite(V0, "ALERT! SEE CAMERA LIVE");
    Serial.println("INTRUDER DETECTED");
  }
  else if (distance > 26 && intrusionDetected)
  {
    intrusionDetected = false;

    digitalWrite(FENCE, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    noTone(BUZZER);

    servoPaused = false;

    Blynk.virtualWrite(V0, "SAFE");
    Serial.println("SAFE");
  }

  delay(100);
}

