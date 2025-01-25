#include <Winnow.h>

// initialize filter
winnow myFilter(0.125, 32, 1023, 0);

void setup() { Serial.begin(115200); }

void loop() {
    // read analog pin
    static double measurement = analogRead(A0);

    // get filtered value
    static double filteredMeasurement = myFilter.getFilteredValue(measurement);

    // print raw and filtered value to monitor
    Serial.print(measurement);
    Serial.print(" ");
    Serial.println(filteredMeasurement);
}
