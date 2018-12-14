/*
 * Filename: LineSensor.h
 * Author: Marquez Jones
 * Desc: This contains drivers necessary to interface the MSP432 launchpad with the
 * Line Sensor board
 *
 * Hardware Notes: The line sensor is attached for Port 7 pins 7 to 0.
 * Pin 7 - far right
 * Pin 0 - far left
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

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

#endif /* LINESENSOR_H_ */
