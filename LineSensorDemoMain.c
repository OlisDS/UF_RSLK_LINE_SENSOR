/*
 * Author: Marquez Jones
 * Project: Module 6 Line Sensor Read Demo
 * Desc: This demo will read from the line sensor and output the results
 * to an LED array
 *
 * Hardware Notes: By TI instructions the light sensor is on port 7
 * which is what the students will use in the final robot design.
 *
 * For LEDs, they are split between port 10 and port Port 6
 * P10.0 - P10.5 will correlate to pins 0 - 5 of the sensor inputs
 * P6.0 - P6.1 will correlate to pins 6-7 of the sensor
 */


/*********************************INCLUDES***********************************/

//From CCS
#include "msp.h"

//From TI Robotics kit
#include "Clock.h"

//Written by UF TAs
#include "LineSensor.h"

/*********************************INCLUDES***********************************/

#define LED_PORT10_BM 0x3F;
#define LED_PORT6_BM 0x03;

/***********************FUNCTION PROTOTYPES***********************************/

// sets all pins on port 4 to output
void led_init(void);

//writes 8 bit value to LEDs on port 4
void led_write(uint8_t data);

/***********************************MAIN**************************************/

void main(void)
{
    //variables
    uint8_t line_state; //results from line sensor read

	//initialize clock
	Clock_Init48MHz();

	//initialize line sensor
	line_sensor_init();

	//initialize LED pins
	led_init();



	while(1){

	    //continually read sensor and output results

	    //read sensor
	    line_state = line_read();

	    //output result to LED
	    led_write(line_state);

	}

}

/***********************FUNCTION PROTOTYPES***********************************/

/*
 * Desc: Initialize LEDs on launchpad
 * P10.0 - P10.5 set to outputs
 * P6.0 - 6.1 set to outputs
 *
 * Note: These pins were selected to avoid
 *       interferring with other used pins on
 *       the robot
 */
void led_init(void){

    // set pins 0 to 5 on port 10 as IO
    P10->SEL0 &= 0xC0;
    P10->SEL1 &= 0xC0;

    // set pins 0 and 1 on port 6 to IO
    P6->SEL0 &= 0xFC;
    P6->SEL1 &= 0xFC;

    //set pins as output
    P10->DIR |= 0x3F;
    P6->DIR |= 0x03;

    //initialize LEDs as off
    P10->OUT &= 0x00;
    P6->OUT &= 0x00;
}

//writes 8 bit value to LEDs on port 4
void led_write(uint8_t data){

    //set LED outputs to line results
    /*
     * with the sensor convention of 0 = white and 1 = black
     * on LEDs will represent bits that are on the line
     */
    P10->OUT = data & LED_PORT10_BM;

    //only use high bits for port 6
    P6->OUT = (data >> 6) & LED_PORT6_BM;

}
