///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        makeMagic.c
// This File:        makeMagic.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Brett Kessler
// Email:            bekessler2@wisc.edu
// CS Login:         kessler
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;     // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	int input = 0;
	int oddOrEven = 0;
	int mod = 0;
	int count = 0;
	while(oddOrEven == 0){
		count++;
		printf("Enter Magic Square's size (odd integer >= 3)\n");
		scanf("%d", &input);
	//	printf("%d\n", input);
		mod = input % 2;
		if((mod == 1) && (input > 2)){
			oddOrEven++;
			break;
		}
		else{
			oddOrEven = 0;
			printf("Invalid number");
		}
	
	}
	//printf("%d\n", input);
	//printf("%d\n", count);
       	return input;   
} 
   
/* TODO:
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
	// M = n(n*n + 1)/2
	// FOR REFERENCE: a 3x3 magic square
	// 6 1 8
	// 7 5 3
	// 2 9 4
MSquare *generateMSquare(int n) {
	int highestNumber = n*n + 1;
	int **msquareCurr = (int **)malloc(n * sizeof(int *));
	for(int i = 0; i<n; i++){
		msquareCurr[i] = (int *)malloc(n * sizeof(int));
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			*(*(msquareCurr + i)+j) = -1;
		}
	}
	int nRow = 0;
	int nCol = 0;
	int row = n/2;
	int col = 0;
	for(int i = 1; i < highestNumber; i++){
	       	*(*(msquareCurr + row) + col) = i;
		if(row == 0){ // if we are on the top row
			nRow = n - 1; // moves next row to the bottom row
		}
		else{
			nRow = row - 1; // Go up 1 row
		}
		if(col == (n-1)){ // column is on
			nCol = 0; // moves the column back to the 
		}
		else{
			nCol = col + 1; // Moving column 1 to the right
		}

		if((*(*msquareCurr + nRow) + nCol) != -1){ // Row is taken
			if(row == (n-1)){ // row is at the bottom  of square
				nRow = 0;
			}
			else{
				nRow = row + 1;
			}
		}
		col = nCol;
		row = nRow;
	}
	//printf("%d\n", n);
       	MSquare *toReturn = NULL;
	MSquare temp;
	temp.msquare = msquareCurr;
	temp.size = n;
	//printf("%d\n", temp.size);
	toReturn = &temp;
	//printf("%d   x\n", toReturn -> size);
       	return toReturn;
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename) {
	FILE *fptr;
	fptr = fopen(filename, "w");
	printf("%d     c\n", msquare -> size);
	if(fptr == NULL){
		printf("Error in the implementation");
		exit(1);
	}
	int **curr = msquare -> msquare;
//	int n = msquare -> size;
	//printf("c\n");
	//printf("%d\n     x", n);
	//printf("x");
	int x = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			x = (*(*curr+i)+j);
			fprintf(fptr, "%d,",x);
		}
		fprintf(fptr, "\n");
	}

	fclose(fptr);
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    if(argc != 2){
	    printf("The number of command-line arguments is incorrect\n - It should be in the following formate: ./makeMagic <outputfilename.txt>\n");
	    exit(1);
    }
    char *filename = *(argv + 1);
    // TODO: Get magin square's size from user
    int size = getSize();
    // TODO: Generate the magic square
    MSquare *toOutput = NULL;
    toOutput = generateMSquare(size);
    // TODO: Output the magic square
   // printf("%d    b\n", toOutput -> size);
    outputMSquare(toOutput, filename);
    return 0;
}  
