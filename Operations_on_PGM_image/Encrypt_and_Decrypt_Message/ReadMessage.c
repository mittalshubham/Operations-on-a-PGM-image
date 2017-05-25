/*
	Purpose:	Read the text message hidden inside an image.
	Author:		Shubham Mittal.
	Date:		April 3,2017.
	Parameters:	Works with command line input of image in which the message has been hidden.
*/


#include"../ImageOperation.h"

int integ(int bin){
	int val=0,factor=1;
	while(bin!=0){
		val+=factor*(bin%10);
		factor*=2;
		bin/=10;
	}
	return val;
}

void main(int argc,char*argv[]){

	image *image_details=ReadImage(argv[1]);

	char *input_file=argv[1];

	int row=0,col=0,k,pos=0;
	char *message;

	message=(char*)malloc(image_details->width*image_details->height*sizeof(char)/8);
		// Size allocated is equal to size of max data that can be hidden in the image.

	int max=image_details->width*image_details->height*sizeof(char)/8;

	int flag=1;

	while(flag&&max--){
		int val=0,factor=1;
		for(k=0;k<8;k++){
			val+=factor*((image_details->color_code[row][col])%2);
			col++;	factor*=10;
			if(col==image_details->width){
				col=0;	row++;
				if(row==image_details->height){
					//printf("1\n");
					flag=0;	break;
				}
			}
			if(flag==0)
				break;
		}
		if(val==0){
			//printf("2\n");
			flag=0;
		}
		else{
			message[pos]=(char)integ(val);	pos++;
		}

	}

	if(pos<image_details->width*image_details->height){
		message[pos]='\0';
	}

	printf("The decrypted message is:\n%s\n",message);

}