#ifndef PID_H
#define PID_H

#include <vector>

enum TwiddlePhase { ADD, REMOVE, ADJUST };

class PID {
public:

    /**
     * Constructor
     */
    PID();

    /**
     * Destructor.
     */
    virtual ~PID();

    /**
     * Initialize PID.
     * @param (Kp_, Ki_, Kd_) The initial PID coefficients
     */
    void Init(double Kp_, double Ki_, double Kd_);

    /**
     * Update the PID error variables given cross track error.
     * @param cte The current cross track error
     */
    void UpdateError(double cte);

    /**
     * Calculate the total PID error.
     * @output The total PID error
     */
    double TotalError();

    /**
     * Returns the target value of the control for PID
     */
    double getControlValue();

    /**
     * Adjusts param during twiddle
     */
    void adjustParam(int index, double amount);

private:
    /**
     * PID Errors
     */
    double errorP;
    double errorI;
    double errorD;

    double prev_cte; // holds cte val from the previous step

    /**
     * PID Coefficients
     */
    double Kp;
    double Ki;
    double Kd;

    /**
    * twiddling parameters
    */
    std::vector<double> dp;
    int twiddleSteps;
    double tolerance;
    double multiplier;

    int step;
    int dpIdx;

    double sumErrors, minError;
    bool twiddleEnabled;
    bool initializedError;
    TwiddlePhase phase;

    void rotateParam();
    void checkTolerance() const;
};

#endif  // PID_H