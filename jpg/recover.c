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
		char fname[500];
		
		//iniltzed a buffer
		unsigned char buffer[512];
		
		int count=0;
		char* infile = "card.raw";
		FILE* outptr = NULL;
		
		//open card.raw
		FILE* inptr = fopen(infile,"r");
		
		//read from card.raw to buffer
		
		// check for end of file
		while(fread(buffer, 512, 1, inptr) == 1)
		{

				//check for begining of JPEG
				if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
				{
					//print the jpg into same directory
					sprintf(fname, "%03d.jpg", count);
					//open the jpg file
					
					outptr = fopen(fname,"w");
					fclose(outptr);
					outptr = fopen(fname,"w");
					count++;
				}
				
				if(outptr !=NULL)
				{
					fwrite(buffer,512,1,outptr);

				}

		}
		
		// close infile
		fclose(inptr);
		
		// Thats, all folk!
		return 0;
	
}