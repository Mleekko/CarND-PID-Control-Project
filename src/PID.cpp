#include <cmath>
#include <iostream>
#include <cfloat>
#include "PID.h"

using namespace std;

static const double INITIAL_TWIDDLE = 0.001;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
    errorP = 0.0;
    errorI = 0.0;
    errorD = 0.0;

    twiddleEnabled = true;
    dp = {Kp * INITIAL_TWIDDLE, Kd * INITIAL_TWIDDLE, Ki * INITIAL_TWIDDLE};
    sumErrors = 0;
    step = 1; // start at 1 to avoid premature error adjustment
    dpIdx = 0;
    phase = ADD;
    minError = DBL_MAX;
    twiddleSteps = 1000;

    tolerance = 0.000001;

//    multiplier = 1.15;
    multiplier = 1.05;
}

void PID::UpdateError(double cte) {
    errorP = cte;
    errorI += cte;

    errorD = cte - prev_cte;
    prev_cte = cte;

    int cycleDuration = twiddleSteps + 1;

    // update total error if this not the 1st step after adjustment
    if (step % cycleDuration > 1) {
        sumErrors += cte * cte;
    }

    if (twiddleEnabled && step % cycleDuration == 0) {
        sumErrors /= twiddleSteps;
        if (sumErrors < minError) {
            std::cout << "Found a better param! Err: " << sumErrors << std::endl;
            minError = sumErrors;
            if (initializedError) {
                dp[dpIdx] *= multiplier * multiplier;
                std::cout << "Adjusted param: dp[" << dpIdx << "]=" << dp[dpIdx] << std::endl;
            }
            initializedError = true;
            rotateParam();
        }
        if (phase == ADD) {
            adjustParam(dpIdx, dp[dpIdx]);
            phase = REMOVE;
        } else if (phase == REMOVE) {
            adjustParam(dpIdx, -2 * dp[dpIdx]);
            phase = ADJUST;
        } else {
            // set it back and penalize dp[i] for not improving
            adjustParam(dpIdx, dp[dpIdx]);
            dp[dpIdx] *= (2 - multiplier) * (2 - multiplier);
            std::cout << "Penalized param: dp[" << dpIdx << "]=" << dp[dpIdx] << std::endl;
            rotateParam();
        }
        sumErrors = 0;
        checkTolerance();

        // Execute addition after moving on to the next parameter
        if (phase == ADD) {
            adjustParam(dpIdx, dp[dpIdx]);
            phase = REMOVE;
        }
    }

    step++;
}

void PID::checkTolerance() const {
    double dp_sum = 0;
    for (int i = 0; i < 3; i++) {
        dp_sum += dp[i];
    }

    if (dp_sum < tolerance) {
        cout << "FINAL RESULT:" << endl;
        cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << endl;
        exit(0);
    }
}

void PID::rotateParam() {
    dpIdx = (dpIdx + 1) % 3;
    phase = ADD;
}

double PID::TotalError() {
    return -Kp * errorP - Ki * errorI - Kd * errorD;
}

double PID::getControlValue() {
    return TotalError();
}


void PID::adjustParam(int index, double amount) {
    if (index == 0) {
        Kp += amount;
    } else if (index == 1) {
        Ki += amount;
    } else if (index == 2) {
        Kd += amount;
    }

    std::cout << "dp[" << index << "]: " << amount << std::endl;
    std::cout << "dp: [" << dp[0] << ", " << dp[1] << ", " << dp[2] << "]" << std::endl;
    std::cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << std::endl;
}