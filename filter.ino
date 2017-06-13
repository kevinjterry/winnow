#include <Winnow.h>

//#define PRINT_PARAMS

// initialize variables
double measurement;
double filteredMeasurement;

double processNoise;
double sensorNoise;
double estimatedError;

// initialize filter
winnow myFilter(0.125,32,1023,0);


void setup() {

  Serial.begin(115200);
  Serial.setTimeout(20);

}


//################# MAIN LOOP #################
void loop() {

  while (Seria.available() > 0){
    // print filter parameters if defined
    #ifdef PRINT_PARAMS
    printParams();
    #endif
  }

  // read analog pin
  measurement = analogRead(A0);

  //get filtered value
  filteredMeasurement = myFilter.getFilteredValue(measurement);

  // print raw and filtered value to monitor
  Serial.print(measurement);
  Serial.print(" ");
  Serial.println(filteredMeasurement);

  // slow main loop to readable speed
  delay(100);

}

/*
//################# MAIN LOOP #################
*/

void printParams(){
  Serial.println("Params: ");

  processNoise = myFilter.getProcessNoise();
  sensorNoise = myFilter.getSensorNoise();
  estimatedError = myFilter.getEstimatedError();

  Serial.print(processNoise);
  Serial.print(" ");
  Serial.print(sensorNoise);
  Serial.print(" ");
  Serial.println(estimatedError);

  // delay for readibility
  delay(500);

}
