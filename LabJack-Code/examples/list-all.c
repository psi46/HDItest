//------------------------------------------------------------------------
//  Author: LabJack
//  11/07/2011
//  This example demonstrates how to use listAll function in the ljacklm
//  library.  The function is documented in section 4.22 of the U12 User's Guide
//  or in the ljacklm.h header file.
//------------------------------------------------------------------------
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

int main(int argc, char *argv[])
{
	long errorcode = 0;
	long productIDList[127] = {0};  //Returned list of product IDs   U12 product ID = 1
	long serialnumList[127] = {0};  //Returned list of serial numbers
	long localIDList[127] = {0};  //Returned list of local IDs
	long powerList[127] = {0};  //Retturned list of power allowances
	long calMatrix[127][20] = {{0}};  //Returned list of calibration constants
	long numberFound = 0;  //Returned number of found devices
	long reserved1 = 0, reserved2 = 0;
	int i = 0, j = 0;

	errorcode = ListAll(productIDList, serialnumList, localIDList, powerList, calMatrix, &numberFound, &reserved1, &reserved2);
	handleError(errorcode, "ListAll");

	printf("\nListAll found %ld U12s.\n ", numberFound);
	printf("\nDevice information: \n\n");
	printf("Product ID, Serial Number, LocalID, Power Allowance, Calibration Constants\n");

	for(i = 0; i < numberFound; i++)
	{
		printf("%ld, %ld, %ld, %ld, { ", productIDList[i], serialnumList[i], localIDList[i], powerList[i]);
		for(j = 0; j < 20; j++)
		{
			printf("%ld ", calMatrix[i][j]);
		}
		printf("}\n\n");

	}
	return 0;
}
