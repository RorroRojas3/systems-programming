#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char *argv[])
{

	int size;
    	int c1;
    	int a[4] = {6, 2, 1, 6};
    	int b[4] = {5,3, 2, 9 };
    	size = sizeof(a) / 4;
    	int dummy[size];
    	int dummy2[size];
    	int c2;
    	int temp;
    	int min;
    	int min2;
    	int x = 0;
    	
	for (c1 = 0; c1 < size; c1++)
    	{
    		dummy[c1] = a[c1];
    		dummy2[c1] = b[c1];
    	}
    	
    	min = dummy[0];
    	min2 = dummy2[0];
    	
    	for (c1 = 0; c1 < size; c1++)
    	{
    		if (min > dummy[c1])
    		{
    			min = dummy[c1];
    		}
    		if (min2 > dummy2[c1])
    		{
    			min2 = dummy2[c1];
    		}
    	}
    	
    	for (c1 = 0; c1 < size; c1++)
    	{
    		for (c2 = 0; c2 < size; c2++)
    		{
    			if (dummy[c2] > dummy[c2 + 1] && (c2 + 1) != size)
   			{
   				temp = dummy[c2];
    				dummy[c2] = dummy[c2 + 1];
    				dummy[c2 + 1] = temp; 
    			}
    			if (dummy2[c2] > dummy2[c2 + 1] && (c2 + 1) != size)
   			{
   				temp = dummy2[c2];
    				dummy2[c2] = dummy2[c2 + 1];
    				dummy2[c2 + 1] = temp; 
    			}
    		}
    	}
    
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
    	
    	if (x == 1)
    	{
    		printf("1\n");
    	}
    	if (x == -1)
    	{
    		printf("-1\n");
    	}
    	if (x == 0)
    	{
    		printf("0\n");
    	}
    	
    	return 0;
}
