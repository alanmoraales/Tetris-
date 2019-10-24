#include <stdio.h>
#include <conio.h>

#define REGRESAR 27 // esc

/* 
	Esta parte sirve para que el jugador pueda entrar a ver las mejores puntuaciones 
	desde el menú principal del juego. 
	Se reutiliza el código de "game_over.h" que sirve para imprimir las puntuaciones.
	Pero la que te permite ingresar datos, pues esta parte del juego no debe permitirlo. 
*/
struct _mejorjugador{
	char nombre[20];
	int puntuacion;
};


void cargar_datos_puntuaciones(struct _mejorjugador jugadores[]);
void imprimir_mejores_puntuaciones(struct _mejorjugador jugadores[]);
void imprimir_tabla_puntuaciones();

void mejores_puntuaciones() {
	
	struct _mejorjugador jugadores[10] = {
		{" ", 0}, // se incializa el vector de estructuras con estos datos.
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0},
		{" ", 0}};
	// para cargar los datos de los 10 jugadores con puntuaciones más altas.
	// Declaramos un vector de estructuras tipo _jugador y la inicializamos. 
	// Este vector servirá para cargar los datos de las mejores puntuaciones.
	char tecla;
	
	system("cls");
	cargar_datos_puntuaciones(jugadores);
	imprimir_tabla_puntuaciones();
	imprimir_mejores_puntuaciones(jugadores);
	
	gotoxy(21, 23); printf("Regresar(esc)");
	// se espera a que el jugador presiones esc para regresar al menú principal.
	do {
		tecla = getch();
		delay(50);
	} while(tecla != REGRESAR);
	
}

void cargar_datos_puntuaciones(struct _mejorjugador jugadores[]){
	
	char auxpuntuacion[15]; // auxiliar para leer la puntuacion de un jugador.
	
	FILE *mejores_puntuaciones = fopen("puntuaciones.txt", "r"); // declaramos el fichero.
	// abrimos el fichero en modo lectura.
	
	// leer los datos.
	for (int i=0; i<10; i++){
		if(fgets(jugadores[i].nombre,20,mejores_puntuaciones) != NULL){
			// si hay información (un nombre) para leer, entonces leemos también la puntuación.
			jugadores[i].puntuacion = atoi(fgets(auxpuntuacion,15,mejores_puntuaciones));
			// esta información se guarda en una structura de tipo _jugador.
			// usamos el auxpuntuacion para convertir el caracter a entero.
		}
		else{
			break; // sino, entonces se ha llegado al final del fichero. Termina el ciclo.
		}
	}
	
	fclose(mejores_puntuaciones); // cerramos el fichero.
	
}

void imprimir_mejores_puntuaciones(struct _mejorjugador jugadores[]){
	
	int y=9; // la y inicial es 9;
	
	for (int i=0; i<10; i++){
		if (jugadores[i].nombre[0] != ' '){
			// si el nombre del jugador es diferente a nulo.
			gotoxy(32,y); printf("%s", jugadores[i].nombre);
			gotoxy(50,y); printf("%d", jugadores[i].puntuacion);
			// se imprime el nombre y la puntuación del jugador.
		}
		else{
			// sino, se imprimen líneas para llenar el espacio.
			gotoxy(32,y); printf("-------------------------");
		}
		y++; // aumentamos la y, para bajar la línea.
	}
}


void imprimir_tabla_puntuaciones(){
	
	//Tablero para mejores puntuaciones.
	//líneas horizontales.
	for (int i=20; i<=70; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,21); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=21; j++){
		gotoxy(20,j); printf("%c", 186);
		gotoxy(70,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(20,5); printf("%c", 201);
	gotoxy(70,5); printf("%c", 187);
	gotoxy(20,21); printf("%c", 200);
	gotoxy(70,21); printf("%c", 188);
	
	// Texto
	gotoxy(25,7); printf("---------- Mejores Puntaciones ----------");
	gotoxy(25,9); printf("   1."); //aquí a el listado de las mejores puntuaciones.
	gotoxy(25,10); printf("   2.");
	gotoxy(25,11); printf("   3.");
	gotoxy(25,12); printf("   4.");
	gotoxy(25,13); printf("   5.");
	gotoxy(25,14); printf("   6.");
	gotoxy(25,15); printf("   7.");
	gotoxy(25,16); printf("   8.");
	gotoxy(25,17); printf("   9.");
	gotoxy(25,18); printf("   10."); // se muestran siempre las 10 más altas. 
	
}

