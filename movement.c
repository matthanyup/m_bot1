/*	movement.c *
*	This is going to be written without any bugs 
*/

//#include "GPS/gps.h"

#define _BSD_SOURCE
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio.h"
#include "movement.h"

#define LEFT_BCK_GPIO 71
#define LEFT_FWD_GPIO 75
#define RIGHT_BCK_GPIO 73
#define RIGHT_FWD_GPIO 77

int fd;
int keepGoing = 1;

int gpioInit(){
	gpio_export(LEFT_FWD_GPIO);
	gpio_set_dir(LEFT_FWD_GPIO, 1);
	gpio_export(LEFT_BCK_GPIO);
	gpio_set_dir(LEFT_BCK_GPIO, 1);
	gpio_export(RIGHT_FWD_GPIO);
	gpio_set_dir(RIGHT_FWD_GPIO, 1);
	gpio_export(RIGHT_BCK_GPIO);
	gpio_set_dir(RIGHT_BCK_GPIO, 1);
}

int testTurn(){
	gpio_set_value(LEFT_FWD_GPIO, 1);
	gpio_set_value(RIGHT_FWD_GPIO,1);
	sleep(1);
	gpio_set_value(LEFT_FWD_GPIO, 0);
	gpio_set_value(RIGHT_FWD_GPIO,0);
	sleep(1);
	gpio_set_value(LEFT_BCK_GPIO, 1);
	gpio_set_value(RIGHT_FWD_GPIO,1);
	sleep(1);
	gpio_set_value(LEFT_BCK_GPIO, 0);
	gpio_set_value(RIGHT_FWD_GPIO,0);
	
}

float wrap180(float angle){
	if (angle > 180.0) angle -= 360.0;
	else if (angle < -180.0) angle += 360.0;
	return angle;
}


void signal_handler(int sig){
    printf( "Program Exited by User\n" );
	gpio_set_value(LEFT_FWD_GPIO, 0);
	gpio_set_value(LEFT_BCK_GPIO, 0);
	gpio_set_value(RIGHT_FWD_GPIO, 0);
	gpio_set_value(RIGHT_BCK_GPIO, 0);
	keepGoing = 0;
}

void moveForward(int useconds){
	gpio_set_value(LEFT_FWD_GPIO, 1);
    gpio_set_value(LEFT_BCK_GPIO, 0);
    gpio_set_value(RIGHT_FWD_GPIO, 1);
    gpio_set_value(RIGHT_BCK_GPIO, 0);
	usleep(useconds);
	gpio_set_value(LEFT_FWD_GPIO, 0);
    gpio_set_value(LEFT_BCK_GPIO, 0);
    gpio_set_value(RIGHT_FWD_GPIO, 0);
    gpio_set_value(RIGHT_BCK_GPIO, 0);
}


int main(){
	signal(SIGINT, signal_handler);

	gpioInit();
	moveForward(10);
	sleep(2);
	testTurn();
	moveForward(10);
}


