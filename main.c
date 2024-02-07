#include "sudoku.h"
#include<stdio.h>
#include<stdbool.h>
#include<windows.h>

#define MAX_TAMAÑO_SUDOKU 9
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

int main(void)
{
    int tableroSudoku[MAX_TAMAÑO_SUDOKU][MAX_TAMAÑO_SUDOKU];
    int tableroSudokuSolucion[MAX_TAMAÑO_SUDOKU][MAX_TAMAÑO_SUDOKU];
    int nivel;

    inicializarMatriz(tableroSudoku);

    
    printf(ANSI_COLOR_CYAN"\n\t\t-_-_-_-_-_-_-_-_-_-_-_-_-SUDOKU LOKO-_-_-_-_-_-_-_-_-_-_-_-_-\n\n"ANSI_COLOR_RESET);
    do{
        printf(ANSI_COLOR_BLUE"\n\n\t\t\t\tSelecciones el nivel de dificultad\n"ANSI_COLOR_RESET);
        printf(ANSI_COLOR_BLUE"\n\t\t\t1. Facil\n\t\t\t2. Intermedio\n\t\t\t3. Dificil\n\t\t\t\t\t>  "ANSI_COLOR_RESET);
        scanf("%d",&nivel);
        validarDatoEntero(nivel);
    } while(nivel < 1 || nivel > 3);

    cargarSudoku(tableroSudoku, nivel, 1);
    cargarSudoku(tableroSudokuSolucion, nivel, 2);

    bool seguirJugando = true;
    int intentos = 3;
    imprimirSudoku(tableroSudoku);
    while(seguirJugando){
        int numFila = 0;
        int numIngresado = 0;
        int numColumna = 0;

        if(verificarRespuestas(tableroSudoku,tableroSudokuSolucion)){
            printf(ANSI_COLOR_GREEN"\t\t\t\t\tGANASTEEEEEEEE :)\n"ANSI_COLOR_RESET);
            seguirJugando = false;
        } else if(intentos == 0){
            printf(ANSI_COLOR_RED"\t\t\t\t\tGAME OVER\n"ANSI_COLOR_RESET);
            printf(ANSI_COLOR_BLUE"\t\t\t\t\tSOLUCION: \n\n\n"ANSI_COLOR_RESET);
            imprimirSudoku(tableroSudokuSolucion);
            seguirJugando = false;
        } else {
            do{
                printf(ANSI_COLOR_CYAN"\t\t\tNumero a ingresar> "ANSI_COLOR_RESET);
                scanf("%d",&numIngresado);
                validarDatoEntero(numIngresado);
            }while(numIngresado < 1 || numIngresado > 9);

            do{
                printf(ANSI_COLOR_CYAN"\n\t\t\tFila> "ANSI_COLOR_CYAN);
                scanf("%d",&numFila);
                validarDatoEntero(numFila);
            }while(numFila < 0 || numFila > 9);

            do{
                printf(ANSI_COLOR_CYAN"\n\t\t\tColumna> "ANSI_COLOR_CYAN);
                scanf("%d",&numColumna);
                validarDatoEntero(numColumna);
            }while(numFila < 0 || numFila > 9);


            if(tableroSudoku[numFila][numColumna] != 0){
                printf(ANSI_COLOR_YELLOW"\n\t\t\t\t\tEntrada no admisible\n\n"ANSI_COLOR_YELLOW);
                continue;
            } else if(revisarBloque3x3(tableroSudoku,numColumna,numFila,numIngresado)){
                if(revisarBloque9x9(tableroSudoku,numColumna,numFila,numIngresado) && tableroSudokuSolucion[numFila][numColumna] == numIngresado){
                    tableroSudoku[numFila][numColumna] = numIngresado;
                    imprimirSudoku(tableroSudoku);
                } else {
                    intentos--;
                    printf(ANSI_COLOR_RED"\n\t\t\t\tPosicion incorrecta\n\t\t\t\tTe restan %d intentos\n\n"ANSI_COLOR_RED, intentos); 
                }     
            } else {
                printf(ANSI_COLOR_YELLOW"\n\t\t\t\tEste numero ya esta presente en el bloque\n"ANSI_COLOR_RESET);
                continue;
            }

        }

    }
    
    return 0;
}

