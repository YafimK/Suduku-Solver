/**
 * @file sudukutree.h
 * @author yefim kazak <yefim.kazak@huji.ac.il>
 * @version 1.0
 * @date 09 12 2014
 * 
 * @brief header file of sudukutree.c
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
 
#ifndef SODUKU_H
#define SODUKU_H
#include "genericdfs.h"

/**
 * the global itneger to mark table size.
 **/
extern int gTableSize;

/**
 * function which validates the row in the suduku table after adding a possiable solution of an empty cell
 * @param checkedGrid the work table
 * @param currentRow the current checked row
 * @param currentColum the coloum where the item were inserted
 * @param trialNumber the insereted solution
 * @return TRUE iff the row doesn't have the added number already (and therefore it's a possiable solution to the empty cell)
 **/
int validateRow(int**, int, int, int);

/**
 * function which validates the coloum in the suduku table after adding a possiable solution of an empty cell
 * @param checkedGrid the work table
 * @param currentRow the current checked row
 * @param currentColum the coloum where the item were inserted
 * @param trialNumber the insereted solution 
 * @return TRUE iff the coloum doesn't have the added number already (and therefore it's a possiable solution to the empty cell)
 **/
int validateColum(int**, int, int, int);

/**
 * this function initates the basic row and colum check for the possiable solution number put in the free cell
 * @param sudukuGrid the suduku table
 * @param row the row where the number were added
 * @param col the row where the number were added
 * @return TRUE iff the possiable number added as solution doesn't appear in the colum or the row
 **/
int checkTableRowCol(int**, int, int);

/**
 * this function calculates the corner of the square so it can be the starting position to check if the added number fits a possiable solution
 * @PARAM coordinate the row or the colum (x or y) that we want to find the corner of it
 * return the corner x or y
 **/
int calculateSquareCorner(int);

/**
 * this function initates the basic row and colum check for the possiable solution number put in the free cell
 * we create an additional helper array for us to mark which digits we already encountered. 
 * fairly speaking thanks to google. this is an awsome algoritem much better then just runnig on all rows and colums and counting occurness
 * @param sudukuGrid the suduku table
 * @param row the row where the number were added
 * @param col the row where the number were added
 * @return TRUE iff the possiable number added as solution doesn't appear in the colum or the row
 **/
int isCubeValid(int**, int, int );

/**
 * validates the table by checking for both uniqness in the row and coloum and then the cube/square
 * @param suduku the suduku table after insertion to be checked
 * @param ROW the insertion x coordinate
 * @param coloum the insertion y coordinate
 * @return TRUE iff the table is valid (aka the number appears only once in the col' row' & cube) 
 **/
int validateTable(int**, int, int );

/**
 * Seeks the given table for a zero - insertion point.
 * @PARAM checkedTable the checked table
 * @PARAM cursorRow the row that marks the row of the empty cell if found
 * @PARAM cursorColoum the row that marks the colum of the empty cell if found
 * @Return TRUE iff an empty cell was found
 */
int emptyCellSearcher(int**, int*, int* );

/**
 * The most importent algoritem - the solution seeker!
 * first it's finds an insertion place - empty space, then tries to insert possiable number (1 to tablesize)
 * and validates each possiablity (row, col, square). afterwords it stores to solution in an array
 * so it later on can be evluated for values
 * 
 * @param parent the suduku 
 * @param possiableSolutionsArray the array that will hold the possiable solutions
 * @return the number of possiable solutions and allocates an array of solutions
 **/
int getNodeChildrenSoduku(pNode , pNode** );

/**
 * Calculates the sum of the given suduku table
 * Assumes the size is the declered size of the starting table - which si logical!
 * @param sudukuTable the suduku table to be summed
 * @return the sum of the table
 **/
unsigned int calculateTableSum(pNode );

/**
 * this function frees the memory held by the given array -
 * which requires a loop since its a double array
 * @param targetNode the node to be freed from memmory
 **/
void nodeReleaser(pNode );

/**
 * This function copies the suduku table array to a new variable
 * (simple array copier)
 * @param sourceTable the sorce table to eb copies
 * @return the target table
 **/
pNode copySudukuTable(pNode );

/**
 * this function prints the given suduku table
 * @param node the table
 * @param size the size of the table
 **/
void printSudukuSolution(int** , int );

#endif
