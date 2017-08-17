/*
 * @file MoveBall.cpp
 * @brief Send the position the ball to the Arduino
 * Used with the Arduino programm : feedback
 * @date august 2014
 * @version 1
 */ 

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sys/time.h>
#include <math.h> 
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "raspivid.h"
#include "Ppm.h"
#include "Ball.h"
#include "StartData.h"
using namespace std;


/*
unsigned long getmsofday() {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return (long long)tv.tv_sec*1000 + tv.tv_usec/1000;
}*/
 
// The PiWeather board i2c address
#define ADDRESS 0x04
 
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
 

int main() {
 
	// Initialization
	printf("I2C: Connecting\n");
	int file;
	if ((file = open(devName, O_RDWR)) < 0) {
		fprintf(stderr, "I2C: Failed to access %d\n", devName);
		exit(1);
	}
	printf("I2C: acquiring buss to 0x%x\n", ADDRESS);
	if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
		fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
		exit(1);
	}
	//Programm
	struct BUF b;
        b.WIDTH = 320;
        b.HEIGHT = 240;
        b.BUFFER = (unsigned char *)malloc(b.HEIGHT*b.WIDTH);
	struct POS pos;

	//Video initialization
     
	RaspiVid v("/dev/video0", b.WIDTH, b.HEIGHT);
	if (!v.initialize(RaspiVid::METHOD_MMAP)) {
		cout << "Unable to initialize!\n";
		return -1;
	}

	//Get images
	long start = getmsofday();
	v.startCapturing();

	ofstream myfile;
	myfile.open("xy.txt");
	
	long nmoinsun=getmsofday();
	while(true) {
		nmoinsun=getmsofday();
		VideoBuffer buffer = v.grabFrame();
  		memcpy(b.BUFFER, buffer.data(), b.WIDTH*b.HEIGHT);
		
  		pos = getPosBall(b);
		myfile << pos.X << "," << pos.Y << endl;

		//Transmission to Arduino
		int position = pos.X;
		unsigned char cmd[16];
		printf("Sending %d\n", position);
		cmd[0] = position;
		if (write(file, cmd, 1) == 1) {
			usleep(30000);
			char buf[1];
			if (read(file, buf, 1) == 1) {
				int temp = (int) buf[0];
				printf("Received %d\n", temp);
			}
		}
	}
	
	// Now wait else you could crash the arduino by sending requests too fast
	usleep(10000);
	return (EXIT_SUCCESS);
}

