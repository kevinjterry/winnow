#ifndef _WINNOW_H
#define _WINNOW_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double process_noise_covariance;      // q: process noise covariance
    double measurement_noise_covariance;  // r: measurement noise covariance
    double estimated_value;               // x: current estimated value
    double estimation_error_covariance;   // p: estimation error covariance
    double kalman_gain;                   // k: kalman gain
} winnow_filter;

// Initialize filter with all parameters
static inline void winnow_init(winnow_filter* filter, double process_noise, double sensor_noise,
    double estimated_error, double initial_value) {
    filter->process_noise_covariance = process_noise;
    filter->measurement_noise_covariance = sensor_noise;
    filter->estimation_error_covariance = estimated_error;
    filter->estimated_value = initial_value;
    filter->kalman_gain = 0.0;
}

// Process new measurement and return filtered value
static inline double winnow_get_filtered_value(winnow_filter* filter, double measurement) {
    // Prediction update
    filter->estimation_error_covariance
        = filter->estimation_error_covariance + filter->process_noise_covariance;

    // Measurement update
    filter->kalman_gain = filter->estimation_error_covariance
        / (filter->estimation_error_covariance + filter->measurement_noise_covariance);
    filter->estimated_value
        = filter->estimated_value + filter->kalman_gain * (measurement - filter->estimated_value);
    filter->estimation_error_covariance
        = (1.0 - filter->kalman_gain) * filter->estimation_error_covariance;

    return filter->estimated_value;
}

// Set all filter parameters at once
static inline void winnow_set_parameters(winnow_filter* filter, double process_noise,
    double sensor_noise, double estimated_error) {
    filter->process_noise_covariance = process_noise;
    filter->measurement_noise_covariance = sensor_noise;
    filter->estimation_error_covariance = estimated_error;
}

// Set process noise covariance
static inline void winnow_set_process_noise(winnow_filter* filter, double process_noise) {
    filter->process_noise_covariance = process_noise;
}

// Set measurement noise covariance
static inline void winnow_set_sensor_noise(winnow_filter* filter, double sensor_noise) {
    filter->measurement_noise_covariance = sensor_noise;
}

// Set estimation error covariance
static inline void winnow_set_estimated_error(winnow_filter* filter, double estimated_error) {
    filter->estimation_error_covariance = estimated_error;
}

// Reset filter to initial state
static inline void winnow_reset(winnow_filter* filter, double initial_value) {
    filter->estimated_value = initial_value;
    filter->kalman_gain = 0.0;
}

// Get current estimated value without processing new measurement
static inline double winnow_get_current_value(const winnow_filter* filter) {
    return filter->estimated_value;
}

// Get process noise covariance
static inline double winnow_get_process_noise(const winnow_filter* filter) {
    return filter->process_noise_covariance;
}

// Get measurement noise covariance
static inline double winnow_get_sensor_noise(const winnow_filter* filter) {
    return filter->measurement_noise_covariance;
}

// Get estimation error covariance
static inline double winnow_get_estimated_error(const winnow_filter* filter) {
    return filter->estimation_error_covariance;
}

#ifdef __cplusplus
}
#endif

#endif  // _WINNOW_H
