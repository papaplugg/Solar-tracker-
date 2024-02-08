#include <Servo.h>

#define POS 10

// Подключение фоторезисторов
int lightSensorPin1 = A0;
int lightSensorPin2 = A1;
int lightSensorPin3 = A2;
int lightSensorPin4 = A3;

int posX = 90;
int posY = 90;

// Установка штырней для сервоприводов
Servo servoX;
Servo servoY;

void setup() {
  // Устанавливаем пины фоторезисторов как входы
  pinMode(lightSensorPin1, INPUT);
  pinMode(lightSensorPin2, INPUT);
  pinMode(lightSensorPin3, INPUT);
  pinMode(lightSensorPin4, INPUT);
  Serial.begin(9600);
  // Прикрепляем сервоприводы к соответствующим пинам
  servoX.attach(10);
  servoY.attach(9);
  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  // Считываем значения с фоторезисторов
  int sensorValue1 = analogRead(lightSensorPin1)*1.4; // up-right
  int sensorValue2 = analogRead(lightSensorPin2)*1.06; // up-left
  int sensorValue3 = analogRead(lightSensorPin3)*1.08; // down-right
  int sensorValue4 = analogRead(lightSensorPin4); // down-left
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println(sensorValue3);
  Serial.println(sensorValue4);
  Serial.println();
  int avgUp = (sensorValue1 + sensorValue2) / 2;
  int avgDown = (sensorValue3 + sensorValue4) / 2;
  int avgLeft = (sensorValue2 + sensorValue4) / 2;
  int avgRight = (sensorValue1 + sensorValue3) / 2;

  //Serial.println(avgUp - avgDown);

  if (abs(avgLeft - avgRight) > POS) {
    posX += (avgLeft < avgRight) ? -1 : 1;
  }
  if (abs(avgUp - avgDown) > POS) {
    posY += (avgUp > avgDown) ? +1 : 1;
  }

  servoX.write(posX);
  servoY.write(posY);
  
  
  // Ждем некоторое время перед повторением цикла
  //delay(50);
}
