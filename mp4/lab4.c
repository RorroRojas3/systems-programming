/* lab4.c template
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 * MP4
 * Subject: ECE222-1,#4
 *
 * Purpose: A simple file editor that can handle files with characters
 *          that are not printable.
 *
 *          The editor can find and replace any byte in the file.  In
 *          addition it can find any string.
 *
 * Assumptions: 
 *     input file is read in as bytes
 *
 * Command line argument
 *   name of file to read
 *
 * Bugs:
 *
 * Notes:
 *
 * See the ECE 222 programming guide
 *
 * Format with
 *     astyle --style=kr lab3.c
 *
 * Replace "kr" with: bsd, ansi, java, gnu, linux, vtk, or google. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAXLINE 128

/*----------------------------------------------------------*/
/* Here is a sketch for a start to searching for a byte
 *
 * Search for a matching byte starting after position.  Wrap around
 *    to beginning of memory until found or return to starting position
 *
 * input:
 *     byte is a string with the hex characters for the byte to find
 *     mem_start is starting address of the data
 *     mem_size is the number of bytes in the memory block
 * input/output:
 *     position is the location of the cursor.  If the byte is found
 *     then position is updated to the memory offset for the match
 *     If the byte is NOT found, then position is not changed
 * return value:
 *     true if byte found
 */
 
 // Calculates the binary digit in decimal.
 int power(int power)
 {
 	int counter1 = 0;
 	int result = 1;
 	for (counter1 = 0; counter1 <= power; counter1++)
 	{
 		if (power == 0)
 		{
 			result = 1;
 		}
 		else if (counter1 > 0)
 		{
 			result = result * 2;
 		}
 	}
 	return result;
 }
 
 
 
 
int find_next_byte_match(int *position, char *byte, char *mem_start, int mem_size)
{
    // Variable Declaration Section.
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    unsigned int count1 = 0;
    unsigned int count2 = 0;
    char bascii;
    int total_count = 0;
    int b0;
    int b1;
    int found = 0;
    
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte[0] >= 65 && byte[0] <= 90)
    {
    	b0 = byte[0] - 55;
    }
    // Makes hexadecimal numbers 0 through 9 into corresponding decimal values.
    else if (byte[0] >= 48 && byte[0] <= 57)
    {
    	b0 = byte[0] - 48;
    }
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte[1] >= 65 && byte[1] <= 90)
    {
    	b1 = byte[1] - 55;
    }
    // Makes hexadecimal number 0 through 9 into their corresponding decimal values. 
    else if (byte[1] >= 48 && byte[1] <= 57)
    {
    	b1 = byte[1] - 48;
    }
 
    // Calculates the decimal number of byte.
    for (counter1 = 3 ;counter1 >= 0; counter1--)
    {
    	if ((b0 & (1 << counter1)) >> counter1 == 1)
    	{
    		count1 = count1 + power(counter1 + 4);
    	}
    } 
    for (counter2 = 3; counter2 >= 0; counter2--)
    {
    	if ((b1 & (1 << counter2)) >> counter2 == 1)
    	{
    		count2 = count2 + power(counter2);
    	}
    }
    
    // Stores addition of count1 and count2 into total_count
    total_count = count1 + count2;
    // Stores decimal value of byte into character bascii.
    bascii = total_count;
    // Stores position after position.
    counter3 = *position + 1;
  		
    // Goes through dynamic memory and sees if bascii is equal to any character in the dynamic memory.		
    for (counter3 = counter3; counter3 < mem_size; counter3++)
    {
    	// If bascii is equal to character in dynamic memory, will set found to 1 and will break from the loop.
    	if (bascii == *(mem_start + counter3))
    	{
    		
    		found = 1;
    		break;
    	}
    	// If position gets to value mem_size -1, it wil set counter3 to 0 and will start looking from the start.
    	if (counter3 == mem_size - 1)
    	{
    		counter3 = -1;
    	}
    	// If the bascii value was not found in a whole loop, it will set found to 0 and will break from loop.
    	if (counter3 == *position)
    	{
    		found = 0;
    		break;
    	}
    }
    
    // If bascii value is found, it will store the new position into pointer position.
    if (found == 1)
    {
    	*position = counter3;
    }
    
    
    
    

    return found;
}
/*----------------------------------------------------------*/
/* Here is a sketch for a start to searching for a string
 *
 * Search for a matching string starting after position.  Wrap around
 *    to beginning of memory until found or return to starting position
 *
 *    Note: the string does not match if it overlaps both the characters
 *          at the end and the beginning of memory.
 *
 * input:
 *     str      : string to find.  It has already been processed to remove escapes
 *     wild_pos : -1 if no wildcard, or position in str with the wildcard
 *     mem_start: starting address of the data
 *     mem_size : the number of bytes in the memory block
 *
 * input/output:
 *     position is the location of the cursor.  If the string is found
 *     the position is updated to the memory offset for the first byte
 *     that matchs the string
 * return value:
 *     true if string found
 *
 */
int find_next_string(int *position, const char *str, int wild_pos, 
        char *mem_start, int mem_size)
{
   
    int counter1 = 0;
    int counter2 = *position + 1;
    int counter3 = 0;
    int counter4 = 0;
    int new_position = 0;
    int length = 0;
    int match = 0;
    int found = -1;
  	
    //Calculate the length of string
    for (counter1 = 0; str[counter1] != '\0'; counter1++)
    {
    	length++;
    }	
    
    if (str[0] != '.' && wild_pos > 0) // If the string entered has a wildcard greater at position greater than 0 and is not the first character, this runs.
    {
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		if (str[0] == *(mem_start + counter2))
    		{
    			match = 1;
    			new_position = counter2; // Stores where counter2 obtained position where str[0] equal same character as dynamic memory.
    			counter3 = 1;
   		}
    	
    		counter4 = counter2 + 1; // Increases location by one if for loop searching for same characters breaks.
    		if (match == 1)
    		{
    			for (counter3 = counter3; counter3 < length; counter3++) // This will search if next characters are same as string.
    			{
    				if (str[counter3] == *(mem_start + counter4)) // If the character of string and character in dynamic memory are same, adds one to match.
    				{
    					match++;
    				}
    				else if (str[wild_pos] == '.' && wild_pos == counter3) // If the character in the wild_position and character str[counter3] are the same, match adds one.
    				{
    					match++;
    				}
    				else // If characters are not the same, sets match to 0.
    				{
    					match = 0; 
    				}
    				counter4++;
    			}
    		}
    		if (match == length) // If match is equal to the length, means that string was found, position is updates, and it breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If position was not found in the range, it loops around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If position loops around and ends up at original position, it did not find a match therefore it make found equal to -1 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    		
    	}
    	
    }
    
    if (str[0] != '.' && wild_pos == -1) // If the string entered is does not have a wildcard this runs.
    {
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		
    		if (str[0] == *(mem_start + counter2))
    		{
    			match = 1;
    			new_position = counter2; // Stores where counter2 obtained position where str[0] equal same character as dynamic memory.
    			counter3 = 1;
   		}
    	
    		counter4 = counter2 + 1; // Increases location by one if for loop searching for same characters breaks.
    		if (match == 1)
    		{
    			for (counter3 = counter3; counter3 < length; counter3++) // This will search if next characters are same as string.
    			{
    				if (str[counter3] == *(mem_start + counter4)) // If the character of string and character in dynamic memory are same, adds one to match.
    				{
    					match++;
    				}
    				else // If characters are not the same, sets match to 0.
    				{
    					match = 0; 
    				}
    				counter4++;
    			}
    		}
    		if (match == length) // If match is equal to the length, means that string was found, position is updates, and it breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If position was not found in the range, it loops around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If position loops around and ends up at original position, it did not find a match therefore it make found equal to -1 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    		
    	}
    }
    
    if (str[0] == '.' && wild_pos == 0) //If the wildcard is positioned in position 0, this will run.
    {
    	counter2 = *position + 2;
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		if (str[1] == *(mem_start + counter2)) // If position one of str is equal to character in dynamic memory, it will run.
    		{
    			match = 2;
    			new_position = counter2 - 1;
    			counter3 = 2;
    		}
    		counter4 = counter2 + 1;
    		if (match == 2 && match != length) // If match is equal to 2 and is not equal to the length, this will run.
    		{
    			for (counter3 = 2; counter3 < length; counter3++)
    			{
    				if (str[counter3] == *(mem_start + counter4)) // Adds one to match if character of str is same of dynamic memory
    				{
    					match++;
    				}
    				else
    				{
    					match = 0; //If not equal match is 0.
    				}
    				counter4++;
    			}
    		}
    		if (match == length) //If there is match, found is set to 1, position changed, and breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If it has searched through all memory, loops back around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If loops around and does not find anything and ends up at starting position, found is set to 0 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    	}
    }
    
    	
     
   	
   
    return found;
}
/*----------------------------------------------------------*/
/* Here is a sketch for a start to replacing a string
 *
 * Search for a matching string starting after position.  Wrap around
 *    to beginning of memory until found or return to starting position
 *
 *    Note: the string does not match if it overlaps both the characters
 *          at the end and the beginning of memory.
 *
 * input:
 *     str      : string to find.  It has already been processed to remove escapes
 *     wild_pos : -1 if no wildcard, or position in str with the wildcard
 *     rstr     : string for replacement
 *     mem_start: starting address of the data
 *     mem_size : the number of bytes in the memory block
 *
 * input/output:
 *     position is the location of the cursor.  If the string is found
 *     the position is updated to the memory offset for the first byte
 *     that matchs the string
 * return value:
 *     true if string found
 */
int replace_next_string(int *position, char *str, int wild_pos, char *rstr, 
        char *mem_start, int mem_size)
{
    int counter1 = 0;
    int counter2 = *position + 1;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int new_position = 0;
    int length = 0;
    int match = 0;
    int found = -1;
  	
    //Calculate the length of string
    for (counter1 = 0; str[counter1] != '\0'; counter1++)
    {
    	length++;
    }	
    
    if (str[0] != '.' && wild_pos > 0) // If the string entered has a wildcard greater at position greater than 0 and is not the first character, this runs.
    {
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		if (str[0] == *(mem_start + counter2))
    		{
    			match = 1;
    			new_position = counter2; // Stores where counter2 obtained position where str[0] equal same character as dynamic memory.
    			counter3 = 1;
   		}
    	
    		counter4 = counter2 + 1; // Increases location by one if for loop searching for same characters breaks.
    		if (match == 1)
    		{
    			for (counter3 = counter3; counter3 < length; counter3++) // This will search if next characters are same as string.
    			{
    				if (str[counter3] == *(mem_start + counter4)) // If the character of string and character in dynamic memory are same, adds one to match.
    				{
    					match++;
    				}
    				else if (str[wild_pos] == '.' && wild_pos == counter3) // If the character in the wild_position and character str[counter3] are the same, match adds one.
    				{
    					match++;
    				}
    				else // If characters are not the same, sets match to 0.
    				{
    					match = 0; 
    				}
    				counter4++;
    			}
    		}
    		if (match == length) // If match is equal to the length, means that string was found, position is updates, and it breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If position was not found in the range, it loops around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If position loops around and ends up at original position, it did not find a match therefore it make found equal to -1 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    		
    	}
    	if (found == 1)
    	{
    		for (counter5 = new_position; counter5 < length + new_position; counter5++) // If string is found, replaces string in dynamic memory with rstr characters.
    		{
    			*(mem_start + counter5) = rstr[counter6];
    			counter6++;
    		}
    	}
    	
    }
    
    if (str[0] != '.' && wild_pos == -1) // If the string entered is does not have a wildcard this runs.
    {
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		if (str[0] == *(mem_start + counter2))
    		{
    			match = 1;
    			new_position = counter2; // Stores where counter2 obtained position where str[0] equal same character as dynamic memory.
    			counter3 = 1;
   		}
    		counter4 = counter2 + 1; // Increases location by one if for loop searching for same characters breaks.
    		if (match == 1)
    		{
    			for (counter3 = counter3; counter3 < length; counter3++) // This will search if next characters are same as string.
    			{
    				if (str[counter3] == *(mem_start + counter4)) // If the character of string and character in dynamic memory are same, adds one to match.
    				{
    					match++;
    				}
    				else // If characters are not the same, sets match to 0.
    				{
    					match = 0; 
    				}
    				counter4++;
    			}
    		}
    		if (match == length) // If match is equal to the length, means that string was found, position is updates, and it breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If position was not found in the range, it loops around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If position loops around and ends up at original position, it did not find a match therefore it make found equal to -1 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    		if (str[0] == *(mem_start + counter2))
    		{
    			match = 1;
    			new_position = counter2; // Stores where counter2 obtained position where str[0] equal same character as dynamic memory.
    			counter3 = 1;
   		}
    	}
    	if (found == 1)
    	{
    		for (counter5 = new_position; counter5 < length + new_position; counter5++) // If string is found, replaces string in dynamic memory with rstr characters.
    		{
    			*(mem_start + counter5) = rstr[counter6];
    			counter6++;
    		}
    	}
    }
    
    if (str[0] == '.' && wild_pos == 0) //If the wildcard is positioned in position 0, this will run.
    {
    	counter2 = *position + 2;
    	for (counter2 = counter2; counter2 < mem_size; counter2++)
    	{
    		if (str[1] == *(mem_start + counter2)) // If position one of str is equal to character in dynamic memory, it will run.
    		{
    			match = 2;
    			new_position = counter2 - 1;
    			counter3 = 2;
    		}
    		counter4 = counter2 + 1;
    		if (match == 2 && match != length) // If match is equal to 2 and is not equal to the length, this will run.
    		{
    			for (counter3 = 2; counter3 < length; counter3++)
    			{
    				if (str[counter3] == *(mem_start + counter4)) // Adds one to match if character of str is same of dynamic memory
    				{
    					match++;
    				}
    				else
    				{
    					match = 0; //If not equal match is 0.
    				}
    				counter4++;
    			}
    		}
    		if (match == length) //If there is match, found is set to 1, position changed, and breaks from loop.
    		{
    			found = 1;
    			*position = new_position;
    			break;
    		}
    		if (counter2 == mem_size - 1) // If it has searched through all memory, loops back around.
    		{
    			counter2 = -1;
    		}
    		if (counter2 == *position) // If loops around and does not find anything and ends up at starting position, found is set to 0 and breaks from loop.
    		{
    			found = 0;
    			break;
    		}
    	}
    	if (found == 1) // If string is found, replaces string in dynamic memory with rstr characters.
    	{
    		for (counter5 = new_position; counter5 < length + new_position; counter5++)
    		{
    			*(mem_start + counter5) = rstr[counter6];
    			counter6++;
    		}
    	}
    }
    
    	
     
    
    
    
    

    return found;
}
/*----------------------------------------------------------*/
/* Here is a sketch for a start to search and replace byte 
 *
 * Search for a matching byte starting after position.  Wrap around
 *    to beginning of memory until found or return to starting position
 *
 * input:
 *     byte_to_find is a string with the hex characters for the byte to find
 *     byte_to_replace is a string with the hex characters to replace 
 *     mem_start is starting address of the data
 * input/output:
 *     position is the location of the cursor.  If the byte is replaced
 *     then position is updated to the memory offset for the match
 *     If the byte is NOT found, then position is not changed
 * return value:
 *     true if byte replaced
 */
int replace_next_byte(int *position, char *byte_to_find, char *byte_to_replace, 
        char *mem_start, int mem_size)
{
       // Variable Declaration Section.
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    unsigned int count1 = 0;
    unsigned int count2 = 0;
    unsigned int count3 = 0;
    unsigned int count4 = 0;
    char bascii;
    char replacement;
    int total_count = 0;
    int total_count2 = 0;
    int b0;
    int b1;
    int b2;
    int b3;
    int found = 0;
    
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte_to_find[0] >= 65 && byte_to_find[0] <= 90)
    {
    	b0 = byte_to_find[0] - 55;
    }
    // Makes hexadecimal numbers 0 through 9 into corresponding decimal values.
    else if (byte_to_find[0] >= 48 && byte_to_find[0] <= 57)
    {
    	b0 = byte_to_find[0] - 48;
    }
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte_to_find[1] >= 65 && byte_to_find[1] <= 90)
    {
    	b1 = byte_to_find[1] - 55;
    }
    // Makes hexadecimal number 0 through 9 into their corresponding decimal values. 
    else if (byte_to_find[1] >= 48 && byte_to_find[1] <= 57)
    {
    	b1 = byte_to_find[1] - 48;
    }
 
    // Calculates the decimal number of byte.
    for (counter1 = 3 ;counter1 >= 0; counter1--)
    {
    	if ((b0 & (1 << counter1)) >> counter1 == 1)
    	{
    		count1 = count1 + power(counter1 + 4);
    	}
    } 
    for (counter2 = 3; counter2 >= 0; counter2--)
    {
    	if ((b1 & (1 << counter2)) >> counter2 == 1)
    	{
    		count2 = count2 + power(counter2);
    	}
    }
    
    // Stores addition of count1 and count2 into total_count
    total_count = count1 + count2;
    // Stores decimal value of byte into character bascii.
    bascii = total_count;
    // Stores position after position.
    counter3 = *position + 1;
  		
    // Goes through dynamic memory and sees if bascii is equal to any character in the dynamic memory.		
    for (counter3 = counter3; counter3 < mem_size; counter3++)
    {
    	// If bascii is equal to character in dynamic memory, will set found to 1 and will break from the loop.
    	if (bascii == *(mem_start + counter3))
    	{
    		
    		found = 1;
    		break;
    	}
    	// If position gets to value mem_size -1, it wil set counter3 to 0 and will start looking from the start.
    	if (counter3 == mem_size - 1)
    	{
    		counter3 = -1;
    	}
    	// If the bascii value was not found in a whole loop, it will set found to 0 and will break from loop.
    	if (counter3 == *position)
    	{
    		found = 0;
    		break;
    	}
    }
    
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte_to_replace[0] >= 65 && byte_to_replace[0] <= 90)
    {
    	b2 = byte_to_replace[0] - 55;
    }
    // Makes hexadecimal numbers 0 through 9 into corresponding decimal values.
    else if (byte_to_replace[0] >= 48 && byte_to_replace[0] <= 57)
    {
    	b2 = byte_to_replace[0] - 48;
    }
    // Makes hexadecimal letters A through F into their corresponding decimal values.
    if (byte_to_replace[1] >= 65 && byte_to_replace[1] <= 90)
    {
    	b3 = byte_to_replace[1] - 55;
    }
    // Makes hexadecimal number 0 through 9 into their corresponding decimal values. 
    else if (byte_to_replace[1] >= 48 && byte_to_replace[1] <= 57)
    {
    	b3 = byte_to_replace[1] - 48;
    }
    
    // Calculates the decimal number of byte.
    for (counter4 = 3 ;counter4 >= 0; counter4--)
    {
    	if ((b2 & (1 << counter4)) >> counter4 == 1)
    	{
    		count3 = count3 + power(counter4 + 4);
    	}
    } 
    for (counter5 = 3; counter5 >= 0; counter5--)
    {
    	if ((b3 & (1 << counter5)) >> counter5 == 1)
    	{
    		count4 = count4 + power(counter5);
    	}
    }
    
    total_count2 = count3 + count4;
    replacement = total_count2;
    
    // If bascii value is found, it will store the new position into pointer position.
    if (found == 1)
    {
    	*position = counter3;
    	*(mem_start + counter3) = replacement;
    }
    

    return found;

}
/*----------------------------------------------------------*/
/* Here is a sketch for a start to printing a 16-byte aligned
 * line of text.
 *
 * input:
 *     position is the cursor location 
 *     slen is the length of the matching string (1 if just cursor position)
 *     mem_start is starting address of the data
 *     mem_size is the number of bytes in the memory block
 *
 * output:
 *     prints a 16-byte line of text that is aligned so that starting
 *     address is a multiple of 16
 *
 *     If slen is greater than one then continues to print 16-byte lines
 *     so that all characters in the string are displayed
 */
void print_line(int position, int slen, int wild_pos, char *mem_start, int mem_size)
{
	int bracket_position; 
	int offset;
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	int counter6 = 0;
	int counter7 = 0;
	int counter8 = 0;
	int counter9 = 0;
	int letter = 0;
	int hexnum;
	int length = slen;
	int reps = 0; 
	int approach;
	int next;
	int *ptrnext = &next;
	int case1 = 0;
	int wsp = 0;
	bracket_position = (position / 16) * 16;
	offset = position % 16;
	approach = bracket_position + offset + length;
	
	
	printf("\t ");

	// If either f or r command is called, it will print the sixteen bytes of memory with the position of the cursor.
	if (slen == 1)
	{
		for (counter1 = 0; counter1 < 16; counter1++) // Prints numbers 1 though 9
		{
			if (counter1 <= 9)
			{
				printf(" %d  ", counter1);
			}
			if (counter1 > 9)
			{
				printf(" %d  ", counter1 - 10);
			}	
		}
		printf("\n"); 
		printf("[%6d]", bracket_position); // Prints position inside the bracket
		for (counter1 = bracket_position; counter1 < (bracket_position + 16); counter1++) // Prints 16 characters in each position onlly if characters are printable.
		{
			if (isprint(mem_start[counter1]))
			{
				printf("  %c ", mem_start[counter1]);
			}
			else 
			{
				printf("    ");
			}
		}
		printf("\n\t ");
		for (counter2 = bracket_position; counter2 < (bracket_position + 16); counter2++) // Prints out the hexadecimal position of each character.
		{
			printf(" %02X ", (mem_start[counter2] & 0xFF));
			
			 
		} 
		printf("\n          ");
		for (counter3 = 0; counter3 < 16; counter3++) // Prints out the starting of position of searched letter or replaced letters which displays it with a "^"
		{
			if (offset == counter3)
			{ 
			printf("^");
			}
			else
			{
				printf("    ");
			}
		}
		
		printf("\n");
	}
	
	// If the user enters "/" or "s" this will runs since the length of the string is bigger than one.
	if (slen > 1)
	{
		for (counter1 = bracket_position; counter1 < approach; counter1 += 16) // Loop will run until counter1 is greater than approach.
		{
			for (counter2 = 0; counter2 < 16; counter2++) // Will print numbers 0 through 9
			{
				if (counter2 <= 9)
				{
					printf(" %d  ", counter2);
				}
				else if (counter2 > 9)
				{
					printf(" %d  ", counter2 - 10);
				}
			}
			
			printf("\n");
			
			printf("[%6d]", counter1); // Will display bracket_position
			printf(" ");
			letter = counter1;
			for (counter3 = 0; counter3 < 16; counter3++) // Will print characters of dynamic memory according to corresponding location.
			{
				if (isprint(mem_start[letter]))
				{
					printf(" %c  ", mem_start[letter]);
				}	
				else 
				{
					printf("    ");
				}
				letter++;
			}
			printf("\n");
			printf("         ");
			hexnum = counter1;
			for (counter4 = 0; counter4 < 16; counter4++) // Will display position of characters in hexadecimal numbers.
			{
				printf(" %02X ", mem_start[hexnum] & 0xFF);
				hexnum++;
			}			
			
			printf("\n          ");
			
			for (counter5 = 0; counter5 < offset && reps == 0; counter5++) // Will prints spaces until the offset is reached and the only runs the first time
			{
				printf("    ");
			}
			
			
			
			if (counter5 == offset) // Will print the starting position only the first time it loops around, if it does.
			{
				if (wild_pos != 0 && reps == 0)
				{
					printf("^ ");
				}
				else if (wild_pos == 0 && reps == 0)
				{
					printf("^*");
				}
			}
			counter7 = offset + 1;
			for (counter6 = 1; counter6 < length && reps == 0 && counter7 < 16; counter6++) // Will print dashes and the end line if only repeated once.
			{
				if (counter6 < length - 1 && counter6 != wild_pos ) // Prints dashes if the counter6 is less that length -1 and counter6 is not on wild position.
				{
					printf("----");
				}
				else if (counter6 < length - 1  && counter6 == wild_pos) // Prints dashes and a * if counter6 < length -1 in some decrease equals same position as wild card.
				{
					printf("--*-");
				}
				else if (counter6 < length && counter6 == wild_pos)
				{
					printf("--*");
					case1  = 1;
				}
				
				counter7++;
				*ptrnext = counter6 + 1; // Will store last position of counter6 in case there is repetition.
			}
			if (counter6 == length  && counter6 != wild_pos && reps == 0 && case1 != 1) // Prints the end of line if there is no wild card and if it does not repeat.
				{
					printf("---|");
				}
			if (counter6 == length && counter6 != wild_pos && reps == 0 && case1 == 1)
				{
					printf("|");
				}
			else if (counter6 == length  && counter6 == wild_pos && reps == 0) // Prints end of line if there is a wild card and if does not repeat.
				{
					printf("--*|");
				}
			counter9 = 0;
			for (counter8 = *ptrnext; counter8 < length && reps > 0 && counter9 < 16; counter8++)
			{
				if (counter8 < length - 1 && counter8 != wild_pos && counter9 != 15)
				{
					printf("----");
				}
				if (counter8 < length - 1 && counter8 == wild_pos && counter9 != 15)
				{
					printf("*---");
				}
				if (counter9 == 15)
				{
					printf("--");
				}
				counter9++;
			}
			*ptrnext = counter8;
			wsp = wild_pos + 1;
			if (counter8 == length && counter8 != wild_pos && counter8 != wsp && reps > 0)
			{
				printf("-|");
			}
			if (counter8 == length && counter8 == wsp && reps > 0)
			{
				printf("*|");
			}
			printf("\n");
			printf("\t ");
			reps++;
			
			
		}
		printf("\n");
		
		
		
		
		
	}
	

	
}

/*----------------------------------------------------------*/
/* Process the search string to remove escapes and identify the location
 * of the first wildcard symbol.
 *
 * input: inputstr is the string from the command
 * output:
 *    searchstr: a copy of the input string with the escapes removed
 *
 * the return value is
 *    -1: no wildcard symbol found
 *     X: the position in the searchstr with the first wildcard
 *
 * This function does not change the input string, and assumes that the pesky '\n'
 *      has been removed.
 *
 * Note that unlike for the s command to search and replace, it is NOT
 * possible for the input string to be invalid.  So there cannot be
 * an invalid input string for searches. 
 *
 * The only possible issue is if the '\' character is the LAST character
 * in the search string. We will take the convention that if the LAST
 * character is the '\' then it is NOT an escape, and should be a literal '\'.
 *
 * Example:
 *
 *   "\"  means search for '\' since the \ is the last character
 *   "\\" also means search for '\' since the first \ is an escape
 *
 *
 * This is not true for the s command (because that makes the dividing '/'
 * poorly defined).
 */
int process_search_string(const char *inputstr, char *searchstr)
{
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int length = 0;
    int backcount = 0;
    int wild_position = -1;
    
    for (counter5 = 0; inputstr[counter5] != '\0'; counter5++)
    {
    	length++;
    }
    
    
    // Stores inputstr (string entered by user) into searchstr.
    for (counter1 = 0; inputstr[counter1] != '\0'; counter1++)
    {
    	if (inputstr[counter1] == 92 && inputstr[length - 1] == 92)
    	{
    		searchstr[counter2] = inputstr[counter1];
    	}
    	if (inputstr[counter1] == 92 && inputstr[length -1] != 92)
    	{
    		searchstr[counter2] = inputstr[counter1 + 1];
    		counter1++;
    	}
    	else
    	{
    		searchstr[counter2] = inputstr[counter1];
    	}
    	counter2++;
    	
    }		
    searchstr[counter2] = '\0'; // Sets NULL to last character.
    
    // Calculates how many backlashes were entered in input string and accounts them to get the right wild card.
    for (counter4 = 0; inputstr[counter4] != '\0';counter4++)
    {
    	if (inputstr[counter4] == '.')
    	{
    		break;
    	}
    	if (inputstr[counter4] == 92 && inputstr[counter4 + 1] != '.')
    	{
    		backcount++;
    	}
    }
    
    // Searches for the wild card on searchstr. 
    for (counter3 = 0; inputstr[counter3] != '\0'; counter3++)
    {
    	if (inputstr[counter3] == 92)
    	{
    		counter3++;
    	}
    	else if (inputstr[counter3] == '.')
    	{
    		wild_position = counter3 - backcount;
    		break;
    	}
    	else
    	{
    		wild_position = -1;
    	}
    }
    
    

    return wild_position;
}


/* Simple test to verify that the replacement string has correct form.
 *
 * Input: inputstr
 * Output:
 *    searchstr: the search string with all escape '\' symbols removed
 *    replacestr: the string used to replace the search string.
 *
 *    the return value:
 *      -2 if there is any error in the strings
 *      -1 if the strings are correct and there is no wildcard
 *       X for some integer X if the input is correct and the first wildcard 
 *         is found at position X in the searchstr.
 *
 * This function does not change the input string, and assumes that the pesky '\n'
 *      has been removed.
 *
 * The string must start and end with a '/', and a '/' divides the input into
 * the searchstr and the replacestr.
 * .  
 * The shortest pattern has the form /a/b/
 *
 * The pattern must have the form /string1/string2/  
 * The string1 many contain one wildcard '.' symbol.  In addition, multiple 
 *    escape '\' symbols may be included.  
 *
 *    Process string1 to create the output searchstr.  Remove the escape symbols 
 *    and save the location of the first wildcard sybmol, if found.  
 *
 *    The length of searchstr must match the length of replacestr.
 *
 *    Note that the rule that the replacestr must have the same length as the
 *    searchstr (after escapes have been removed) means that there is no need
 *    for escapes '\' in the replacement string.  No wildcard symbols can be 
 *    included in the replacement string.
 *
 *    Examples
 *      s /Clems.n/Clemson/ -- a wildcard matches any byte but replaces it with 'o'
 *      s /Cl.ms.n/Clemson/ -- The first '.' is wildcard but the second '.' is 
 *                             a literal '.' and must be matched
 *      s /.ear./Here!/ -- The first '.' is a wildcard by the second is not.
 *      s /a\.b/a/b/  -- find the literal pattern "a.b" and change to "a/b". This
 *                       will not match a*b because the '.' is not a wildcard. 
 *                       Note that "a/b" does not cause confusion in finding the 
 *                       replacement string because the length of the replacement
 *                       string is known once "a\.b" is processed to "a.b"
 *      s /a\/b/a+b/ -- find the literal pattern "a/b" and replace with "a+b"
 *      s /a\\b/a/b/ -- find the literal pattern "a\b" and replace with "a/b"
 *
 */
int process_replace_string(const char *inputstr, char *searchstr, char *replacestr)
{
    // Variable Declaration Section.	
    int wild_position = -1;  // -1 means no wildcard found
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;
    int counter8 = 0;
    int counter9 = 0;
    int searchlength = 0;
    int replacelength = 0;
    int bch = 0;
    int ech = 0;
    int length = 0;
    int wlocation = 0;
    int backcount = 0;
    
    for (counter1 = 0; inputstr[counter1] != '\0'; counter1++) // Sees length of input string.
    {
    	length++;
    }
   
    bch = length - length; // Determines position 0 of input string.
    ech = length - 1; // Determines position of last character of input string.
    
    if (inputstr[bch] == '/' && inputstr[ech] == '/') // If start and end characters of inputstr are '/' this runs.
    {
    	for (counter2 = 1; inputstr[counter2] != '/'; counter2++) // Stores characters from inputstr into searchstr with all exceptions.
    	{
    		if (inputstr[counter2] == 92 && inputstr[counter2 + 1] == '/')
    		{
    			searchstr[counter3] = inputstr[counter2 + 1];
    			counter2++;
    		}
    		else if (inputstr[counter2] == 92 && inputstr[counter2 + 1] != '/') 
    		{
    			searchstr[counter3] = inputstr[counter2 +1];
    			counter2++;
    		}
    		else
    		{
    			searchstr[counter3] = inputstr[counter2];
    		}
    		counter3++;
    	}
    	searchstr[counter3] = '\0'; // Stores NULL in searchstr.
    	
    	for (counter4 = counter2  + 1; inputstr[counter4] != '\0'; counter4++) //Stores characters from inpustr into replacestr without any exceptions.
    	{
    		replacestr[counter5] = inputstr[counter4];
    		counter5++;
    	}
    	replacestr[counter5 - 1] = '\0'; // Stores NULL into replacestr.
    	
    	for (counter6 = 0; searchstr[counter6] != '\0'; counter6++) // Calculates length of searchstr
    	{
    		searchlength++;
    	}
    	for (counter7 = 0; replacestr[counter7] != '\0'; counter7++) // Calculates length of replacestr
    	{
    		replacelength++;
    	}
    	
    	// Calculates how many backlashes were entered in input string and accounts them to get the right wild card.
   	 for (counter8 = 1; inputstr[counter8] != '/';counter8++)
   	{
   		if (inputstr[counter8] == 92)
    		{
    			backcount++;
    		}
    		if (inputstr[counter8] == '.')
    		{
    			break;
    		}
   		if (inputstr[counter8] == 92 && inputstr[counter8 + 1] == '/')
    		{
    			counter8++;
    		}
    		else if (inputstr[counter8] == 92 && inputstr[counter8 + 1] != '/') 
    		{
    			counter8++;
    		}
    		
    		
    	}
    
   	 // Searches for the wild card on searchstr. 
    	for (counter9 = 1; inputstr[counter9] != '\0'; counter9++)
    	{
    		if (inputstr[counter9] == 92)
    		{
    			counter9++;
    		}
    		else if (inputstr[counter9] == '.')
    		{
    			wlocation = counter9 - backcount - 1;
    			break;
    		}
    		else
    		{
    			wlocation = -1;
    		}
   	 }
 	   	
    	
    	if (searchlength == replacelength && wlocation >= 0) //If searchlength and replacelength are equal and there is a wild card, will set wild_position to location of wild card.
    	{
    		wild_position = wlocation;
    	}
    	if (searchlength == replacelength && wlocation == -1) // If searchlength and replacelength are equal and there is not a wild card, will set wild_position to -1.
    	{
    		wild_position = wlocation;
    	}
    	if (searchlength != replacelength) // If searchlength and replacelength are not equal, sets wild position to -2, meaning user entered unvalid strings.
    	{
    		wild_position = -2;
    	}
    }
    
    // If something is wrong with strings entered by user, returns -2.
    else
    {
    	wild_position = -2;
    }
    return wild_position;
}

/*----------------------------------------------------------*/
/* The function to open the file, find the size of the file,
 * malloc memory to hold the contents of the file.
 *
 * There are two return values
 *   1.  the return value is a pointer to the starting
 *       memory location of the data
 *   2.  the size of the memory block in bytes is also
 *       returned in file_size
 */
char *store_file(char * filename, int * file_size)
{
    FILE *filein;
    
    int count1 = 0;
    int count2 = 0;
    char character;
    char *ptrmemory_size;
    if ((filein = fopen(filename, "r")) == NULL) 
    {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }

    // Reads file open and scans that each character is 1 byte and will store number of bytes in file.
    while (fscanf(filein, "%c", &character) == 1)
    {
    	count1++;
    }
    
    // Creates dynamic memory according to the size of the file and address is stored in pointer ptrmemory_size.
    ptrmemory_size = (char*)malloc(count1 * sizeof(char));
    
    // If the pointer memory_size cannot allocate space it will exit the program.
    if (ptrmemory_size == NULL)
    {
    	exit(1);
    }
    
    rewind(filein);
    // 	Reads file open and scans that each character is 1 byte and will store each character of filein into the dynamic memory. 
    
    while (fscanf(filein, "%c", &character) == 1)
    {
    	ptrmemory_size[count2] = character;
    	count2++;
    } 
    // Closes file that was being read.
    fclose(filein);
    // Returns the number of bytes of filein into pointer file_size.
    *file_size = count1;  
    //Returns the starting address of the dynamic memory by returning pointer ptrmemory_size.
    return  ptrmemory_size;      
}

// 
// Functions from here to end of this file should NOT be changed
//
/* print the menu of choices to the user 
 *
 */
void print_menu(void)
{
    printf("Simple editor commands\n\n");
    printf("f FF    : Search for next matching byte (in hex) after current location\n");
    printf("r AB CD : Same as search, then replace byte if found\n");
    printf("/Blue Ridge  : Search for next matching string after current location\n");
    printf("s /Blue/Red / : Same as search, then replace string of same length\n");
    printf("G num : Goto byte at position 'num' from start of memory\n");
    printf("j     : Move forward 16 bytes from current location\n");
    printf("k     : Move backward 16 bytes from current location\n");
    printf("q     : Quit\n");
    printf("?     : Print this menu\n");
}

/*----------------------------------------------------------*/
int main(int argc, char *argv[])
{
    char *filename;        // the input file name
    char *file_in_memory;  // starting address of memory block to store file
    int file_size;
    int fn_len;            // length of the input file name
    int found = 0;         // if search was successful
    int location = 0;      // current location in memory [0, file_size)
    int items;
    char line[MAXLINE];
    char command[MAXLINE];
    char inputcs[MAXLINE];
    char replacecs[MAXLINE];
    char searchstr[MAXLINE];
    char replacestr[MAXLINE];

    if (argc != 2) {
        printf("Usage: lab4 filename\n");
        exit(1);
    }

    // prepare filename
    fn_len = strlen(argv[1]);
    // remember the null
    filename = (char *) malloc((fn_len + 1) * sizeof(char));
    strcpy(filename, argv[1]);

    // open file and store in memory starting at pointer
    file_in_memory = store_file(filename, &file_size);

    print_menu();

    printf("> ");
    while (fgets(line, MAXLINE, stdin) != NULL) {
        printf("\n");
        items = sscanf(line, "%s%s%s", command, inputcs, replacecs);
        if (items == 2 && strcmp(command, "f") == 0) { 
            if (strlen(inputcs) != 2 || !isxdigit(inputcs[0]) ||
                    !isxdigit(inputcs[1])) {
                printf("f Invalid byte: %s\n", inputcs);
            } else {
                found = find_next_byte_match(&location, inputcs, file_in_memory, file_size);
                if (!found) {
                    printf("Did not find byte: %s\n", inputcs);
                } else {
                    print_line(location, 1, -1, file_in_memory, file_size);
                }
            }
        } else if (items == 3 && strcmp(command, "r") == 0) {  
            if (strlen(inputcs) != 2 || !isxdigit(inputcs[0]) ||
                    !isxdigit(inputcs[1]) || strlen(replacecs) != 2 ||
                    !isxdigit(replacecs[0]) || !isxdigit(replacecs[1])) {
                printf("r Invalid bytes: %s %s\n", inputcs, replacecs);
            } else {
                found = replace_next_byte(&location, inputcs, replacecs, file_in_memory, file_size);
                if (!found) {
                    printf("Did not replace byte: %s\n", inputcs);
                } else {
                    print_line(location, 1, -1, file_in_memory, file_size);
                }
            }
        } else if (strncmp(line, "/", 1) == 0) {  
            strcpy(inputcs, line + 1);
            // chomp the pesky \n
            if (inputcs[strlen(inputcs)-1] == '\n')
                inputcs[strlen(inputcs)-1] = '\0';
            int wild_pos = process_search_string(inputcs, searchstr);
            found = find_next_string(&location, searchstr, wild_pos, 
                    file_in_memory, file_size);
            if (!found) {
                if (wild_pos == -1) {
                    printf("String not found: '%s' (no wildcard)\n", searchstr);
                } else {
                    printf("String not found: '%s' wildcard at %d\n", 
                            searchstr, wild_pos);
                }
            } else {
                print_line(location, strlen(searchstr), wild_pos, file_in_memory, file_size);
            }
        } else if (strncmp(line, "s /", 3) == 0) {  
            strcpy(inputcs, line + 2);
            // chomp the pesky \n
            if (inputcs[strlen(inputcs)-1] == '\n')
                inputcs[strlen(inputcs)-1] = '\0';
            int wild_pos = process_replace_string(inputcs, searchstr, replacestr);
            if (wild_pos == -2) {
                printf("s Invalid input: %s\n", inputcs);
            } else {
                found = replace_next_string(&location, searchstr, wild_pos, 
                        replacestr, file_in_memory, file_size);
                if (!found) {
                    if (wild_pos == -1) {
                        printf("String not replaced: '%s' (no wildcard)\n", searchstr);
                    } else {
                        printf("String not replaced: '%s' wildcard at %d\n", 
                                searchstr, wild_pos);
                    }
                } else {
                    print_line(location, strlen(searchstr), wild_pos, file_in_memory, file_size);
                }
            }
        } else if (items == 2 && strcmp(command, "G") == 0) {  
            int new_location = -1;
            new_location = atoi(inputcs);
            if (new_location < 0 || new_location >= file_size) {
                printf("Invalid goto: %s\n", inputcs);
            } else {
                location = new_location;
                print_line(location, 1, -1, file_in_memory, file_size);
            }
        } else if (items == 1 && strcmp(command, "j") == 0) { 
            if (location + 16 >= file_size) {
                printf("Invalid move down: %d\n", location);
            } else {
                location += 16;
                print_line(location, 1, -1, file_in_memory, file_size);
            }
        } else if (items == 1 && strcmp(command, "k") == 0) { 
            if (location - 16 < 0) {
                printf("Invalid move up: %d\n", location);
            } else {
                location -= 16;
                print_line(location, 1, -1, file_in_memory, file_size);
            }
        } else if (items == 1 && strcmp(command, "q") == 0) { 
            break;
        } else if (items == 1 && strcmp(command, "?") == 0) { 
            print_menu();
        } else {
            printf("# :%s", line);
        }
        printf("> ");
    }

    // for every malloc there must be a free
    free(file_in_memory);
    free(filename);

    printf("Goodbye\n");
    return EXIT_SUCCESS;
}
