#include <stdio.h>
#include <windows.h>
#include <time.h>

// función para manejo de coordenadas.
void gotoxy(int x, int y){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

// función para manejo de tiempo.
void delay(int number_of_seconds){ 
	// Converting time into milli_seconds 
	//int milli_seconds = 1000 * number_of_seconds; 
	
	// Stroing start time 
	clock_t start_time = clock(); 
	
	// looping till required time is not acheived 
	while (clock() < start_time + number_of_seconds); 
} 

// función para imprimir un cuadro en unas coordenadas dadas.
void cuadro(int x, int y){
	gotoxy(x,y); printf("%c", 219);
	gotoxy(x+1,y); printf("%c", 219);
}

/// control de matriz. llenado y vaciado.
void poner_unos(int M[20][20], int x, int y){
	
	M[y][x] = 1;
	M[y][x+1] = 1; 
}

void poner_ceros(int M[20][20], int x, int y){
	
	M[y][x] = 0;
	M[y][x+1] = 0; 
}

// para llenar la matriz de coordenadas.
void poner_coordenadas(int M[3][4], int x, int y, int c){
	
	M[0][c] = x;
	M[1][c] = x+1; 
	M[2][c] = y; 
	
}
///números aleatorios.
int random_x(){
	
	int x;
	
	srand(time(NULL));
	x = 5 + (rand() % 12);
	
	if ((x%2)!= 0){
		return x-1;
	}
	else{
		return x;
	}
}

int generar_pieza(){
	
	srand(time(NULL));
	return 1 + (rand() % 14);
}

int generar_pieza_siguiente(){
	
	srand(time(NULL));
	return 1 + (rand() % 14);;
}

