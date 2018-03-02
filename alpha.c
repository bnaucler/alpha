#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MXY 5
#define MXX 900

#define TXX 18 // X axis of time display matrix

char msg[] = "ABCDE FGHIJ KLMNO PQRST UVWXYZ";

char num[10][4] = {
    {31, 17, 31},
    {18, 31, 16},
    {29, 21, 21},
    {21, 21, 31},
    {7, 4, 31},
    {23, 21, 29},
    {31, 21, 29},
    {1, 1, 31},
    {31, 21, 31},
    {7, 5, 31},
};

char alpha[26][6] = {
    {30, 5, 5, 30},
    {31, 21, 21, 10},
    {14, 17, 17},
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

// Voodoo
static int getlen(char *str) {

    int ret = 0;

    do ret += 1 + (*str == ' ' ? 3 : strlen(alpha[(*str - 'A')]));
    while(*++str);

    return --ret;
}

static void addsym(char **board, const int mxy, int *pos, char *ptr) {

    do {
        for(int y = 0; y < mxy; y++) board[y][*pos] = *ptr & 1 << y;
        (*pos)++;
    } while(*++ptr);
}

static void addchar(char **board, char ch, int *pos, const int mxy) {

    if(ch == ' ') *pos += 3;
    else  {
        char *ptr = alpha[(ch - 'A')];
        addsym(board, mxy, pos, ptr);
    }

    (*pos)++;
}

static void fillboard(char **board, char *str, const int y) {

    int pos = 0;

    while(*str) addchar(board, *str++, &pos, y);
}

static void tpair(char **board, const int mxy, int *pos, int s) {

    char *ptr = num[(s / 10)];
    addsym(board, mxy, pos, ptr);
    (*pos)++;

    ptr = num[(s % 10)];
    addsym(board, mxy, pos, ptr);
}

static void cmin(char **board, const int mxy, int *pos, int s) {

    tpair(board, mxy, pos, s / 60);
    (*pos)++;

    for(int y = 0; y < mxy; y++) board[y][*pos] = 10 & 1 << y; // 10 for colon
    *pos += 2;

    tpair(board, mxy, pos, s % 60);
}

static void ftboard(char **board, const int mxy, const int s) {

    int pos = 0;

    if(!(s / 60)) {
        pos += 6;
        tpair(board, mxy, &pos, s % 60);

    } else {
        cmin(board, mxy, &pos, s);
    }
}

static void printboard(char **board, const int mxy, const int mxx) {

    for(int y = 0; y < mxy; y++) {
        for(int x = 0; x < mxx; x++) {
            putchar(board[y][x] ? '#' : ' ');
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

    int bx = getlen(msg);

    // printf("len: %d\n", bx);

    char **board = mkboard(MXY, bx);
    char **tboard = mkboard(MXY, 18);

    // fillboard(board, msg, MXY);
    ftboard(tboard, MXY, 214);
    // printboard(board, MXY, bx);
    printboard(tboard, MXY, 18);

    freeboard(board, MXY);
    freeboard(tboard, MXY);

    return 0;
}
