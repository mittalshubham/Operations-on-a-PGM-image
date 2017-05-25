/*
	Purpose:	Hide a text message inside image using stenography.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	Works with command line input of the image behind which the message is to be
				hidden followed by the message.
*/


#include"../ImageOperation.h"

int binary(int value){		//	Function to return binary equivalent of a number.
	int bin=0,factor=1;
	while(value!=0){
		bin+=(value%2)*factor;	value/=2;	factor*=10;
	}
	//printf("%d\n",bin);
	return bin;
}


void main(int argc,char*argv[]){

	image *image_details;
	char *input_file=argv[1];
	image_details=ReadImage(input_file);

	int row=0,col=0,k,pos,arg;

	int flag=1;		//	To detect if more data can be written in the image.
					//	flag=1 means more data can be written.
					//	flag=0 means no more data can be written.

	for(arg=2;arg<argc&&flag==1;arg++){
		for(pos=0;pos<=strlen(argv[arg])&&flag;pos++){
			/*if(row==image_details->height){
				printf("Entered amount of data exceeds the amount ");
				printf("of data that can be stenographed.\n");
				return;
			}*/
			int val;
			if(pos==strlen(argv[arg])&&arg!=argc-1){
					val=binary(32);
			}
			else if(pos!=strlen(argv[arg])){
				val=binary((int)argv[arg][pos]);
			}
			else{
				break;
			}
			for(k=0;k<8&&flag;k++){
				if(val%10==0){
					if(image_details->color_code[row][col]%2!=0){
						image_details->color_code[row][col]++;
					}
				}
				else{
					if(image_details->color_code[row][col]%2==0){
						image_details->color_code[row][col]++;
					}
				}
				val/=10;	col++;
				if(col==image_details->width){
					row++;	col=0;
					if(row==image_details->height){
						if(arg!=argc-1||(arg==argc-1&&k!=7)){
							printf("\nEntered amount of data exceeds the amount ");
							printf("of data that can be stenographed.\n");
						}
						flag=0;	break;
					}
				}
			}
		}
	}

	int val=0;

	if(flag){
		printf("\nThe message has been stenographed in \"%s\".\n",input_file);
	}
	else{
		printf("The amount of message possible to be hidden has been stenographed in");
		printf(" \"%s\".\n",input_file);
	}

	// Writing null charcter in the file to detect the end of message.

	if(flag){
		for(k=0;k<8&&flag;k++){
			if(image_details->color_code[row][col]%2!=0){
				image_details->color_code[row][col]++;
			}
			col++;
			if(col==image_details->width){
				row++;	col=0;
				if(row==image_details->height){
					flag=0;	break;
				}
			}
		}
	}

	WriteImage(input_file,image_details);
	//printf("\nThe message has been stenographed in \"%s\".\n",input_file);
}
