/*
	Purpose:	Demagnify a PGM image 4 times.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	Works with command line input of input image address followed by the new
				image name after downscaling.
*/


#include"../ImageOperation.h"	// Contains functions ReadImage and WriteImage & other libraries.

# define code image->color_code

void demagnify(image*);		// To half the image width and height and adjust the pixels.

image image_details;		// Image is structure & image_details stores image input.

void main(int argc,char*argv[]){

	char *input_file=argv[1],*output_file=argv[2];
	image_details=*ReadImage(input_file);	// argv[1] stores input file name taken from command line.

	demagnify(&image_details);

	WriteImage(output_file,&image_details);	// argv[2] stores output file name taken from command line.

	printf("The new image has successfully been written as \"%s\".\n",output_file);

}

void demagnify(image*image){
	
	int row,col;

	int **new_color;	//	It will store the changed pixels.
	new_color=(int**)calloc((image->height+1)/2,sizeof(int*));

	for(row=0;row<(image->height+1)/2;row++)
		new_color[row]=calloc((image->width+1)/2,sizeof(int));
	

	for(row=0;row<(image->height-1);row+=2){

		for(col=0;col<(image->width-1);col+=2){

			new_color[row/2][col/2]=code[row][col]+code[row][col+1]+code[row+1][col]+code[row+1][col+1];
			new_color[row/2][col/2]/=4;		//Averaging four pixels to a single pixel.

		}
	}

	if(image->height%2!=0){
		for(col=0;col<image->width/2;col++){
			new_color[image->height/2][col]=code[image->height-1][col];
		}
	}

	if(image->width%2!=0){
		for(row=0;row<image->height/2;row++){
			new_color[row][image->width/2]=code[row][image->width-1];
		}
	}

	free(image->color_code);
	image->color_code=new_color;

	image->width=(image->width+1)/2;		//	Decreasing the image width & height by a factor of 2.
	image->height=(image->height+1)/2;		//	In case of even exactly half and in case of odd half+1.

}