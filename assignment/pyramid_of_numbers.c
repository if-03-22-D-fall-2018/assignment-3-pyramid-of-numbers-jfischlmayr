/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 3
 * Title:			Pyramid of Numbers
 * Author:			Jan Fischlmayr
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The numint strtobig_int(const char *str, int len, struct BigInt *big_int);
int strtobig_int(const char *str, int len, struct BigInt *big_int);
ber of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/** Asks the user for his BigInt*/
void get_user_input(char* inputNumber);

void bigIntArrayReverse(struct BigInt *big_int);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[]) {
	char inputNumber[MAX_DIGITS];
	int lengthOfCharArray;
	struct BigInt bigInt;
	struct BigInt bigResult;
	struct BigInt bigResultDivide;

	printf("Pyramid of Numbers\n");
	printf("==================\n");
	get_user_input(inputNumber);
	lengthOfCharArray = strlen(inputNumber);
	int length = strtobig_int(inputNumber, lengthOfCharArray, &bigInt);

	if (length == 0)
	{
		return 0;
	}

	for (int i = 2; i < 10; i++) {
		multiply(&bigInt, i, &bigResult);
		bigIntArrayReverse(&bigResult);
		bigIntArrayReverse(&bigInt);
		print_big_int(&bigInt);
		printf(" * %d = ",i);
		print_big_int(&bigResult);
		printf("\n");
		bigIntArrayReverse(&bigResult);
		bigIntArrayReverse(&bigInt);
		bigInt = bigResult;
	}

	bigIntArrayReverse(&bigResult);

	for (int i = 2; i < 10; i++) {
		print_big_int(&bigResult);
		divide(&bigResult,i,&bigResultDivide);
		bigResult = bigResultDivide;
		printf(" / %d = ",i);
		print_big_int(&bigResultDivide);
		printf("\n");
}
	return 0;
}

void get_user_input(char* inputNumber) {
	printf("Enter your Number: ");
	scanf("%s\n", inputNumber);
}

int strtobig_int(const char *str, int len, struct BigInt *big_int) {
	int counter = 0;
	for (int i = 0; i < len; i++) {
		big_int->the_int[i] = str[i] - '0';
		counter++;
	}
	return counter;
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result) {
	int overflowNumber = 0;
	int tempResult = 0;
	for (int i = big_int->digits_count - 1 ; i > 0; i--) {
		tempResult = big_int->the_int[i] * factor + overflowNumber;

		if (tempResult>9) {
			if (i == big_int->digits_count-1) {
				big_result->digits_count++;
				big_result->the_int[i] = tempResult % 10;
				big_result->the_int[i + 1] = tempResult / 10;
			}
			else {
				overflowNumber = tempResult / 10;
				big_result->the_int[i] = tempResult % 10;
			}
		}
		else{
			big_result->the_int[i]=tempResult;
		}
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result) {
	int overflowNumber = 0;
	int tempResult;
	for (int i = 0; i < big_int->digits_count; i++) {
		big_result->the_int[i] = 0;
		big_result->digits_count = i + 1;
		tempResult = overflowNumber * 10 + big_int->the_int[i];
		if (tempResult >= divisor) {
			big_result->the_int[i] = tempResult / divisor;
			overflowNumber = tempResult % divisor;
		}
		else
		{
				overflowNumber = big_int->the_int[i];
		}
	}
}

void print_big_int(const struct BigInt *big_int)
{
	bool notNullDigitFound = false;
		for (int i = 0; i < big_int->digits_count; i++) {
			if (big_int->the_int[i] > 0 || notNullDigitFound == true)
			{
					printf("%d",big_int->the_int[i]);
					notNullDigitFound = true;
			}
		}
}

void bigIntArrayReverse(struct BigInt *big_int)
{
	int i = big_int->digits_count-1;
  int j = 0;
   while(i > j)
   {
     int temp = big_int->the_int[i];
		 int temp2 = big_int->the_int[j];
     big_int->the_int[i] = temp2;
     big_int->the_int[j] = temp;
     i--;
     j++;
   }
}
