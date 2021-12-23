//
// Created by CarlY on 2021/12/22.
//

#ifndef PLAY_FAIR_PLAYFAIR_H
#define PLAY_FAIR_PLAYFAIR_H

#include <string>
#include <cstring>
#include <iostream>

const unsigned int MAX_COL = 6;

void prepare(const char* input, char* output);

void grid(const char *codeWord, char square[][MAX_COL]);

bool check_is_in(char square[][MAX_COL], char checkedChar, const int &count);

void bigram(char square[][MAX_COL], char inchar1, char inchar2, char &outchar1, char &outchar2);

void givePositions(char square[][MAX_COL], char inchar1, char inchar2, int &count1, int &count2);

void encode(char square[][MAX_COL], const char* prepared, char* encoded);

#endif //PLAY_FAIR_PLAYFAIR_H
