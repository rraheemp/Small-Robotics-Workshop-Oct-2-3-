#include <Arduino.h>
#define Stating_SPEED 50

class M_Profile
{
    int MotorSpeedValue = Stating_SPEED;

public:
    int GetSpeedValue()
    {
        return MotorSpeedValue;
    }
    void SetSpeedValueHigher()
    {
        MotorSpeedValue += 1;
        if(GetSpeedValue() >= 200){
            MotorSpeedValue = 200;
        }
    }
    void SetSpeedValueLower()
    {
        MotorSpeedValue -= 1;
        if(GetSpeedValue() <= 50){
            MotorSpeedValue = 50;
        }
    }
};
