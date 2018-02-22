#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MXY 5
#define MXX 900

char str[] = "PALJETTKUNGEN";

char alpha[26][6] = {
    {30, 5, 5, 30},
    {31, 21, 21, 10},
    {14, 17, 14},
    {31, 17, 17, 14},
    {31, 21, 21},
    {31, 5, 5},
    {14, 17, 21, 13},       // G
    {31, 4, 4, 31},
    {31},
    {8, 16, 15},
    {31, 4, 10, 17},
    {31, 16, 16},           // L
    {31, 2, 4, 2, 31},
    {31, 2, 4, 8, 31},
    {14, 17, 17, 14},
    {31, 5, 5, 2},
    {14, 17, 17, 30, 16},
    {31, 5, 13, 18},        // R
    {23, 21, 29},
    {1, 31, 1},
    {15, 16, 16, 15},
    {7, 8, 16, 8, 7},
    {31, 8, 4, 8, 31},
    {17, 10, 4, 10, 17},    // X
    {1, 2, 28, 2, 1},
    {25, 21, 19, 17}
};

static int getclen(char ch) {

    int ret = 0;

    while(alpha[(ch - 'A')][ret]) ret++;

    return ret;
}

static int getlen(char *str, const int slen) {

    int ret = 0;

    for(int i = 0; i < slen; i++) ret += getclen(str[i]);

    return ret + slen - 1;
}

static int addchar(char **board, char ch, int pos) {

    char *lnptr = alpha[(ch - 'A')];

    while(*lnptr) {
        board[4][pos] = *lnptr & 16;
        board[3][pos] = *lnptr & 8;
        board[2][pos] = *lnptr & 4;
        board[1][pos] = *lnptr & 2;
        board[0][pos] = *lnptr & 1;
        pos++;
        lnptr++;
    }

    return ++pos;
}

static void fillboard(char **board, char *str, const int slen) {

    int bpos, spos;

    for(spos = 0; spos < slen; spos++) {
        bpos = addchar(board, str[spos], bpos);
    }

}

static void printboard(char **board, const int mxy, const int mxx) {

    for(int y = 0; y < mxy; y++) {
        for(int x = 0; x < mxx; x++) {
            putchar(board[y][x] ? '*' : ' ');
        }
        putchar('\n');
    }
}

static char **mkboard(const int y, const int x) {
    
    char **board = calloc(y, sizeof(char*));

    for(int i = 0; i < y; i++) board[i] = calloc(x, sizeof(char));
    
    return board;
}

static void freeboard(char **board, const int y) {

    for(int i = 0; i < y; i++) free(board[i]);
    free(board);
}

int main(void) {

    int slen = strlen(str);
    int bx = getlen(str, slen);

    char **board = mkboard(MXY, bx);

    // printf("bx: %d\n", bx);

    fillboard(board, str, slen);

    printboard(board, MXY, bx);

    freeboard(board, MXY);

    return 0;
}
