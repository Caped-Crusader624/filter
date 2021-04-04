#include "helpers.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
int i,j,avg;
RGBTRIPLE tmp;
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            avg=((image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3);
            image[i][j].rgbtBlue=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtRed=avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for(i=0;i<(height);i++){
        for(j=0;j<(width/2);j++){
            tmp.rgbtBlue=image[i][j].rgbtBlue;
            tmp.rgbtGreen=image[i][j].rgbtGreen;
            tmp.rgbtRed=image[i][j].rgbtRed;

            image[i][j]= image[i][width-j-1];
            image[i][width-j-1]=tmp;

        }
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])

{
    grayscale(height,width,image);
            int gx;
            int gy;
            int g[(height-2)*(width-2)];
            int index = 0;

            for( i = 2;i < (height); i++)
            {
                for(j = 2; j < width; j++)
                {
                    gx= ((image[i][j].rgbtBlue)+((image[i-1][j].rgbtBlue)*2)+(image[i-2][j].rgbtBlue)-(image[i][j-2].rgbtBlue)-((image[i-1][j-2].rgbtBlue)*2)-(image[i-2][j-2].rgbtBlue));
                    gy= ((image[i][j].rgbtBlue)+ ((image[i][j-1].rgbtBlue)*2)+(image[i][j-2].rgbtBlue)-(image[i-2][j].rgbtBlue)-((image[i-2][j-1].rgbtBlue)*2)-(image[i-2][j-2].rgbtBlue));
                    g[index]=round(sqrt((gx * gx) + (gy * gy)));
                    index++;
                }
            }
            index=0;
            for(i=0;i<(height-2);i++){
                for(j=0;j<(width-2);j++){
                    if(g[index]>255){
                        image[i][j].rgbtBlue=255;
                        image[i][j].rgbtGreen=255;
                        image[i][j].rgbtRed=255;
                        index++;
                    }

                    else{
                    image[i][j].rgbtBlue=g[index];
                    image[i][j].rgbtGreen=g[index];
                    image[i][j].rgbtRed=g[index];
                    index++;
                    }
                }
            }

}
