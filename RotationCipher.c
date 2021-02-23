//Carlos Garcia 
//CSC362-001, Programming Assignment #1, 1/24/21
//This program reads a file from the project directory character by character. It then 
//rotates all letters in the file up or down the alphabet, excluding white space. The rotation
//starts at +1 and rotates the next letter by the rotation amount, wrapping around the alphabet 
//if the new character does not stay within the alphabet. The rotation amount increases by 1 until 
//it reaches +13 in which it resets to -1. It then rotates a negative amount until it reaches -13 
//in which it resets to +1. 
//
//Thus, a rotation cipher is created and the program outputs all characters to an output file. The
//program also counts the number of input characters and the number of characters rotated. The program 
//also outputs a report to the console that includes the input files name, the outputs files name, the 
//number of input characters, the number of characters rotated, and the fraction of the output file that
//matches the input file as a percent.
//
//The program uses stdio.h for I/O functions and ctype.h to test alphabetic/numeric.

#include<stdio.h>
#include<ctype.h>

void main() {
	int inputChars = 0, rotatedChars = 0, rotationAmount = 1; //counters for number of characters input, characters rotated, & rotation amount
	double matchPercentage = 0.0; //fraction for percentage of output file matching input file
	FILE *fp1, *fp2; //fp1 points to input file & fp2 points to output file
	char inputFilename[20], outputFilename[20], current, newChar; //inputFilename, outputFilename, current is current character from input file, & 
																  //newChar points to character change
	printf("Enter the input file name: ");
	scanf("%s", inputFilename);
	printf("Enter the output file name: ");
	scanf("%s", outputFilename);

	fp1 = fopen(inputFilename, "r"); //opens input file as read-only
	fp2 = fopen(outputFilename, "w"); //opens output file as write-only

	while ((current = getc(fp1)) != EOF) { //reads each character until end of file is reached
		inputChars++; //regardless of what currents is, number of input characters increases

		if (rotationAmount > 13) { //checks if rotation amount exceeds 13 or -13
			rotationAmount = -1;   //if so, change it to 1 or -1 respectively
		}
		else if (rotationAmount < -13) {
			rotationAmount = 1;
		}

		if (isspace(current) || current == '\t' || current == '\n') { //checks if currents is a space, tab, or new line
			putc(current, fp2);										  //if so, adds it to output file
		}
		else if (isdigit(current) || ispunct(current)) { //checks if current is a digit or punctuation
			if (rotationAmount > 0) {					 //if so, check whether to rotate up or down 
				rotationAmount++;						 //and add it to the output file
			}
			else {
				rotationAmount--;
			}
			putc(current, fp2);
		}
		else if (isalpha(current)) { //checks if current is a letter
			newChar = (char)(current + rotationAmount); //if so, rotate the character
			if (islower(current) && (newChar < 'a' || newChar > 'z')) { //checks whether rotated character
				if (rotationAmount > 0) {								//needs to wrap around & is lower case
					newChar = (char)(newChar - 26); //wrap around alphabet backward for positive rotation
					rotationAmount ++;				//if rotation amount is positive and less than or equal to 13
				}
				else {
					newChar = (char)(newChar + 26); //wrap around alphabet forwards for negative rotation
					rotationAmount--;				//updates rotation amount respectively
				}
			}
			else if (isupper(current) && (newChar < 'A' || newChar > 'Z')) { //checks whether rotated character
				if (rotationAmount > 0) {									 //needs to wrap arond & is upper case
					newChar = (char)(newChar - 26); //wrap around alphabet backward for positive rotation
					rotationAmount++;				//if rotation amount is positive and less than or equal to 13
				}
				else {
					newChar = (char)(newChar + 26); //wrap around alphabet forwards for negative rotation
					rotationAmount--;				//updates rotation amount respectively
				}
			}
			else { //if new character does not need to wrap around, update rotation amount respectively
				if (rotationAmount > 0) { //if rotation amount is positive and less than or equal to 13
					rotationAmount++;	  //increment it, otherwise decrement it
				}
				else {
					rotationAmount--;
				}
			}

			putc(newChar, fp2); //add new character to output file
			rotatedChars++; //update number of rotated characters

		}
	}

	matchPercentage = (1 - ((double)rotatedChars / inputChars)) * 100; //finds match percent difference between input and output files

	printf("Input file name:%25s\n", inputFilename); //prints report to console window
	printf("Output file name:%24s\n", outputFilename);
	printf("Number of input characters:%14d\n", inputChars);
	printf("Number of characters rotated:%12d\n", rotatedChars);
	printf("Percentage output matches input:%8.2f%%", matchPercentage);

	fclose(fp1); //closes both files
	fclose(fp2);
}