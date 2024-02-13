#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define MAX_TAMAÑO_SUDOKU 9
#define ANSI_COLOR_PINK    "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

typedef struct {
    int valor;
    int fila;
    int columna;
} Dato;

int tableroSudoku[MAX_TAMAÑO_SUDOKU][MAX_TAMAÑO_SUDOKU];
int tableroSudokuSolucion[MAX_TAMAÑO_SUDOKU][MAX_TAMAÑO_SUDOKU];
int intentos = 3;

void imprimirSudoku(int tipo);
void inicializarMatriz(void);
void menu(void);
void ubicarDatoEnTablero(int fila, int columna, int numero);
void seleccionarArchivo(int nivelDeDificultad, int tipoDeArchivo);
int jugar(void); 
bool ingresarDatos(void);
bool validarDatoEntero(int dato);
bool revisarBloque9x9(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado);
bool revisarBloque3x3(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado);
bool verificarRespuestas(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int tableroSudokuSolucion[][MAX_TAMAÑO_SUDOKU]);
int cargarSudoku(char *csv, int tipo);

void inicializarMatriz(void){
    for(int i = 0; i < MAX_TAMAÑO_SUDOKU; i++){
        for(int j = 0; j < MAX_TAMAÑO_SUDOKU; j++){
            tableroSudoku[i][j] = 0;
        }
    }
}

void menu(void){
    int nivel;
    printf(ANSI_COLOR_CYAN"\n\t\t-_-_-_-_-_-_-_-_-_-_-_-_-SUDOKU LOKO-_-_-_-_-_-_-_-_-_-_-_-_-\n\n"ANSI_COLOR_RESET);
    do{
        printf(ANSI_COLOR_BLUE"\n\n\t\t\t\tSeleccione el nivel de dificultad\n\n\t\t\t1. Facil\n\t\t\t2. Intermedio\n\t\t\t3. Dificil\n\t\t\t\t\t>  "ANSI_COLOR_RESET);
        scanf("%d",&nivel);
        validarDatoEntero(nivel);
    } while(nivel < 1 || nivel > 3);

    seleccionarArchivo(nivel, 1);
    seleccionarArchivo(nivel, 2);
}

void seleccionarArchivo(int nivelDeDificultad, int tipoDeArchivo){
    char csv[30];
    if(nivelDeDificultad == 1 && tipoDeArchivo == 1)
        strncpy(csv,"sudokuFacil.csv",30);
    else if(nivelDeDificultad == 1 && tipoDeArchivo == 2)
        strncpy(csv,"sudokuFacilSolucion.csv",30);
    else if(nivelDeDificultad == 2 && tipoDeArchivo == 1)
        strncpy(csv,"sudokuInter.csv",30);
    else if(nivelDeDificultad == 2 && tipoDeArchivo == 2)
        strncpy(csv,"sudokuInterSolucion.csv",30);
    else if(nivelDeDificultad == 3 && tipoDeArchivo == 1)
        strncpy(csv,"sudokuDificil.csv",30);
    else
        strncpy(csv,"sudokuDificilSolucion.csv",30);

    cargarSudoku(csv,tipoDeArchivo);
}

int cargarSudoku(char *csv, int tipo){
    Dato datos[MAX_TAMAÑO_SUDOKU * MAX_TAMAÑO_SUDOKU];
    FILE * archivo = fopen(csv, "r");
    
    if(archivo == NULL){
        printf("\t\t\t\tError al cargar el sudoku");
        return 1;
    }   

    int numDatos = 0;
    while (fscanf(archivo, "%d,%d,%d\n", &datos[numDatos].valor, &datos[numDatos].fila, &datos[numDatos].columna) == 3) {
        numDatos++;
        if (numDatos == MAX_TAMAÑO_SUDOKU * MAX_TAMAÑO_SUDOKU)
            break;
    }
    fclose(archivo);

    if(tipo == 1){
        for(int i = 0; i < numDatos; i++){
        tableroSudoku[datos[i].fila][datos[i].columna] = datos[i].valor;
        }
    } else {
        for(int i = 0; i < numDatos; i++){
        tableroSudokuSolucion[datos[i].fila][datos[i].columna] = datos[i].valor;
        }
    }
    return 0;
}

int jugar(void){
    while(intentos != 0)
    {
        imprimirSudoku(1);
        ingresarDatos();
        if(verificarRespuestas(tableroSudoku,tableroSudokuSolucion)){
            printf(ANSI_COLOR_GREEN"\t\t\t\tGANASTEEEEEEEE :)\n"ANSI_COLOR_RESET);
            imprimirSudoku(2);
            return 0;
        }     
        else
            continue;
    }
    printf(ANSI_COLOR_RED"\t\t\t\t\tGAME OVER\n\t\t\t\t\tSOLUCION: \n\n\n"ANSI_COLOR_RESET);
    imprimirSudoku(2);
    return 1;
}

bool ingresarDatos(void){
    int fila, columna, numero;

    printf(ANSI_COLOR_CYAN"\n\t\t\tIngrese el numero de fila (1-9): "ANSI_COLOR_RESET);
    scanf("%d", &fila);
    if(!validarDatoEntero(fila) || fila < 1 || fila > 9){
        printf(ANSI_COLOR_YELLOW"\n\t\t\t\tNumero de fila no valido\n"ANSI_COLOR_RESET);
        return false;
    }

    printf(ANSI_COLOR_CYAN"\n\t\t\tIngrese el numero de columna (1-9): "ANSI_COLOR_RESET);
    scanf("%d", &columna);
    if(!validarDatoEntero(columna) || columna < 1 || columna > 9){
        printf(ANSI_COLOR_YELLOW"\n\t\t\t\tNumero de columna no valido\n"ANSI_COLOR_RESET);
        return false;
    }
        
    printf(ANSI_COLOR_PINK"\n\t\t\tIngrese el numero para colocar en la celda (%d, %d): "ANSI_COLOR_RESET, fila, columna);
    scanf("%d", &numero);
    if(!validarDatoEntero(numero) || numero < 1 || numero > 9){
        printf(ANSI_COLOR_YELLOW"\n\t\t\t\tValor fuera de rango\n"ANSI_COLOR_RESET);
        return false;
    }
        
    ubicarDatoEnTablero(fila - 1,columna - 1,numero);
    return true;
}

void ubicarDatoEnTablero(int fila, int columna, int numero){
    if(tableroSudoku[fila][columna] != 0)
        printf(ANSI_COLOR_YELLOW"\n\t\t\t\t\tEntrada no admisible\n\n"ANSI_COLOR_YELLOW);
    else if(revisarBloque3x3(tableroSudoku,columna,fila,numero)){
        if(revisarBloque9x9(tableroSudoku,columna,fila,numero) && tableroSudokuSolucion[fila][columna] == numero){
            tableroSudoku[fila][columna] = numero;
        } else {
            intentos--;
            printf(ANSI_COLOR_RED"\n\t\tEste numero no puede ser ubicado. Te restan %d intentos\n"ANSI_COLOR_RESET,intentos);
        }          
    }
    else{
        intentos--;
        printf(ANSI_COLOR_RED"\n\t\t\t\tEste numero no puede ser ubicado. Te restan %d intentos\n"ANSI_COLOR_RESET,intentos);
    }
}

bool verificarRespuestas(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int tableroSudokuSolucion[][MAX_TAMAÑO_SUDOKU]){
    for(int i = 0; i < MAX_TAMAÑO_SUDOKU; i++){
        for(int j = 0; j < MAX_TAMAÑO_SUDOKU; j++){
            if(tableroSudoku[i][j] != tableroSudokuSolucion[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool revisarBloque9x9(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado){
    for(int i = 0; i < MAX_TAMAÑO_SUDOKU; ++i){
        if(tableroSudoku[i][numColumna] == numIngresado || tableroSudoku[numFila][i] == numIngresado){
            return false;
        }
    }
    return true;
}

bool revisarBloque3x3(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado){
    int filaInicio = (numFila / 3) * 3;
    int columnaInicio = (numColumna / 3) * 3;

    for (int i = filaInicio; i < filaInicio + 3; ++i) {
        for (int j = columnaInicio; j < columnaInicio + 3; ++j) {
            if (tableroSudoku[i][j] == numIngresado) {
                return false;
            }
        }
    }
    return true;
}

bool validarDatoEntero(int dato){
    while ((dato = getchar()) != '\n' && dato != EOF) {
        if (!isdigit(dato)){
            while (getchar() != '\n');
            return false;
        }
    }
    return true;
}

void imprimirSudoku(int tipo){ 
    if(tipo == 1){
        printf("\n\n\n");
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){     
                if(j == 0){
                    printf(ANSI_COLOR_PINK"\t\t\t\t   | "ANSI_COLOR_RESET);
                } 
                if(tableroSudoku[i][j] == 0){
                    printf("  ");            
                } else{
                    printf("%d ", tableroSudoku[i][j]);
                }  
                if(j == 2 || j==5 || j == 8){
                    printf(ANSI_COLOR_PINK"|"ANSI_COLOR_RESET);
                } 
            }
            printf("\n");
            if(i == 2 || i==5){
                printf(ANSI_COLOR_PINK"\t\t\t\t   -----------------------\n"ANSI_COLOR_RESET);
            } 
        }
        printf("\n\n\n");
    } else {
        printf("\n\n\n");
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){     
                if(j == 0){
                    printf(ANSI_COLOR_PINK"\t\t\t\t   | "ANSI_COLOR_RESET);
                } 
                if(tableroSudokuSolucion[i][j] == 0){
                    printf("  ");            
                } else{
                    printf("%d ", tableroSudokuSolucion[i][j]);
                }  
                if(j == 2 || j==5 || j == 8){
                    printf(ANSI_COLOR_PINK"|"ANSI_COLOR_RESET);
                } 
            }
            printf("\n");
            if(i == 2 || i==5){
                printf(ANSI_COLOR_PINK"\t\t\t\t   -----------------------\n"ANSI_COLOR_RESET);
            } 
        }
        printf("\n\n\n");
    }
    
}
