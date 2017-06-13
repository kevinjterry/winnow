#include <Winnow.h>

// initialize variables
double measurementOne;
double measurementTwo;
double filteredMeasurementOne;
double filteredMeasurementTwo;

double processNoise;
double sensorNoise;
double estimatedError;

// initialize filter
winnow filterOne(0.125, 32, 1023, 0);
winnow filterTwo(0.35, 8, 500, 0);


void setup() {

  Serial.begin(115200);
  Serial.setTimeout(20);

}


void loop() {

  // read analog pin
  measurementOne = analogRead(A0);
  measurementTwo = analogRead(A1);

  //get filtered value
  filteredMeasurementOne = filterOne.getFilteredValue(measurementOne);
  filteredMeasurementTwo = filterTwo.getFilteredValue(measurementTwo);

  // print raw and filtered value to monitor
  Serial.print(measurementOne);
  Serial.print(" ");
  Serial.print(filteredMeasurementOne);
  Serial.print(" ");
  Serial.print(measurementTwo);
  Serial.print(" ");
  Serial.println(filteredMeasurementTwo);

  // slow main loop to readable speed
  delay(100);

}
