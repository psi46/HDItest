//------------------------------------------------------------------------
//  Author: LabJack
//  11/10/2011
//  This example demonstrates how to use the U12 easy functions in the 
//  ljacklm library.
//
//  The functions used are EAnalogIn, EAnalogOut, ECount, EDigitalIn and
//  EDigitalOut, which are documented in sections 4.1 - 4.5 in the U12 User's
//  Guide or in the ljacklm.h header file.
//------------------------------------------------------------------------
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ljacklm.h"

void handleError(long error, char *functionName)
{
	char errorString[50];

	if(error)
	{
		GetErrorString(error, errorString);
		printf("%s error %ld: %s\n", functionName, error, errorString);
		exit(1);
	}
}

long GetTickCount ()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main (int argc, char *argv[])
{
	char fStr[50];
	float version = 0.0;
	long error = 0;
	int i = 0;

	long idnum = -1;  //Using first found U12
	long demo = 0;  //Normal operations
	long channel = 0;  //Channel to be read/set.  Used by multiple functions.
	long state = 0;  //Digital states to set or states read.  Used by digital functions.

	//EAnalogOut specific parameters
	float analogOut0 = 2.0, analogOut1 = 3.5;  //Voltages of AO0 and AO1 to set

	//EAnalogIn specific parameters
	long gain = 0;  //G=1, +-20 V (gain 0 = 1)
	long overVoltage = 0;  //Returns >0 if overvoltage is detected
	float voltage = 0.0;  //Returns the voltage reading

	//EDigitalOut specific paramters
	long writeD = 0;  //Indicates if D line is to be written instead of IO line

	//EDigitalIn specific paramters
	long readD = 0;  //Indicates if D line is read instead of IO line

	//ECount specific parameters
	long resetCounter = 0;  //Indicates if counter is reset to zero after read
	double count = 0;  //Current count before reset
	double ms = 0;  //Returns the number of milliseconds since the Epoch.


	version = GetDriverVersion();
	printf("Driver version: %.3f\n", version);

	version = GetFirmwareVersion(&idnum);
	printf("U12 Firmware version: %.3f\n\n", version);


	/* Setting analog outputs */
	printf("Setting AO0 to %.3f V and AO1 to %.3f V.\n\n", analogOut0, analogOut1);

	error = EAnalogOut(&idnum, demo, 2.0, 3.5);
	handleError(error, "EAnalogOut");

	/* Reading analog inputs */
	printf("Reading some analog inputs:\n");

	/* Reading from single-ended AI0 and AI1 */
	for(i = 0; i < 2; i++)
	{
		channel = i;
		error = EAnalogIn(&idnum, demo, channel, gain, &overVoltage, &voltage);
		sprintf(fStr, "EAnalogIn (%ld)", channel);
		handleError(error, fStr);

		printf("Single-ended AI%ld = %.3f V, overVoltage = %ld\n", channel, voltage, overVoltage);
	}
	printf("\n");

	/* Reading from differential AI0-AI1 (channel 8) and AI2-AI3 (channel 9), G=1 (+-20 V) */
	for(i = 8; i < 10; i+=1)
	{
		channel = i;
		error = EAnalogIn(&idnum, demo, channel, gain, &overVoltage, &voltage);
		sprintf(fStr, "EAnalogIn (%ld) diff.", channel);
		handleError(error, fStr);

		printf("Differential AI%ld-AI%ld = %.3f V, overVoltage = %ld\n", (channel-8)*2, (channel-8)*2+1, voltage, overVoltage);
	}


	/* Setting digital outputs */
	printf("\nSetting digital lines IO1 and D1 to output-low, and IO2 to output-high\n\n");	

	channel = 1;
	writeD = 0;
	state = 0;
	error = EDigitalOut(&idnum, demo, channel, writeD, state);
	handleError(error, "EDigitalOut (IO1)");

	channel = 1;
	writeD = 1;
	state = 0;
	error = EDigitalOut(&idnum, demo, channel, writeD, state);
	handleError(error, "EDigitalOut (D1)");

	channel = 2;
	writeD = 0;
	state = 1;
	error = EDigitalOut(&idnum, demo, channel, writeD, state);
	handleError(error, "EDigitalOut (IO2)");


	/* Reading digital inputs */
	printf("Reading some digital inputs:\n");

	channel = 0;
	readD = 0;
	error = EDigitalIn(&idnum, demo, channel, readD, &state);
	handleError(error, "EDigitalIn (IO0)");
	printf("IO%ld state = %ld\n", channel, state);

	channel = 0;
	readD = 1;
	error = EDigitalIn(&idnum, demo, channel, readD, &state);
	handleError(error, "EDigitalIn (D0)");
	printf("D%ld state = %ld\n\n", channel, state);


	/* Read from the Counter */

	//Reseting counter first
	printf("Reading Counter:\nResetting count and waiting 2 seconds for new data.\n");

	resetCounter = 1;
	error = ECount(&idnum, demo, resetCounter, &count, &ms);
	handleError(error, "ECount (reset)");

	//Wait for 2 seconds for data
	usleep(2000000);

	//Read Counter reading with 2 second timer
	resetCounter = 0;
	error = ECount(&idnum, demo, resetCounter, &count, &ms);
	handleError(error, "ECount (read)");

	printf("Count = %.0f, OS timer = %0.3f ms\n", count, ms);

	return 0;
}
