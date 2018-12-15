/*
 * Filename: LineSensor.h
 * Author: Marquez Jones
 * Desc: This contains drivers necessary to interface the MSP432 launchpad with the
 * Line Sensor board
 *
 * Hardware Notes: The line sensor is attached for Port 7 pins 7 to 0.
 * Pin 7 - far left
 * Pin 0 - far right
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

//defines

/*
 * line_position function should never return a value between 0 and 47 if a line exists
 * if the function returns 0x01, the machine is no longer on the line and
 * student should create proper measures to either navigate without the
 * line or find the line
 */
#define NO_LINE_ERROR 0x01
#define YEET 0x59454554

/* Desc: Initializes pins in use of the line sensor
 * Port 7:
 * All pins initialized as I/O and inputs
 *
 * Port 5:
 * Pin 3 initialized as I/O and set to output
 * Pin set low(turns off IR LED)
 *
 * Inputs: None
 * Outputs: None
 * Assumptions: None
 */
void line_sensor_init(void);

/* Desc: Reads line sensor
 * TI use instructions(from 6.4.3)
 *   1) Set P5.3 high (turn on IR LED)
 *   2) Make P7.7 – P7.0 outputs, and set them high (charging 8 capacitors)
 *   3)Wait 10 us, Clock_Delay1us(10);
 *   4) Make P7.7 – P7.0 input
 *   5)Wait time us, Clock_Delay1us(time);
 *   6) Read P7.7 – P7.0 inputs (converts voltages into binary)
 *   7) Set P5.3 low (turn off IR LED, saving power)
 *   8) Return 8-bit binary measured in step 6
 * Inputs: None
 * Outputs: sensor status as an 8 bit value
 * Assumptions: That line_sensor_init() was called
 */
uint8_t line_read(void);

/*
 * Desc: outputs a distance(in 0.1mm) between center of robot and line
 *       if the line is not within range of the, the function will output an
 *       error code
 *
 * Hardware Notes:
 * Assuming the robot is constructed with P7.7 being far left
 * and P7.0 being on the far right,
 *
 * A negative value should mean the line is on the left side of the robot
 * while a positive value means the line is right of the robot's center
 *
 * Inputs: data from line read
 * Outputs: signed distance from center or error if no line
 */
int32_t line_position(uint8_t data);

#endif /* LINESENSOR_H_ */
