# Winnow

A tiny one-dimensional Kalman filter for smoothing noisy sensor data in real time.

- Works in C (C89 and later) and C++.
- No dependencies and no heap

## Quick start

```c
#include "winnow.h"

winnow_filter filter;
/* process noise, sensor noise, initial error, initial value */
winnow_init(&filter, 0.01f, 1.0f, 1.0f, read_sensor());

for (;;) {
    float smoothed = winnow_update(&filter, read_sensor());
}
```

C++ gets a small wrapper:

```cpp
#include "winnow.h"

winnow::Winnow filter(0.01f, 1.0f, 1.0f, read_sensor());

float smoothed = filter.update(read_sensor());
```

Seeding the filter with a first real reading as the initial value avoids a slow ramp up from zero at startup.

## API

| C | C++ | |
|---|---|---|
| `winnow_init(&f, q, r, p, x)` | `Winnow f(q, r, p, x)` | Set tuning and initial state. |
| `winnow_update(&f, m)` | `f.update(m)` | Feed a measurement, get the filtered value. |
| `winnow_reset(&f, p, x)` | `f.reset(p, x)` | Restart from a new state, keeping the tuning. |

The fields are public, in C and C++ alike. You can retune the filter between updates by assigning to them directly, for example `f.sensor_noise = 2.0f;`, and read the latest output from `f.estimated_value`.

## Tuning

| Parameter | Field | Meaning |
|---|---|---|
| q | `process_noise` | How much the true value moves between samples. Higher values respond faster but smooth less. |
| r | `sensor_noise` | How noisy each reading is. Higher values smooth more. Must be greater than 0. |
| p | `estimated_error` | How uncertain the initial value is. Only affects the first few samples. |
| x | `estimated_value` | Starting value. Use a real reading if you have one. |

**Only the ratio q / r matters once the filter has warmed up.** After a few samples the filter behaves like an exponential moving average with a fixed weight `k` (see [How it works](#how-it-works)). That gives an easy way to pick values:

| q / r | Steady-state weight `k` | Roughly averages the last… |
|---|---|---|
| 0.0001 | 0.010 | ~100 samples |
| 0.001 | 0.031 | ~30 samples |
| 0.01 | 0.095 | ~10 samples |
| 0.1 | 0.270 | ~4 samples |
| 1 | 0.618 | ~2 samples |

A practical recipe:

1. Set `r = 1`.
2. Pick `q` from the table for the amount of smoothing you want.
3. Set `p = r`, and set `x` to your first reading.

## Things to know

- **Fixed sample rate.** `q` is the drift per sample. If your sample rate changes, the amount of smoothing changes with it. Scale `q` to match.
- **Bad readings are ignored.** A NaN or ±infinity measurement leaves the filter unchanged and returns the previous value. This check does not work if you compile with `-ffast-math` or `-ffinite-math-only`.
- **`float` only.** If you really need `double`, change the type in your copy of the file. It's that small.

## How it works

Each call to `update` with a measurement `m` runs:

```
p = p + q              # predict: the true value may have drifted
k = p / (p + r)        # gain: how much to trust this measurement
x = x + k * (m - x)    # correct: move toward the measurement
p = (1 - k) * p        # the estimate is now more certain
return x
```

If `m` is NaN or infinite, the step is skipped and `x` is returned unchanged.

With `q` and `r` held constant, `k` converges to a fixed value. From then on the filter is exactly an exponential moving average with weight `k`:

```
P = (q + sqrt(q*q + 4*q*r)) / 2
k = P / (P + r)
```

### Porting

The algorithm above is the whole filter, so porting it to another language takes a few lines. To check a port, run it with `q = 0.01, r = 1, p = 1, x = 0` and compare against this output (4 decimal places):

| Step | Input | Output |
|---|---|---|
| 1 | 10 | 5.0249 |
| 2 | 10 | 6.7106 |
| 3 | 10 | 7.5613 |
| 4 | 10 | 8.0777 |
| 5 | 10 | 8.4266 |
| 6 | 12 | 9.0009 |
| 7 | 8 | 8.8550 |
| 8 | 10 | 9.0093 |
| 9 | 10 | 9.1346 |
| 10 | 10 | 9.2386 |

## License

MIT. See `LICENSE`
