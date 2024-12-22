#ifndef FANCONTROL_H
#define FANCONTROL_H

class FanController
{
public:
    FanController(int fanPin);
    void controlFan(float temperature);

private:
    int fanPin;
};

#endif