/* 
 *  -------------------------------
 *  NxG - CAQDAA 
 *  -------------------------------
 */

float maxVoltageWithoutFilter = 4.5;
float minVoltageWithCleanFilter = 3.5; // or maxVoltageForCleaningRequired
float minVoltageForCleaningRequired = 2.0; // or maxVoltageForReplacementRequired

const int sensorInPinA0 = A0; 
const int sensorInPinA1 = A1;

const int redLed = 12;
const int greenLed = 13;
const int yellowLed = 11;

void setup() {
  Serial.println("Beginning Setup");
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
}

void loop() {
  float voltage1 = readSensorVoltageFrom(sensorInPinA0);
  float voltage2 = readSensorVoltageFrom(sensorInPinA1);
  float averageVoltage = (voltage1 + voltage2)/2;
  logValues(voltage1, voltage2, averageVoltage);
  
  if(averageVoltage > maxVoltageWithoutFilter){
    showRed();
  } else if(averageVoltage > minVoltageForCleaningRequired && averageVoltage < minVoltageWithCleanFilter) {
    showYellow();
  } else if (averageVoltage < minVoltageForCleaningRequired){
    showRed();
  } 
  //else {
  //  showGreen();
  //}

  delay(500);
}

void showRed() {
  toggleOutputs(HIGH, LOW, LOW);
}

void showYellow() {
  toggleOutputs(LOW, LOW, HIGH);
}
void logValues(float sensor1Volt, float sensor2Volt, float averageVolt) {
  Serial.print("Sensor1 = ");
  Serial.print(sensor1Volt);
  Serial.print(", Sensor2 = ");
  Serial.print(sensor2Volt);
  Serial.print(", Average = "); 
  Serial.println(averageVolt);
}

float readSensorVoltageFrom(int senorPinNumber) {
  int sensorValue = analogRead(senorPinNumber);
  return sensorValue * (5.0 / 1023.0);
}

void toggleOutputs(int redLedState, int greenLedState, int yellowLedState) {
  digitalWrite(greenLed, greenLedState);
  digitalWrite(redLed, redLedState);
  digitalWrite(yellowLed, yellowLedState);
}
