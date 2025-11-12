# Winnow

A lightweight single-dimension Kalman filter for real-time data smoothing.
Useful for reducing noise and impulses in slow or noisy signals where windowed averaging isn’t practical.

## What it does

Filters incoming data by tracking the previous state and estimating the next with tunable system noise parameters.

## Parameters

- **Process noise**: How much the true value changes (smaller = smoother but slower response)
- **Sensor noise**: How noisy your sensor is (higher = more filtering)
- **Error estimate**: Initial uncertainty
- **Initial value**: Starting point for the filter

## Usage

### C++ Version (winnow.hpp)

```cpp
#include "winnow.hpp"

using winnow::Winnow;

Winnow filter(0.1, 0.5, 1.0, 0.0); // process noise, sensor noise, error estimate, initial value

double noisy_reading = readAnalogPin(analog_pin);
double clean_value = filter.getFilteredValue(noisy_reading);
```

### C Version (Winnow.h)

```c
#include "Winnow.h"

winnow_filter filter;
winnow_init(&filter, 0.1, 0.5, 1.0, 0.0); // process noise, sensor noise, error estimate, initial value

double noisy_reading = readAnalogPin(analog_pin);
double clean_value = winnow_get_filtered_value(&filter, noisy_reading);
```

## License

MIT
