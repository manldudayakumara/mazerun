#ifndef BOARD_H
#define BOARD_H

struct position{ //To track the player index
        int f;
        int w;
        int l;
        int mp;
        int b_e;
};
extern struct position A;
extern struct position B;
extern struct position C;

int g_board(char player_t, int *f, int *w, int *l, int *c_mv, char *c_player, int round, int call, int *bawana_e, int *mp);
void draw(int x, int y, int z, int board[x][y][z]);

#endif
