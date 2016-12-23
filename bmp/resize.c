/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, just because.
 * by new pointer method
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{

        // ensure proper usage
        if (argc != 4)
        {
            printf("Usage: ./copy n infile outfile\n");
            return 1;
        }
    
        // remember filenames
        char* n = argv[1];
        char* infile = argv[2];
        char* outfile = argv[3];
        
        if(atoi(n)<1 || atoi(n)>100)
        {
            printf("ERROR: n must line in 1 to 100");
            return 4;
        }
    
        // open input file 
        FILE* inptr = fopen(infile, "r");
        if (inptr == NULL)
        {
            printf("Could not open %s.\n", infile);
            return 2;
        }
    
        // open output file
        FILE* outptr = fopen(outfile, "w");
        if (outptr == NULL)
        {
            fclose(inptr);
            fprintf(stderr, "Could not create %s.\n", outfile);
            return 3;
        }
    
        // read infile's BITMAPFILEHEADER
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
        // read infile's BITMAPINFOHEADER
        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
        // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
            bi.biBitCount != 24 || bi.biCompression != 0)
        {
            fclose(outptr);
            fclose(inptr);
            fprintf(stderr, "Unsupported file format.\n");
            return 4;
        }
        
        // save old header info
    
        long oldwidth = bi.biWidth;
        long oldheight = bi.biHeight;
        long oldpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
        
        // change header info
        bi.biWidth = atoi(n) * bi.biWidth;
        bi.biHeight = atoi(n) * bi.biHeight;
        
        // determine padding for scanlines
        int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
        
        //change image size according to new resize image
        bi.biSizeImage = (bi.biWidth*3 + padding) * labs(bi.biHeight);
        
        // edit outfile's BITMAPFILEHEADER to account for resize
        bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
        
        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        
        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
        
        //initialize a new pointer
        RGBTRIPLE* BUFFER;
        
        //allocates memory to a new pointer
        BUFFER = malloc(sizeof(RGBTRIPLE) * bi.biWidth);
        
         // iterate over infile's scanlines
        for (int i = 0; i < labs(oldheight); i++)
        {
                                //initializing a variable
                                int cur=0;
                                
                                // iterate over pixels in scanline
                                for (int j = 0; j < oldwidth; j++)
                                {
                                       
                                        // temporary storage
                                        RGBTRIPLE triple;
                            
                                        // read RGB triple from infile
                                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                                        
                                        //store a pixel n times into new address(BUFFER)
            
                                        for(int m = 0; m < atoi(n); m++) 
                            			{
                                				BUFFER[cur] = triple;
                                				cur++;
                            			}
                            			
                                }
                                
                                
                                //expands vertically
                                for(int m = 0; m < atoi(n); m++) 
                        		{
                        				//write a scanline
                        				fwrite(BUFFER, sizeof(RGBTRIPLE), bi.biWidth, outptr);
                        				
                                        // add padding (to demonstrate how)
                                        for (int k = 0; k < padding; k++)
                                        {
                                            fputc(0x00, outptr);
                                                
                                        }
                                        
                                        
                    			}
                    			
                    			
                                // skip over padding, if any for printing next line
                                fseek(inptr, oldpadding, SEEK_CUR);
                            
                                
        
        }
        
        //free the allocated memory
        free(BUFFER);
        // close infile
        fclose(inptr);
    
        // close outfile
        fclose(outptr);
    
        // that's all folks
        return 0;
}
