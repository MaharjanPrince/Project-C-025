// Input and output for the maize
#include<stdio.h>
#define ROW 6
#define COLUMN 6
int maize[ROW][COLUMN]={
    {'S', '0', '1', '1', '1', '1'},
    {'1', '0', '1', '0', '0', '0'},
    {'1', '0', '1', '0', '1', 'E'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '1', '1', '1', '1', '1'}
};
void maizeprint(int,int);
void main(){
    maizeprint(ROW,COLUMN);
}
void maizeprint(ROW,COLUMN){
    int i;
    for(i=