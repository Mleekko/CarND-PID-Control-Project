//
// Created by Mleekko on 2020-03-16.
//

#ifndef PID_STEERINGWHEEL_H
#define PID_STEERINGWHEEL_H


class SteeringWheel {
    private:
        double angle = 0.;
    public:
        double turnTo(double desiredAngle);

    void reset();
};


#endif //PID_STEERINGWHEEL_H
