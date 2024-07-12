#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROWS 10
#define COLS 20

void initBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

void printBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(board[i][j] ? "O" : ".");
        }
        printf("\n");
    }
}

int countNeighbors(int board[ROWS][COLS], int row, int col) {
    int neighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                neighbors += board[newRow][newCol];
            }
        }
    }
    return neighbors;
}

void nextGen(int board[ROWS][COLS], int newBoard[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j] == 1) {
                // Célula morre devido à subpopulação ou superpopulação
                if (neighbors < 2 || neighbors > 3) {
                    newBoard[i][j] = 0;
                }
                else {
                    newBoard[i][j] = 1; // Célula sobrevive para a próxima geração
                }
            }
            else {
                // Célula se torna viva devido à reprodução
                if (neighbors == 3) {
                    newBoard[i][j] = 1;
                }
                else {
                    newBoard[i][j] = 0;
                }
            }
        }
    }
}

void copyBoard(int dest[ROWS][COLS], int src[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void delay(int seconds) {
    int ms = 1000 * seconds; // Convertendo o tempo para milissegundos
    clock_t start_time = clock(); // Armazenando o tempo inicial
    // Loop até que o tempo requerido seja atingido
    while (clock() < start_time + ms);
}

int main() {
    int board[ROWS][COLS];
    int newBoard[ROWS][COLS];

    initBoard(board);

    while (1) {
        system("cls"); // use "clear" em sistemas Unix
        printBoard(board);
        nextGen(board, newBoard);
        copyBoard(board, newBoard);
        delay(2); // Pausa de 2 segundos
    }

    return 0;
}