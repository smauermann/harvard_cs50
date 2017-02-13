/**
 * read a 24-bit uncompressed BMP file
 * the file is mostly redish pixels
 * however there is some clue hidden among the red pixels
 * change certain populations of pixels to find out the clue
 * save the modified BMP into the outfile.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    // save filenames
    char *infile = argv[1];
    char *outfile = argv[2];
    
    // try to open input file in read mode
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }
    
    // try to open output file in write mode
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", outfile);
        return 3;
    }
    
    // read infiles BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infiles BITMAPFILEHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    /**
     * ensure infile is a 24-bit uncompressed BMP4.0
     * bfType = the magic numbers, aka first two bits of a BMP
     * bfOffBits = offset until bmp bits start
     * = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) = 54
     * biSize = sizeof(BITMAPINFOHEADER) = 40
     * biBitCount = 8 bit per blue, green and red = 24 bit
     */
    
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        // close all the files and pipe an appropriate error message
        // stderr standard stream is the terminal
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfiles BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfiles BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for scanlines
    // if not multiple of 4 (eg 3 pixels) then append 1 to 3 24-bit blocks
    //int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over infile scanlines (rows)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline (columns)
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temp store for rgb triples
            RGBTRIPLE triple;
            
            // read triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            /**
             * modify triplets to uncover the hidden clue
             * make all pure red pixels white
             */
            if (triple.rgbtRed == 0xff &&
                triple.rgbtGreen == 0x00 &&
                triple.rgbtBlue == 0x00)
            {
                triple.rgbtGreen = 0xff;
                triple.rgbtBlue = 0xff;
            }
            else if (triple.rgbtRed < 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0xff;
            }
            /**
             * print out all the pixels with less than full red,
             * to find the hidden guys
             * else if (triple.rgbtRed < 0xff)
             * {
             *     printf("%2x%2x%2x\n",triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
             * }
             */

            
            // write triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }
    return 0;
}