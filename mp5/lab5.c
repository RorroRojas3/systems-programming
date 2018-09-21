/* lab5.c
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 *
 * Purpose: The program's purpose is to change the truncation of desired bmp file or to change the direction of the bmp file either to the left or the right and store it into a new output file. The program first reads in the input.bmp and stores it into struct variable matrix. Then it will do all four functions, edtrunct, edmag, rotr, and rotf. The two truncation functions consists of the same process except of the final storage. The calculation consists of multiplying the current pixel by 4 and then multiplying the pixel above, below, left, and right from it by -1. Then it will add all the values and will store it into matrix edtrunct or edmag. The exception with edmag is the calculation first goes into an struct that has three integers which can calculate the absolute value if the number is negative or greater than 255. Then, if the value is greater than 255 it will store that value into result again as 255. Finally all resulsts of variable result will be stored into edmag matrix. The rotation to the right and left consists of the same process. Each of them take one edge and read the row and the column from matrix and store it into either right or left starting by the column and going down in the row. Depending of the command, the output file will be written and will be output as a bmp file.
 *          
 * Assumptions:  The file must be 24-bit color, without compression, and without a color map. The user is aware that the program can only run bmp files and that the input.bmp and output.bmp cannot have the same name.
*
 * Bugs:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* WARNING: the header is 14 bytes, however on most systems
 * you will find that sizeof(struct Header) is 16 due to alignment
 * Thus trying to read the header with one fread may fail.  So,
 * read each member separately
 */
struct Header
{  
    unsigned short int Type;                 /* Magic identifier            */
    unsigned int Size;                       /* File size in bytes          */
    unsigned short int Reserved1, Reserved2;
    unsigned int Offset;                     /* Offset to image data, bytes */
};

struct InfoHeader
{  
    unsigned int Size;               /* header size in bytes      */
    int Width, Height;               /* Width and height of image */
    unsigned short int Planes;       /* Number of colour planes   */
    unsigned short int Bits;         /* Bits per pixel            */
    unsigned int Compression;        /* Compression type          */
    unsigned int ImageSize;          /* Image size in bytes       */
    int xResolution,yResolution;     /* Pixels per meter          */
    unsigned int Colors;             /* Number of colors         */
    unsigned int ImportantColors;    /* Important colors         */
};

const char Matrix[3][3] = 
{ 
    {  0, -1,  0 },
    { -1,  4, -1 },
    {  0, -1,  0 }
};

#define LINE 256

struct Pixel
{ 
    unsigned char Red, Green, Blue;
}; 

struct IntPix
{
	int Red, Green, Blue;
};
/*----------------------------------------------------------*/
int main(int argc, char *argv[])
{ 
    // Variable Declaration Section.
    char filein[LINE];
    FILE *fpin;
    char fileout[LINE];
    FILE *fout;
    struct InfoHeader infoheader;
    struct Header header;
    int pixel_cols, pixel_rows, pixel_count;
    int items_found;
    struct Pixel one_pixel;
    char command[LINE];
   
    // If the user does not enter as many commands as needed, it will print what it needs.
    if (argc != 4)
    {
        printf("Usage: ./lab5 command input.bmp output.bmp\n");
        exit(1);
    }
    
    // If the input.bmp file and output.bmp file are the same name, it will terminate the program.
    if (strcmp(argv[2],argv[3]) == 0)
    {
    	printf("Input.bmp file and output.bmp cannot be the same name.\n");
    	exit(1);
    }
    
    // Copies command ("edtrunc", "edmag", "rotr", "rotl") into variable command.
    strcpy(command,argv[1]);
    strcpy(filein, argv[2]);
    strcpy(fileout, argv[3]);

    // If file is not bmp it cannot open and will display message.
    if ((fpin = fopen(filein, "rb")) == NULL)
    { 
        printf("Cannot Open File. %s\n", filein);
        exit (1);
    }
    
    // States that will open a new file and will write on it.
    fout = fopen(fileout, "wb");

    /* Read header */
    fread(&header.Type, sizeof(short int), 1, fpin);
    fread(&header.Size, sizeof(int), 1, fpin);
    fread(&header.Reserved1, sizeof(short int), 1, fpin);
    fread(&header.Reserved2, sizeof(short int), 1, fpin);
    fread(&header.Offset, sizeof(int), 1, fpin);


    if (header.Type != 0x4D42)
    {
        printf("This does not appear to be a bmp file: %s\n", filein);
        exit(1);
    }
    
    // Reads information from input.bmp
    fread(&infoheader.Size, sizeof(int), 1, fpin);
    fread(&infoheader.Width, sizeof(int), 1, fpin);
    fread(&infoheader.Height, sizeof(int), 1, fpin);
    fread(&infoheader.Planes, sizeof(short int), 1, fpin);
    fread(&infoheader.Bits, sizeof(short int), 1, fpin);
    fread(&infoheader.Compression, sizeof(int), 1, fpin);
    fread(&infoheader.ImageSize, sizeof(int), 1, fpin);
    fread(&infoheader.xResolution, sizeof(int), 1, fpin);
    fread(&infoheader.yResolution, sizeof(int), 1, fpin);
    fread(&infoheader.Colors, sizeof(int), 1, fpin);
    fread(&infoheader.ImportantColors, sizeof(int), 1, fpin);


    // Variable Declaration Section
    pixel_rows = infoheader.Height;
    pixel_cols = infoheader.Width;
    pixel_count = 0;
    struct Pixel **matrix;
    struct Pixel **trunc_matrix;
    struct Pixel **edmag_matrix;
    struct Pixel **left;
    struct Pixel **right;
    struct IntPix **result;
    int c1;
    int c2;
    int c3;
    int c4;
    
    // Allocate memory according to number of rows and the size of struct Pixel (24 bytes)
    matrix = (struct Pixel **)calloc(pixel_rows,sizeof(struct Pixel*));
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	// Allocates memory according to number of columns and rows and creates 3 bytes in each memory according to struct Pixel
    	matrix[c1] = (struct Pixel *)calloc(pixel_cols, sizeof(struct Pixel));
    }
    
    // Allocates dynamic memory of the trunc_matrix.
    trunc_matrix = (struct Pixel **)calloc(pixel_rows, sizeof(struct Pixel*));
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	trunc_matrix[c1] = (struct Pixel *)calloc(pixel_cols, sizeof(struct Pixel));
    } 
    
    // Allocates dynamic memory for result which will be used to store temporary values if they are less than 0 or greater than 255.
    result = (struct IntPix **)calloc(pixel_rows, sizeof(struct IntPix *));
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	result[c1] = (struct IntPix *)calloc(pixel_cols, sizeof(struct IntPix));
    }
    
    // Allocates dynamic memory for the edmag_matrix.
    edmag_matrix = (struct Pixel **)calloc(pixel_rows, sizeof(struct Pixel*));
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	edmag_matrix[c1] = (struct Pixel *)calloc(pixel_cols, sizeof(struct Pixel));
    }
    
    // Allocates dynamic memory for the rotation to the right of the bmp file
    right = (struct Pixel **)calloc(pixel_cols, sizeof(struct Pixel*));
    for (c1 = 0; c1 < pixel_cols; c1++)
    {
    	right[c1] = (struct Pixel *)calloc(pixel_rows, sizeof(struct Pixel));
    }
    
    // Allocates dynamic memory for the rotation to the left of the bmp file
    left = (struct Pixel **)calloc(pixel_cols, sizeof(struct Pixel*));
    for (c1 = 0; c1 < pixel_cols; c1++)
    {
    	left[c1] = (struct Pixel *)calloc(pixel_rows, sizeof(struct Pixel));
    }
        
    // Stores the pixel (24 bits) into dynamic memory.
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	for (c2 = 0; c2 < pixel_cols; c2++)
    	{ 	
    		// Reads in each pixel
    		items_found = fread(&one_pixel, 3, 1, fpin);
            	if (items_found != 1)
            	{
                	printf("failed to read pixel %d at [%d][%d]\n", 
                        pixel_count, c1, c2);
                	exit(1);
           	}
           	// Stores each pixel read into struct Pixel matrix
    		matrix[c1][c2].Red = one_pixel.Red;
    		matrix[c1][c2].Green = one_pixel.Green;
    		matrix[c1][c2].Blue = one_pixel.Blue;
    	}
    }
    
    // Copies edge of the the first row
    for (c1 = 0; c1 < pixel_cols; c1++)
    	{
    		trunc_matrix[0][c1].Red = matrix[0][c1].Red;
    		trunc_matrix[0][c1].Green = matrix[0][c1].Green;
    		trunc_matrix[0][c1].Blue = matrix[0][c1].Blue;
    		
    		edmag_matrix[0][c1].Red = matrix[0][c1].Red;
    		edmag_matrix[0][c1].Green = matrix[0][c1].Green;
    		edmag_matrix[0][c1].Blue = matrix[0][c1].Blue;
    	}
    
    // Copies edges of the first column.
    for (c1 = 0; c1 < pixel_rows; c1++)
   	{	
    		trunc_matrix[c1][0].Red = matrix[c1][0].Red;
    		trunc_matrix[c1][0].Green = matrix[c1][0].Green;
    		trunc_matrix[c1][0].Blue = matrix[c1][0].Blue;
    		
    		edmag_matrix[c1][0].Red = matrix[c1][0].Red;
    		edmag_matrix[c1][0].Green = matrix[c1][0].Green;
    		edmag_matrix[c1][0].Blue = matrix[c1][0].Blue;
    	}
    
    // Copies edge of the last row.
    for (c1 = 0; c1 < pixel_cols; c1++)
   	{	
    		trunc_matrix[pixel_rows -1][c1].Red = matrix[pixel_rows - 1][c1].Red;
    		trunc_matrix[pixel_rows -1][c1].Green = matrix[pixel_rows - 1][c1].Green;
    		trunc_matrix[pixel_rows -1][c1].Blue = matrix[pixel_rows - 1][c1].Blue;
    		
    		edmag_matrix[pixel_rows -1][c1].Red = matrix[pixel_rows - 1][c1].Red;
    		edmag_matrix[pixel_rows -1][c1].Green = matrix[pixel_rows - 1][c1].Green;
    		edmag_matrix[pixel_rows -1][c1].Blue = matrix[pixel_rows - 1][c1].Blue;
   	}	
    
    // Copies edge of the last column.
    for (c1 = 0; c1 < pixel_rows; c1++)
    	{
    		trunc_matrix[c1][pixel_cols - 1].Red = matrix[c1][pixel_cols - 1].Red;
    		trunc_matrix[c1][pixel_cols - 1].Green = matrix[c1][pixel_cols - 1].Green;
    		trunc_matrix[c1][pixel_cols - 1].Blue = matrix[c1][pixel_cols - 1].Blue;
    		
    		edmag_matrix[c1][pixel_cols - 1].Red = matrix[c1][pixel_cols - 1].Red;
    		edmag_matrix[c1][pixel_cols - 1].Green = matrix[c1][pixel_cols - 1].Green;
    		edmag_matrix[c1][pixel_cols - 1].Blue = matrix[c1][pixel_cols - 1].Blue;
    	}	
    
    // Stores value of red, green, and blue according to the edge detection of the image.
    for (c1 = 1; c1 < pixel_rows - 1; c1++)
   	 {
   	 	for (c2 = 1; c2 < pixel_cols - 1; c2++)
   	 	{ 	
   	 		// Stores colors of the edtrunc command	
    			trunc_matrix[c1][c2].Red = (matrix[c1][c2].Red * Matrix[1][1]) + (matrix[c1][c2-1].Red*Matrix[1][0]) + (matrix[c1][c2+1].Red*Matrix[1][2]) + (matrix[c1-1][c2].Red*Matrix[0][1]) + (matrix[c1+1][c2].Red*Matrix[2][1]);
    			trunc_matrix[c1][c2].Green = (matrix[c1][c2].Green * Matrix[1][1]) + (matrix[c1][c2-1].Green*Matrix[1][0]) + (matrix[c1][c2+1].Green*Matrix[1][2]) + (matrix[c1-1][c2].Green*Matrix[0][1]) + (matrix[c1+1][c2].Green*Matrix[2][1]);
    			trunc_matrix[c1][c2].Blue = (matrix[c1][c2].Blue * Matrix[1][1]) + (matrix[c1][c2-1].Blue*Matrix[1][0]) + (matrix[c1][c2+1].Blue*Matrix[1][2]) + (matrix[c1-1][c2].Blue*Matrix[0][1]) + (matrix[c1+1][c2].Blue*Matrix[2][1]);
    			
    			// Stores temporary colors into result if theyr are greater than 255 or less than 0 and calculates absolute value for edmag command.
    			result[c1][c2].Red = (matrix[c1][c2].Red * Matrix[1][1]) + (matrix[c1][c2-1].Red*Matrix[1][0]) + (matrix[c1][c2+1].Red*Matrix[1][2]) + (matrix[c1-1][c2].Red*Matrix[0][1]) + (matrix[c1+1][c2].Red*Matrix[2][1]);
    			result[c1][c2].Red = abs(result[c1][c2].Red);
    			result[c1][c2].Green = (matrix[c1][c2].Green * Matrix[1][1]) + (matrix[c1][c2-1].Green*Matrix[1][0]) + (matrix[c1][c2+1].Green*Matrix[1][2]) + (matrix[c1-1][c2].Green*Matrix[0][1]) + (matrix[c1+1][c2].Green*Matrix[2][1]);
    			result[c1][c2].Green = abs(result[c1][c2].Green);
    			result[c1][c2].Blue = (matrix[c1][c2].Blue * Matrix[1][1]) + (matrix[c1][c2-1].Blue*Matrix[1][0]) + (matrix[c1][c2+1].Blue*Matrix[1][2]) + (matrix[c1-1][c2].Blue*Matrix[0][1]) + (matrix[c1+1][c2].Blue*Matrix[2][1]);
    			result[c1][c2].Blue = abs(result[c1][c2].Blue);
    			
    			// If the result is greater than 255, it will set result to 255.
    			if (result[c1][c2].Red > 255)
    			{
    				result[c1][c2].Red = 255;
    			}
    			if (result[c1][c2].Green > 255)
    			{
    				result[c1][c2].Green = 255;
    			}
    			if (result[c1][c2].Blue > 255)
    			{
    				result[c1][c2].Blue = 255;
    			}
    			
    			// Finals values of result are stored into edmag_matrix since edmag command was typed.
    			edmag_matrix[c1][c2].Red = result[c1][c2].Red;
    			edmag_matrix[c1][c2].Green = result[c1][c2].Green;
    			edmag_matrix[c1][c2].Blue = result[c1][c2].Blue;
    		}		
   	 } 
  
  
    // Stores original picture into left which will be the original picture turned to the left.
    c3 = 0;
    for (c1 = pixel_rows -1; c1 >= 0; c1 --)
    {     c4 = 0;
        for (c2 = 0; c2 < pixel_cols; c2++)
        {
            left[c4][c3] = matrix[c1][c2];
            c4++;
        }
        c3++;
    }
    
    // Stores original picture into right whcih will be the original picture turned to the right.
    c3 = 0;
    for (c1 = 0; c1 < pixel_rows; c1++)
    {	c4 = 0;
    	for (c2 =pixel_cols - 1; c2 >= 0; c2--)
    	{
    		right[c4][c3] = matrix[c1][c2];
    		c4++;
    	}
    	c3++;
    }
    
    // Writes edtrunc matrix into the output file if command is "edtrunc"
    if (strcmp(argv[2], argv[3]) != 0 && strcmp("edtrunc", command) == 0)
    {
    	
    
    	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 fwrite(&header.Type, sizeof(short int), 1, fout);
   	 fwrite(&header.Size, sizeof(int), 1, fout);
   	 fwrite(&header.Reserved1, sizeof(short int), 1, fout);
   	 fwrite(&header.Reserved2, sizeof(short int), 1, fout);
   	 fwrite(&header.Offset, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Size, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Width, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Height, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Planes, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Bits, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Compression, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImageSize, sizeof(int), 1, fout);
   	 fwrite(&infoheader.xResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.yResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Colors, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImportantColors, sizeof(int), 1, fout);
   	 
   	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 for (c1 = 0; c1 < pixel_rows; c1++)
   	 {
   	 	for (c2 = 0; c2 < pixel_cols; c2++)
   	 	{
   	 		fwrite(&trunc_matrix[c1][c2],sizeof(struct Pixel),1, fout);
   	 	}
   	 }
    }
    
    // Writres edmag_matrix into the output file if the command is "edmag"
    if (strcmp(argv[2], argv[3]) != 0 && strcmp("edmag", command) == 0)
    {
    	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 fwrite(&header.Type, sizeof(short int), 1, fout);
   	 fwrite(&header.Size, sizeof(int), 1, fout);
   	 fwrite(&header.Reserved1, sizeof(short int), 1, fout);
   	 fwrite(&header.Reserved2, sizeof(short int), 1, fout);
   	 fwrite(&header.Offset, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Size, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Width, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Height, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Planes, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Bits, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Compression, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImageSize, sizeof(int), 1, fout);
   	 fwrite(&infoheader.xResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.yResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Colors, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImportantColors, sizeof(int), 1, fout);
   	 
   	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 for (c1 = 0; c1 < pixel_rows; c1++)
   	 {
   	 	for (c2 = 0; c2 < pixel_cols; c2++)
   	 	{
   	 		fwrite(&edmag_matrix[c1][c2],sizeof(struct Pixel),1, fout);
   	 	}
   	 }
    }
    
      // Writes the right matrix into the output file if the command is "rotr"	
      if (strcmp(argv[2], argv[3]) != 0 && strcmp("rotr", command) == 0)
      {
    	 infoheader.Width = pixel_rows;
    	 infoheader.Height = pixel_cols;
    	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 fwrite(&header.Type, sizeof(short int), 1, fout);
   	 fwrite(&header.Size, sizeof(int), 1, fout);
   	 fwrite(&header.Reserved1, sizeof(short int), 1, fout);
   	 fwrite(&header.Reserved2, sizeof(short int), 1, fout);
   	 fwrite(&header.Offset, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Size, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Width, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Height, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Planes, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Bits, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Compression, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImageSize, sizeof(int), 1, fout);
   	 fwrite(&infoheader.xResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.yResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Colors, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImportantColors, sizeof(int), 1, fout);
   	 
   	 // Writes the edges calculated in rotr and stores it in fout file.
   	 for (c1 = 0; c1 < pixel_cols; c1++)
   	 {
   	 	for (c2 = 0; c2 < pixel_rows; c2++)
   	 	{
   	 		fwrite(&right[c1][c2],sizeof(struct Pixel),1, fout);
   	 	}
   	 }
     }
    
    // Writes the left matrix into the output file if the command is "rotl"
    if (strcmp(argv[2], argv[3]) != 0 && strcmp("rotl", command) == 0)
    {
    	 infoheader.Width = pixel_rows;
    	 infoheader.Height = pixel_cols;
    	 // Writes the edges calculated in edtrunc and stores it in fout file.
   	 fwrite(&header.Type, sizeof(short int), 1, fout);
   	 fwrite(&header.Size, sizeof(int), 1, fout);
   	 fwrite(&header.Reserved1, sizeof(short int), 1, fout);
   	 fwrite(&header.Reserved2, sizeof(short int), 1, fout);
   	 fwrite(&header.Offset, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Size, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Width, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Height, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Planes, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Bits, sizeof(short int), 1, fout);
   	 fwrite(&infoheader.Compression, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImageSize, sizeof(int), 1, fout);
   	 fwrite(&infoheader.xResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.yResolution, sizeof(int), 1, fout);
   	 fwrite(&infoheader.Colors, sizeof(int), 1, fout);
   	 fwrite(&infoheader.ImportantColors, sizeof(int), 1, fout);
   	 
   	 // Writes the edges calculated in rotl and stores it in fout file.
   	 for (c1 = 0; c1 < pixel_cols; c1++)
   	 {
   	 	for (c2 = 0; c2 < pixel_rows; c2++)
   	 	{
   	 		fwrite(&left[c1][c2],sizeof(struct Pixel),1, fout);
   	 	}
   	 }
    }
   
    // Frees dynamic memory of matrix
    for (c1 = 0; c1 < pixel_rows; c1++)
    { 	
   	free(matrix[c1]);
    }
    free(matrix);
    
    // Frees dynamic memory of trunc_matrix
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	free(trunc_matrix[c1]);
    } 
    free(trunc_matrix);
    
    //Frees dynamic memory of result
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	free(result[c1]);
    }
    free(result);
    
    // Frees dynamic memory of edmag_matrix
    for (c1 = 0; c1 < pixel_rows; c1++)
    {
    	free(edmag_matrix[c1]);
    } 
    free(edmag_matrix);
    
    // Frees dynamic memory of right rotation
    for (c1 = 0; c1 < pixel_cols; c1++)
    {
    	free(right[c1]);
    } 
    free(right);
    
    // Frees dynamic memory of left rotation
    for (c1 = 0; c1 < pixel_cols; c1++)
    {
    	free(left[c1]);
    } 
    free(left);
    
    fclose(fpin);
    fclose(fout);
    return 0;
}
