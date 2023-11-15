/*#include <stdint.h>
#include "gpio.h"
#include "pwm.h"
#include "i2cHandler.h"
*/
#include "i2cHandler.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "ads1015.h"
#define PWM_LED "0"
#define RED_LED "17"
#define I2C_ADDR 0x48
#define I2C_DEVICE "i2c-1"

int main(int argc, char** argv)
{
	ADS1015 ads1015(I2C_ADDR, I2C_DEVICE);

	while(1)
	{
        uint16_t val = ads1015.Read(0);
		printf("Read value: %i, Voltage: %f\n", val, (float)val * 3 / 1000.0);
		usleep(500000);
	}

	return 0;
}
