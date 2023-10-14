#include "gpio.h"

#define GREEN_LED "32"

int main(int argc, char** argv)
{
	GPIO GreenOutputLed(GREEN_LED);
	
	GreenOutputLed.Set(INPUT);

	return 0;
}
