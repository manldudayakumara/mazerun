#include "board.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct position A={0,6,12,100,0}; //To track the players
struct position B={0,9,8,100,0};
struct position C={0,9,16,100,0};

int direction(){ //To get random direction for stairs 1-unidirectional 2-one way up 3-one way down
static int seed = 0;
        if (!seed){
                srand(time(NULL));
                seed = 1;
        }
        short d = (rand()%3)+1;
        return d;
}

int valid_cell(int f, int w, int l) { //To check whether a valid cell
    return (f >= 0 && f < 3) &&
           (w >= 0 && w < 10) &&
           (l >= 0 && l < 25);
}

int r_effects(void){ //To get effects for bawana cells randomly
	static int count_mp = 0, count_e = 0,
		   seed = 0,
		   e1 = 0, e2 = 0, e3 = 0, e4 =0;
	short effect=0, r_c=0;
	
	if (count_mp >= 4 && count_e >= 8) {
        return 0; 
    	}

	if (!seed){
                srand(time(NULL));
                seed = 1;
        }
        if(count_mp<4 && count_e<8){
		r_c = (rand()%2);
	}
	else{ 
		if(count_mp < 4){r_c = 1;}
		else{r_c = 0;}
	}

	if (r_c == 1){
		count_mp++;
		return effect = ((rand()%10)+1)*10;
	}
	else{
		while(effect == 0){
        		effect = (rand()%4)+1;
			switch(effect){
				case 1:
					if (e1 < 2) { count_e++; e1++; return 1; }
					else{effect = 0;}
              				break;
        			case 2:
                			if (e2 < 2) { count_e++; e2++; return 2; }
                			else{effect = 0;}
					break;
            			case 3:
                			if (e3 < 2) { count_e++; e3++; return 3; }
                			else{effect = 0;}
					break;
            			case 4:
                			if (e4 < 2) { count_e++; e4++; return 4; }
                			else{effect = 0;}
					break;
			}
		}
		return 0;
	}
}

int bawana_eff(int effect, int *f, int *w, int *l, char player_t){
	int mp=0;
	switch(player_t){
		case 'A':
			A.b_e = effect;
			break;

		case 'B':
			B.b_e = effect;
			break;

		case 'C':
			C.b_e = effect;
			break;
	}
	if(effect<=4){
		switch(effect){
			case 1:
				return 0;
				break;

			case 2:
				*f = 0;	*w = 9;	*l =19;
				return mp = 50;
				break;

			case 3:
				*f = 0; *w = 9; *l =19;
				return mp = 50;
				break;

			case 4:
				*f = 0; *w = 9; *l =19;
				return mp = 200;
				break;
		}
	}
	
	return mp = effect;
}

int ran_val(int active_c){
	int fun = 0, r=0;
	static int seed = 0;
	static int c_z=0, c_v=0, b_1 =0, b_3=0, m_f=0;

	if (!seed){
                srand(time(NULL));
                seed = 1;
        }
	
	while(fun == 0){
		r = (rand()%5);
		if(c_z < (active_c/0.25) && r == 0){c_z++; return 0;}
		else{fun = 0;}

		if(c_v< (active_c/0.35) && r == 1){
			c_v++; 	return ((rand()%4)+1);
		}
		else{fun = 0;}
		
		if(b_1 < (active_c/0.25) && r == 2){
			b_1++;	return ((rand()%2)+5); 
		}
		else{fun = 0;}

		if(b_3 < (active_c/0.1) && r == 3){
			b_3++; 	return ((rand()%3)+7); 
		}
		else{fun = 0;}

		if(m_f < (active_c/0.05) && r == 4){
			m_f++;	return ((rand()%2)+10);
		}
		else{fun = 0;}
	}

	return 0;

}

int mv_point(int fun, int mp){
	switch (fun){
		case 0:
			return mp;
		case 1:
			return mp = mp -1;
		case 2:
			return mp = mp -2;
		case 3:
			return mp = mp -3;
		case 4:
			return mp = mp -4;
		case 5:
			return mp = mp +1;
		case 6:
			return mp = mp +2;
		case 7:
			return mp = mp +3;
		case 8:
			return mp = mp +4;
		case 9:
			return mp = mp +5;
		case 10:
			return mp = mp * 2;
		case 11:
			return mp = mp * 3;
	}
	return 0;
}

void check_pol(int poles_i[10][4], int u_poles[10][2][3], int *pol, int *p_f, int *p_w, int *p_l, int *t_mp, int init_val[750]){ //To check whether player is at a pole point
        for(int i=0; i<10; i++){
                 if(poles_i[i][0] == *p_f && poles_i[i][2] == *p_w && poles_i[i][3] == *p_l){
                        u_poles[*pol][0][0] = *p_f;       u_poles[*pol][0][1] = *p_w;       u_poles[*pol][0][2] = *p_l;
                        (*pol)++;
                        u_poles[*pol-1][1][0]= *p_f = poles_i[i][1];
                        u_poles[*pol-1][1][1]= *p_w = poles_i[i][2];
                        u_poles[*pol-1][1][2]= *p_l = poles_i[i][3];
                        *t_mp = mv_point(init_val[(*p_f)*100+(*p_w)*10+(*p_l)], *t_mp);
                        if(*t_mp>500){ *t_mp = 500;}
                 }

                 if(poles_i[i][0] ==2 && *p_f == 1 && poles_i[i][2]== *p_w && poles_i[i][3] == *p_l){
                        u_poles[*pol][0][0] = *p_f;       u_poles[*pol][0][1] = *p_w;       u_poles[*pol][0][2] = *p_l;
                        (*pol)++;
                        u_poles[*pol-1][1][0]= *p_f = poles_i[i][1];
                        u_poles[*pol-1][1][1]= *p_w = poles_i[i][2];
                        u_poles[*pol-1][1][2]= *p_l = poles_i[i][3];
                        *t_mp = mv_point(init_val[(*p_f)*100+(*p_w)*10+(*p_l)], *t_mp);
                        if(*t_mp>500){ *t_mp = 500;}
                }
        }
}

int manh_dis(int f1, int f2, int w1, int w2, int l1, int l2) { //To get manhattan distance
    return abs(f1 - f2) + abs(w1 - w2) + abs(l1 - l2);
}

void check_sta(int stairs_i[12][2][3], int u_stairs[12][2][3], int stairs_d[12], int *p_f, int *p_w, int *p_l, int *sta, int *t_mp, int init_val[750], int flag_i[3]) {
   
    for(int i=0; i<12; i++){
        int f_f=0, f_w=0, f_l=0, t_f=0, t_w=0, t_l=0;

        if(stairs_i[i][0][0] == *p_f && stairs_i[i][0][1] == *p_w && stairs_i[i][0][2] == *p_l && (stairs_d[i] == 1 || stairs_d[i] == 2)){
            f_f = stairs_i[i][0][0]; f_w = stairs_i[i][0][1]; f_l = stairs_i[i][0][2];
            t_f = stairs_i[i][1][0]; t_w = stairs_i[i][1][1]; t_l = stairs_i[i][1][2];
        }
        else if(stairs_i[i][1][0] == *p_f && stairs_i[i][1][1] == *p_w && stairs_i[i][1][2] == *p_l && (stairs_d[i] == 1 || stairs_d[i] == 3)){
            f_f = stairs_i[i][1][0]; f_w = stairs_i[i][1][1]; f_l = stairs_i[i][1][2];
            t_f = stairs_i[i][0][0]; t_w = stairs_i[i][0][1]; t_l = stairs_i[i][0][2];
        }
        else{
            continue; 
        }

        int choose_idx = -1;
        for(int j=0; j<*sta; j++){
            if(u_stairs[j][0][0] == f_f && u_stairs[j][0][1] == f_w && u_stairs[j][0][2] == f_l){
                choose_idx = j;
                break;
            }
        }

        if(choose_idx == -1){
            u_stairs[*sta][0][0] = f_f;
            u_stairs[*sta][0][1] = f_w;
            u_stairs[*sta][0][2] = f_l;
            u_stairs[*sta][1][0] = *p_f = t_f;
            u_stairs[*sta][1][1] = *p_w = t_w;
            u_stairs[*sta][1][2] = *p_l = t_l;
            *t_mp = mv_point(init_val[(*p_f)*100 +(*p_w)*10 +(*p_l)], *t_mp);
            if(*t_mp>500) *t_mp = 500;
            (*sta)++;
        }
        else{
            int ot_f = u_stairs[choose_idx][1][0];
            int ot_w = u_stairs[choose_idx][1][1];
            int ot_l = u_stairs[choose_idx][1][2];
            int o_dis = manh_dis(ot_f, flag_i[0],ot_w,flag_i[1], ot_l, flag_i[2]);
            int n_dis = manh_dis(t_f, flag_i[0],t_w,flag_i[1],t_l,flag_i[2]);

            if(n_dis < o_dis){
                u_stairs[choose_idx][1][0] = *p_f = t_f;
                u_stairs[choose_idx][1][1] = *p_w = t_w;
                u_stairs[choose_idx][1][2] = *p_l = t_l;
                *t_mp = mv_point(init_val[(*p_f)*100 +(*p_w)*10 +(*p_l)], *t_mp);
                if(*t_mp>500) *t_mp = 500;
            }
        }
    }

}


int g_board(char player_t, int *f, int *w, int *l, int *c_mv, char *c_player, int round, int call, int *bawana_e,int *mp){
	int p_l= 0, p_w= 0 , p_f= 0, items_r, i , sta=0, b_mp=0, t_mp=0, pol=0, flg=0, min_mp=0;
	static int board[3][10][25];
	static int stairs_i[12][2][3];
	static int stairs_d[12];
	static int walls_i[3][2][3];
	static int poles_i[10][4];
       	static int flag_i[3];
	int u_poles[10][2][3];
	int u_stairs[12][2][3];
	static int bawana[12];
	static int init_val[750];
	static int active_c=0;
	char effect[5][15]={"Movement point","Food Poisoning","Disoriented","Triggered","Happy"};
	FILE *stairs, *walls, *poles, *flag;
	
	*c_player = 'N';
	if(round == 1 && call == 1){	
		stairs = fopen("stairs.txt","r"); //To get the indexes of stairs
		if (stairs == NULL){
			printf("Error 404\nstairs file is not available\n");
		}
		else{
			i=0;

			while((items_r=fscanf(stairs, "[%d, %d, %d, %d, %d, %d] ", 
							&stairs_i[i][0][0], &stairs_i[i][0][1], &stairs_i[i][0][2], 
							&stairs_i[i][1][0], &stairs_i[i][1][1], &stairs_i[i][1][2])) == 6){
           			i++;
       			}
			fclose(stairs);
		}

		walls = fopen("walls.txt","r"); //To get the indexes of walls
       		if (walls == NULL){
        	       	printf("Error 404\nwalls file is not available\n");
       		}
		else{
			i = 0;

       			while((items_r = fscanf(walls, "[%d, %d, %d, %d, %d, %d] ", 
							&walls_i[i][0][0], &walls_i[i][0][1], &walls_i[i][0][2], 
							&walls_i[i][1][0], &walls_i[i][1][1], &walls_i[i][1][2])) == 6){
           			i++;
       			}
			fclose(walls);
		}

		poles = fopen("poles.txt","r"); //To get the indexes of poles
       		if (poles == NULL){
        	       		printf("Error 404\npoles file is not available\n");
       		}
		else{
			i = 0;

			while((items_r = fscanf(poles, "[%d, %d, %d, %d] ", 
							&poles_i[i][0], &poles_i[i][1], &poles_i[i][2], &poles_i[i][3])) == 4){
        			i++;
       			}
			fclose(poles);
		}

		flag = fopen("flag.txt","r"); //To get the index of flag
		if (flag == NULL){
			printf("Error 404\nflag file is not available\n");
		}
		else{
			if(fscanf(flag,"[%d, %d, %d] ", &flag_i[0], &flag_i[1], &flag_i[2]) != 3){
			printf("Failed to read flag.txt");
			}
			fclose(flag);
		}
	  
		for(int i=0; i<2; i++){	//To create first & second floor
			for(int j=0; j<10; j++){	
				for(int k=0; k<25; k++){
					board[i][j][k] = 1;
					active_c++;
				}
			}
		}

		for(int i=6; i<10; i++){  //To create start area
               		for(int j=8; j<=16; j++){
                       		board[0][i][j] = 2;
				active_c--;
               		}
       		}

		for(int i=0; i<6; i++){  //To create second floor inactive cells
               		for(int j=8; j<=16; j++){
                       		board[1][i][j] = 0;
				active_c--;
               		}
       		}

		for(int i=0; i<10; i++){  //To create third floor active cells
               		for(int j=8; j<=16; j++){
                       		board[2][i][j] = 1;
				active_c++;
               		}
       		}
	
		for(int i=0; i<3; i++){	//To create walls
			if(walls_i[i][0][1] == walls_i[i][1][1]){
				for(int j=walls_i[i][0][2]; j<= walls_i[i][1][2]; j++){
					int	x = walls_i[i][0][0],
						y = walls_i[i][0][1];
					board[x][y][j] = 0;
					active_c--;
				}	
			}

			else{
				for(int j=walls_i[i][0][1]; j<= walls_i[i][1][1]; j++){
       	        			int     x = walls_i[i][0][0],
                        	       		z = walls_i[i][0][2];
                	               	board[x][j][z] = 0;
					active_c--;
        	               	}
	
			}
		}
		
		for(int i=0; i<12; i++){
                        stairs_d[i] = 1;
                }

		for(int i = 6; i<=9; i++){ //To create walls of bawana
			board[0][i][20] = 0;
			active_c--;
		}

		for(int i = 20; i<=24; i++){ //To create walls of bawana
			board[0][6][i] = 0;
			active_c--;
		}	
		i = 0;
		for(int j = 7; j<=9; j++){ //To create bawana area
			for(int k = 21; k<=24; k++){
				board[0][j][k] = 3;
				bawana[i] = r_effects();				
				i++;
				active_c--;
			}
		}
	
		for(int i=0; i<3; i++){
			for(int j=0; j<10; j++){
				for(int k=0; k<25; k++){
					if(board[i][j][k] == 1){
						init_val[i*100+j*10+k] = ran_val(active_c);
					}
					else{
						init_val[i*100+j*10+k] = 0;	
					}
				}
			}
		}
		draw(3, 10, 25, board);
		return 0;
	}
		
	round = round % 5;
	if(round == 0 && call == 1){	//To get a random direction for stairs
		draw(3, 10, 25, board);
		for(int i=0; i<12; i++){
			stairs_d[i] = direction();
			printf("Stair from %d %d %d to %d %d %d is ",stairs_i[i][0][0], stairs_i[i][0][1], stairs_i[i][0][2], stairs_i[i][1][0], stairs_i[i][1][1], stairs_i[i][1][2]);
			switch(stairs_d[i]){
				case 1:
					printf("unidirectional\n");
					break;
				case 2:
					printf("one way up\n");
					break;
				case 3:
					printf("one way down\n");
			}
		}
	return 0;
	}
	else if( call == 1){
		draw(3, 10, 25, board);
		return 0;
	}
        	
	int mv, l_i;
	if(*l == 0){	//To check which element has increased
		mv = *w;
		l_i = 0;
	}
	else{
		mv = *l;
		l_i = 1;
	}
	 
	switch (player_t){
		case 'A' :	
			p_f = A.f;
			*f = A.f;
			p_l = A.l + *l;
			*l = A.l;
			p_w = A.w + *w;
			*w = A.w;
			*mp = t_mp =A.mp;
			A.b_e = *bawana_e;
			break;

		case 'B' :
			p_f = B.f;
			*f = B.f;
			p_l = B.l + *l;
			*l = B.l;
			p_w = B.w + *w;
			*w = B.w;
			*mp = t_mp =B.mp;
			B.b_e = *bawana_e;
			break;

		case 'C' :
			p_f = C.f;
			*f = C.f;
			p_l = C.l + *l;
			*l = C.l;
			p_w = C.w + *w;
			*w = C.w;
			*mp = t_mp = C.mp;
			C.b_e = *bawana_e;
			break;
	}

	if(*bawana_e != 1){

	if (valid_cell(p_f,p_w,p_l)){ 
		
		if(l_i == 1){
			p_l = p_l - mv;
		}
		else{
			p_w = p_w - mv;	
		}
		if(mv>0){
			for(int x = 1; x <= mv; x++){
				if(l_i == 1){
					p_l = p_l + 1;	
				}
				else{
					p_w = p_w + 1;
				}
				t_mp = mv_point(init_val[p_f*100+p_w*10+p_l], t_mp);
				if(t_mp>500){ t_mp = 500;}
				if(t_mp<=0){ min_mp = 1;}	

				if(flag_i[0] == p_f && flag_i[1] == p_w && flag_i[2] == p_l){ //To check whether the player is at flag pole
                        		flg= 1;
                		}

				check_pol(poles_i, u_poles, &pol, &p_f, &p_w, &p_l, &t_mp, init_val);
				check_sta(stairs_i, u_stairs, stairs_d, &p_f, &p_w, &p_l, &sta, &t_mp, init_val, flag_i);
			}
		}

		else{
			for(int x = 1; x <= (-mv); x++){
                                if(l_i == 1){
                                        p_l = p_l - 1;	
                                }
                                else{
                                        p_w = p_w - 1;
                                }
				t_mp = mv_point(init_val[p_f*100+p_w*10+p_l], t_mp);
				if(t_mp>500){ t_mp = 500;}
				if(t_mp<=0){ min_mp = 1;}

                                if(flag_i[0] == p_f && flag_i[1] == p_w && flag_i[2] == p_l){ //To check whether the player is at flag pole
                                        flg= 1;
                                }

				check_pol(poles_i, u_poles, &pol, &p_f, &p_w, &p_l, &t_mp, init_val);
				check_sta(stairs_i, u_stairs, stairs_d, &p_f, &p_w, &p_l, &sta, &t_mp, init_val, flag_i);
                        }

		}
	}
	
		if(valid_cell(p_f,p_w,p_l) && board[p_f][p_w][p_l] == 2 && (sta>0 || pol>0)){ //To check whether the player is at starting area
			*c_player = player_t;
			printf("%c has entered to start area\n",player_t);
		}

		if (valid_cell(p_f,p_w,p_l) && board[p_f][p_w][p_l] == 0){ //To check whether the player is at a valid cell
			min_mp = 0;
		}
	}
		if(*bawana_e == 1 || min_mp == 1){
			static int seed = 0;
			if (!seed){
                		srand(time(NULL));
                		seed = 1;
        		}
			p_f = 0;
			p_w = (rand()%3)+7;
			p_l = (rand()%4)+21;

			if(min_mp == 1){
				
				printf("%c movement points are depleted and requires replenishment. Transport to Bawana\n",player_t);
			}
		}

		if(valid_cell(p_f,p_w,p_l) && board[p_f][p_w][p_l] == 3 && (sta>0 || pol>0)){ //To check whether the player is at bawana area
			i = 0;
			*c_mv = 3;
			for(int j = 7; j<=9; j++){ 
                        	for(int k = 21; k<=24; k++){ 
					if(p_w == j && p_l == k){
						b_mp = bawana_eff(bawana[i], &p_f, &p_w, &p_l, player_t);
						t_mp = t_mp + b_mp;
						if(t_mp>500){ t_mp = 500;}
						*bawana_e = bawana[i];
						if(bawana[i]>4){
							bawana[i] = 0;
						}
						 printf("%c is placed on a %s and effect take place\n", player_t, effect[bawana[i]]);
						break;
					}
                                	i++;
                        	}
                	}
		}

		if (valid_cell(p_f,p_w,p_l) && board[p_f][p_w][p_l] == 1){ //To check whether the player is at a valid cell
			*c_mv = 1;
			
			if(sta>0){
				for(int i=0; i<sta; i++){
					printf("%c lands on %d %d %d which is a stair cell. %c takes the stairs and now placed at %d %d %d in floor %d\n",
						player_t, u_stairs[i][0][0], u_stairs[i][0][1], u_stairs[i][0][2],
						player_t, u_stairs[i][1][0], u_stairs[i][1][1], u_stairs[i][1][2], u_stairs[i][1][0]);
				}
			}
			
			if(pol>0){
				for(int i=0; i<pol; i++){
					printf("%c lands on %d %d %d which is a pole cell. %c slides down and now placed at %d %d %d in floor %d\n",
                                                player_t, u_poles[i][0][0], u_poles[i][0][1], u_poles[i][0][2],
                                                player_t, u_poles[i][1][0], u_poles[i][1][1], u_poles[i][1][2], u_poles[i][1][0]);
				}
			}

			switch (player_t){
               			case 'A' :
					if(p_f == B.f && p_w == B.w && p_l == B.l){ //To check whether player B got captured
						B.f = 0;
						B.w = 9;
						B.l = 8;
						*c_player = 'B';
						printf("%d %d %d \n",B.f,B.w,B.l);
						printf("Player B got captured\n");
					}
					
					if(p_f == C.f && p_w == C.w && p_l == C.l){ //To check whether player C got captured
						C.f = 0;
						C.w = 9;
						C.l = 16;
						*c_player = 'C';
						printf("%d %d %d \n",C.f,C.w,C.l);
						printf("Player C got captured\n");
					}

					*f = A.f = p_f;
                       			*l = A.l = p_l;
                       			*w = A.w = p_w;
					*mp = A.mp = t_mp;
                       			break;
	
                		case 'B' :
					if(p_f == A.f && p_w == A.w && p_l == A.l){ //To check whether player A got captured 
                                                A.f = 0;
						A.w = 6;
						A.l = 12;
						*c_player = 'A';
                                        	printf("%d %d %d \n",A.f,A.w,A.l);
						printf("Player A got captured\n");
					}
					
					if(p_f == C.f && p_w == C.w && p_l == C.l){ //To check whether player C got captured
                                                C.f = 0;
						C.w = 9;
						C.l = 16;
						*c_player = 'C';
						printf("%d %d %d \n",C.f,C.w,C.l);
						printf("Player C got captured\n");
                                        }

					*f = B.f = p_f;
                       			*l = B.l = p_l;
                       			*w = B.w = p_w;
					*mp = B.mp = t_mp;
                       			break;

				case 'C' :
					if(p_f == B.f && p_w == B.w && p_l == B.l){ //To check whether player B got captured
                                                B.f = 0;
						B.w = 9;
						B.l = 8;
						*c_player = 'B'; 
						printf("%d %d %d \n",B.f,B.w,B.l);
						printf("Player B got captured\n");
                                        }
					
                                        if(p_f == A.f && p_w == A.w && p_l == A.l){ //To check whether player A got captured
                                                A.f = 0;
						A.w = 6;
						A.l = 12;
						*c_player = 'A';
						printf("%d %d %d \n",A.f,A.w,A.l);
						printf("Player A got captured\n");
                                        }
					
					*f = C.f = p_f;
                       			*l = C.l = p_l;
                       			*w = C.w = p_w;
					*mp = C.mp = t_mp;
                        		break;
        		}

			if(flg == 1){
                                printf("\n====================Player %c Won======================\n",player_t);
                                draw(3, 10, 25, board);
                                return 1;
                        }

		}
		
		else{
			*c_mv=0;

			switch(player_t){
				case 'A':
					*mp = A.mp - 2;
					A.mp = *mp;
					break;
				case 'B':
					*mp = B.mp - 2;
					B.mp = *mp;
					break;
				case 'C':
					*mp = C.mp - 2;
					C.mp = *mp;
					break;
			}
		}

	return 0;
}
