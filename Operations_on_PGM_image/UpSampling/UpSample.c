/*
	Purpose:	Magnify a PGM image 4 times.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	Works with command line input of input image address followed by the new
				image name after upscaling.
*/


#include"../ImageOperation.h"

void magnify(image*);		//	Function to magnify the image by doubling width and height.

image image_details;

void main(int argc,char*argv[]){

	char *input_file=argv[1],*output_file=argv[2];
	image_details=*ReadImage(input_file);

	magnify(&image_details);

	WriteImage(output_file,&image_details);
	printf("The new image has successfully been written as \"%s\".\n",output_file);

}

void magnify(image*image_details){
	
	int row,col;

	int **new_color;		//	Stores new color codes.
	new_color=(int**)calloc((image_details->height)*2,sizeof(int*));

	for(row=0;row<image_details->height*2;row++)
		new_color[row]=calloc(image_details->width*2,sizeof(int));
	

	for(row=0;row<(image_details->height);row++){

		for(col=0;col<(image_details->width);col++){

			# define code image_details->color_code
			int x=2*row,y=2*col;
			new_color[x][y]=new_color[x+1][y]=new_color[x+1][y+1]=new_color[x][y+1]=code[row][col];
			//	Assigning 1 pixel value to 4 new pixels to double width and height.
		}
	}

	free(image_details->color_code);
	image_details->color_code=new_color;

	image_details->width*=2;		//	Doubling the width.
	image_details->height*=2;		//	Doubling the height.

}