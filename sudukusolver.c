/**
 * @file sudukusolver.c
 * @author yefim kazak <yefim.kazak@huji.ac.il>
 * @version 1.0
 * @date 09 12 2014
 * 
 * @brief progrem to solve cool suduku
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * This progrem tries to solve suduku puzzels
 * Input  : suduku puzzle.
 * Process: tries all possiable solutions which is not efficent and slow
 * Output : the solved suduku or in case there is no - "no solution"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include "sudukutree.h"
#include "genericdfs.h"

/**
 * The defaultive line delimeter used to read the lines and tokenize
 **/
#define DEFAULT_LINE_DELIMETER " \n"
#define EMPTY_LINE_FLAG -1
/**
 * The default number of argumnets - currently 2 since c puts the name of the progrem in the first and the second and etc are the arguments
 **/
const int ALLOWED_ARGUMENTS = 2;

/**
 * This will hold the file for the small time being it's being used
 **/
static FILE* sudukuTableFile = NULL;

/**
 * this will hold for the whole run the table size as enterd by the user
 **/
int gTableSize = 0;

/**
 * this function closes all open file streams
 **/
void cleanFiles();

void argumentParser(int argumentCount, char* arguments[]);
int** fileParser();

/**
 * the main progrems - calls the diffrent functions to start the orchestras
 * in case of success finding a solution or the best one -  will print it
 * otherwise will print a message
 * @param argc the number of arguments give
 * @param argv the char array that hodls the arguments
 * return 0
 **/
int main(int argc, char* argv[])
{
	atexit(cleanFiles);
	argumentParser(argc, argv);
	int** sudukuTable = NULL;
	sudukuTable = fileParser(sudukuTableFile);
	unsigned int best = ((gTableSize*(1 + gTableSize)) / 2)*gTableSize;
	pNode bestNode = getBest((pNode)sudukuTable, getNodeChildrenSoduku, calculateTableSum, 
							 nodeReleaser, copySudukuTable, best);
	if (bestNode != NULL)
	{
		printSudukuSolution((int**)bestNode, gTableSize);
		nodeReleaser(bestNode);
	}
	else
	{
		printf("no solution!\n");
	}
	
	nodeReleaser(sudukuTable);
	return 0;
}

/**
 * Checks if the open file has been closed - and if not,
 * closes it and frees the memmory
 **/
void cleanFiles()
{
	if (sudukuTableFile != NULL)
	{
		fclose(sudukuTableFile);
		sudukuTableFile = NULL;
	}
}

/**
 * the function parses the arguments given to the progrem, validates them and open the file needed for the progrem
 * @param argumentCount the number of arguments give
 * @param arguments the char array that hodls the arguments
 **/
void argumentParser(int argumentCount, char* arguments[])
{
	if (argumentCount != ALLOWED_ARGUMENTS)
	{
		printf("please supply a file!\n usage: sudukusolver <filename>\n");
		exit(0);
	}
	else
	{
		errno = 0;
		sudukuTableFile = fopen(arguments[1], "r");
		if (errno != 0)
		{
			perror(arguments[1]);
			exit(0);
		}
	}
}

/**
 * the exception which rises in case the file is with incorrect format
 **/
void notValidFileException()
{
	printf("<filename>:not a valid suduku file\n");
	exit(1);
}

/**
 * checks whetever the specified table size is correct (perfect sqrt, positive)
 * @param sizeArgiment the first line in the file with the specified size
 * @return the table size as unsigned int in case its valid otherwise exits.
 **/
unsigned int isTableSizeValid(char* sizeArgument)
{
	unsigned int wantedSize;
	if(sizeArgument == NULL || ((sscanf(sizeArgument, " %u\n", &wantedSize)) != 1))
	{
		free(sizeArgument);
		notValidFileException();
	}
	
	if(wantedSize <= 0 || ((sqrt(wantedSize) * sqrt(wantedSize) != wantedSize)))
	{
		notValidFileException();
	}
	
	return wantedSize;
}


/**
 * The function gets the opened file and parses it,
 * first reads the table size and then the table itself to the correct variabals
 * which the functions sets and returns.
 **/
int** fileParser()
{
	size_t readBytes = 0;
	int tableSize = 0;
	char* readLine = NULL;
	int lineCount = 0;
	int** baseSudukuTable = NULL;
	//this gives warning but allowed byt the crew of the course
	int readCharCount = getline(&readLine, &readBytes, sudukuTableFile);
	
	if(readCharCount == EMPTY_LINE_FLAG)
	{
		free(readLine);
		notValidFileException();
	}
	
	tableSize = isTableSizeValid(readLine);
	
	free(readLine);
	readLine = NULL;
	
	baseSudukuTable = malloc(tableSize * sizeof(int*));	
	
	char* readItem = NULL;
	int newGridItem = 0;

	while ((readCharCount = getline(&readLine, &readBytes, sudukuTableFile)) != EMPTY_LINE_FLAG)
	{
		baseSudukuTable[lineCount] = malloc(tableSize * sizeof(int));
		if (lineCount >= tableSize)
		{
			nodeReleaser(baseSudukuTable);
			notValidFileException();
			exit(1);
		}
		
		int columCounter = 0;
		
		readItem = strtok(readLine, DEFAULT_LINE_DELIMETER);
		do
		{
			if (columCounter >= tableSize && readItem!=NULL)
			{
				nodeReleaser(baseSudukuTable);
				notValidFileException();
				exit(1);
			}
			
			sscanf(readItem, "%d", &newGridItem);
			baseSudukuTable[lineCount][columCounter] = newGridItem;
			readItem = strtok(NULL, DEFAULT_LINE_DELIMETER);
			columCounter++;
		}
		while (readLine != NULL && readItem!=NULL);
		
		if (columCounter != tableSize)
		{
				nodeReleaser(baseSudukuTable);
				notValidFileException();
				exit(1);
		}
		
		lineCount++;
	

	}
	
	free(readLine);
	readLine = NULL;
	gTableSize = tableSize;
	cleanFiles();
	return baseSudukuTable;
}
