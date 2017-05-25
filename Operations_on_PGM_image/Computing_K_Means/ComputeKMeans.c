/*
	Purpose:	Using K means algorithm to separate out different clusters
				from a PGM image.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	Works with command line input of input image address followed by value
				of K(no. of cluster images to be formed) and the output folder name.
				The folder should already exist.
*/


#include"../ImageOperation.h"

# define color image_details->color_code
# define white image_details->color_range
# define black 0

image*image_details;

int flag=0,row,col,k,K;

int**cluster;	float *x;	// Cluster stores the value of x to which each pixel belongs to.
							// x stores the different color codes for different clusters

void setup(int row,int col){

	int min=(x[0]-color[row][col])*(x[0]-color[row][col]);
	int temp=0;


	for(k=0;k<K;k++){
		if(min>(x[k]-color[row][col])*(x[k]-color[row][col])){
			min=(x[k]-color[row][col])*(x[k]-color[row][col]);
			temp=k;
		}
	}

	if(temp!=cluster[row][col]){
		flag=0;
		cluster[row][col]=temp;
	}
};


void main(int argc,char*argv[]){

	char *input_file=argv[1],*output_folder_name=argv[3];
	mkdir(output_folder_name,0700);
	K=atoi(argv[2]);

	image_details=ReadImage(input_file);
	int **arr=color;

	x=calloc(K,sizeof(float));
	for(k=0;k<K;k++){
		x[k]=random()%white;
	}


	cluster=calloc(image_details->height,sizeof(int*));

	for(row=0;row<image_details->height;row++){
		cluster[row]=calloc(image_details->width,sizeof(int));
	}

	int iter=0;

	while(flag!=1&&iter<1000){

		flag=1;	iter++;
		
		for(row=0;row<image_details->height;row++){
			for(col=0;col<image_details->width;col++){
				setup(row,col);
			}
		}

		int count[K];

		for(k=0;k<K;k++){
			x[k]=0;	count[k]=0;
		}

		for(row=0;row<image_details->height;row++){
			for(col=0;col<image_details->width;col++){
				x[cluster[row][col]]+=color[row][col];
				count[cluster[row][col]]++;
			}
		}

		for(k=0;k<K;k++){
			if(count[k]!=0)
				x[k]/=count[k];
		}

	}

	for(k=0;k<K;k++){
		for(row=0;row<image_details->height;row++){
			for(col=0;col<image_details->width;col++){
				if(x[cluster[row][col]]==x[k]){
					color[row][col]=white;
				}
				else{
					color[row][col]=black;
				}
			}
		}
		char str[100];
		sprintf(str,"%s/%d",output_folder_name,k+1);
		WriteImage(str,image_details);
	}

	printf("\n%d cluster images have successfully been written in the ",K);
	char str[100];
	printf("folder \"%s\"\nfor the image \"%s\".\n",output_folder_name,input_file);

}
