#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define MAX_TAMAÑO_SUDOKU 9
#define LIMITE_1_SUBMATRIZ 2
#define LIMITE_2_SUBMATRIZ 5
#define LIMITE_3_SUBMATRIZ 8
#define ANSI_COLOR_PINK    "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    int valor;
    int fila;
    int columna;
} Dato;

void imprimirSudoku(int tableroSudoku[][MAX_TAMAÑO_SUDOKU]);
void inicializarMatriz(int tableroSudoku[][MAX_TAMAÑO_SUDOKU]);
int validarDatoEntero(int dato);
bool revisarBloque9x9(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado);
bool revisarBloque3x3(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int numColumna, int numFila, int numIngresado);
bool verificarRespuestas(int tableroSudoku[][MAX_TAMAÑO_SUDOKU], int tableroSudokuSolucion[][MAX_TAMAÑO_SUDOKU]);
int cargarSudoku(int tablero[][MAX_TAMAÑO_SUDOKU], int nivelDeDificultad, int tipo);

void inicializarMatriz(int tableroSudoku[][MAX_TAMAÑO_SUDOKU]){
    for(int i = 0; i < MAX_TAMAÑO_SUDOKU; i++){
        for(int j = 0; j < MAX_TAMAÑO_SUDOKU; j++){
            tableroSudoku[i][j] = 0;
        }
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
    if(numFila <= LIMITE_1_SUBMATRIZ && numColumna <= LIMITE_1_SUBMATRIZ){
        for(int i = 0; i <= LIMITE_1_SUBMATRIZ; i++){
            for(int j = 0; j <= LIMITE_1_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_1_SUBMATRIZ && numColumna <= LIMITE_2_SUBMATRIZ) {
        for(int i = 0; i <= LIMITE_1_SUBMATRIZ; i++){
            for(int j = LIMITE_1_SUBMATRIZ + 1; j <= LIMITE_2_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_1_SUBMATRIZ && numColumna <= LIMITE_3_SUBMATRIZ){
        for(int i = 0; i <= LIMITE_1_SUBMATRIZ; i++){
            for(int j = LIMITE_2_SUBMATRIZ + 1; j <= LIMITE_3_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_2_SUBMATRIZ && numColumna <= LIMITE_1_SUBMATRIZ){
        for(int i = LIMITE_1_SUBMATRIZ + 1; i <= LIMITE_2_SUBMATRIZ; i++){
            for(int j = 0; j <= LIMITE_1_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_2_SUBMATRIZ && numColumna <= LIMITE_2_SUBMATRIZ){
        for(int i = LIMITE_1_SUBMATRIZ + 1; i <= LIMITE_2_SUBMATRIZ; i++){
            for(int j = LIMITE_1_SUBMATRIZ + 1; j <= LIMITE_2_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_2_SUBMATRIZ && numColumna <= LIMITE_3_SUBMATRIZ){
        for(int i = LIMITE_2_SUBMATRIZ + 1; i <= LIMITE_3_SUBMATRIZ; i++){
            for(int j = 0; j <= LIMITE_1_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    }  else if(numFila <= LIMITE_3_SUBMATRIZ && numColumna <= LIMITE_1_SUBMATRIZ){
        for(int i = LIMITE_2_SUBMATRIZ + 1; i <= LIMITE_3_SUBMATRIZ; i++){
            for(int j = 0; j <= LIMITE_1_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_3_SUBMATRIZ && numColumna <= LIMITE_2_SUBMATRIZ){
        for(int i = LIMITE_2_SUBMATRIZ + 1; i <= LIMITE_3_SUBMATRIZ; i++){
            for(int j = LIMITE_1_SUBMATRIZ + 1; j <= LIMITE_2_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    } else if(numFila <= LIMITE_3_SUBMATRIZ && numColumna <= LIMITE_3_SUBMATRIZ){
        for(int i = LIMITE_2_SUBMATRIZ + 1; i <= LIMITE_3_SUBMATRIZ; i++){
            for(int j = LIMITE_2_SUBMATRIZ + 1; j <= LIMITE_3_SUBMATRIZ ;j++){
                if(tableroSudoku[i][j] == numIngresado){
                    return false;
                }
            }
        }
    }

    return true;
}

int cargarSudoku(int tablero[][MAX_TAMAÑO_SUDOKU], int nivelDeDificultad, int tipo){
    char csv[30];

    if(nivelDeDificultad == 1 && tipo == 1){
        strncpy(csv,"sudokuFacil.csv",30);
    }  else if(nivelDeDificultad == 1 && tipo == 2){
        strncpy(csv,"sudokuFacilSolucion.csv",30);
    }  else if(nivelDeDificultad == 2 && tipo == 1){
        strncpy(csv,"sudokuInter.csv",30);
    }  else if(nivelDeDificultad == 2 && tipo == 2){
        strncpy(csv,"sudokuInterSolucion.csv",30);
    }  else if(nivelDeDificultad == 3 && tipo == 1){
        strncpy(csv,"sudokuDificil.csv",30);
    }   else if(nivelDeDificultad == 3 && tipo == 2){
        strncpy(csv,"sudokuDificilSolucion.csv",30);
    }

    Dato datos[MAX_TAMAÑO_SUDOKU * MAX_TAMAÑO_SUDOKU];
    FILE * archivo = fopen(csv, "r");

    if(archivo == NULL){
        printf("Error al abrir al cargar el sudoku");
        return 1;
    }

    int numDatos = 0;
    while (fscanf(archivo, "%d,%d,%d\n", &datos[numDatos].valor, &datos[numDatos].fila, &datos[numDatos].columna) == 3) {
        numDatos++;
        if (numDatos == MAX_TAMAÑO_SUDOKU * MAX_TAMAÑO_SUDOKU) {
            break;
        }
    }

    fclose(archivo);

    for(int i = 0; i < numDatos; i++){
        tablero[datos[i].fila][datos[i].columna] = datos[i].valor;
    }
}


int validarDatoEntero(int dato){
    int datoIngresado;
    while ((datoIngresado = getchar()) != '\n' && datoIngresado != EOF) {
        if (!isdigit(datoIngresado)){
            while (getchar() != '\n');
            datoIngresado = 0;  
            break;
        }
    }
    return datoIngresado;
}

void imprimirSudoku(int tableroSudoku[][MAX_TAMAÑO_SUDOKU]){
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
}
