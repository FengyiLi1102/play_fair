//
// Created by CarlY on 2021/12/22.
//

#include "playfair.h"
using namespace std;


void prepare(const char* input, char* output) {
    unsigned int index = 0;
    unsigned int length = strlen(input);
    unsigned int realLength = 0;

    while (input[index] != '\0' && index < length) {
        if ((input[index] >= 'a' && input[index] <= 'z')) {
            output[realLength] = toupper(input[index]);
            realLength++;
        } else if ((input[index] >= '0' && input[index] <= '9') || (input[index] >= 'A' && input[index] <= 'Z')){
            output[realLength] = input[index];
            realLength++;
        }

        index++;
    }

    if (realLength % 2 != 0) {
        output[realLength] = 'X';
    }

    output[++realLength] = '\0';
}


void grid(const char *codeWord, char square[][MAX_COL]) {
    unsigned int count = 0;
    int inputLength = 0;
    int a = 0, b = 0;

    while (inputLength < strlen(codeWord)) {
        if (!check_is_in(square, codeWord[inputLength], count)) {
            square[a][b] = codeWord[inputLength];
            b = (b + 1) % MAX_COL;
            if (b == 0)
                a += 1;
            count++;
        }
        inputLength++;
    }

    unsigned int tempRow = strlen(codeWord) / MAX_COL;
    unsigned int row = (tempRow >= 0 ? tempRow : 0);

    for (auto col = count % MAX_COL; col < MAX_COL; col++) {
        char filledChar = 'A';

        for (; filledChar <= 'Z'; filledChar++) {
            if (!check_is_in(square, filledChar, count)) {
                square[row][col] = filledChar;
                count++;
                break;
            }
        }
    }

    for (row = row + 1; row < MAX_COL; row++) {
        for (auto col = 0; col < MAX_COL; col++) {
            bool flag = false;
            char filledChar = 'A';

            for (; filledChar <= 'Z'; filledChar++) {
                if (!check_is_in(square, filledChar, count)) {
                    square[row][col] = filledChar;
                    count++;
                    flag = true;
                    break;
                }
            }

            if (flag)
                continue;

            filledChar = '0';
            for (; filledChar <= '9'; filledChar++) {
                if (!check_is_in(square, filledChar, count)) {
                    square[row][col] = filledChar;
                    count++;
                    break;
                }
            }
        }
    }
}


bool check_is_in(char square[][MAX_COL], char checkedChar, const int &count) {
    int thisCount = 0;

    for (auto i = 0; i < MAX_COL; i++) {
        for (auto j = 0; j < MAX_COL; j++) {
            if (thisCount == count)
                return false;

            if (square[i][j] == checkedChar)
                return true;

            thisCount++;
        }
    }

    return false;
}


void bigram(char square[][MAX_COL], char inchar1, char inchar2, char &outchar1, char &outchar2) {
    int pos1, pos2;

    givePositions(square, inchar1, inchar2, pos1, pos2);

    int row1 = pos1 / MAX_COL, row2 = pos2 / MAX_COL;
    row1 = (pos1 % MAX_COL == 0 ? row1 - 1 : row1);
    row2 = (pos2 % MAX_COL == 0 ? row2 - 1: row2);

    int col1 = pos1 % MAX_COL, col2 = pos2 % MAX_COL;
    col1 = (col1 == 0 ? MAX_COL - 1 : col1 - 1);
    col2 = (col2 == 0 ? MAX_COL - 1 : col2 - 1);

    outchar1 = square[row1][col2];
    outchar2 = square[row2][col1];
}


void givePositions(char square[][MAX_COL], char inchar1, char inchar2, int &count1, int &count2) {
    int count = 0, flag = 0;

    for (auto i = 0; i < MAX_COL; i++) {
        for (auto j = 0; j < MAX_COL; j++) {
            count++;

            if (flag == 2)
                return;

            if (square[i][j] == inchar1) {
                count1 = count;
                flag++;
            }

            if (square[i][j] == inchar2) {
                count2 = count;
                flag++;
            }
        }
    }
}


void encode(char square[][MAX_COL], const char* prepared, char* encoded) {
    for (auto i = 0; i <= strlen(prepared) - 2; i += 2) {
        char c1 = prepared[i];
        char c2 = prepared[i+1];

        bigram(square, c1, c2, encoded[i], encoded[i+1]);
    }

    encoded[strlen(prepared)] = '\0';
}