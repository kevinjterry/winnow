/*
Simple Arduino based example of using the Winnow filter to smooth out a noisy analog input.
*/
#include <Winnow.h>

// Initialize Winnow filter with parameters:
// - Process noise: 0.125
// - Sensor noise: 32
// - Initial value: 1023
// - Initial estimated error: 0
Winnow myFilter(0.125, 32, 1023, 0);

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    Serial.setTimeout(20);
}

void loop() {
    // Send anything (e.g. "5") via serial to print filter parameters.
    if (Serial.available() > 0) {
        printParams();
    }

    // Read and filter analog input
    static double measurement = analogRead(A0);
    static double filteredMeasurement = myFilter.getFilteredValue(measurement);

    // Output results
    Serial.print(measurement);
    Serial.print(" ");
    Serial.println(filteredMeasurement);

    // Control sampling rate
    delay(100);
}

void printParams() {
    // Get current filter parameters
    static double processNoise = myFilter.getProcessNoise();
    static double sensorNoise = myFilter.getSensorNoise();
    static double estimatedError = myFilter.getEstimatedError();

    // Output parameters
    Serial.println("Params:");
    Serial.print(processNoise);
    Serial.print(" ");
    Serial.print(sensorNoise);
    Serial.print(" ");
    Serial.println(estimatedError);
}
