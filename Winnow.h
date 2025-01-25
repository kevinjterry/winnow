#ifndef _Winnow_h
#define _Winnow_h

/**
 * @brief Implements a simple Kalman filter for one-dimensional data
 */
class Winnow {
   private:
    double q;  // process noise covariance
    double r;  // measurement noise covariance
    double x;  // value
    double p;  // estimation error covariance
    double k;  // kalman gain

   public:
    // Constructors
    Winnow() : q(0.0), r(0.0), p(0.0), x(0.0), k(0.0) {}

    Winnow(double process_noise, double sensor_noise, double estimated_error, double initial_value)
        : q(process_noise), r(sensor_noise), p(estimated_error), x(initial_value), k(0.0) {}

    double getFilteredValue(double measurement) {
        this->p = this->p + this->q;

        // measurement update
        this->k = this->p / (this->p + this->r);
        this->x = this->x + this->k * (measurement - this->x);
        this->p = (1 - this->k) * this->p;

        return this->x;
    }

    // Setters
    void setParameters(double process_noise, double sensor_noise, double estimated_error) {
        this->q = process_noise;
        this->r = sensor_noise;
        this->p = estimated_error;
    }

    void setParameters(double process_noise, double sensor_noise) {
        this->q = process_noise;
        this->r = sensor_noise;
    }

    void setProcessNoise(double process_noise) { this->q = process_noise; }
    void setSensorNoise(double sensor_noise) { this->r = sensor_noise; }
    void setEstimatedError(double estimated_error) { this->p = estimated_error; }

    // Getters
    double getProcessNoise() const { return this->q; }
    double getSensorNoise() const { return this->r; }
    double getEstimatedError() const { return this->p; }
};

#endif
