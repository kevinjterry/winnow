#include <Winnow.h>

// initialize variables
double measurement;
double filteredMeasurement;

// initialize filter
winnow myFilter(0.125,32,1023,0);


void setup() {

  Serial.begin(115200);

}


void loop() {

  // read analog pin
  measurement = analogRead(A0);

  //get filtered value
  filteredMeasurement = myFilter.getFilteredValue(measurement);

  // print raw and filtered value to monitor
  Serial.print(measurement);
  Serial.print(" ");
  Serial.println(filteredMeasurement);

}
