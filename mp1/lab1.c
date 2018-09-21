/* lab1.c
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 * MP1
 *
 * NOTE:  You must update all of the following comments!
 *
 * Purpose:  The purpose of this program is to simulate the process of receiving a transmission, meaning detecting the incoming of a waveform. The program has three stages, input, process,
 	     and output. Input section consists of asking the user for the correlation threshold, minimum correlation value, and sample collection of numbers. The correlation value consists of how 		     many times a number must be repreated and the minimum correlation value consists of the minimum value a number must have to be considered in the repetition. After these two numbers have 		     been set, a sample collection of numbers are entered by the user until the numberer of zero's in a row equal STOPCOUNT or if the user number of inputs is equal to the number of 		     MAXSAMPLES. Then, the process stage starts. Process stage consists of indentifying the greatest number from inputs entered and see if the number is repeated as many or more than the       	      correlation value. If the highest number does not repeat as many times as the correlation number, it looks for the next hihgest number and so until it finds a number that has all 	     requirements needed and goes into the output section. If this is the case, the output will tell that there is a waveform, and will give its position, value, and repetition.. If there are 	     no numbers that fulfill the requirements, it jumps into the ouput section. If this is the case, the output will says that there is no waveform. Then, the program starts again and if user 	     wants to exit, he/she must type -1 into the first sample.

 *
 * Assumptions: For the program to be solved, the user must know that that the minimum correlation value is the minimum value that a number will be read in the program. Also the user must know that 
 		the correlation threshold is the minimum number of times the minimum value must repeated for there to be a waveform. Fact that the user must knows that if first sample is -1, the 			program will exit. Finally the user must know that either three zero's or the maximum number of samples are required for the program to process if there is a waveform in set of samples 			entered or not.
 *
 * Bugs:
 *
 *

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//notice there is no semi-colon at the end of a #define
#define MAXLINE 100
#define MAXSAMPLES 10
#define STOPCOUNT 3
#define MINTHRESH 3

int main()
{
    char line[MAXLINE];
    int corr_thresh = -1;
    int min_corr_val = -1;
    int samples[MAXSAMPLES];
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int highest_number = 0;
    int position = 0;
    int value = -1;
    int count = 0;
    int count2 = 0;


    printf("What is the correlation threshold? ");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &corr_thresh);
    // While correlation threshold is NOT equal to -1 AND MINTHRESH is greater than correlation threshold, while loop runs and asks for a valid correlation threshold until valid value is entered.
    while ((corr_thresh != -1) && (MINTHRESH > corr_thresh)) {
        printf("That is not a valid correlation threshold!\n");
        printf("What is the correlation threshold? ");
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &corr_thresh);
    }
    // If correlation threshold is equal to -1, if statement runs.
    if (corr_thresh == -1) {
        printf("Goodbye\n");
        exit(0);
    }
    // If correlation threshold is greater than or equal to MINTHRESH, if statement runs.
    if (corr_thresh >= MINTHRESH) {
        printf("\nThe correlation threshold is equal to: %d\n", corr_thresh);
        printf("What is the minimum correlation value? ");
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &min_corr_val);
        // While minimum correlation value is less than 0 and not equal to -1, while loop runs and asks for a valid minimum correlation value until valid value is entered.
        while ((min_corr_val <= 0) && (min_corr_val != -1) ) {
            printf("That is not a valid minimum correlation value!\n");
            printf("What is the minimum correlation value? ");
            fgets(line, MAXLINE, stdin);
            sscanf(line, "%d", &min_corr_val);
        }
        // If minimum corelation value is equal to -1, if statement runs.
        if (min_corr_val == -1) {
            printf("Goodbye\n");
            exit(0);
        }
        // If minimum correlation value is greater than 0, if statement runs.
        if (min_corr_val > 0) {
            printf("\nThe minimum threshold is equal to: %d\n", min_corr_val);
        }
    }

    // If correlation threshold is greater than or equal to MINTHRESH AND minimum correlation value is greater than 0, if statement runs.
    while ( MAXSAMPLES != MAXSAMPLES +1) {
    	// If the correlation threshold is greater than or equal to MINTHRESH, AND minimum correlation value is greater than 0, if statement runs.
        if ((corr_thresh >= MINTHRESH) && (min_corr_val > 0)) {
            printf("\nPlease enter a new set of values or enter -1 to quit:\n");

            // For loop will run until it reaches the value of MAXSAMPLES.
            for (counter = 0; counter < MAXSAMPLES; counter++) {
                fgets(line, MAXLINE, stdin);
                sscanf(line, "%d", &samples[counter]);
                // If the fist entered samle is equal to -1, exits program.
                if (samples[0] == -1) {
                    printf("Goodbye\n");
                    exit(0);
                }
                // If number entered is not 0, if statement runs.
                if (samples[counter] != 0) {
                    // Count is set to equal 0.
                    count = 0;
                }
                // If the number entered is 0, if statement runs.
                if (samples[counter] == 0) {
                    // If number entered is 0, count increases by one.
                    count += 1;
                    // If counr reaches same value as STOPCOUNT, exits the loop.
                    if (count == STOPCOUNT) {
                        break;
                    }
                }
                // If counter reaches same value as MAXSAMPLES, sets count to 0, and exits the loop.
                if (counter == MAXSAMPLES) {
                    count = 0;
                    break;
                }
            }
        }
        // If count equals STOPCOUNT, if statement runs.
        if (count == STOPCOUNT) {
            // For loop will run until counter2 reaches value of counter.
            for (counter2 = 0; counter2 < counter; counter2++) {
                // If samples[counter] is greater than or equal to minimum correlation value, if samples runs.
                if ((samples[counter2] >= min_corr_val)) {
                    // If samples[counter2] is greater than the highest number, if statement runs.
                    if (samples[counter2] > highest_number) {
                        // Highest number is stored in variable.
                        highest_number = samples[counter2];
                        value = highest_number;
                    }
                }
            }
            // For loop will run until counter3 reaches value of counter.
            for (counter3 = 0; counter3 < counter; counter3++) {
                // If samples[counter3] is equal to the highest_number, count adds by one.
                if (samples[counter3] == highest_number) {
                    count2 +=1;
                }

            }

            // While count2 is less than the correlation threshold, while loop will run.
            while (count2 < corr_thresh) {
                // For loop will run until counter4 equal counter.
                highest_number = 0;
                for (counter4 = 0; counter4 < counter; counter4++) {
                    // If samples[counter4] is greater or equal to the minimum correlation number, if statement runs.
                    if (samples[counter4] >= min_corr_val) {
                        // If samples[counter4] is greater than highest_number AND samples[counter] is less than value.
                        if ((samples[counter4] < value)) {
                            // Next highest value is stored into highest_number.
                            highest_number = samples[counter4];
                            // Highest_number stored into value.
                            value = highest_number;
                            // Repeated counter is set to 0.
                            count2 = 0;
                        }
                    }
                }
                // For loop will run until counter5 reaches value of counter.
                for (counter5 = 0; counter5 < counter; counter5++) {
                    // If samples[couter5] is equal to the highest number, if statement will run.
                    if (samples[counter5] == highest_number) {
                        // Count of repeated number increases by one.
                        count2 += 1;
                    }
                }
                // If count2 is greater than the corelation threshold AND highest_number is greater than minimum correlation value, while loop breaks.
                if (count2 >= corr_thresh && highest_number >= min_corr_val) {
                    break;
                }



            }
            // For runs until counter6 reaches same value as counter.
            for (counter6 = 0; counter6 < counter; counter6++) {
                // If samples[counter6] is equal to the highest_number, if statement runs.
                if (samples[counter6] == highest_number ) {
                    // Gets position of first time highest_number is stored.
                    position = counter6 + 1;
                    break;
                }
            }

        }

        // If counter reaches MAXSAMPLES value, this executes.
        if (counter == MAXSAMPLES) {
            // For loop will run until counter2 reaches value of counter.
            for (counter2 = 0; counter2 < MAXSAMPLES; counter2++) {
                // If samples[counter] is greater than or equal to minimum correlation value, if samples runs.
                if ((samples[counter2] >= min_corr_val)) {
                    // If samples[counter2] is greater than the highest number, if statement runs.
                    if (samples[counter2] > highest_number) {
                        // Highest number is stored in variable.
                        highest_number = samples[counter2];
                        value = highest_number;
                    }

                }
            }

            // For loop will run until counter3 reaches value of counter.
            for (counter3 = 0; counter3 < MAXSAMPLES; counter3++) {
                // If samples[counter3] is equal to the highest_number, count adds by one.
                if (samples[counter3] == highest_number) {
                    count2 +=1;
                }

            }


            // While count2 is less than the correlation threshold, AND trials is less than the MAXSAMPLES, while loop runs.
            int trials = 0;
            while (count2 < corr_thresh && trials < MAXSAMPLES) {
                // For loop will run until counter4 equal counter.
                highest_number = 0;
                for (counter4 = 0; counter4 < MAXSAMPLES; counter4++) {
                    // If samples[counter4] is greater or equal to the minimum correlation number, if statement runs.
                    if (samples[counter4] >= min_corr_val) {
                        // If samples[counter4] is greater than highest_number AND samples[counter] is less than value.
                        if ((samples[counter4] < value)) {
                            // Next highest value is stored into highest_number.
                            highest_number = samples[counter4];
                            // Highest_number stored into value.
                            value = highest_number;
                            // Repeated counter is set to 0.
                            count2 = 0;
                        }
                    }

                }
                // For loop will run until counter5 reaches value of counter.
                for (counter5 = 0; counter5 < MAXSAMPLES; counter5++) {
                    // If samples[couter5] is equal to the highest number, if statement will run.
                    if (samples[counter5] == highest_number) {
                        // Count of repeated number increases by one.
                        count2 +=1;
                    }
                }
                // If count2 is greater or equal to the correlation threshold, AND highest_number is greater of equal to minimum correlation value, it breaks from while loop.
                if ((count2 >= corr_thresh) && (highest_number >= min_corr_val)) {
                    break;
                }



                trials++;
            }

            // For runs until counter6 reaches same value as counter.
            for (counter6 = 0; counter6 < MAXSAMPLES; counter6++) {
                // If samples[counter6] is equal to the highest_number, if statement runs.
                if (samples[counter6] == highest_number ) {
                    // Gets position of first time highest_number is stored.
                    position = counter6 + 1;
                    break;
                }
            }
        }
        // If count2 is greater or equal to correlation threshold, if statement will run.
        if ((count2 >= corr_thresh) && (highest_number >= min_corr_val)) {
            // Display position, highest_number, and repeated number of times.
            printf("Waveform detected at position %d with value %d and appears %d times\n", position, highest_number, count2);
            position =0;
            highest_number = 0;
            value = 0;
            count = 0;
            count2 = 0;
            counter = 0;
            counter2 =0;
            counter3 = 0;
            counter4 = 0;
            counter5 = 0;
            counter6 = 0;

        }
        // If none of the requirements exists, this else statement executes.
        else {
            printf("No waveform detected\n");
            counter = 0;
            highest_number = 0;
            value = 0;
            count =0;
            position =0;
            count = 0;
            count2 = 0;
            counter = 0;
            counter2 =0;
            counter3 = 0;
            counter4 = 0;
            counter5 = 0;
            counter6 = 0;

        }

    }
    exit(0);
}

