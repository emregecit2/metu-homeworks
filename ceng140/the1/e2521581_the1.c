#include <stdio.h>
void fill(int changed_pixels[25][25],int pixels[25][25],int row,int column,int fill_color,int current_color){
	int row_max,column_max;
	pixels[row][column]=fill_color;
	changed_pixels[row][column]=0;
	column_max=column+1;
	row_max=row+1;
	for(column=column_max-2;column<=column_max;column+=1){
		if(column<0 || column>24) continue;
		for(row=row_max-2;row<=row_max;row+=1){
			if(row<0 || row>24) continue;
			if(pixels[row][column]==current_color && changed_pixels[row][column]){
				fill(changed_pixels,pixels,row,column,fill_color,current_color);
			}}
		}
	}
void print(int pixels[][25]){
	int row,column;
	for(row=0;row<25;row++){
		for(column=0;column<25;column++){
			printf("%d ",pixels[row][column]);
		}
		printf("\n");
	}
}
void copyf(int pixels[][25],int copy[][25],int row1,int column1,int row2,int column2){
	int row,column;
	for(row=0;row<=row2-row1;row++)
		for(column=0;column<=column2-column1;column++)
			copy[row][column]=pixels[row+row1][column+column1];
}

int main(void)
{
	char mode;
	int row,column,pixels[25][25],changed_pixels[25][25];
	for(row=0;row<25;row++){
		for(column=0;column<25;column++){
			scanf("%d",&pixels[row][column]);
			changed_pixels[row][column]=1;
		}
	}
	scanf(" %c",&mode);
	switch(mode){
		case 'F':{
			int fill_color,column,row;
			scanf("%d%d",&row,&column);
			if(column<0){
				if(row<0) fill_color=0;
				else if(row>24) fill_color=6;
				else fill_color=7;
			}
			else if(column>24){
				if(row<0) fill_color=2;
				else if(row>24) fill_color=4;
				else fill_color=3;
			}
			else{
				if(row<0) fill_color=1;
				else if(row>24) fill_color=5;
				else fill_color=pixels[row][column];
			}
			scanf("%d%d",&row,&column);
			fill(changed_pixels,pixels,row,column,fill_color,pixels[row][column]);
			print(pixels);
			break;}
		case 'P':{
			int column1,row1,column2,row2,copy[25][25],counter=0;
			scanf("%d%d%d%d",&row1,&column1,&row2,&column2);
			if(column1>column2){
				int t=column2;
				column2=column1;
				column1=t;
			}
			if(row1>row2){
				int t=row2;
				row2=row1;
				row1=t;
			}
			copyf(pixels,copy,row1,column1,row2,column2);
			scanf("%d%d%d%d",&row1,&column1,&row2,&column2);
			if(column1>column2){
				int t=column2;
				column2=column1;
				column1=t;
			}
			if(row1>row2){
				int t=row2;
				row2=row1;
				row1=t;
			}
			for(column=0;column<=column2-column1;column++){
				for(row=0;row<=row2-row1;row++){
					if(pixels[row+row1][column+column1]!=copy[row][column]) counter+=1;
					pixels[row+row1][column+column1]=copy[row][column];
				}
			}
			print(pixels);
			printf("%d\n",counter);
			break;}
		case 'R':{
			char direction;
			int degree,column1,column2,row1,row2,counter=0,copy[25][25];;
			scanf(" %c",&direction);
			scanf("%d",&degree);
			scanf("%d%d%d%d",&row1,&column1,&row2,&column2);
			copyf(pixels,copy,row1,column1,row2,column2);
			if(direction=='R'){
				degree=360-degree;
			}
			scanf("%d%d%d%d",&row1,&column1,&row2,&column2);
			switch(degree){
				case 90:
					for(column=0;column<=column2-column1;column++){
						for(row=0;row<=row2-row1;row++){
							if(pixels[row+row1][column+column1]!=copy[column][column2-column1-row]) counter+=1;
							pixels[row+row1][column+column1]=copy[column][column2-column1-row];
						}
			}
					break;
				case 180:
					for(column=0;column<=column2-column1;column++){
						for(row=0;row<=row2-row1;row++){
							if(pixels[row+row1][column+column1]!=copy[row2-row1-row][column2-column1-column]) counter+=1;
							pixels[row+row1][column+column1]=copy[row2-row1-row][column2-column1-column];
						}
			}
					break;
				case 270:
					for(column=0;column<=column2-column1;column++){
						for(row=0;row<=row2-row1;row++){
							if(pixels[row+row1][column+column1]!=copy[column2-column1-column][row]) counter+=1;
							pixels[row+row1][column+column1]=copy[column2-column1-column][row];
						}}
					break;
				default:
					for(column=0;column<=column2-column1;column++){
						for(row=0;row<=row2-row1;row++){
							if(pixels[row+row1][column+column1]!=copy[row][column]) counter+=1;
							pixels[row+row1][column+column1]=copy[row][column];
						}
}}
			print(pixels);
			printf("%d\n",counter);
			break;
	}
}
return 0;
}
