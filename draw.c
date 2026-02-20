#include<stdio.h>
#include "board.h"


#define RED 	"\x1b[31m"
#define BLUE 	"\x1b[34m"
#define GREEN 	"\x1b[32m"
#define YELLOW 	"\x1b[33m"
#define WHITE 	"\x1b[37m"
#define RESET 	"\x1b[0m"

void print_cell(int ind){
	switch(ind){
		case 0:
			printf(RED"[x]"RESET);
			break;

		case 1:
			printf(GREEN"[ ]"RESET);
			break;

		case 2:
			printf(WHITE"[ ]"RESET);
			break;

		case 3:
			printf(BLUE"[ ]"RESET);
			break;
	}
}

void draw(int x, int y, int z, int board[x][y][z]){
	for(int i=0; i<3; i++){
		for(int j=0; j<10; j++){
			for (int k=0; k<25; k++){
				if(i == A.f && j == A.w && k == A.l){
					printf(YELLOW"[A]"RESET);
					
				}
				else{
					if(i == B.f && j == B.w && k == B.l){
                                        	printf(YELLOW"[B]"RESET);
					}
					else{
						if(i == C.f && j == C.w && k == C.l){
                                        	printf(YELLOW"[C]"RESET);
						}
						else{print_cell(board[i][j][k]);}
					}
				}
			}
		printf("\n");
		}
		printf("\n");
	}
}
