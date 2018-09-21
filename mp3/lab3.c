/* lab3.c
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 222, Fall 2016
 * MP3
 * Subject: ECE222-1,#3
 *
 * Purpose: The program is divided into two sections, verification and calculation. The purpose of the verification process is to recognize if the input entered by the user is valid. The input is only valid only if the left operation is less or equal to 12 characters, the operator is '+', '*', '/', or '^', and the right operation is less than or equal to 12 characters that must be letters from 'a' to 'z' or 'A' to 'U'. If the user's input is valid, the program will jump into calculation of these characters depending of operator chosen, if not will ask to enter an input again. When calculation starts, the entered input is divided into left operator and right operators, in both cases the value of those characters arrays will be stored into two different integer arrays for each one of them and will make them to a value fro 0-46 depending if the leter is upper case or lower case. Then the program calculates the result of each position according to the opeartor chosen. The final result is converted into ASCII code and stored into a character array. Finally the program returns the new value and displays the result of the operations chosen.
 
 * Assumptions: The user knows that the program can only take up to 12 characters per side of operation. The user knows that he/she can only entered one operation symbol. String and character libraries where not used in the program. No changes were made to code in main.
functions.  Additional functions are encouraged.  
 *
 * Bugs:
 *
 * Notes:
 *
 * See the ECE 222 programming guide
 *
 * If your formatting is not consistent you must fix it.  You can easily
 * reformat (and automatically indent) your code using the astyle 
 * command.  In a terminal on the command line do
 *
 *     astyle --style=kr lab3.c
 *
 * See "man astyle" for different styles.  Replace "kr" with one of
 * ansi, java, gnu, linux, or google to see different options.  Or, set up 
 * your own style.
 */

// do not include any additional libraries
#include <stdio.h>

// do not change these constants
#define MAXLINE 80
#define MAXOPER 13

// named constants and strings 
enum operations { NOOP, ADD, MUL, DIV, POW};
const char *operation_str[] = {"Invalid", "+", "*", "/", "^"};

// function prototypes
int process_input(const char *input, char *op_left, char *op_right);
void calc_output(const char *op_l, int op, const char *op_r, char *result);

// do not change any code in main.  We are grading based on the format
// of the output as given in the printfs in main.
int main()
{
    char input_line[MAXLINE];
    char left_operand[MAXOPER];
    char right_operand[MAXOPER];
    char answer[MAXOPER];
    int  operator;

    printf("\nMP3: Arithmetic on GF(47) with + * / ^ using letters\n");
    printf("Commands:\n\tabc+bbc\n\tturtle/frog\n\ttiger^one");
    printf("\tOperands are no more than 12 letters and no spaces\n");
    printf("\tCtrl-d to quit\n\n");
    printf("> ");

    // each call to fgets collects one line of input and stores in input_line
    // BEWARE: fgets includes the end-of-line character '\n' in input_line
    while (fgets(input_line, sizeof input_line, stdin) != NULL) {

        // clear for next round
        left_operand[0] = right_operand[0] = answer[0] = '\0';

        // check for valid grammar
        operator = process_input(input_line, left_operand, right_operand);

        if (operator == ADD || operator == MUL 
                || operator == DIV || operator == POW) {

            // print parsed input
            printf("'%s'", left_operand);
            printf(" %s ", operation_str[operator]);
            printf("'%s' => ", right_operand);

            // perform pseudo arithmetic 
            calc_output(left_operand, operator, right_operand, answer);

            // print result
            printf("'%s'\n\n", answer);
        } else {
            printf("# %s", input_line);
        }
        printf("> ");
    }
    printf("\nGoodbye\n");
    return 0;
}

/* Parse input of the form SOS where S is a string and O is a character.
 *
 * A string S must consist of up to 12 valid symbols a-z and A-U.  
 * The operand O must be one character from: + * / ^
 * Any other characters found in the input, including spaces, are
 * grammatically incorrect and invalidate the input.
 *
 * There must be no spaces anywhere in the input, including between 
 * either SO, OS, or leading or trailing spaces.
 *
 * Input: The input string is collected using fgets.  Recall the end-of-line
 *        character is included in the input string and marks the end of
 *        the input.  This string must not be changed.
 *
 * Output: There are three outputs from this function.
 *
 *   The return value is one of NOOP, ADD, MUL, DIV, POW which are
 *      named constants.  If the input is invalid for any reason 
 *      then the output must be NOOP.  Otherwise the return value 
 *      corresponds to operand O. 
 *
 *   If the input is grammatically correct, then two strings are also 
 *   returned, one for each of the left and right operands.  If the input 
 *   in invalid the two output strings are undefined.
 */
int process_input(const char *input, char *op_left, char *op_right)
{
    // replace the following with your code
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    char op_symbol;
    
    // Stores left operation of input into op_left only if is not equal to a symbol.
    for (counter1 = 0; input[counter1] != '\0' && counter1 < 12; counter1++)
    {	
    
    	if (input[counter1] == '+' || input[counter1] == '^' || input[counter1] == '*' || input[counter1] == '/')
    	{
    		break;
    	}
    	op_left[counter1] = input[counter1];
    }
    // Stores NULL into last letter in op_left array.
    op_left[counter1] = '\0';
    // Stores symbol into op_symbol.
    op_symbol = input[counter1];
    // Stores where counter1 left on array of the input and adds one to it.
    counter2 = counter1 + 1;
    
    // Stores right operation of iput into op_right only if is not equal to a symbol.
    for (counter2 = counter2; input[counter2] != '\0' && counter3 < 12; counter2++)
    {
    	op_right[counter3] = input[counter2];
    	counter3++;
    }
    
    // Stores NULL into last letter in op_right array.
    if (counter3 < 12)
    {
    	op_right[counter3 - 1] = '\0';
    } 
    else if (counter3 == 12)
    {
    	op_right[counter3] = '\0';
    }
    
    // Verifies that op_left only has valid symbols.
    for (counter4 = 0; op_left[counter4] != '\0' && counter4 < 12; counter4++)
    {
    	if ((op_left[counter4] >= 'a' && op_left[counter4] <= 'z') || (op_left[counter4] >= 'A' && op_left[counter4] <= 'U'))
    	{
    		count += 1;
    	}
    	else
    	{
    		count = 0;
    		break;
    	}
    }
    
    // Verifies that op_right has valid symbols.
   for (counter5 = 0; op_right[counter5] != '\0' && counter5 < 12; counter5++)
   {
   	if ((op_right[counter5] >= 'a' && op_right[counter5] <= 'z') || (op_right[counter5] >= 'A' && op_right[counter5] <= 'U'))
   	{
   		count2++;
   	}
   	else
   	{
   		count2 = 0;
   		break;
   	}
   }
    
    // Will return different symbols depending on op_symbol if count and count2 are greater or equal to 1 and less than or equal to 12.
    if ((count >= 1 && count <= 12) && (count2 >= 1 && count2 <= 12))
    {
    	if (op_symbol == '+')
    	{
    		return ADD;
    	}
    	else if (op_symbol == '*')
    	{
    		return MUL;
    	}
    	else if (op_symbol == '/')
    	{
    		return DIV;
    	}
    	else if (op_symbol == '^')
    	{
    		return POW;
    	}
    }
    
    // If entered input is invalid, will return -1 so process starts again.
    if (count == 0 || count2 == 0 || count3 > 12 || count4 > 12)
    {
    	return -1;
    }
   return 0;
   }

/* Pseudo mathematical opertions on the two operands work as follows.
 *
 * Each character is converted to an integer in the range 1...46, where a is 0,
 * b is 1, c is 2, ..., z is 25.  The operation is then performed using 
 * math on a finite field with no carries.  
 *
 * If the two input strings are not the same length, then each output character
 * beyond the length of the shorter string should be a copy of the character 
 * from the longer string but with the opposite case.
 *
 * Input: The two operand strings and the operator are assumed to be valid (and
 *        are verified as valid in the parse_input function).
 *
 * Output: The final string generated by the above rules is stored in the
 *         output string named result.  The input strings must not be 
 *         changed.
 */
void calc_output(const char *l_op, int op, const char *r_op, char *result) 
{
    // Variable Declaration Section.
    int op_left[12];
    int op_right[12];
    int answer[12];
    char answer2[12] = { 0 };
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;
    int counter8 = 0;
    int counter9 = 0;
    int counter10 = 0;
    int counter11 = 0;
    int counter12 = 0;
    int counter13 = 0;
    int counter14 = 0;
    int counter15 = 0;
    int counter16 = 0;
    int z = 1;
    
    // If operator is '+', this runs.
    if (op == ADD)
    {
    	// Makes character array into an integer array for both l_op and r_op.
    	for (counter1 = 0; l_op[counter1] != '\0'; counter1++)
    	{
    		if (l_op[counter1] >= 'a' && l_op[counter1] <= 'z')
    		{
    			op_left[counter1] = l_op[counter1] - 97;
    		}
    		else if (l_op[counter1] >= 'A' && l_op[counter1] <= 'U')
    		{
    			op_left[counter1] = l_op[counter1] - 39;
    		}
    	}
    	op_left[counter1] = '\0';
    	for (counter2 = 0; r_op[counter2] != '\0'; counter2++)
    	{
    		if (r_op[counter2] >= 'a' && r_op[counter2] <= 'z')
    		{
    			op_right[counter2] = r_op[counter2] - 97;
    		}
    		else if (r_op[counter2] >= 'A' && r_op[counter2] <= 'U')
    		{
    			op_right[counter2] = r_op[counter2] - 39;
    		}
    	}
    	op_right[counter2] = '\0';
    	
    	// If both character arrays are equal in size it will store addition into character array answer2.
    	if (counter1 == counter2)
    	{
    		// Stores addition of integer arrays op_left and op_right into integer array answer.
    		for (counter3 = 0; counter3 < counter1; counter3++)
    		{
    			answer[counter3] = op_left[counter3] + op_right[counter3];
    		}
    		answer[counter3] = '\0';
    		// Integer array answer is converted into ASCII and stored into character array answer2.
    		for (counter4 = 0; counter4 < counter1; counter4++)
    		{
    			if (answer[counter4] >= 0 && answer[counter4] <= 25)
    			{
    				answer2[counter4] = answer[counter4] + 97;
    			}
    			else if (answer[counter4] >= 26 && answer[counter4] <= 46)
    			{
    				answer2[counter4] = answer[counter4] + 39;
    			}
    			// If addition of op_left and op_right is greater than 46, will do Mod 47 to the value and store it in integer array answer. Then it will make values into ASCII and store into character array answer2.
    			else if (answer[counter4] > 46)
    			{
    				answer[counter4] = answer[counter4]%47;
    				if (answer[counter4] >= 0 && answer[counter4] <= 25)
    				{
    					answer2[counter4] = answer[counter4] + 97;
    				}
    				else if (answer[counter4] >= 26 && answer[counter4] <= 46)
    				{
    					answer2[counter4] = answer[counter4] + 39;
    				}		
    			}
    		}
    		answer2[counter4] = '\0';
    		// Stores final answer into result.
    		for (counter5 = 0; counter5 < counter1; counter5++)
    		{
    			result[counter5] = answer2[counter5];
    		}
 		result[counter5] = '\0';   		
    	}
    	
    	// If op_left is greater than op_right, it will copy last characters of op_left in lower/upper case after addition has been done into character array answer2.
	if (counter1 > counter2)
	{
		// Stores addition into integer array answer until both operations are not the same length.
		for (counter5 = 0; counter5 < counter2; counter5++)
		{
			answer[counter5] = op_left[counter5] + op_right[counter5];
		}
		// Stores remaining values of op_left into integer array answer.
		for (counter6 = counter5; counter6 < counter1; counter6++)
		{
			if (op_left[counter6] >= 0 && op_left[counter6] <= 25)
			{
				answer[counter6] = op_left[counter6];
			}
			else if(op_left[counter6] >= 26 && op_left[counter6] <= 46)
			{
				answer[counter6] = op_left[counter6];
			}
		}
		answer[counter6] = '\0';
		// Makes integer array into character array and stores values into character array answer2. 
		for (counter7 = 0; counter7 < counter1; counter7++)
		{
			if (answer[counter7] >= 0 && answer[counter7] <= 25)
			{
				answer2[counter7] = answer[counter7] + 97;
				// Last values of op_left stored in answer are converted to upper case and stored in character array2 answer2.
				if (counter7 >= counter2)
				{
					answer2[counter7] = answer[counter7] + 65;
				}
			}
			else if (answer[counter7] >= 26 && answer[counter7] <= 46)
			{
				answer2[counter7] = answer[counter7] + 39;
				// Last values of op_left stores in answer are converted to lower case and stored in character array answer2.
				if (counter7 >= counter2)
				{
					answer2[counter7] = answer[counter7] + 71;
				}
			}
			// If the sum of op_right and op_left greater than 46, it will do Mod 47 to that value, make that value into ASCII code and store it on answer2.
			else if (answer[counter7] > 46)
    			{
    				answer[counter7] = answer[counter7]%47;
    				if (answer[counter7] >= 0 && answer[counter7] <= 25)
    				{
    					answer2[counter7] = answer[counter7] + 97;
    					if (counter7 >= counter2)
					{
						answer2[counter7] = answer[counter7] + 65;
					}
    				}
    				else if (answer[counter7] >= 26 && answer[counter7] <= 46)
    				{
    					answer2[counter4] = answer[counter4] + 39;
    					if (counter7 >= counter2)
					{
						answer2[counter7] = answer[counter7] + 71;
					}
    				}		
    			}
		}
		answer2[counter7] = '\0';
		// Stores the final answer into result.
		for (counter8 = 0; counter8 < counter1; counter8++)
		{
			result[counter8] = answer2[counter8];
		}
		result[counter8] = '\0';
	}
	
	// If op_right is greater than op_left, it will store last characters of op_right into answer2 as upper/lower case letters.
	if (counter2 > counter1)
	{	// Stores addition of op_left and op_right into integer array answer until both sizes are not equal.
		for (counter8 = 0; counter8 < counter1; counter8++)
		{
			answer[counter8] = op_left[counter8] + op_right[counter8];
		}
		// Stores remaining values of op_right into integer array answer.
		for (counter9 = counter8; counter9 < counter2; counter9++)
		{
			if (op_right[counter9] >= 0 && op_right[counter9] <= 25)
			{
				answer[counter9] = op_right[counter9];
			}
			else if (op_right[counter9] >= 26 && op_right[counter9] <= 46)
			{
				answer[counter9] = op_right[counter9];
			}
		}
		answer[counter9] = '\0';
		// Values of integer array answer are made into ASCII and stored into character array answer2.
		for (counter10 = 0; counter10 < counter2; counter10++)
		{	
			if (answer[counter10] >= 0 && answer[counter10] <= 25)
			{
				answer2[counter10] = answer[counter10] + 97;
				// Last values of op_right that were stored into answer are converted from lower case to upper case.
				if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 65;
					}
			}
			else if (answer[counter10] >= 26 && answer[counter10] <= 46)
			{
				answer2[counter10] = answer[counter10] + 39;
				// Last values of op_right that were stored into asnwer are converted from upper case to lower case.
				if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 71;
					}
			}
			// If addition of op_right and op_left is greater than 46 it will mod47 the value and store it into answer. Then is turned into ASCII and stored into characeter array answer2.
			else if (answer[counter10] > 46)
    			{
    				answer[counter10] = answer[counter10]%47;
    				if (answer[counter10] >= 0 && answer[counter10] <= 25)
    				{
    					answer2[counter10] = answer[counter10] + 97;
    					if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 65;
					}
    				}
    				else if (answer[counter10] >= 26 && answer[counter10] <= 46)
    				{
    					answer2[counter10] = answer[counter10] + 39;
    					if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 71;
					}
    				}		
    			}
		}
		answer2[counter10] = '\0';
		// Final answer is stored into result.
		for (counter11 = 0; counter11 < counter2; counter11++)
		{
			result[counter11] = answer2[counter11];
		}
		result[counter11] = '\0';
	}
	
    }
    
    // If op is '*' this will run.
    if (op == MUL)
    {
    	// Makes character array l_op and r_op into an integer array and is stored in op_left and op_right
    	for (counter1 = 0; l_op[counter1] != '\0'; counter1++)
    	{
    		if (l_op[counter1] >= 'a' && l_op[counter1] <= 'z')
    		{
    			op_left[counter1] = l_op[counter1] - 97;
    		}
    		else if (l_op[counter1] >= 'A' && l_op[counter1] <= 'U')
    		{
    			op_left[counter1] = l_op[counter1] - 39;
    		}
    	}
    	op_left[counter1] = '\0';
    	for (counter2 = 0; r_op[counter2] != '\0'; counter2++)
    	{
    		if (r_op[counter2] >= 'a' && r_op[counter2] <= 'z')
    		{
    			op_right[counter2] = r_op[counter2] - 97;
    		}
    		else if (r_op[counter2] >= 'A' && r_op[counter2] <= 'U')
    		{
    			op_right[counter2] = r_op[counter2] - 39;
    		}
    	}
    	op_right[counter2] = '\0';
    	
    	// If op_left and op_right are the same size it will store the multiplication of both integers arrays into integer array answer and then store result into character array answer2.
    	if (counter1 ==  counter2)
    	{	// Stores multiplication of op_left and op_right into answer.
    		for (counter3 = 0; counter3 < counter1; counter3++)
    		{
    			answer[counter3] = op_left[counter3] * op_right[counter3];
    		}
    		answer[counter3] = '\0';
    		// Converts values of answer into ASCII code and stores it into character array answer2.
    		for (counter4 = 0; counter4 < counter1; counter4++)
    		{
    			if (answer[counter4] >= 0 && answer[counter4] <= 25)
    			{
    				answer2[counter4] = answer[counter4] + 97;
    			}
    			else if (answer[counter4] >= 26 && answer[counter4] <= 46)
    			{
    				answer2[counter4] = answer[counter4] + 39;
    			}
    			// If multiplication is greater than 46, it will mod47 the value, make into ASCII, and store it into answer2.
    			else if (answer[counter4] > 46)
    			{
    				answer[counter4] = answer[counter4]%47;
    				if (answer[counter4] >= 0 && answer[counter4] <= 25)
    				{
    					answer2[counter4] = answer[counter4] + 97;
    				}
    				else if (answer[counter4] >= 26 && answer[counter4] <= 46)
    				{
    					answer2[counter4] = answer[counter4] + 39;
    				}		
    			}
    		}
    		answer2[counter4] = '\0';
    		// Stored final answer into result.
    		for (counter5 = 0; counter5 < counter1; counter5++)
    		{
    			result[counter5] = answer2[counter5];
    		}
    		result[counter5] = '\0';
    	}
    	
    	// If op_left is greater in size than op_right, it will store the multiplication of both integers arrays into integer array answer and then store result into character array answer2.
    	if (counter1 > counter2)
	{
		// Stores multiplication of op_left and op_right into asnwer until they are no longer the same size.
		for (counter5 = 0; counter5 < counter2; counter5++)
		{
			answer[counter5] = op_left[counter5] * op_right[counter5];
		}
		// Stores last values of op_left into answer.
		for (counter6 = counter5; counter6 < counter1; counter6++)
		{
			if (op_left[counter6] >= 0 && op_left[counter6] <= 25)
			{
				answer[counter6] = op_left[counter6];
			}
			else if(op_left[counter6] >= 26 && op_left[counter6] <= 46)
			{
				answer[counter6] = op_left[counter6];
			}
		}
		answer[counter6] = '\0';
		// Converst values of answer into ASCII and stores it into character array answer2.
		for (counter7 = 0; counter7 < counter1; counter7++)
		{
			if (answer[counter7] >= 0 && answer[counter7] <= 25)
			{
				answer2[counter7] = answer[counter7] + 97;
				// Converts last values stored from op_left into answer into ASCII and stored as upper case in answer2.
				if (counter7 >= counter2)
				{
					answer2[counter7] = answer[counter7] + 65;
				}
			}
			else if (answer[counter7] >= 26 && answer[counter7] <= 46)
			{
				answer2[counter7] = answer[counter7] + 39;
				// Convert last values stored from op_left into answer into ASCII and stored as lower case in answer2.
				if (counter7 >= counter2)
				{
					answer2[counter7] = answer[counter7] + 71;
				}
			}
			// If multiplication stored in answer is greater than 46, it will mod47 the value and make it into ASCII and store into answer2.
			else if (answer[counter7] > 46)
    			{
    				answer[counter7] = answer[counter7]%47;
    				if (answer[counter7] >= 0 && answer[counter7] <= 25)
    				{
    					answer2[counter7] = answer[counter7] + 97;
    					if (counter7 >= counter2)
					{
						answer2[counter7] = answer[counter7] + 65;
					}
    				}
    				else if (answer[counter7] >= 26 && answer[counter7] <= 46)
    				{
    					answer2[counter4] = answer[counter4] + 39;
    					if (counter7 >= counter2)
					{
						answer2[counter7] = answer[counter7] + 71;
					}
    				}		
    			}
		}
		answer2[counter7] = '\0';
		// Stores final answer into result.
		for (counter8 = 0; counter8 < counter1; counter8++)
		{
			result[counter8] = answer2[counter8];
		}
		result[counter8] = '\0';
	}
	
	// If op_right is greater in size than op_left, it will store the multiplication of both integers arrays into integer array answer and then store result into character array answer2.
	if (counter2 > counter1)
	{	// Stores multiplication of op_left and op_right into answer until lengths are no longer equal.
		for (counter8 = 0; counter8 < counter1; counter8++)
		{
			answer[counter8] = op_left[counter8] * op_right[counter8];
		}
		// Stores remaining values of op_right into answer.
		for (counter9 = counter8; counter9 < counter2; counter9++)
		{
			if (op_right[counter9] >= 0 && op_right[counter9] <= 25)
			{
				answer[counter9] = op_right[counter9];
			}
			else if (op_right[counter9] >= 26 && op_right[counter9] <= 46)
			{
				answer[counter9] = op_right[counter9];
			}
		}
		answer[counter9] = '\0';
		// Converts values of answer into ASCII and stores it into character array answer2.
		for (counter10 = 0; counter10 < counter2; counter10++)
		{
			if (answer[counter10] >= 0 && answer[counter10] <= 25)
			{
				answer2[counter10] = answer[counter10] + 97;
				// Remaining value of op_right stored in answer is made into ASCII upper case and stored in answer2.
				if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 65;
					}
			}
			else if (answer[counter10] >= 26 && answer[counter10] <= 46)
			{
				answer2[counter10] = answer[counter10] + 39;
				// Remaining value of op_right stored in answer is made into ASCII lower case and stored into answer2.
				if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 71;
					}
			}
			// Mod47 value if the value is greater than 46 from array answer and converted into ASCII and stored into answer2.
			else if (answer[counter10] > 46)
    			{
    				answer[counter10] = answer[counter10]%47;
    				if (answer[counter10] >= 0 && answer[counter10] <= 25)
    				{
    					answer2[counter10] = answer[counter10] + 97;
    					if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 65;
					}
    				}
    				else if (answer[counter10] >= 26 && answer[counter10] <= 46)
    				{
    					answer2[counter10] = answer[counter10] + 39;
    					if (counter10 >= counter1)
					{
						answer2[counter10] = answer[counter10] + 71;
					}
    				}		
    			}
		}
		answer2[counter10] = '\0';
		// Stores final answer into result.
		for (counter11 = 0; counter11 < counter2; counter11++)
		{
			result[counter11] = answer2[counter11];
		}
		result[counter11] = '\0';
	}	
    }
    
    // If op is equal to '/' this runs.
    if (op == DIV)
    {
    	// Makes character array into an integer array for both l_op and r_op.
    	for (counter1 = 0; l_op[counter1] != '\0'; counter1++)
    	{
    		if (l_op[counter1] >= 'a' && l_op[counter1] <= 'z')
    		{
    			op_left[counter1] = l_op[counter1] - 97;
    		}
    		else if (l_op[counter1] >= 'A' && l_op[counter1] <= 'U')
    		{
    			op_left[counter1] = l_op[counter1] - 39;
    		}
    	}
    	op_left[counter1] = '\0';
    	for (counter2 = 0; r_op[counter2] != '\0'; counter2++)
    	{
    		if (r_op[counter2] >= 'a' && r_op[counter2] <= 'z')
    		{
    			op_right[counter2] = r_op[counter2] - 97;
    		}
    		else if (r_op[counter2] >= 'A' && r_op[counter2] <= 'U')
    		{
    			op_right[counter2] = r_op[counter2] - 39;
    		}
    	}
    	op_right[counter2] = '\0';
    	// If op_right and op_left have the same size, this will run.
    	if (counter1 == counter2)
    	{
    		// Stores division of op_left and op_right into integer array answer.
    		for (counter3 = 0; counter3 < counter1; counter3++)
    		{
    			for (counter4 = 0; counter4 < 47; counter4++)
    			{
    				if (op_left[counter3] == ((op_right[counter3] * counter4) %47))
    				{
    					answer[counter3] = counter4;
    				}
    				// If division by 0, it will set answer to 0.
    				else if (op_right[counter3] == 0)
    				{
    					answer[counter3] = 0;
    				}
    			}
    		}
    		answer[counter3] = '\0';	
    		// Converst values into ASCII code and stores it into character array answer2.
    		for (counter5 = 0; counter5 < counter1; counter5++)
    		{
    			if (answer[counter5] >= 0 && answer[counter5] <= 25)
    			{
    				answer2[counter5] = answer[counter5] + 97;
    			}
    			else if (answer[counter5] >= 26 && answer[counter5] <= 46)
    			{
    				answer2[counter5] = answer[counter5] + 39;
    			}
    			// If division is greater than 46, it will mode47 the value and make it into ASCII 
    			else if (answer[counter5] > 46)
    			{
    				answer[counter5] = answer[counter5] % 47;
    				if (answer[counter5] >= 0 && answer[counter5] <= 25)
    				{
    					answer2[counter5] = answer[counter5] + 97;
    				}
    				else if (answer[counter5] >= 26 && answer[counter5] <= 46)
    				{
    					answer2[counter5] = answer[counter5] + 39;
    				}
    			}
    		}
    		answer2[counter5] = '\0';
    		// Stores final answer into result.
    		for (counter6 = 0; counter6 < counter1; counter6++)
    		{
    			result[counter6] = answer2[counter6];
    		}
    		result[counter6] = '\0';
    	}
    	
    	// If op_left length is greater than op_right length, it will divide same amount of time as length of op_right and will store remainding last characters of op_left into answers.
    	if (counter1 > counter2)
    	{	// Stores division of op_left and op_right into answer until length are no longer equal.
    		for (counter6 = 0; counter6 < counter2; counter6++)
    		{
    			for (counter7 = 0; counter7 < 47; counter7++)
    			{
    				if(op_left[counter6] == (op_right[counter6]*counter7)%47)
    				{
    					answer[counter6] = counter7;
    				}
    				else if (op_right[counter6] == 0)
    				{
    					answer[counter6] = 0;
    				}
    			}
    		}
    		// Stores remaining values of op_left into integer array answer.
    		for (counter8 = counter6; counter8 < counter1; counter8++)
    		{
    			if (op_left[counter8] >= 0 && op_left[counter8] <= 25)
    			{
    				answer[counter8] = op_left[counter8];
    			}
    			else if(op_left[counter8] >= 26 && op_left[counter8] <= 46)
    			{
    				answer[counter8] = op_left[counter8];
    			}
    		}
    		answer[counter8] = '\0';
    		// Converts values of answer into ASCII and stored into character array answer2.
    		for (counter9 = 0; counter9 < counter1; counter9++)
    		{
    			if (answer[counter9] >= 0 && answer[counter9] <= 25)
    			{
    				answer2[counter9] = answer[counter9] + 97;
    				if (counter9 >= counter2)
    				{
    					answer2[counter9] = answer[counter9] + 65;
    				}
    			}
    			else if (answer[counter9] >= 26 && answer[counter9] <= 46)
    			{
    				answer2[counter9] = answer[counter9] + 39;
    				if (counter9 >= counter2)
    				{
    					answer2[counter9] = answer[counter9] + 71 ;
    				}
    			}
    		}
    		answer2[counter9] = '\0';
    		for (counter10 = 0; counter10 < counter1; counter10++)
    		{
    			result[counter10] = answer2[counter10];
    		}
    		result[counter10] = '\0';
    	}
    	
    	// If op_right length is greater than op_left length, it will compare both sizes and then store remaining numbers into integer array answer and then make them ASCII codes and store into character array answer2 and then stores answer2 into result.
    	if (counter2 > counter1)
    	{
    		for (counter10 = 0; counter10 < counter1; counter10++)
    		{
    			for (counter11 = 0; counter11 < 47; counter11++)
    			{
    				if (op_left[counter10] == (op_right[counter10]*counter11)%47)
    				{
    					answer[counter10] = counter11;
    				}
    				else if (op_right[counter10] == 0)
    				{
    					answer[counter10] = 0;
    				}
    			}
    		}
    		for (counter12 = counter10; counter12 < counter2; counter12++)
    		{
    			if (op_right[counter12] >= 0 && op_right[counter12] <= 25)
    			{
    				answer[counter12] = op_right[counter12];
    			}
    			else if (op_right[counter12] >= 26 && op_right[counter12] <= 46)
    			{
    				answer[counter12] = op_right[counter12];
    			}
    		}
    		answer[counter12] = '\0';
    		for (counter13 = 0; counter13 < counter2; counter13++)
    		{
    			if (answer[counter13] >= 0 && answer[counter13] <= 25)
    			{
    				answer2[counter13] = answer[counter13] + 97;
    				if (counter13 >= counter1)
    				{
    					answer2[counter13] = answer[counter13] + 65;
    				}
    			}
    			else if (answer[counter13] >= 26 && answer[counter13] <= 46)
    			{
    				answer2[counter13] = answer[counter13] + 39;
    				if (counter13 >= counter1)
    				{
    					answer2[counter13] = answer[counter13] + 71;
    				}
    			}
    			else if (answer[counter13] > 46)
    			{
    				answer[counter13] = answer[counter13] % 47;
    				if (answer[counter13] >= 0 && answer[counter13] <= 25)
    				{
    					answer2[counter13] = answer[counter13] + 97;
    					if (counter13 >= counter1)
    					{
    						answer2[counter13] = answer[counter13] + 65;
    					}
    				}
    				if (answer[counter13] >= 26 && answer[counter13] <= 46)
    				{
    					answer2[counter13] = answer[counter13] + 39;
    					if (counter13 >= counter1)
    					{
    						answer2[counter13] = answer[counter13] + 71;
    					}
    				}
    			}
    		}
    		answer2[counter13] = '\0';
    		for (counter14 = 0; counter14 < counter2; counter14++)
    		{
    			result[counter14] = answer2[counter14];
    		}
    		result[counter14] = '\0';
    		
    	}
    	
    }
    
    
    // If op is equal to '^' this will run.
    if (op == POW)
    {
    	// Makes character array into an integer array for both l_op and r_op.
    	for (counter1 = 0; l_op[counter1] != '\0'; counter1++)
    	{
    		if (l_op[counter1] >= 'a' && l_op[counter1] <= 'z')
    		{
    			op_left[counter1] = l_op[counter1] - 97;
    		}
    		else if (l_op[counter1] >= 'A' && l_op[counter1] <= 'U')
    		{
    			op_left[counter1] = l_op[counter1] - 37;
    		}
    	}
    	op_left[counter1] = '\0';
    	for (counter2 = 0; r_op[counter2] != '\0'; counter2++)
    	{
    		if (r_op[counter2] >= 'a' && r_op[counter2] <= 'z')
    		{
    			op_right[counter2] = r_op[counter2] - 97;
    		}
    		else if (r_op[counter2] >= 'A' && r_op[counter2] <= 'U')
    		{
    			op_right[counter2] = r_op[counter2] - 39;
    		}
    	}
    	op_right[counter2] = '\0';
    	// If both op_left and op_right have the same length, this runs.
    	if (counter1 == counter2)
    	{	
    		for (counter3 = 0; counter3 < counter1; counter3++)
    		{	
    			z = 1;
    			// Calculates op_left to the power of op_right and stores it in integer array answer.
    			for (counter4 = 0; counter4 < op_right[counter3] || counter4 == op_right[counter3]; counter4++)
    			{
    				if (op_right[counter3] > 1)
    				{
    					z = z * (op_left[counter3] % 47);
    					z = z%47;
    					if (counter4 == op_right[counter3] - 1)
    					{
    						answer[counter3] = z;
    					}
    				}
    				// If op_right is 0, 1 will be stored into answer.
    				else if (op_right[counter3] == 0)
    				{
    					answer[counter3] = 1;
    				}
    				// If op_right is1, same value of op_left is stored into answer.
    				else if (op_right[counter3] == 1)
    				{
    					answer[counter3] = op_left[counter3];
    				}
    			}
    		}
    		answer[counter3] = '\0';
    		// Converts values of answer into ASCII and stores it into character array answer2.
    		for (counter5 = 0; counter5 < counter1; counter5++)
    		{
    			if (answer[counter5] >= 0 && answer[counter5] <= 25)
    			{
    				answer2[counter5] = answer[counter5] + 97;
    			}
    			else if (answer[counter5] >= 26 && answer[counter5] <= 46)
    			{
    				answer2[counter5] = answer[counter5]  + 39;
    			}
    			// If the answer is greater than 46, it will mod47 the answers and store it in value and then make it ASCII and then store it into character array answer2.
    			else if (answer[counter5] > 46)
    			{
    				answer[counter5] = answer[counter5] % 47;
    				if (answer[counter5] >= 0 && answer[counter5] <= 25)
    				{
    					answer2[counter5] = answer[counter5] + 97;
    				}
    				else if (answer[counter5] >= 26 && answer[counter5] <= 46)
    				{
    					answer2[counter5] = answer[counter5] + 39;
    				}
    			}
    		}
    		answer2[counter5] = '\0';
    		// Stores final answer into result.
    		for (counter6 = 0; counter6 < counter1; counter6++)
    		{
    			result[counter6] = answer2[counter6];
    		}
    		result[counter6] = '\0';
    	}
    	// If length of op_left is greater than op_right this runs.
    	if (counter1 > counter2)
    	{
    		// Calculates op_left raised to op_right until both lengths are not the same and stores it into integer array answer.
    		for (counter7 = 0; counter7 < counter2; counter7++)
    		{
    			z = 1;
    			for (counter8 = 0; counter8 < op_right[counter7] || counter8 == op_right[counter7]; counter8++)
    			{
    				if (op_right[counter7] > 1)
    				{
    					z = z * (op_left[counter7] % 47);
    					z = z % 47;
    					if (counter8 == op_right[counter7] - 1)
    					{
    						answer[counter7] = z;
    					}
    				}
    				// If op_left is raised to 0, answer will be always 1 and stored into answer.
    				else if (op_right[counter7] == 0)
    				{
    					answer[counter7] = 1;
    				}
    				// If op_left is raised to 1, answer will always equal value of op_left and stores it into answer.
    				else if (op_right[counter7] == 1)
    				{
    					answer[counter7] = op_left[counter7];
    				}
    			}
    		}
    		// Stores remaining values of op_left into integer array answer.
    		for (counter9 = counter7; counter9 < counter1; counter9++)
    		{
    			if (op_left[counter9] >= 0 && op_left[counter9] <= 25)
    			{
    				answer[counter9] = op_left[counter9];
    			}
    			else if (op_left[counter9] >= 26 && op_left[counter9] <= 46)
    			{
    				answer[counter9] = op_left[counter9];
    			}
    		}
    		answer[counter9] = '\0';
    		// Converts values into ASCII and stores it into character array answer2.
    		for (counter10 = 0; counter10 < counter1; counter10++)
    		{
    			if (answer[counter10] >= 0 && answer[counter10] <= 25)
    			{
    				answer2[counter10] = answer[counter10] + 97;
    				// Remaining values of op_left are turned into ASCII and into lower case.
    				if (counter10 >= counter2)
    				{
    					answer2[counter10] = answer[counter10] + 65;
    				}
    			}
    			else if (answer[counter10] >= 26 && answer[counter10] <= 46)
    			{
    				answer2[counter10] = answer[counter10] + 39;
    				// Remaining values of op_left are turned into ASCII and into upper case.
    				if (counter10 >= counter2)
    				{
    					answer2[counter10] = answer[counter10] + 71;
    				}
    			}
    			// If value of answer is greater than 46, it will take the mod47 of answer, store it, converted to ASCII, and store it into asnwer2.
			else if (answer[counter10] > 46)
			{
				answer[counter10] = answer[counter10] % 47;
				if (answer[counter10] >= 0 && answer[counter10] <= 25)
				{
					answer2[counter10] = answer[counter10] + 97;
					// Remaining value stored from op_left are converted to capital letters.
					if (counter10 >= counter2)
					{
						answer2[counter10] = answer[counter10]  + 65;
					}
				}
				if (answer[counter10] >= 26 && answer[counter10] <= 46)
				{
					answer2[counter10] = answer[counter10] + 39;
					// Remaining value stored from op_left are converted to lower case.
					if (counter10 >= counter2)
					{
						answer2[counter10] = answer[counter10] + 71;
					}
				}
			}
    		}
    		answer2[counter10] = '\0';
    		// Final answer is stored in result.
    		for (counter11 = 0; counter11 < counter1; counter11++)
    		{
    			result[counter11] = answer2[counter11];
    		}
    		result[counter11] = '\0';
    	}
    	// If length of op_right is greater than op_left, this runs.
    	if (counter2 > counter1)
    	{
    		for (counter12 = 0; counter12 < counter1; counter12++)
    		{
    			z = 1;
    			// Calculates op_left raised to op_right until lengths are not equal and stores it into integer array answer.
    			for (counter13 = 0; counter13 < op_right[counter12] || counter13 == op_right[counter13]; counter13++)
    			{
    				if (op_right[counter12] > 1)
    				{
    					z = z * (op_left[counter12] % 47);
    					z = z % 47;
    					if (counter13 == op_right[counter12] - 1)
    					{
    						answer[counter12] = z;
    					}
    				}
    				// If op_right is equal to zero, answer will be set to zero.
    				else if (op_right[counter12] == 0)
    				{
    					answer[counter12] = 0;
    				}
    				// If op_right is equal to 1, answer is set to value of op_left.
    				else if (op_right[counter12] == 1)
    				{
    					answer[counter12] = op_left[counter12];
    				}
    			}
    		}
    		// Stores remaining values of op_right into answer.
    		for (counter14 = counter12; counter14 < counter2; counter14++)
    		{
    			if (op_right[counter14] >= 0 && op_right[counter14] <= 25)
    			{
    				answer[counter14] = op_right[counter14];
    			}
    			else if (op_right[counter14] >= 26 && op_right[counter14] <= 46)
    			{
    				answer[counter14] = op_right[counter14];
    			}
    		}
    		answer[counter14] = '\0';
    		// Converts values into ASCII and stored into asnwer2.
    		for (counter15 = 0; counter15 < counter2; counter15++)
    		{
    			if (answer[counter15] >= 0 && answer[counter15] <= 25)
    			{
    				answer2[counter15] = answer[counter15] + 97;
    				// Converts remaining values of op_right to ASCII and into upper case.
    				if (counter15 >= counter1)
    				{
    					answer2[counter15] = answer[counter15] + 65;
    				}
    			}
    			else if (answer[counter15] >= 26 && answer[counter15] <= 46)
    			{
    				answer2[counter15] = answer[counter15] + 39;
    				// Converts remaining values of op_right to ASCII and into lower case.
    				if (counter15 >= counter1)
    				{
    					answer2[counter15] = answer[counter15] + 71;
    				}
    			}
    			// If answer is greater than 46, it will mode47 the answer and store it in answer and convert it to ASCII and store into answer2.
    			else if (answer[counter15] > 46)
    			{
    				answer[counter15] = answer[counter15] % 47;
    				if (answer[counter15] >= 0 && answer[counter15] <= 25)
    				{
    					answer2[counter15] = answer[counter15] + 97;
    					if (counter15 >= counter1)
    					{
    						answer2[counter15] = answer[counter15] + 65;
    					}
    				}
    				if (answer[counter15] >= 26 && answer[counter15] <= 46)
    				{
    					answer2[counter15] = answer[counter15] + 39;
    					if (counter15 >= counter1)
    					{
    						answer2[counter15] = answer[counter15] + 71;
    					}
    				}
    			}
    		}
    		answer2[counter15] = '\0';
    		// Stores final answer into answer2.
    		for (counter16 = 0; counter16 < counter2; counter16++)
    		{
    			result[counter16] = answer2[counter16];
    		}
    		result[counter16] = '\0';
    	}
    	
    	
    }
    
}

