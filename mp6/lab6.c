/* lab6.c template
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 * MP6
 *
 * Purpose: The purpose of this program is to sort the id number, value, integer array of numbers, and character array of strings with the functions bubblesort and qsort and demonstrate which one is 		    faster. The program consists of the user entering the number of records and the seed into the geninput6.c program and this program will generate as many number of records entered and the seed  will determine the randomness of the numbers and characters. After this has happened, the file lab6.c reads in the data output from geninput6.c. The next step on the program lab6.c will be 	     determine by what the user chooses to do, he/she will either want to display the number of records with their id, value, numbers, and name without being sorted or by being sorted by their id, value, number, or name. The sorting will also depened on which function the user chooses, either qsort or bubblesort. When the user enters eveyrthing it will display they output and how long it took to display it with being sorted or not. 
 *
 * Assumptions: The assumptions that can be made are that the user knows that the data created in geninput6.c will not be "random" due to the fact that if the seed is the same, it will produce the same 			outcome. Also the user knows what the command line arguments are.  
 *
 * Command line arguments: The command arguments are as follows:
 *				0) Display information without being sorted. 
 *				1) Sort the strucutres by id
 *				2) Sort the structures by value
 *   				3) Sort the structures by array
 *				4) Sort the structure by name
 *
 * Performance Evaluation: 	qsort
 				1) ./geninput6 2900000 312 | ./lab6 1 1 > /dev/null -> t = 977.28 s
				2) ./geninput6 2850000 312 | ./lab6 2 1 > /dev/null -> t = 979.404 s
				3) ./geninput6 370000 312 | ./lab6 3 1 > /dev/null -> t = 984.727 s
				4) ./geninput6 2430000 332 | ./lab6 4 1 > /dev/null -> t = 999.598 s
				
				bubblesort
				1) ./geninput6 10800 332 | ./lab6 1 2 > /dev/null -> t = 999.202 s
				2) ./geninput6 10700 332 | ./lab6 2 2 > /dev/null -> t = 999.773 s
				3) ./geninput6 2550 332 | ./lab6 3 2 > /dev/null -> t = 972.886 s
				4) ./geninput6 9500 332 | ./lab6 4 2 > /dev/null -> t = 999.151 s
				
 * Known bugs: No bugs detected. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define NUMINTS 4
#define NUMLTRS 8
struct Record {
    int id;
    float value;
    int a[NUMINTS];
    char name[NUMLTRS];
};

/* This function verifies that the list is sorted.
 * It also checks that the id's are all present
 *
 * The function produces no output if the list is correct.  It
 * causes the program to terminate and print a line beginning with 
 * "Assertion failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void validate_list(struct Record *ptr, int records, 
        int (*fcomp)(const void *, const void *))
{
    int i;
    int * id_list = (int *)calloc(records, sizeof(int));
    if (id_list == NULL) {
        fprintf(stderr, "lab6: Cannot malloc array of size %d\n", records);
        exit(1);
    }
    for(i = 0; i < records - 1; i++) {
        assert(fcomp(ptr+i, ptr+i+1) <= 0);
        assert(ptr[i].id > 0 && ptr[i].id <= records);
        id_list[ptr[i].id-1] = 1;
    }
    assert(ptr[i].id > 0 && ptr[i].id <= records);
    id_list[ptr[i].id-1] = 1;
    for(i = 0; i < records; i++)
        assert(id_list[i] == 1);
    free(id_list);
}

/* turn the binary data into formated ASCII text and send to sdtout
 *
 * This function is complete.  
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void print_records(struct Record *S, int nrecs)
{
    int i, j;
    for (i = 0; i < nrecs; i++)
    {
        printf("\nS[%d]->id = %d\n", i, S[i].id);
        printf("S[%d]->value = %g\n", i, S[i].value);
        printf("S[%d]->a = %d", i, S[i].a[0]);
        for (j = 1; j < NUMINTS; j++) 
        { 
            printf(", %d", S[i].a[j]);
        }
        printf("\nS[%d]->name = %s\n", i, S[i].name);
    }
}


/* Your bubble sort algorithm goes here
 *
 * The arguments must be exactly as defined here.
 *
 * Input:
 *    ptr:     points to the start of the array
 *    records: the number of elements in the array
 *    fcomp:   function pointer to comparison function
 *
 * Assumptions: 
 *    the function sorts an array of type struct Record.
 *    
 *    The comparison function must return an integer less than, equal to,
 *    or greater than zero if the first argument should appear in the list
 *    respectively before, no change, or after the second.  
 */
void bubblesort(struct Record *ptr, int records, 
        int (*fcomp)(const void *, const void *))
{
	// Variable Declaration Section
	int c1 = 0;
	int c2 = 0;
        struct Record bubble;
        
        // Nested for loop that will compare the one structure with the one following it and will see which one is bigger. If the first one is bigger than the next to it, it will swap them and store 		the smallest one first and the bigger one second and so on.
	for (c1 = 0; c1 < records; c1++)	
	{
		for (c2 = 0; c2 < records; c2++)
		{
			if (fcomp(&ptr[c2], &ptr[c2 + 1]) > 0 && (records != (c2+1)))
			{
				bubble = ptr[c2];
				ptr[c2] = ptr[c2 + 1];
				ptr[c2 + 1] = bubble;
			}
		}
	}
}

/* An example of a function to compare records for use with qsort
 * or bubble sort.
 *
 * The function returns one of three values:
 *    -1 : record a should be before record b
 *     0 : the two records have the same ranking
 *     1 : record a should be after record b
 */
int IDCompare(const void *a, const void *b)
{ 
    struct Record *sa, *sb;

    sa = (struct Record *) a;
    sb = (struct Record *) b;

    if (sa->id < sb->id) return -1;
    else if (sa->id > sb->id) return 1;
    else return 0;
}

// Function Declarartion Section
int ValueCompare (const void *a, const void *b);
int ArrayCompare(const void *a, const void *b);
int NameCompare(const void *a, const void *b);

/*----------------------------------------------------------*/
int main(int argc, char *argv[])
{ 
    int sort_field = 0;
    int sort_type  = 1;
    clock_t start, end;

    if (argc != 2 && argc != 3) { 
        fprintf(stderr, "Usage: lab6 sort-field [sort-type]\n");
        fprintf(stderr, "Sort-field\n");
        fprintf(stderr, "  1   id\n");
        fprintf(stderr, "  2   value\n");
        fprintf(stderr, "  3   array\n");
        fprintf(stderr, "  4   name\n");
        fprintf(stderr, "Sort-type\n");
        fprintf(stderr, "  0   do not sort just print data\n");
        fprintf(stderr, "  1   qsort (default)\n");
        fprintf(stderr, "  2   bubble-sort\n");

        exit(1);
    }
    sort_field = atoi(argv[1]);
    if (sort_field < 1 || sort_field > 4) {
        fprintf(stderr, "lab6: Invalid sort field %d\n", sort_field);
        exit(1);
    }
    if (argc == 3) {
        sort_type = atoi(argv[2]);
        if (sort_type < 0 || sort_type > 2) {
            fprintf(stderr, "lab6: Invalid sort type %d\n", sort_type);
            exit(1);
        }
    }

    int num_records = -1;
    int num_items = -1;
    struct Record *rec_ptr;

    num_items = fread(&num_records, sizeof(num_records), 1, stdin);
    if (num_items != 1) {
        fprintf(stderr, "lab6: Error fread failed to read number records %d\n", num_items);
        exit(1);
    }
    if (num_records < 2) {
        fprintf(stderr, "lab6: Error invalid number records %d\n", num_records);
        exit(1);
    }
    printf("lab6: num records %d\n", num_records);

    /* Notice this is the same approach we used in MP5 except here
     * we can read all the the records with one call to fread.
     */
    rec_ptr = (struct Record *) malloc(num_records * sizeof(struct Record));
    num_items = fread(rec_ptr, sizeof(struct Record), num_records, stdin);
    if (num_items != num_records) {
        fprintf(stderr, "lab6: failed to read all records %d\n", num_items);
        exit(1);
    }

    // If user chooses 1 as argv[3], it will sort the data by the function qsort
    if (sort_type == 1)   
    {
    	// Stores th type of sort into variable command
    	char command[2];
    	strcpy(command, argv[1]);
    	
        // Sorts ID numbers from lowest to highest.
    	if (strcmp(command, "1") == 0)
    	{
        	start = clock();
        	qsort(rec_ptr, num_records, sizeof(struct Record), IDCompare);
        	end = clock();
        	validate_list(rec_ptr, num_records, IDCompare);
	}
	// Sorts structures by value
	if (strcmp(command, "2") == 0)
	{
		start = clock();
		qsort(rec_ptr, num_records, sizeof(struct Record), ValueCompare);
		end = clock();
		validate_list(rec_ptr, num_records, ValueCompare);
	}
	// Sorts structures by array
	if (strcmp(command, "3") == 0)
	{
		start = clock();
		qsort(rec_ptr, num_records, sizeof(struct Record), ArrayCompare);
		end = clock();
		validate_list(rec_ptr, num_records, ArrayCompare);
	}
	// Sorts structures by name
	if (strcmp(command, "4") == 0)
	{
		start = clock();
		qsort(rec_ptr, num_records, sizeof(struct Record), NameCompare);
		end = clock();
		validate_list(rec_ptr, num_records, NameCompare);
	}
	
        // you must print using exactly this format
        fprintf(stderr, "lab6: qsort time=%g for %d records\n", 1000*((double)(end-start))/CLOCKS_PER_SEC, num_records); 
    }
    
    // If user chooses 2 as argv[3] it will sort by bubble sort
    if (sort_type == 2)
    {
    	// Stores type of sort command into variable command
    	char command[2];
    	strcpy(command, argv[1]);
    	// Sorts the structures by ID
    	if (strcmp(command, "1") == 0)
    	{
        	start = clock();
        	bubblesort(rec_ptr, num_records, IDCompare);
        	end = clock();
        	validate_list(rec_ptr, num_records, IDCompare);
	}
	// Sorts the structure by value
	if (strcmp(command, "2") == 0)
	{
		start = clock();
		bubblesort(rec_ptr, num_records, ValueCompare);
		end = clock();
		validate_list(rec_ptr, num_records, ValueCompare);
	}
	// Sorts structures by array
	if (strcmp(command, "3") == 0)
    	{
        	start = clock();
        	bubblesort(rec_ptr, num_records, ArrayCompare);
        	end = clock();
        	validate_list(rec_ptr, num_records, ArrayCompare);
	}
	// Sorts structures by name
	if (strcmp(command, "4") == 0)
    	{
        	start = clock();
        	bubblesort(rec_ptr, num_records, NameCompare);
        	end = clock();
        	validate_list(rec_ptr, num_records, NameCompare);
	}
        fprintf(stderr, "lab6: bubble sort time=%g for %d records\n", 1000*((double)(end-start))/CLOCKS_PER_SEC, num_records);
    }

    // printing the records is required.  If you don't want to save
    // the output, on the shell redirect stdout to /dev/null
    print_records(rec_ptr, num_records);

    free(rec_ptr);

    return EXIT_SUCCESS;
}
// ValuCompare will compare the float values and will determine the smallest to greatest in the structure compared.
int ValueCompare(const void *a, const void *b)
{	
	// Variable Declaration Section
	struct Record *sa, *sb;
	sa = (struct Record *) a;
    	sb = (struct Record *) b;
    	
    	// If the float value of sa is greater than sb, it will return a 1
    	if (sa->value > sb->value)
    	{
    		return 1;
    	}
    	// If the float value of sb is greater than sa, it will return a -1
    	else if (sa->value < sb->value)
    	{
    		return -1;
    	}
    	// If the float values of sa and sb are equal it returns a 0
    	else
    	{
    		return 0;
    	}
}
// ArrayCompare will return -1, .0, or 1 depending if the smallest value in each array of the structure
int ArrayCompare(const void *a, const void *b)
{
	// Variable Declaration Section
	struct Record *sa, *sb;
	sa = (struct Record *) a;
    	sb = (struct Record *) b;
    	int size;
    	int c1;
    	int c2;
    	size = 4;
    	int dummy[size];
    	int dummy2[size];
    	int temp;
    	int x = 0;
    	// Stores the number array into variables dummy and dummy2
    	for (c1 = 0; c1 < size; c1++)
    	{
    		dummy[c1] = sa->a[c1];
    		dummy2[c1] = sb->a[c1];
    	}	
    	// Re-arranges the integer dummy array from smallest to largest
    	for (c1 = 0; c1 < size; c1++)
    	{
    		for (c2 = 0; c2 < size; c2++)
    		{
    			if ((dummy[c2] > dummy[c2 + 1]) && (c2 + 1 != size))
   			{
   				temp = dummy[c2];
    				dummy[c2] = dummy[c2 + 1];
    				dummy[c2 + 1] = temp; 
    			}
    			if ((dummy2[c2] > dummy2[c2 + 1]) && (size != c2 + 1))
   			{
   				temp = dummy2[c2];
    				dummy2[c2] = dummy2[c2 + 1];
    				dummy2[c2 + 1] = temp; 
    			}
    		}
    	}
    	// Compares smallest values and determines what to return.
    	for (c1 = 0; c1 < size; c1++)
    	{
    		if (dummy[c1] > dummy2[c1])
    		{
    			x = 1;
    			break;
    		}
    		if (dummy[c1] < dummy2[c1])
    		{
    			x = -1;
    			break;
    		}
    	}
    	// If statements that will return -1, 0, or 1 depending of the sort.
    	if (x == 1)
    	{
    		return 1;
    	}
    	if (x == -1)
    	{
    		return -1;
    	}
    	return 0; 
}
// NameCompare will return -1, 0, or 1 depending of the size of the name in the structures
int NameCompare(const void *a, const void *b)
{
	// Variable Declaration Section
	struct Record *sa, *sb;
	sa = (struct Record *) a;
    	sb = (struct Record *) b;
    	// Compares both strings and determines if sa or sb is larger or smaller or equal, returning either -1, 1, or 0
    	return strcmp(sa->name, sb->name);
}

