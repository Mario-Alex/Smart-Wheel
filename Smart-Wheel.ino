

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int MS1 = 22;
int MS2 = 23;
int AC1 = 36;
int AC2 = 39;


void setup() {
  SerialBT.begin("SmartWhell"); //Bluetooth device name
  Serial.begin(115200);
  SerialBT.println("Please intput simulated operation.");
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);

  while(SerialBT.read() >= 0);
}

void loop() {
  String operation = "";
  if (SerialBT.available() > 0) {
    operation = SerialBT.readString();
     Serial.println(operation);
    if(operation == "Left"){
      digitalWrite(MS1, HIGH);
      delay(200);
      digitalWrite(MS1, LOW);
      SerialBT.println("OKL");
    }
    if(operation == "Right"){
      digitalWrite(MS2, HIGH);
      delay(200);
      digitalWrite(MS2, LOW);
      SerialBT.println("OKR");
    }
  }

  while(SerialBT.read() >= 0);

  int LeftValue = analogRead(AC1);
  int RightValue = analogRead(AC2);
  Serial.print("AC1:");
  Serial.println(LeftValue);
  Serial.print("AC2:");
  Serial.println(RightValue);
  if((LeftValue > 3000) || (RightValue > 3000)){
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, HIGH);
    delay(400);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    SerialBT.println("Warning!");
  }
 
}