//REMEMBER TO RUN AS SUDO!!!!!
//MCP4725 C program
//by Lewis Loflin
//Modded by D.Vest
//
// by Lewis Loflin lewis@bvu.net
// www.bristolwatch.com
// http://www.bristolwatch.com/rpi/ads1115.html

#include <stdio.h>
#include <sys/types.h> 		// open
#include <sys/stat.h>  		// open
#include <fcntl.h>     		// open
#include <string.h>		//for atoi()
#include <unistd.h>    		// read/write usleep
#include <stdlib.h>    		// exit
#include <inttypes.h>  		// uint8_t, etc
#include <linux/i2c-dev.h> 	// I2C bus definitions
#include <sys/ioctl.h>


int main(int argc, char *argv[])
{

	int fd;						//file descriptor
	int mcp4725_addr = 0x60;	//MCP4725 defaults to 0x60
	int16_t val;				//16 bit integer exactly
	int count = 0;				//loop counter
	char buffer[15];			//input value for DAC

	//Only 3 8-bit buffers needed for MCP4715
	//1 control byte, 2 data bytes (MSB, LSB)
	uint8_t writeBuf[3];

  	// open device on /dev/i2c-1 
  	// Raspberry Pi really only has 1 i2c bus
  	//same first step for all i2c devices
  	if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
    		printf("Error: Couldn't open device! %d\n", fd);
    		printf("Are you running this as SUDO?\n");
    		exit (1);
  	}

  	// connect to mcp4725 as i2c slave
  	if (ioctl(fd, I2C_SLAVE, mcp4725_addr) < 0) {
    		printf("Error: Couldn't find device on address!\n");
    		exit (1);
  	}


  	//page 18-19 of data sheets
  	writeBuf[0] = 0x40;    // control byte
  	// bits 7-5; 010 write DAC; 011 write DAC and EEPROM
  	// bits 4-3; unused
  	// bits 2-1; PD1, PD--PWR down P19, 00 is normal
  	// bit -; unused
	// from Adafruit: regular=0x40, EEPROM = 0x60

  	writeBuf[1] = 0; // HIGH data(MSB)
  	writeBuf[2] = 0; // LOW data(LSB)
  	// bits 7-0; Databits D11 - D4 (12-bit number)
  	//                             (spans two bytes)
  	// These are pre-assignments.  Actual to come later.

   	// #2
   	// bits 7-4; Databits D3-D0
   	// bits 3-0 unused

	if(argc == 2){
	
		if(atoi(argv[1]) > 4096)
		{
			val = 4096;
		}
		else if(atoi(argv[1]) < 0)
		{
			val = 0;
		}
		else
		{
			val = atoi(argv[1]);
		}
		//write the number (two bytes) to DAC
		writeBuf[1] = val >> 4; //MSB shifted right 4 places
		writeBuf[2] = val << 4; //LSB shifted left 4 places
		//Write to MCP4725 device
		if (write(fd, writeBuf, 3) != 3) {
			perror("Write to register failed.");
			exit(1);
		}


	}
	else
	{
		while(count < 4096){

    		val=count;
    		//write the number (two bytes) to DAC
			writeBuf[1] = val >> 4; //MSB shifted right 4 places
			writeBuf[2] = val << 4; //LSB shifted left 4 places
		
			//Write to MCP4725 device
			if (write(fd, writeBuf, 3) != 3) {
				perror("Write to register failed.");
				exit(1);
			}

			count += 100;
			printf("%d   %d   %d\n", val,writeBuf[1],writeBuf[2]);
			sleep(2);
	 	}
	}	 
	return 0;
}
