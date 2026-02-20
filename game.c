#include<stdio.h>
#include<termios.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include "board.h"

static char started_p[3];

char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);              // get terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);            // disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);     // apply new settings
    ch = getchar();                              // read one char
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);     // restore settings
    return ch;
}

void player_tag(char *players, char *player_t, int *c_d, int *s_d){ //to give an unique tag to player
	short invalid=1;
	static short j=0;
	static short size =3;

	while(invalid ==1){
		printf("Choose player tag : ");
	
		for (int i=0; i<size ; i++){
			printf("%c ",players[i]);
		}

		printf("\n");
		char tag;
		scanf(" %c",&tag);
	
		for (int i=0; i<size ; i++){
			if(tag == players[i]){
				player_t[j] = tag;
				s_d[j] = c_d[i]; 
		       		j++;
				size--;
			
				switch(i){
					case 0:
						for(int k=0; k<size; k++ ){
							i++;
							players[k]=players[i];
							c_d[k] = c_d[i];
						}
						break;
				
					case 1:
						if(i==size){
							break;
						}

						i=0;

						for(int k=0; k<size; k++){
							players[k]=players[i];
							c_d[k] = c_d[i];
							i=i+2;
						}
						break;

					case 2:
						i=0;
					
						for(int k =0; k<size; k++){
							players[k]=players[i];
							c_d[k] = c_d[i];
							i++;
						}
						break;

				}
				
				invalid=0;
				printf("\033[H");
        			printf("\033[J");
				break;	
			}
			else{
				invalid = 1;
			}
		}
		if(invalid == 1){
			printf("Invalid data\n");
			sleep(2);
                	printf("\033[3A");
                	printf("\033[J");
		}

	}
	
}

int dice(){     //used to get random numbers for dice
        static int seed = 0;
	FILE *ran;
	int d;

	ran = fopen("seed.txt","r"); //To get the indexes of stairs
        if (ran == NULL){
        	if (!seed){
                	srand(time(NULL));
                	seed = 1;
        	}
        	d = (rand()%6)+1;
        	return d;
	}
	else{
		fscanf(ran,"%d",&d);
		return d;
		fclose(ran);
	}
}

void direction_d(int mv, int *w, int *l, short count, short p_i, int *c_d, int *d, int eff){  //used to change the direction
	*d= c_d[p_i];
	if(count == 4 || eff == 2){
		*d = dice();	
	
		if(*d==1 || *d==6){
			*d = c_d[p_i];
		}
		else{
			c_d[p_i] = *d;
		}
	}

	switch(*d){
		case 2:
			*w = -mv;
			break;
		
		case 3:
			*l = mv;
			break;
		
		case 4:
			*w = mv;
			break;

		case 5:
			*l = -mv;
			break;
	}
	
}

int start(int *mv, int p_i, char player_t[], int *j_start, int *s_p){ //To check whether the player can start the game or already started the game
	short beg;
	short size = *s_p; 	

	if(size != 3 && *mv == 6){
		
		if (size == 0){
			started_p[0] = player_t[p_i];
			*mv = 1;
			*j_start = 1;
			size++;
                }
                else{
                        for(int i=0; i<=size; i++){
                                if (started_p[i] == player_t[p_i]){
                                        break;
                                }
                                else{
                                        if (i == size){
                                                started_p[i] = player_t[p_i];
						*mv = 1;
						*j_start = 1;
						size++;
                                                break;
                                        }
                                }
                        }
                }	
		*s_p = size;
		return beg =1;
	}

	else{
		if(size == 3){
			return beg = 1;
		}

		for(int i=0; i<size; i++){
                                if (started_p[i] == player_t[p_i]){
                                        return beg = 1;
                                }
		}

		return beg = 0;
	}

}

int count_m_d(int p_i){ // To count how many times movement dice has been thrown
	static int count[]={0,0,0};
	if(count[p_i] == 4){
		count[p_i] = 0;	
	}
	return count[p_i] = count[p_i] + 1;
}

void captured_player(char c_player, int n){
	for(int i=0; i < n; i++){
		if(started_p[i] == c_player){
			for(int j = i; j<n-1; j++){
				started_p[j] = started_p[j+1];
			}	
			break;
		}
	}
}

int main(){
	printf("Press enter to start the game\n");
	char s = getch();	
	if (s == '\n'){
		sleep(1);
		printf("\033[H");
		printf("\033[J");
		
		char players[]={'A','B','C'};
		char player_n[3][20];
		char player_t[3];
		int c_d[]={2, 5, 3};
		int s_d[3];
		int s_p = 0;
		char direction[6][10]={"Empty", "North", "East", "South", "West", "Empty"};
		
		for (int i = 0; i<3; i++){
                        short cls=0;
                        while(cls==0){ //to avoid two players getting same name
                                printf("Enter the player name: ");
                                scanf("%19s",player_n[i]);
                                if (i==0){
                                        break;
                                }
                                
				for(int x=0; x<i;x++){
                                        if (strcmp(player_n[i],player_n[x])==0){
                                                printf("Username already exists\n");
                                                sleep(2);
                                                printf("\033[H");
                                                printf("\033[J");
                                                cls=0;
                                                break;
                                        }
                                        else{
						cls=1;
					}
				}		
			
			}	
			player_tag(players, player_t, c_d, s_d);
		}
		
		memcpy(c_d,s_d, sizeof(s_d));
		printf("Game begins");
		sleep(2);
		printf("\033[H");
		printf("\033[J");
		short begin, win =0;
		while(getchar() != '\n'); 
		char c_player;
		int round=1, t_d;
		int bawana_e[3] = {0,0,0};
		int fp_c[3] = {3,3,3};
		int dis[3] = {0,0,0};
		int trigg[3] = {0,0,0};
		int m_p[3] = {0,0,0};

		while(win != 1){

			printf("====================Round %d ======================\n",round);
			
			int call = 1;
			for(int i=0; i<3; i++){
				int f=0,w=0,l=0, i_mp=0,
				    j_start=0 ,c_mv = 0, dd =0;
				i_mp = m_p[i];

				if(i==0){
					win = g_board(player_t[i],&f,&w,&l,&c_mv,&c_player,round, call, &bawana_e[i], &m_p[i]);
					f = 0; w=0; l=0;
				}
				printf("Player %s's turn\n",player_n[i]);
				
				if( bawana_e[i] != 3){ trigg[i]=0;}

				if( bawana_e[i] != 1 && fp_c[i] == 3){ //To skip 3 rounds after food poisoning				
					int mv = dice();
					begin = start(&mv, i, player_t, &j_start, &s_p);
				         	
					if (bawana_e[i] == 3 && trigg[i] == 1){
						t_d = mv;
						mv = mv * 2;
					}

					if (begin == 1 && j_start == 1){
						short count = count_m_d(i);
						c_d[i] = s_d[i];
						direction_d(mv, &w, &l, count, i, c_d, &dd, bawana_e[i]);
						call = 0;
						win = g_board(player_t[i], &f, &w, &l, &c_mv, &c_player, round, call, &bawana_e[i], &m_p[i]);
						
						printf("%c is at the starting area and rolls 6 on the movement dice and is placed on %d %d %d of the maze\n",
								player_t[i], f, w, l);
					}
					
					else{
						if (begin == 1){
							short count = count_m_d(i);
                                                	direction_d(mv, &w, &l, count, i, c_d, &dd, bawana_e[i]);
							call = 0;
							win = g_board(player_t[i], &f, &w, &l, &c_mv, &c_player, round, call, &bawana_e[i], &m_p[i]);

							if(win == 1){
                                				printf("%s won the match\n",player_n[i]);
								break;
                        				}
							
							if(c_player != 'N'){
                                                		captured_player(c_player,s_p);
                                                		s_p--;
                                        		}
							
							if(bawana_e[i]==1){
								fp_c[i] = 0;
								printf("%c eats from Bawana and have a bad case of food poisoning. Will need three rounds to recover\n", player_t[i]);
								
							}
							
							if(bawana_e[i] == 2 && dis[i] != 0){
								printf("%c rolls and %d on the movement dice and is disoriented and move in the %s and moves %d cells and is placed at the %d %d %d\n", 
										player_t[i], mv, direction[c_d[i]-1], mv, f, w, l);
								dis[i]++;
								if(dis[i]==5){ 
									dis[i] = 0; 
									printf("%c has recovered from disorientation", player_t[i]);
									bawana_e[i]=0;
								}	
							}

							if(bawana_e[i]==2 && dis[i]==0){
								c_d[i] = 2;
								printf("%c eats from Bawana and is disoriented and is placed at the entrance of Bawana with 50 movement points\n", 
										player_t[i]);
								dis[i]++;
							}

							if(bawana_e[i] == 3 && trigg[i]==0){
								c_d[i] = 2;
								printf("%c eats from Bawana and is triggered due to bad quality of food. %c is placed at the entrance of Bawana with 50 movement points\n",
										player_t[i], player_t[i]);
								trigg[i]=1;
							}

							if(bawana_e[i] == 3 && trigg[i] == 1){
								printf("%c is triggered and rolls and %d on the movement dice and move in the %s and moves %d cells and is placed at the  %d %d %d\n",
										player_t[i], t_d, direction[c_d[i]-1], mv, f, w, l);
							}

							if(bawana_e[i] == 4){
								c_d[i]=2;
								printf("%c eats from Bawana and is happy. %c is placed at the entrance of Bawana with 200 movement points\n",
										player_t[i],player_t[i]);
								bawana_e[i] = 0;
							}

							if(bawana_e[i] > 4){
								c_d[i]=2;
								printf("%c eats from Bawana and earns %d movement points and is placed at the %d %d %d\n",
										player_t[i], bawana_e[i],f, w, l);
								bawana_e[i] = 0;
							}

							if (c_mv == 1){
								if(count == 4){
									printf("%c rolls and %d on the movement dice and %s on the direction dice, change direction to %s and moves %d cells and is now at %d %d %d\n", 
											player_t[i], mv, direction[dd-1], direction[c_d[i]-1], mv, f, w, l);
								}
								
								else{
                                                		printf("%c rolls and %d on the movement dice and moves %s by %d cells and is now at %d %d %d\n", 
										player_t[i], mv, direction[c_d[i]-1], mv, f, w, l);
								}
							}
							
							else if(c_mv == 0){
								printf("%c rolls and %d on the movement dice and cannot move in the %s. player remains at %d %d %d \n", 
										player_t[i], mv, direction[c_d[i]-1], f, w, l);
							}
							
							printf("%c moved %d that cost %d movement points and is left with %d and is moving in %s\n",
									player_t[i], mv, m_p[i]-i_mp,m_p[i], direction[c_d[i]-1]);
						}
					
						else{
							printf("%c is at the starting area and rolls %d on the movement dice cannot enter the maze\n", player_t[i], mv);
					
						}
					}
				}
				
				else{
					printf("%c is still food poisoned and misses the run\n", player_t[i]);
					fp_c[i]++;
					
					if(fp_c[i] == 3){
						bawana_e[i] = 0;
					}
				}
			}
	
			round++;
		}
	}
	printf("Game over\n");
	return 0;
}
