#include <stdio.h>
#include <ctype.h>

int main(void) {

    /* �e���̏�� */
    enum {
        none = 0,
        black = 1,
        white = 2,
    };

    /* �Տ�̏�� */
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

    /* �^�[���� */
    int t;

    /* �e�^�[���̏��� */
    for (t = 0; 1; ++t) {

        /* �����̐΂̐F */
        int oneDisk;

        /* ����̐΂̐F */
        int otherDisk;

        /* ���͕����� */
        char s[80];

        /* Y���W�̓��͕��� */
        char yc;

        /* X���W�̓��͕��� */
        char xc;

        /* Y���W�l */
        int y;

        /* X���W�l */
        int x;

        /* �Ԃ����΂̐� */
        int flippedCount;

        /* ���̑� */
        int i;
        int j;
        int disk;

        /* �����Ƒ���̐΂̐F������ */
        if (t % 2 == 0) {
            oneDisk = black;
            otherDisk = white;
        }
        else {
            oneDisk = white;
            otherDisk = black;
        }

        /* �Ֆʂ��o�� */
        fputs("   a b c d e f g h\n", stdout);
        for (j = 1; j <= 8; ++j) {
            fprintf(stdout, "%d ", j);
            for (i = 1; i <= 8; ++i) {
                switch(board[j][i]) {
                case none:
                    fputs("�{", stdout);
                    break;
                case black:
                    fputs("��", stdout);
                    break;
                case white:
                    fputs("��", stdout);
                    break;
                }
            }
            fputs("\n", stdout);
        }

        /* �s���ȓ��͂̏ꍇ�͂����ɖ߂� */
    CONTINUE:

        /* ���͎�t */
        if (t % 2 == 0) {
            fputs("��> ", stdout);
        }
        else {
            fputs("��> ", stdout);
        }

        /* ���� */
        fgets(s, 80, stdin);
        sscanf(s, "%c%c", &xc, &yc);

        /* ���͕�������Y���W�ɕϊ� */
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

        /* ���͕�������X���W�ɕϊ� */
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

        /* �ՊO�̍��W�Ȃ�G���[ */
        if (!((1 <= y) && (y <= 8) && (1 <= x) && (x <= 8))) {
            fputs("�����ȓ��͂ł�\n", stdout);
            goto CONTINUE;
        }

        /* ���W��ɂ��łɐ΂�����Ȃ�G���[ */
        if (board[y][x] != none) {
            fputs("���łɐ΂�����܂�\n", stdout);
            goto CONTINUE;
        }

        /* �Ԃ����΂̐�����U0�ɏ����� */
        flippedCount = 0;

        /* �΂�Ԃ��B�����A���S���Y���v�����Ȃ��������炲�艟�� */
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

        /* �Ԃ����΂̐���0�Ȃ�G���[ */
        if (!(flippedCount > 0)) {
            fputs("�Ԃ���΂�����܂���\n", stdout);
            goto CONTINUE;
        }

        /* ���W��ɐ΂�u�� */
        board[y][x] = oneDisk;
    }
    return 0;
}
