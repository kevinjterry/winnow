#ifndef WINNOW_H
#define WINNOW_H

#define WINNOW_VERSION "2.0.0"

#ifndef WINNOW_INLINE
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#define WINNOW_INLINE static inline
#else
#define WINNOW_INLINE static __inline
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Fields are public: tuning values can be changed at any time between updates. */
typedef struct {
    float process_noise;   /* q: how much the true value moves per sample */
    float sensor_noise;    /* r: how noisy each measurement is (must be > 0) */
    float estimated_error; /* p: current uncertainty of the estimate */
    float estimated_value; /* x: current filtered value */
} winnow_filter;

/* Start (or restart) the filter with both tuning values and an initial state. */
WINNOW_INLINE void winnow_init(winnow_filter *filter, float process_noise, float sensor_noise,
    float estimated_error, float initial_value) {
    filter->process_noise = process_noise;
    filter->sensor_noise = sensor_noise;
    filter->estimated_error = estimated_error;
    filter->estimated_value = initial_value;
}

/* Restart from a new initial state, keeping the current tuning. */
WINNOW_INLINE void winnow_reset(winnow_filter *filter, float estimated_error, float initial_value) {
    filter->estimated_error = estimated_error;
    filter->estimated_value = initial_value;
}

/* Feed one measurement and return the new filtered value. */
WINNOW_INLINE float winnow_update(winnow_filter *filter, float measurement) {
    float gain;

    /* Ignore NaN and infinite readings, which would otherwise poison the estimate forever. */
    if (measurement - measurement != 0.0f) {
        return filter->estimated_value;
    }

    /* Predict: the true value may have drifted since the last sample. */
    filter->estimated_error += filter->process_noise;

    /* Correct: move toward the measurement in proportion to how much we trust it. */
    gain = filter->estimated_error / (filter->estimated_error + filter->sensor_noise);
    filter->estimated_value += gain * (measurement - filter->estimated_value);
    filter->estimated_error *= 1.0f - gain;

    return filter->estimated_value;
}

#ifdef __cplusplus
} /* extern "C" */

namespace winnow {

/* C++ convenience wrapper. Same fields as winnow_filter, so tuning works the same way. */
class Winnow : public winnow_filter {
   public:
    Winnow(float process_noise, float sensor_noise, float estimated_error, float initial_value) {
        winnow_init(this, process_noise, sensor_noise, estimated_error, initial_value);
    }

    float update(float measurement) { return winnow_update(this, measurement); }

    void reset(float estimated_error, float initial_value) {
        winnow_reset(this, estimated_error, initial_value);
    }
};

} /* namespace winnow */
#endif

#endif /* WINNOW_H */
