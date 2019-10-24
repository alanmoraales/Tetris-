#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "jugar.h"
#include "mejorespuntuaciones.h"

// definimos controles.
#define SALIR 27 // esc
#define JUGAR 32 // espacio
#define PUNTUACIONES 115 // s
#define PUNTUACIONES2 83 // S
#define CONTROLES 119 // w
#define CONTROLES2 87 // W  

/// Desde este archivo se lanza el juego.

// declaración de funciones
void imprimir_menu();
// la función controles muestra los controles del juego. 
// el usuario puede acceder a ella desde el menú principal.
void controles();

int main(int argc, char *argv[]) {
	
	char tecla; 
	
	//abrimos el fichero de puntajes. sino existe se creará uno, si existe se mantendrá.
	FILE *ficheropuntuaciones = fopen("puntuaciones.txt", "a");
	// lo cerramos.
	fclose(ficheropuntuaciones);
	// esto solo es para que, en caso de no existir un fichero, se cree uno. 
	
	do{
		
		imprimir_menu();
		tecla = getch(); // pedimos la tecla.
		
		switch(tecla){
		case JUGAR:
			system("cls");
			jugar(); // entramos al juego. 
			system("cls");
			break;
		case PUNTUACIONES: case PUNTUACIONES2:
			system("cls");
			mejores_puntuaciones();
			system("cls");
			break;
		case CONTROLES: case CONTROLES2:
			system("cls");
			controles();
			system("cls");
			break;
		}
		
	} while(tecla != SALIR);
	
	return 0;
}


void imprimir_menu(){
	
	gotoxy (5,5);  printf(" ___________    _________    ___________    _________    ____    _________   ");
	gotoxy (5,6);  printf("|___     ___|  |   ______|  |___     ___|  |   __    |  |    |  |         |  ");
	gotoxy (5,7);  printf("    |   |      |  |______       |   |      |  |  |   |  |    |   |      _|   ");
	gotoxy (5,8);  printf("    |   |      |   ______|      |   |      |  |__|  |   |    |    |    |     ");
	gotoxy (5,9);  printf("    |   |      |  |             |   |      |       |    |    |     |    |    ");
	gotoxy (5,10); printf("    |   |      |  |______       |   |      |  ||    |   |    |      |    |   ");
	gotoxy (5,11); printf("    |   |      |         |      |   |      |  | |    |  |    |   __|    |    ");
	gotoxy (5,12); printf("    |___|      |_________|      |___|      |__|  |____| |____|  |______|     ");
	
	//líneas horizontales.
	for (int i=25; i<=60; i++){
		gotoxy(i,15); printf("%c", 205);
		gotoxy(i,25); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=15; j<=25; j++){
		gotoxy(25,j); printf("%c", 186);
		gotoxy(60,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(25,15); printf("%c", 201);
	gotoxy(60,15); printf("%c", 187);
	gotoxy(25,25); printf("%c", 200);
	gotoxy(60,25); printf("%c", 188);
	
	gotoxy(31, 17); printf("     Jugar(espacio)    ");
	gotoxy(31, 19); printf("Mejores Puntuaciones(s)");
	gotoxy(31, 21); printf("      Controles(w)     ");
	gotoxy(31, 23); printf("       Salir(esc)      ");
}
void controles(){
	
	char tecla;
	
	//Tablero para mostrar controles.
	//líneas horizontales.
	for (int i=15; i<=53; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,19); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=19; j++){
		gotoxy(15,j); printf("%c", 186);
		gotoxy(53,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(15,5); printf("%c", 201);
	gotoxy(53,5); printf("%c", 187);
	gotoxy(15,19); printf("%c", 200);
	gotoxy(53,19); printf("%c", 188);
	
	// texto
	gotoxy(17,7); printf("A --------- Izquierda");
	gotoxy(17,8); printf("D --------- Derecha");
	gotoxy(17,9); printf("W --------- Caida Rápida");
	gotoxy(17,10); printf("S --------- Bajar Pieza Lentamente");
	gotoxy(17,13); printf("O --------- Rotar Pieza");
	gotoxy(17,14); printf("P --------- Guardar Pieza");
	gotoxy(17,17); printf("Esc ------- Menu de Pausa");
	
	gotoxy(16, 21); printf("Regresar(esc)");
	
	// ciclamos hasta que el usuario quiera salir.
	do {
		tecla = getch();
		delay(50);
	} while(tecla != REGRESAR);
	
	
}
