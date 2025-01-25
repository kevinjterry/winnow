#include <Winnow.h>

// initialize filter
winnow filterOne(0.125, 32, 1023, 0);
winnow filterTwo(0.35, 8, 500, 0);

void setup() { Serial.begin(115200); }

void loop() {
    // read analog pin
    static double measurementOne = analogRead(A0);
    static double measurementTwo = analogRead(A1);

    // get filtered value
    static double filteredMeasurementOne = filterOne.getFilteredValue(measurementOne);
    static double filteredMeasurementTwo = filterTwo.getFilteredValue(measurementTwo);

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
