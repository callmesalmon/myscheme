/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2025 Elis Staaf                                             *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>

/* Variables */
struct termios term, old_term;
bool term_textlock = false;

/* Cursor type */
typedef struct {
    int x;
    int y;
} cursor;

/* Cursor defs */
cursor *srstack;
int srstackp;

/* Clear terminal. */
void clear() {
    fprintf(stdout, "\e[H\e[2J\e[3J\n");
    fflush(stdout);
}

/* Clear terminal without moving cursor. */
void blank() {
    fprintf(stdout, "\e[2J\e[3J\n");
    fflush(stdout);
}

/* Get size of terminal. */
struct winsize termsz() {
    struct winsize tmp;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &tmp);
    return tmp;
}

/* Get amount of characters in 
 * stdin, returns integer. */
int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;
    if (!initialized) {
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytes;
    ioctl(STDIN, FIONREAD, &bytes);
    return bytes;
}

cursor getCurPos() {
    fflush(stdout);
    char buf[16];
    int ret, i;
    i = kbhit();
    while (i > 0) {getchar(); i--;}
    if (!term_textlock) {
        tcgetattr(0, &term);
        tcgetattr(0, &old_term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &term);
    }
    fprintf(stdout, "\e[6n\n");
    fflush(stdout);
    ret = read(1, &buf, 16);
	cursor cur = {0, 0};
    if (!ret) {
        if (!term_textlock) tcsetattr(0, TCSANOW, &old_term);
        return cur;
    }
	if (!term_textlock) tcsetattr(0, TCSANOW, &old_term);
    sscanf(buf, "\e[%d;%dR", &cur.y, &cur.x);
    return cur;
}

void setCurPos(cursor cur) {
    printf("\e[%d;%dH", cur.y, cur.x);
    fflush(stdout);
}

void saveCurPos() {
    srstackp++;
    srstack = (cursor*)realloc(srstack, srstackp * sizeof(srstack));
    srstack[srstackp - 1] = getCurPos();
}

void restoreCurPos() {
    if (srstackp < 0) return;
    srstackp--;
    setCurPos(srstack[srstackp]);
    srstack = (cursor*)realloc(srstack, srstackp * sizeof(srstack));
}

/* Goes to position, writes
 * character there, and 
 * goes back. */
void putCharAt(int x, int y, char ch) {
    printf("\e[s\e[%d;%dH%c\e[u", y, x, ch);
    fflush(stdout);
}

/* Same as putCharAt, but write
 * an entire string to pos. */
void putStrAt(int x, int y, char* str) {
    printf("\e[s\e[%d;%dH%s\e[u", y, x, str);
    fflush(stdout);
}

/* Text effects */
#define reset fprintf(stdout, "\e[0m")

#define truecolorfg(color) \
    printf("\e[38;2;%u;%u;%um", (uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)color)
#define truecolorbg(color) \
    printf("\e[48;2;%u;%u;%um", (uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)color)

#define bytecolorfg(color) printf("\e[38;5;%um", (uint8_t)color)
#define bytecolorbg(color) printf("\e[48;5;%um", (uint8_t)color)

#define bold fputs("\e[1m", stdout)
#define italic fputs("\e[3m", stdout)
#define underline fputs("\e[4m", stdout)
#define doubleunderline fputs("\e[21m", stdout)
#define squiggleunderline fputs("\e[4:3m", stdout)
#define strikethrough fputs("\e[9m", stdout)
#define overline fputs("\e[53m", stdout)
#define dim fputs("\e[2m", stdout)
#define blink fputs("\e[5m", stdout)
#define hide fputs("\e[8m", stdout)
#define reverse fputs("\e[7m", stdout)

void lockterm() {
    if (!term_textlock) {
        tcgetattr(0, &term);
        tcgetattr(0, &old_term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &term);
        term_textlock = true;
    }
}

void unlockterm() {
    if (term_textlock) {
        tcsetattr(0, TCSANOW, &old_term);
        term_textlock = false;
    }
}

/* Are you in a terminal? */
#define intty !system("tty -s 1> /dev/null 2> /dev/null")