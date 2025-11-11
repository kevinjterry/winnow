#pragma once
/**
 * Winnow - A lightweight 1D Kalman filter implementation
 *
 * Quick library for a simple Kalman filter for smoothing noisy sensor
 * (or other) data in embedded systems projects.
 *
 * Author: Kevin Terry
 * License: MIT
 */

namespace winnow {

class Winnow {
   private:
    double process_noise_covariance;      // q: process noise covariance
    double measurement_noise_covariance;  // r: measurement noise covariance
    double estimated_value;               // x: current estimated value
    double estimation_error_covariance;   // p: estimation error covariance
    double kalman_gain;                   // k: kalman gain

   public:
    Winnow()
        : process_noise_covariance(0.0),
          measurement_noise_covariance(0.0),
          estimation_error_covariance(0.0),
          estimated_value(0.0),
          kalman_gain(0.0) {}

    // Constructor initialization
    Winnow(double process_noise, double sensor_noise, double estimated_error, double initial_value)
        : process_noise_covariance(process_noise),
          measurement_noise_covariance(sensor_noise),
          estimation_error_covariance(estimated_error),
          estimated_value(initial_value),
          kalman_gain(0.0) {}

    // Process new measurement and return filtered value
    double getFilteredValue(double measurement) {
        // Prediction update
        estimation_error_covariance = estimation_error_covariance + process_noise_covariance;

        // Measurement update
        kalman_gain = estimation_error_covariance
            / (estimation_error_covariance + measurement_noise_covariance);
        estimated_value = estimated_value + kalman_gain * (measurement - estimated_value);
        estimation_error_covariance = (1 - kalman_gain) * estimation_error_covariance;

        return estimated_value;
    }

    // Set all filter parameters at once
    void setParameters(double process_noise, double sensor_noise, double estimated_error) {
        process_noise_covariance = process_noise;
        measurement_noise_covariance = sensor_noise;
        estimation_error_covariance = estimated_error;
    }

    // Set noise parameters (keeps current error estimate)
    void setParameters(double process_noise, double sensor_noise) {
        process_noise_covariance = process_noise;
        measurement_noise_covariance = sensor_noise;
    }

    // Individual parameter setters
    void setProcessNoise(double process_noise) { process_noise_covariance = process_noise; }
    void setSensorNoise(double sensor_noise) { measurement_noise_covariance = sensor_noise; }
    void setEstimatedError(double estimated_error) {
        estimation_error_covariance = estimated_error;
    }

    // Reset filter to initial state
    void reset(double initial_value = 0.0) {
        estimated_value = initial_value;
        kalman_gain = 0.0;
    }

    // Get current estimated value without processing new measurement
    double getCurrentValue() const { return estimated_value; }

    // Get current filter parameters
    double getProcessNoise() const { return process_noise_covariance; }
    double getSensorNoise() const { return measurement_noise_covariance; }
    double getEstimatedError() const { return estimation_error_covariance; }
};

}  // namespace winnow