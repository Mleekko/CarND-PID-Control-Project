# CarND-Controls-PID - Project Report

## Rubric Points:
### Your code should compile.
I've added the created sources to the `CMakeLists.txt` so the project should build without any issues.
### The PID procedure follows what was taught in the lessons.
The PID procedure produces the desired steering angle based on the Cross-Track Error (CTE) and the hyper-param
coefficients.
### Describe the effect each of the P, I, D components had in your implementation.
PID-controller consists of 3 parts that determine the resulting control value:
* P (Proportional) - impacts the resulting value proportionally to the current CTE. P-Controller constantly oscillates
near the target trajectory.
* D (Derivative) - adjusts the value by a derivative of the CTE. This allows to flatten the P-Controller oscillations.
* I (Integral) - aggregates the parameters error over time. Allows to detect parameter bias.

### Describe how the final hyperparameters were chosen.
To start, I've picked a reasonable P-coefficient value to allow the car to stay on track. Later on, I've implemented
the Twiddle algorithm that would adjust the PID coeffs by just driving the track. I've stopped adjustments with params:
    [Kp = 0.169248, Ki = 0.00100723, Kd = 1.64468]

### The vehicle must successfully drive a lap around the track.
Yes, it does!

<iframe width="560" height="315" src="https://www.youtube.com/embed/mPFFiNDQxJM" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

