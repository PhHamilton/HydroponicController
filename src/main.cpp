#include <stdint.h>
#include "gpio.h"
#include "pwm.h"

#define PWM_LED "0"
#define RED_LED "17"

int main(int argc, char** argv)
{
	PWMOutput PwmOutputLed(PWM_LED);
	PwmOutputLed.SetPeriod("1000000000");
	PwmOutputLed.Enable();
	PwmOutputLed.SetDutyCycle(50);
	
	GPIO RedOutputLed(RED_LED);
	RedOutputLed.Set(OUTPUT);
	for(int i = 0; i < 10000000; i++);	
	RedOutputLed.TurnOff();

	uint8_t nBlinks = 15;
	for(int i = 0; i < nBlinks; i++)
	{
		for(int i = 0; i < 10000000; i++);	
		RedOutputLed.Toggle();
	}

	for(int i = 0; i < 10000000; i++);	

	RedOutputLed.TurnOff();
	PwmOutputLed.Disable();

	return 0;
}
