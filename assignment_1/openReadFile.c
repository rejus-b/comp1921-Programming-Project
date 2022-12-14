/* library for I/O routines					*/
#include <stdio.h>

/* library for memory routines 				*/
#include <stdlib.h>

/* header for including string operations	 */
#include <string.h>

/* header for pgm structures 				*/
#include "pgmStruct.h"

/* header for reading the error code		 */
#include "errors.h"

/* header for openReadFile macros			 */
#include "openReadFile.h"

int readFile(char *fileName, pgm *pgmStruct)
{ /* openReadFile()		*/

	/* now start reading in the data */
	/* try to open the file for text I/O */
	/* in ASCII mode b/c the header is text */
	FILE *inputFile = fopen(fileName, "r");
	/* if it fails, return error code */
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name (%s)", fileName);
		exit(EXIT_BAD_INPUT_FILE);
	}

	/* read in the magic number	*/
	pgmStruct->magic_number[0] = getc(inputFile);
	pgmStruct->magic_number[1] = getc(inputFile);
	pgmStruct->magic_Number = (unsigned short *) pgmStruct->magic_number;
	
	/* checks that the magic number is valid */
	magicNumCheck(pgmStruct->magic_Number, inputFile, fileName);
	
	/* scan whitespace if present */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line	*/
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
		{ /* comment line */
		/* allocate buffer */
		pgmStruct->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH + 2);
		/* fgets() reads a line	*/
		/* capture return value	*/
		char *commentString = fgets(pgmStruct->commentLine, MAX_COMMENT_LINE_LENGTH + 2, inputFile);
		/* NULL means failure */
		if (commentString == NULL || strlen(commentString) > 128)
			{ /* NULL comment read */
			/* free memory	*/
			free(pgmStruct->commentLine);
			/* close file */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Bad Comment Line (%s)", fileName);	
		
			/* and return */
			exit(EXIT_BAD_COMMENT_LINE);
			} /* NULL comment read */
		} /* comment line */
	else
	{ 	
		/* not a comment line */
		/* put character back */
		ungetc(nextChar, inputFile);
	} /* not a comment line */


	/* read in width, height, maxGray */
	/* whitespace to skip blanks */
	scanCount = fscanf(inputFile, " %u %u %u ", &(pgmStruct->width), &(pgmStruct->height), &(pgmStruct->maxGray));

	if 	(
		(scanCount != 3		)	||
		(pgmStruct->width 	< MIN_IMAGE_DIMENSION	) 	||
		(pgmStruct->width 	> MAX_IMAGE_DIMENSION	) 	||
		(pgmStruct->height < MIN_IMAGE_DIMENSION	) 	||
		(pgmStruct->height > MAX_IMAGE_DIMENSION	)		
		)
		{ /* failed size sanity check */
		/* free up the memory */
		free(pgmStruct->commentLine);

		/* be tidy: close file pointer */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)", fileName);	
		
		/* and return */
		exit(EXIT_BAD_DIMENSIONS);
		} /* failed size sanity check */

	if (pgmStruct->maxGray != 255)
	{ /* failed maxGray sanity check */
		/* free up the memory */
		free(pgmStruct->commentLine);

		/* be tidy: close file pointer */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value (%s)", fileName);	
		
		/* and return */
		exit(EXIT_BAD_MAX_GRAY_VALUE);
		} /* failed maxGray sanity check */
	

	/* mallocing for a 2D array, malloc a 1D array first, then malloc arrays into this array */
	pgmStruct->imageData = (unsigned char **) malloc(pgmStruct->height * sizeof(unsigned char*));
	for (int row = 0; row < pgmStruct->width; row++)
	{
		pgmStruct->imageData[row] = (unsigned char *) malloc (pgmStruct->width * sizeof(unsigned char));
	}

	/* sanity check for memory allocation */
	imageMallocCheck(inputFile, pgmStruct);

	if (pgmStruct->magic_number[1] == '2')
	{	
		/* this is used to check what piece of data we are on, and more specifically when we reach the end */
		int EOFCount = 0;
		for (int row = 0; row < pgmStruct->height; row++)
		{		
			for (int col = 0; col < pgmStruct->width; col++)
			{	
				EOFCount ++;		
				/* read next value */
				int grayValue = -1;
				int scanCount = fscanf(inputFile, " %u", &grayValue);

				/* sanity check too little data	or too much data. The first comparison is for too little the second compare is for too much */
				if ((scanCount > (pgmStruct->width*pgmStruct->height)) || ((EOFCount == (pgmStruct->height * pgmStruct->width)) && (((fscanf(inputFile, " %u", &grayValue)) != -1))))
				{
					/* free memory	*/
					free(pgmStruct->commentLine);

					/* print error message */
					printf("ERROR: Bad Data (%s)", fileName);

					/* exit with error code */
					exit(EXIT_BAD_DATA);
				}


				/* sanity check	*/
				if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
					{ /* fscanf failed */
					/* free memory	*/
					free(pgmStruct->commentLine);

					/* close file */
					fclose(inputFile);

					/* print error message */
					printf("ERROR: Bad Gray Value");	
				
					/* and return */
					return EXIT_MISCELLANEOUS;
					} /* fscanf failed */

				/* set the pixel value */
				pgmStruct->imageData[row][col] = (unsigned char) grayValue;
			}
		}
	}

	/* if the magic number is binary read in binary data */
	else if (pgmStruct->magic_number[1] == '5'){
		/* loop through the image data to be fread, reading in a row at a time */
		for (int row = 0; row < pgmStruct->height; row++)
		{
			/* this tests for too little data */
			if (fread(pgmStruct->imageData[row], sizeof(unsigned char), pgmStruct->width, inputFile) == 0)
			{
				free(pgmStruct->commentLine);
		
				/* close file */
				fclose(inputFile);
		
				/* print error message */
				printf("ERROR: Bad Data (%s)", fileName);
			
				/* exit with error code */
				exit(EXIT_BAD_DATA);
			}
		}
	}

	/* we're done with the file, so close it  and return*/
	fclose(inputFile);
	return EXIT_NO_ERRORS;

} /* openReadFile()		*/

int magicNumCheck(unsigned short *magic_Number, FILE *inputFile, char *fileName)
{ /* magicNumCheck()	*/
	/* sanity check on the magic number */
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM && *magic_Number != MAGIC_NUMBER_RAW_PGM)
		{ /* failed magic number check */
		/* be tidy: close the file */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fileName);	
		
		/* and return */
		exit(EXIT_BAD_MAGIC_NUMBER);
	} /* failed magic number check */

	return EXIT_NO_ERRORS;
} /* magicNumCheck()	 */

int imageMallocCheck(FILE *inputFile, pgm *pgmStruct)
{	/* imageMallocCheck()	 */
	/* sanity check for memory allocation */
	for (int row = 0; row < pgmStruct->height; row++)
	{
		for (int col = 0; col < pgmStruct->width; col++)
		{
			if (&pgmStruct->imageData[row][col] == NULL)	
			{ /* malloc failed */
			/* free up memory */
			free(pgmStruct->commentLine);

			/* close file pointer */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Image Malloc Failed");	
			
			/* return error code */
			exit(EXIT_IMAGE_MALLOC_FAILED);
			} /* malloc failed */
		}
	}
	return EXIT_NO_ERRORS;
} /* imageMallocCheck()		*/

