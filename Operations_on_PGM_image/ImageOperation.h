/*
	Purpose:	Serves as a header file for functions ReadImage and WriteImage used to
				read and write PGM format images.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	ReadImage requires image location as parameter and WriteImage requires
				image data and new location for saving the image.
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct image{
	char magic_num[10];
	char comment[100];
	int width,height;
	int color_range;
	int **color_code;
}image;

image image_data;

image*ReadImage(char*input_name){
	
	FILE *ptr=fopen(input_name,"r");

	if(ptr==NULL){
		printf("ERROR.	Input image \"%s\" was not found!!!\n",input_name);
		exit(0);
	}

	fgets(image_data.magic_num,9,ptr);
	fgets(image_data.comment,99,ptr);
	fscanf(ptr,"%d %d %d",&image_data.width,&image_data.height,&image_data.color_range);
	image_data.color_code=(int**)calloc(image_data.height,sizeof(int*));

	int i,j;
	for(i=0;i<image_data.height;i++)
		image_data.color_code[i]=(int*)calloc(image_data.width,sizeof(int));

	for(i=0;i<image_data.height;i++){
		for(j=0;j<image_data.width;j++){
			fscanf(ptr,"%d",&image_data.color_code[i][j]);
		}
	}

	fclose(ptr);

	return &image_data;
}

void WriteImage(char*output_name,image*image_data){
	FILE *ptr=fopen(output_name,"w");
	fprintf(ptr,"%s%s%d %d\n%d\n",image_data->magic_num,image_data->comment,image_data->width,image_data->height,image_data->color_range);

	int i,j;
	for(i=0;i<(image_data->height);i++){
		for(j=0;j<(image_data->width);j++){
			fprintf(ptr,"%d ",image_data->color_code[i][j]);
		}
	}
}