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

#define PWM_LED "0"
#define RED_LED "17"
#define I2C_ADDR 0x48
#define I2C_DEVICE "i2c-1"

int main(int argc, char** argv)
{
	I2CHandler i2cHandler(I2C_ADDR, I2C_DEVICE);
	i2cHandler.Initialize();

	uint8_t buf[2];
	buf[0] = 0x01;
	i2cHandler.Write(buf, 1);
	i2cHandler.Read(buf, 2);
	printf("Buffer values: 0x%02X%02X\n", buf[0], buf[1]);
	return 0;
}
