#include <stdio.h>
#include <ctype.h>

int main(void) {

    /* 各升の状態 */
    enum {
        none = 0,
        black = 1,
        white = 2,
    };

    /* 盤上の状態 */
    int board[10][10] = {
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, white, black, none, none, none, none},
        {none, none, none, none, black, white, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none, none, none},
    };

    /* ターン数 */
    int t;

    /* 各ターンの処理 */
    for (t = 0; 1; ++t) {

        /* 自分の石の色 */
        int oneDisk;

        /* 相手の石の色 */
        int otherDisk;

        /* 入力文字列 */
        char s[80];

        /* Y座標の入力文字 */
        char yc;

        /* X座標の入力文字 */
        char xc;

        /* Y座標値 */
        int y;

        /* X座標値 */
        int x;

        /* 返した石の数 */
        int flippedCount;

        /* その他 */
        int i;
        int j;
        int disk;

        /* 自分と相手の石の色を決定 */
        if (t % 2 == 0) {
            oneDisk = black;
            otherDisk = white;
        }
        else {
            oneDisk = white;
            otherDisk = black;
        }

        /* 盤面を出力 */
        fputs("   a b c d e f g h\n", stdout);
        for (j = 1; j <= 8; ++j) {
            fprintf(stdout, "%d ", j);
            for (i = 1; i <= 8; ++i) {
                switch(board[j][i]) {
                case none:
                    fputs("＋", stdout);
                    break;
                case black:
                    fputs("●", stdout);
                    break;
                case white:
                    fputs("○", stdout);
                    break;
                }
            }
            fputs("\n", stdout);
        }

        /* 不正な入力の場合はここに戻る */
    CONTINUE:

        /* 入力受付 */
        if (t % 2 == 0) {
            fputs("●> ", stdout);
        }
        else {
            fputs("○> ", stdout);
        }

        /* 入力 */
        fgets(s, 80, stdin);
        sscanf(s, "%c%c", &xc, &yc);

        /* 入力文字からY座標に変換 */
        switch (yc) {
        default:
            y = 0;
            break;
        case '1':
            y = 1;
            break;
        case '2':
            y = 2;
            break;
        case '3':
            y = 3;
            break;
        case '4':
            y = 4;
            break;
        case '5':
            y = 5;
            break;
        case '6':
            y = 6;
            break;
        case '7':
            y = 7;
            break;
        case '8':
            y = 8;
            break;
        }

        /* 入力文字からX座標に変換 */
        switch (tolower(xc)) {
        default:
            x = 0;
            break;
        case 'a':
            x = 1;
            break;
        case 'b':
            x = 2;
            break;
        case 'c':
            x = 3;
            break;
        case 'd':
            x = 4;
            break;
        case 'e':
            x = 5;
            break;
        case 'f':
            x = 6;
            break;
        case 'g':
            x = 7;
            break;
        case 'h':
            x = 8;
            break;
        }

        /* 盤外の座標ならエラー */
        if (!((1 <= y) && (y <= 8) && (1 <= x) && (x <= 8))) {
            fputs("無効な入力です\n", stdout);
            goto CONTINUE;
        }

        /* 座標上にすでに石があるならエラー */
        if (board[y][x] != none) {
            fputs("すでに石があります\n", stdout);
            goto CONTINUE;
        }

        /* 返した石の数を一旦0に初期化 */
        flippedCount = 0;

        /* 石を返す。いいアルゴリズム思いつかなかったからごり押し */
        for (i = 1; i <= 8; ++i) {
            disk = board[y + i][x];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y + j][x] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y + i][x + i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y + j][x + j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y][x + i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y][x + j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y - i][x + i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y - j][x + j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y - i][x];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y - j][x] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y - i][x - i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y - j][x - j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y][x - i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y][x - j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }
        for (i = 1; i <= 8; ++i) {
            disk = board[y + i][x - i];
            if (disk == oneDisk) {
                for (j = 1; j < i; ++j) {
                    board[y + j][x - j] = oneDisk;
                }
                flippedCount += i - 1;
                break;
            }
            else if (disk == none) {
                break;
            }
        }

        /* 返した石の数が0ならエラー */
        if (!(flippedCount > 0)) {
            fputs("返せる石がありません\n", stdout);
            goto CONTINUE;
        }

        /* 座標上に石を置く */
        board[y][x] = oneDisk;
    }
    return 0;
}
