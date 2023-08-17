#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


#define MAX_LINES 50
#define MAX_LEN 100



// function main begins program execution
int main(void) {

	FILE* inFilePtr; // pointer to input file
	FILE* outFilePtr; // pointer to output file
	char inputFileName[30] = "";
	char outputFileName[30] = "";
	int linecount = 0;
	char timestampArr[MAX_LINES][MAX_LEN];
	char hold[MAX_LEN]; //temporary char used to swap array elements

	// sorting variables 
	char day[3]; 
	char mon[3]; 
	char year[5]; 
	char time[10];

	// sorted array
	char sortedTimestamps[MAX_LINES][MAX_LEN];


	// 1.Prompt the user for the names of the input and output files and store for later use.If the input file does not exist, display an error messageand re - prompt.

		// prompt for name of input file. if file not found - repprompt
	while (1)
	{
		printf("Enter the name of the input file: ");
		scanf("%s", inputFileName);  // annoying warning, still works
		inFilePtr = fopen(inputFileName, "r");
		if (inFilePtr == NULL)
		{
			printf("File does not exist. Please try again.\n");
		}
		else
		{
			break;
		}
	}

	// prompt for name of output file
	printf("Enter the name of the output file (dont forget to add .txt): ");
	scanf("%s", outputFileName);


	// 2. Read in the series of strings from the text file and store these in an array of strings.

	while (!feof(inFilePtr) && !ferror(inFilePtr)) {
		if (fgets(timestampArr[linecount], MAX_LEN, inFilePtr) != NULL)
			linecount++;
	}

	fclose(inFilePtr);
	printf("Total lines %d\n", linecount); 

	// prints out data in array
	printf("\n");
	printf("Raw Data from File\n");
	for (int i = 0; i < linecount; i++) {
		printf("%s", timestampArr[i]);
	}




	//Change timestamps to year/mon/day-time format
	for (int i = 0; i < MAX_LINES; i++)
	{
		sscanf(timestampArr[i], "%2s/%2s/%4s-%8s", day, mon, year, time); 

		sprintf(sortedTimestamps[i], "%4s/%2s/%2s-%8s", year, mon, day, time);


		
	}


	// Print sorted timestamps.
	printf("\n");
	printf("\nSorted Data:\n");

	for (int i = 0; i < MAX_LINES; i++)
	{
		printf("%s\n", sortedTimestamps[i]);
		
	}


	// 3. Sort the array alphabetically using the bubble sort algorithm.

		// loop to control number of passes
	for (int pass = 1; pass <= MAX_LINES; pass++) {

		// loop to control number of comparisons per pass //
		for (int i = 0; i < MAX_LINES - pass; i++) {

			/* compare adjacent elements and swap them if first
			element is greater than second element */
			if (strcmp(sortedTimestamps[i], sortedTimestamps[i + 1]) > 0) {
				strcpy(hold, sortedTimestamps[i]);
				strcpy(sortedTimestamps[i], sortedTimestamps[i + 1]);
				strcpy(sortedTimestamps[i + 1], hold);
			} // end if //
		} // end inner for //
	} // end outer for //


	// print the data in chronological order
	printf("\nSorted Data in Chronological Order:\n");

	for (int i = 0; i < MAX_LINES; i++)
	{

		printf("%s\n", sortedTimestamps[i]);

	}



	// 4. Write the sorted array to the output file

	   /* fopen opens file. Exit program if unable to create file  */
	if ((outFilePtr = fopen(outputFileName, "w")) == NULL) {
		printf("File could not be opened\n");
	} /* end if */
	else {




		for (int i = 0; i < MAX_LINES; i++) {
			// fprintf prints to file
			fprintf(outFilePtr, sortedTimestamps[i], "%4s/%2s/%2s-%8s", year, mon, day, time);
			fprintf(outFilePtr, "\n");
		}


		fclose(outFilePtr); /* fclose closes file */
	} /* end else */


	return 0;
}