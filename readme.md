# Winnow

A simple Kalman filter library for smoothing noisy sensor data in embedded systems and Arduino projects.

## What it does

Takes noisy measurements and gives you cleaner, more stable values. Great for smoothing out unstable sensor readings.

## Usage

### C++ Version (winnow.hpp)

```cpp
#include "winnow.hpp"

using winnow::Winnow;

Winnow filter(0.1, 0.5, 1.0, 0.0);  // process noise, sensor noise, error estimate, initial value

double noisy_reading = analogRead(A0);
double clean_value = filter.getFilteredValue(noisy_reading);
```

### C Version (Winnow.h)

```c
#include "Winnow.h"

winnow_filter filter;
winnow_init(&filter, 0.1, 0.5, 1.0, 0.0);

double noisy_reading = analogRead(A0);
double clean_value = winnow_get_filtered_value(&filter, noisy_reading);
```

## Parameters

- **Process noise**: How much the true value changes (smaller = smoother but slower response)
- **Sensor noise**: How noisy your sensor is (higher = more filtering)
- **Error estimate**: Initial uncertainty (usually start with 1.0)
- **Initial value**: Starting point for the filter

## License

MIT
