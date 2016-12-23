/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include<stdio.h>
#include<cs50.h>
#include <stdlib.h>
int main(void)
{
		//initilized filename
		char fname[50];
		
		//iniltzed a buffer
		unsigned char buffer[512];
		
		int count=0;
		char* infile = "card.raw";
		FILE* outptr = NULL;
		
		//open card.raw
		FILE* inptr = fopen(infile,"r");
	
		// check for end of file
		while(fread(&buffer, sizeof(int)*128, 1, inptr) > 0)
		{
			    //read from card.raw to buffer
				fread(&buffer, sizeof(int)*128, 1, inptr);
				
				//check for begining of JPEG
				if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
				{
					
					//print the jpg into same directory
					sprintf(fname, "%03d.jpg", count);
					count++;
					//close already open file
					if(outptr != NULL)
					{
						fclose(outptr);
					}
					//open a new file
		        	outptr = fopen(fname,"w");
				}
				
				//write into outfile
				if(outptr != NULL)
				{
					fwrite(&buffer, sizeof(int)*128, 1, outptr);
				}
	
		}
		
		// close infile
		fclose(inptr);
		
		// Thats all folk!
		return 0;
	
}