/**
 * @file sudukutree.c
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
 * this defines the declered fucntins of the suduku solution tree
 * Input  : //////
 * Process: helps to find all possiable solutions
 * Output : ///////
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genericdfs.h"
#include "sudukutree.h"

/**
 * TRUE/FALSE - boolean flags
 * FREE_CELL_FLAG - flag to match empty cells
 * NO_POSSIABLE_SOLUTIONS_FLAG - flag to show there are no possaible solutions
 **/
#define TRUE 1
#define FALSE 0
#define FREE_CELL_FLAG 0
#define NO_POSSIABLE_SOLUTIONS_FLAG 0


/**
 * function which validates the row in the suduku table after adding a possiable solution of an empty cell
 * @param checkedGrid the work table
 * @param currentRow the current checked row
 * @param currentColum the coloum where the item were inserted
 * @param trialNumber the insereted solution
 * @return TRUE iff the row doesn't have the added number already (and therefore it's a possiable solution to the empty cell)
 **/
int validateRow(int** checkedGrid, int currentRow, int currentColum, int trialNumber)
{
	for (int colIndex = 0; colIndex < gTableSize; colIndex++)
	{
		if (checkedGrid[currentRow][colIndex] == trialNumber)
		{
			if (colIndex != currentColum)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**
 * function which validates the coloum in the suduku table after adding a possiable solution of an empty cell
 * @param checkedGrid the work table
 * @param currentRow the current checked row
 * @param currentColum the coloum where the item were inserted
 * @param trialNumber the insereted solution 
 * @return TRUE iff the coloum doesn't have the added number already (and therefore it's a possiable solution to the empty cell)
 **/
int validateColum(int** checkedGrid, int currentRow, int currentColum, int trialNumber)
{
	for (int rowIndex = 0; rowIndex < gTableSize; rowIndex++)
	{
		if ((checkedGrid[rowIndex][currentColum] == trialNumber) && (rowIndex != currentRow))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**
 * this function initates the basic row and colum check for the possiable solution number put in the free cell
 * @param sudukuGrid the suduku table
 * @param row the row where the number were added
 * @param col the row where the number were added
 * @return TRUE iff the possiable number added as solution doesn't appear in the colum or the row
 **/
int checkTableRowCol(int** sudukuGrid, int row, int col)
{
	int trialNumber = sudukuGrid[row][col];
	if (validateColum(sudukuGrid, row, col, trialNumber) && 
		validateRow(sudukuGrid, row, col, trialNumber))
	{
		return TRUE;
	}
	return FALSE;
}

/**
 * this function calculates the corner of the square so it can be the starting position to check if the added number fits a possiable solution
 * @PARAM coordinate the row or the colum (x or y) that we want to find the corner of it
 * return the corner x or y
 **/
int calculateSquareStartCorner(int coordinate)
{
	int corner = 0;
	corner =  ceil((coordinate + 1) / sqrt(gTableSize))-1;
	corner *= sqrt(gTableSize);
	return corner;
}

/**
 * this function initates the basic row and colum check for the possiable solution number put in the free cell
 * we create an additional helper array for us to mark which digits we already encountered. 
 * fairly speaking thanks to google. this is an awsome algoritem much better then just runnig on all rows and colums and counting occurness
 * @param sudukuGrid the suduku table
 * @param row the row where the number were added
 * @param col the row where the number were added
 * @return TRUE iff the possiable number added as solution doesn't appear in the colum or the row
 **/
int isCubeValid(int** table, int row, int col)
{
	int xCornerCoordinate = calculateSquareStartCorner(row);
	int yCornerCoordinate = calculateSquareStartCorner(col);

	int sqaureLength = sqrt(gTableSize);	
	int xRightCorner = (xCornerCoordinate + sqaureLength);
	int yLowestCorner = (yCornerCoordinate + sqaureLength);

	int* booleanArray = (int*)malloc(sizeof(int)*gTableSize);

	for (int index = 0; index < gTableSize; index++)
	{
		booleanArray[index] = FALSE;
	}
	
	for (int rowIndex = xCornerCoordinate; rowIndex < xRightCorner; rowIndex++)
	{
		for (int colIndex = yCornerCoordinate; colIndex < yLowestCorner; colIndex++)
		{
			if (table[rowIndex][colIndex] != FREE_CELL_FLAG)
			{
				if (booleanArray[table[rowIndex][colIndex] - 1] == FALSE)
				{
					booleanArray[table[rowIndex][colIndex] - 1] = TRUE;
				}
				else
				{
					free(booleanArray);
					return FALSE;
				}	
			}
		}
	}
	
	free(booleanArray);
	return TRUE;
}

/**
 * validates the table by checking for both uniqness in the row and coloum and then the cube/square
 * @param suduku the suduku table after insertion to be checked
 * @param ROW the insertion x coordinate
 * @param coloum the insertion y coordinate
 * @return TRUE iff the table is valid (aka the number appears only once in the col' row' & cube) 
 **/
int validateTable(int** suduku, int row, int col)
{
	if (checkTableRowCol(suduku, row, col)
		&& isCubeValid(suduku, row, col))
	{
		return TRUE;
	}
	return FALSE;
}

/**
 * Seeks the given table for a zero - insertion point.
 * @PARAM checkedTable the checked table
 * @PARAM cursorRow the row that marks the row of the empty cell if found
 * @PARAM cursorColoum the row that marks the colum of the empty cell if found
 * @Return TRUE iff an empty cell was found
 */
int emptyCellSearcher(int** checkedTable, int *cursorRow, int *cursorColoum)
{
	for (*cursorRow = 0; (*cursorRow) < gTableSize; (*cursorRow)++)
	{
		for (*cursorColoum = 0; (*cursorColoum) < gTableSize; (*cursorColoum)++)
		{
			if (checkedTable[(*cursorRow)][(*cursorColoum)] == FREE_CELL_FLAG)
			{
				return TRUE;
			}
		}

	}
	return FALSE;
}

/**
 * helper function in order to assign one array items to second
 * @param sourceArray the soruce array to be assigned
 * @param size the size of the array
 * @return the newely assigned array
 **/
pNode* assignArrayToArray(int*** sourceArray, int size)
{
		pNode *newArray = (pNode*)malloc(size * sizeof(pNode));
		
		for (int i = 0; i < size; i++)
		{
			newArray[i] = (pNode)sourceArray[i];
		}
		
		free(sourceArray);
		return newArray;	
}

/**
 * The most importent algoritem - the solution seeker!
 * first it's finds an insertion place - empty space, then tries to insert possiable number (1 to tablesize)
 * and validates each possiablity (row, col, square). afterwords it stores to solution in an array
 * so it later on can be evluated for values
 * @param parent the suduku 
 * @param possiableSolutionsArray the array that will hold the possiable solutions
 * @return the number of possiable solutions and allocates an array of solutions
 **/
int getNodeChildrenSoduku(pNode parent, pNode** possiableSolutionsArray)
{
	int** parentTable = (int**)parent;
	int emptyCellRow = 0;
	int emptyCellColoum = 0;

	if ((emptyCellSearcher(parent, &emptyCellRow, &emptyCellColoum)) == FALSE)
	{
		return NO_POSSIABLE_SOLUTIONS_FLAG;
	}
	
	int*** tempSolutionHolder = (int***)malloc(0 * sizeof(int**));
	int solutionCounter = 0;
	
	for (int possiableSolutions = 1; possiableSolutions <= gTableSize; possiableSolutions++)
	{
		int** tempSolutionTestTable = copySudukuTable(parentTable);
		tempSolutionTestTable[emptyCellRow][emptyCellColoum] = possiableSolutions;
		if (!validateTable(tempSolutionTestTable, emptyCellRow, emptyCellColoum)) 
		{
			nodeReleaser(tempSolutionTestTable);
		}
		else
		{
			tempSolutionHolder = (int***)realloc(tempSolutionHolder, (solutionCounter + 1)*sizeof(int**));
			tempSolutionHolder[solutionCounter] = tempSolutionTestTable;
			solutionCounter++;			
		}
	}

	if(solutionCounter != NO_POSSIABLE_SOLUTIONS_FLAG)
	{
		*possiableSolutionsArray = assignArrayToArray(tempSolutionHolder, solutionCounter);
		return solutionCounter;
	}
	
	free(tempSolutionHolder);
	return NO_POSSIABLE_SOLUTIONS_FLAG;
}

/**
 * Calculates the sum of the given suduku table
 * Assumes the size is the declered size of the starting table - which si logical!
 * @param sudukuTable the suduku table to be summed
 * @return the sum of the table
 **/
unsigned int calculateTableSum(pNode sudukuTable)
{
	int** tmpNode = (int**)sudukuTable;
	
	int tableSum = 0;
	int row = 0;
	int col = 0;
	
	for (row = 0; row < gTableSize; row++)
	{	
		for (col = 0; col < gTableSize; col++)
		{
			tableSum += tmpNode[row][col];
		}
	}
	
	return tableSum;
}

/**
 * this function prints the given suduku table
 * @param node the table
 * @param size the size of the table
 **/
void printSudukuSolution(int** node, int size)
{
	int row = 0 , coloum = 0;
	printf("%d\n", size);
	for (row = 0; row < size; row++)
	{
		for (coloum = 0; coloum < size; coloum++)
		{
			if (coloum != (size-1))
			{
				printf("%d ", node[row][coloum]);
			}
			else
			{
				printf("%d", node[row][coloum]);
			}
		}
		printf("\n");
	}
}

/**
 * This function copies the suduku table array to a new variable
 * (simple array copier)
 * @param sourceTable the sorce table to eb copies
 * @return the target table
 **/
pNode copySudukuTable(pNode sourceTable)
{
	int** temoreryTable = (int**)sourceTable;
	int** targetTable = malloc(gTableSize * sizeof(int*));
	
	int row = 0;
	int coloum = 0;
	
	for (row = 0; row < gTableSize; row++)
	{
		targetTable[row] = malloc(gTableSize * sizeof(int));
	}

	for (row = 0; row < gTableSize; row++)
	{
		for (coloum = 0; coloum < gTableSize; coloum++)
		{
			targetTable[row][coloum] = temoreryTable[row][coloum];
		}
	}

	return targetTable;
}

/**
 * this function frees the memory held by the given array -
 * which requires a loop since its a double array
 * @param targetNode the node to be freed from memmory
 **/
void nodeReleaser(pNode targetPnode)
{
	int** targetNode = (int**)targetPnode;

	for (int index = 0; index < gTableSize; index++)
	{
		free(targetNode[index]);
	}
	
	free(targetNode);
}
