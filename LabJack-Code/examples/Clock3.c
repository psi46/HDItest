//------------------------------------------------------------------------
//  Author: LabJack
//  11/10/2011
//  This example demonstrates how to use the U12 DigitalIO function in the 
//  ljacklm library.  The function is documented in section 4.17 in the U12
//  User's Guide or in the ljacklm.h header file.  For EDigitalIn and
//  EDigitalOut examples look at the easyFunctions.c example.
//------------------------------------------------------------------------
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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

int main (int argc, char *argv[])
{
	float version = 0.0;
	long errorcode;

	long idnum = -1;  //Using first found U12
	long demo = 0;  //Normal operations
	long trisD = 0;  //Directions for D0-D15
	long trisIO = 0;  //Directions for IO0-IO3
	long stateD = 0;  //Output states for D0-D15
	long stateIO = 0;  //Output states for IO0-IO3
	long updateDigital = 0;  //Indicates is tris states will be written
	long outputD = 0;  //Returns of the output registers for D0-D15
	long outputIO = 0;  //Output states of IO0-IO3.  Cannot be read.


	version = GetDriverVersion();
	printf("Driver version: %.3f\n", version);

	version = GetFirmwareVersion(&idnum);
	printf("U12 Firmware version: %.3f\n\n", version);

	/* Setting and reading directions and states */
	trisD = (long)0x4800;  //Setting D0-7 to outputs, D8-15 to inputs (b0000000011111111)
	trisIO = (long)0x0;  //Setting IO0-1 to outputs, IO2-3 to inputs (b0011)
	stateD = (long)0x4800;  //Setting D0-3 to low. D4-7 to high (b0000000011110000)
	stateIO = (long)0x0;  //Setting IO0 to low. IO1 to high (b0010)
	outputIO = trisIO & stateIO;
	updateDigital = 1;  //Updating D and IO lines
	errorcode = DigitalIO(&idnum, demo, &trisD, trisIO, &stateD, &stateIO,
				updateDigital, &outputD);
	handleError(errorcode, "DigitalIO (update)");

	printf("DigitalIO, updating lines\n");
	printf("D directions (read) = 0x%.4lx, states (read) = 0x%.4lx, output registers (read) = 0x%.4lx\n", trisD, stateD, outputD);
	printf("IO directions (set) = 0x%lx, states (read) = 0x%lx, output (set) = 0x%lx\n\n", trisIO, stateIO, outputIO);

	/* Only reading current directions (D lines only) and states */
	trisD = 0;
	trisIO = 0;
	stateD = 0;
	stateIO = 0;
	updateDigital = 0;  //Only read performed
	errorcode = DigitalIO(&idnum, demo, &trisD, trisIO, &stateD, &stateIO,
				updateDigital, &outputD);
	handleError(errorcode, "DigitalIO (read)");

	printf("DigitalIO read only:\n");
	printf("D directions = 0x%.4lx, states = 0x%.4lx, output registers = 0x%.4lx\n", trisD, stateD, outputD);
	printf("IO states = 0x%lx\n", stateIO);

	return 0;
}
