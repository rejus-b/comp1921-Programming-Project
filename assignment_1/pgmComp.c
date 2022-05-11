
//* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for including string operations	*/
#include <string.h>

/* header for pgmComp				*/
#include "pgmComp.h"

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"



/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: first file name        */
/* argv[2]: second file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/



int main(int argc, char **argv)
{ /* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s inputImage.pgm inputImage.pgm", argv[0]);
		/* return no errors */
		return EXIT_NO_ERRORS;
	}

    /* check for correct number of arguments */
    if (argc != 3)
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

	/* malloc for a structure for the first input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileOne = NULL;
	pgmStructFileOne = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStructFileOne);
	
	
    /* malloc for a structure for the second input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileTwo = NULL;
	pgmStructFileTwo = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStructFileTwo);

    // /* pass the first pgm to be read from */
    if (readFile(argv[1], pgmStructFileOne) == 0)
	{
		/* pass the second pgm to be read from */
		if (readFile(argv[2], pgmStructFileTwo) == 0)
		{
			/* If no errors are thrown when reading the two data files, see if they are equivelant */
			if (equivalence(pgmStructFileOne, pgmStructFileTwo) == 0)
			{
				printf("IDENTICAL");
				return EXIT_NO_ERRORS;
			}
			else 
			{
				printf("DIFFERENT");
				return EXIT_NO_ERRORS;
			}
		}
	}

} /* main() */


int equivalence(pgm *pgmStructFileOne, pgm *pgmStructFileTwo)
{ /* equivalence()	*/
	/* check that the maxGray of the two input files is equivalent */
	if (pgmStructFileOne->magic_number[0] != pgmStructFileTwo->magic_number[0])
	{
		// printf("ERROR: Miscellaneous (Magic Number Not Equivalent)");
		return EXIT_MISCELLANEOUS;
	}

	/* check that the width of the two input files is equivalent */
	if (pgmStructFileOne->width != pgmStructFileTwo->width )
	{
		// printf("ERROR: Miscellaneous (Width Not Equivalent)");
		return EXIT_MISCELLANEOUS;
	}

	/* check that the height of the two input files is equivalent */
	else if (pgmStructFileOne->height != pgmStructFileTwo->height)
	{
		// printf("ERROR: Miscellaneous (Height Not Equivalent)");
		return EXIT_MISCELLANEOUS;
	}

	/* check that the maxGray of the two input files is equivalent */
	else if (pgmStructFileOne->maxGray != pgmStructFileTwo->maxGray)
	{
		// printf("ERROR: Miscellaneous (Max Gray Not Equivalent)");
		return EXIT_MISCELLANEOUS;
	}

	

	// /* allocate the data pointer for one structure, this does not need to be done twice as you only have to read the data pointer once            */ 
	// long nImageBytes = pgmStructFileOne->width * pgmStructFileTwo->height * sizeof(unsigned char);

	// /* check that each pixel is equivalent  */
	// if (memcmp(pgmStructFileOne->imageData, pgmStructFileTwo->imageData, nImageBytes) != 0)
	// {
	// 	printf("ERROR: Miscellaneous Image Data Not Equivalent \n");
	// 	return EXIT_MISCELLANEOUS;			
	// }

	// 	long nImageBytes = pgmStructFileOne->width * sizeof(unsigned char);

	// for (int i = 0; i < pgmStructFileOne->height ; i++)
	// {
	// 	/* check that each pixel is equivalent  */
	// 	if (memcmp(pgmStructFileOne->imageData, pgmStructFileTwo->imageData, nImageBytes) != 0)
	// 	{
	// 		printf("\n (%i) \n", memcmp(pgmStructFileOne->imageData[i], pgmStructFileTwo->imageData[i], nImageBytes));
	// 		printf("ERROR: Miscellaneous (Image Data Not Equivalent)");
	// 		return EXIT_MISCELLANEOUS;			
	// 	}
	// }

	for (int i = 0; i < pgmStructFileOne->height; i++)
	{
		for (int j = 0; j < pgmStructFileOne->width; j++)
		{
			printf("\n One %i \n", pgmStructFileOne->imageData[i][j]);
			printf("\n Two %i \n", pgmStructFileTwo->imageData[i][j]);
			if (pgmStructFileOne->imageData[i][j] != pgmStructFileTwo->imageData[i][j])
			{
				// printf("ERROR: Miscellaneous (Image Data Not Equivalent)");
				return EXIT_MISCELLANEOUS;
			}
		}
	}
	

	return EXIT_NO_ERRORS;

	/*
	for h in range height:
		for w in range width:
			if a[h][w] != b[h][w]:
				return bad;
	
	*/

} /* equivalence()	*/
