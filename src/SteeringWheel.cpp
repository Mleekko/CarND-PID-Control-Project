//
// Created by Mleekko on 2020-03-16.
//

#include <cmath>
#include "SteeringWheel.h"

using namespace std;

double SteeringWheel::turnTo(double desiredAngle) {
//    double diff = desiredAngle - angle;

//    double step = (pow(1 + abs(diff), 2) - 1) / 3 * diff;
//    angle += step;

    angle = desiredAngle;

    if (angle > 1.0) {
        angle = 1.0;
    } else if (angle < -1.0) {
        angle = -1.0;
    } else if (abs(angle) < 0.0001) {
        angle = 0; // avoid wiggling
    }

    return angle;
}

void SteeringWheel::reset() {
    angle = 0;
}
