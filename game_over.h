#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>   
// Librería local con funciones creadas de forma específica para el juego.
#include "tetris.h"  
                   

// structura con datos del jugador. 
struct _jugador {
	char nombre[20];
	// se declara como una cadena de 20 caracteres, pero el usuario final solo será capaz de 
	// introducir un nombre de hasta 15 caracteres.
	int puntuacion;
};

void animacion();
void imprimir_tabla(struct _jugador *pjugador);
void pedir_nombre(struct _jugador puntuaciones[], struct _jugador *pjugador);
void cargar_datos(struct _jugador puntuaciones[]);
void imprimir_puntuaciones(struct _jugador puntuaciones[]);
void actualizar_datos(struct _jugador puntuaciones[], struct _jugador *pjugador);
void actualizar_fichero(struct _jugador puntuaciones[], struct _jugador *pjugador);

void game_over(int puntuacion) {
	
	struct _jugador jugador, *pjugador = &jugador; 
	// Declaramos dos variables de tipo _jugador: jugador, y un apuntador que apunta a jugador.
	struct _jugador puntuaciones[10] = {
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
	
	jugador.puntuacion = puntuacion; // pasamos la puntuacion del jugador a la estructura.. 
	
	system("cls");
	animacion();
	cargar_datos(puntuaciones);
	imprimir_tabla(pjugador);
	imprimir_puntuaciones(puntuaciones);
	pedir_nombre(puntuaciones, pjugador);
	actualizar_datos(puntuaciones, pjugador);
	actualizar_fichero(puntuaciones, pjugador);
	
	// para probar actualizar_datos... ESTA PARTE NO SE AGREGA AL TRABAJO FINAL.
	/*system("cls");
	imprimir_tabla(pjugador);
	//imprimir_estructuras(puntuaciones);
	imprimir_puntuaciones(puntuaciones);
	system("pause");
	*/
}

void actualizar_fichero(struct _jugador puntuaciones[], struct _jugador *pjugador){
	
	FILE *mejores_puntuaciones = fopen("puntuaciones.txt", "w"); // abrimos el fichero para escribir.
	
	for (int i=0; i<10; i++){
		if (puntuaciones[i].nombre[0] != ' '){
			// si el nombre es diferente de " " ...
			if (strcmp(puntuaciones[i].nombre, pjugador->nombre) == 0){
				// comparamos cadenas. si los nombres con iguales.
				fprintf(mejores_puntuaciones, "%s\n", puntuaciones[i].nombre); // escribimos el nombre con salto de línea.
			}
			else {
				fprintf(mejores_puntuaciones, "%s", puntuaciones[i].nombre); //escribimos el nombre, sin salto de línea.
				// porque el nombre que ya estaba en el fichero contiene el cambio de línea. 
			}
			fprintf(mejores_puntuaciones, "%d\n", puntuaciones[i].puntuacion); // escribimos la puntuacion.
		}
		else{
			break; // sino, entonces no hay más datos y se rompe el ciclo. 
		}
	}
	
	fclose(mejores_puntuaciones); // cerramos el fichero.
}

void actualizar_datos(struct _jugador puntuaciones[], struct _jugador *pjugador){
	
	int auxintercambiopuntuacion1, auxintercambiopuntuacion2;
	char auxintercambionombre1[20], auxintercambionombre2[20];
	// declaramos auxiliares para intercambio.
	
	for (int i=0; i<10; i++){
		if(pjugador->puntuacion >= puntuaciones[i].puntuacion){
			// si la puntuacion del jugador actual es mayor a la de algún jugador en la lista de mejores puntuaciones.
			// hacemos el intercambio. Corremos todas las puntuaciones desde la posición actual hasta la última.
			
			auxintercambiopuntuacion1 = puntuaciones[i].puntuacion;
			strcpy(auxintercambionombre1, puntuaciones[i].nombre);
			// guardamos la información del jugador en la posición i.
			// esta es la posición en donde meteremos la nueva información del jugador actual.
			
			for(int j=i+1; j<10; j++){
				// haremos el intercambio de la información de la posición actual (i)
				// con la siguiente posición (j) para ir "bajando" las puntuaciones.
				// lo haremos primero para la puntuación.
				auxintercambiopuntuacion2 = puntuaciones[j].puntuacion;
				// salvamos la puntuación de la posición j.
				puntuaciones[j].puntuacion = auxintercambiopuntuacion1; 
				// luego intercambiamos con la puntuación de la posición anterior.
				// para ir "bajando" las puntuaciones.
				auxintercambiopuntuacion1 = auxintercambiopuntuacion2;
				
				// hacemos lo mismo para el nombre de los jugadores.
				strcpy(auxintercambionombre2, puntuaciones[j].nombre);
				strcpy(puntuaciones[j].nombre, auxintercambionombre1);
				strcpy(auxintercambionombre1, auxintercambionombre2);
			}
			
			// ahora metemos los datos del nuevo jugador en la posición que le corresponde.
			strcpy(puntuaciones[i].nombre, pjugador->nombre); // nombre.
			puntuaciones[i].puntuacion = pjugador->puntuacion; //puntuación.
			
			break; // terminamos el ciclo. 
		} // si la puntuación del jugador actual no es mayor a ninguna de las mejores puntuaciones actuales.
		// entonces la información no cambiará. 
	}
}

void imprimir_puntuaciones(struct _jugador puntuaciones[]){
	
	int y=9; // la y inicial es 9;
	
	for (int i=0; i<10; i++){
		if (puntuaciones[i].nombre[0] != ' '){
			// si el nombre del jugador es diferente a nulo, significa que hay información para leer.
			gotoxy(22,y); printf("%s", puntuaciones[i].nombre);
			gotoxy(40,y); printf("%d", puntuaciones[i].puntuacion);
			// se imprime el nombre y la puntuación del jugador.
		}
		else{
			// sino, se imprimen líneas para llenar el espacio.
			gotoxy(22,y); printf("-------------------------");
		}
		y++; // aumentamos la y, para bajar la línea.
	}
}

void cargar_datos(struct _jugador puntuaciones[]){
	
	char auxpuntuacion[15]; // auxiliar para leer la puntuacion de un jugador.
	
	FILE *mejores_puntuaciones = fopen("puntuaciones.txt", "r"); // declaramos el fichero.
	// abrimos el fichero en modo lectura.
	
	// leer los datos.
	for (int i=0; i<10; i++){
		if(fgets(puntuaciones[i].nombre,20,mejores_puntuaciones) != NULL){
			// si hay información (un nombre) para leer, entonces leemos también la puntuación.
			puntuaciones[i].puntuacion = atoi(fgets(auxpuntuacion,15,mejores_puntuaciones));
			// esta información se guarda en una structura de tipo _jugador.
			// usamos el auxpuntuacion para convertir el caracter a entero.
		}
		else{
			break; // sino, entonces se ha llegado al final del fichero. Termina el ciclo.
		}
	}
	
	fclose(mejores_puntuaciones); // cerramos el fichero.
}
void imprimir_tabla(struct _jugador *pjugador){
	
	//Tablero para mejores puntuaciones.
	//líneas horizontales.
	for (int i=10; i<=60; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,21); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=21; j++){
		gotoxy(10,j); printf("%c", 186);
		gotoxy(60,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(10,5); printf("%c", 201);
	gotoxy(60,5); printf("%c", 187);
	gotoxy(10,21); printf("%c", 200);
	gotoxy(60,21); printf("%c", 188);
	
	// Texto
	gotoxy(15,7); printf("---------- Mejores Puntaciones ----------");
	gotoxy(15,9); printf("   1."); //aquí a el listado de las mejores puntuaciones.
	gotoxy(15,10); printf("   2.");
	gotoxy(15,11); printf("   3.");
	gotoxy(15,12); printf("   4.");
	gotoxy(15,13); printf("   5.");
	gotoxy(15,14); printf("   6.");
	gotoxy(15,15); printf("   7.");
	gotoxy(15,16); printf("   8.");
	gotoxy(15,17); printf("   9.");
	gotoxy(15,18); printf("   10."); // se muestran siempre las 10 más altas. 
	
	
	// Tablero para puntuación del jugador.
	//líneas horizontales.
	for (int i=62; i<=90; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,21); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=21; j++){
		gotoxy(62,j); printf("%c", 186);
		gotoxy(90,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(62,5); printf("%c", 201);
	gotoxy(90,5); printf("%c", 187);
	gotoxy(62,21); printf("%c", 200);
	gotoxy(90,21); printf("%c", 188);
	
	gotoxy(65,7); printf("--- Tus Resultados ---");
	gotoxy(65,9); printf(" + Puntuación:"); 
	// Imprimir puntuación
	gotoxy(65,11); printf("     %d", pjugador->puntuacion);
	gotoxy(65,14); printf(" + Ingresa tu nombre:");
}

void animacion(){
	
	char tecla; 
	
	// Esta animación se muestra justo después de que el jugador haya perdido.
	// la leyenda dice "Haz Perdido".
	gotoxy(5,5); printf("  _    _          ______      _____  ______ _____  _____ _____ _____   ____  \n");
	gotoxy(5,6); printf(" | |  | |   /%c   |___   /    |  __ %c|  ____|  __ %c/  __ %c_   _|  __ %c / __ %c \n", 92,92,92,92,92,92);
	gotoxy(5,7); printf(" | |__| |  /  %c      / /     | |__) | |__  | |__) | |  | || | | |  | | |  | |\n",92);
	gotoxy(5,8); printf(" |  __  | / /%c %c    / /      |  ___/|  __| |  _  /| |  | || | | |  | | |  | |\n",92,92);
	gotoxy(5,9); printf(" | |  | |/ ____ %c  / /__     | |    | |____| | %c %c| |__| || |_| |__| | |__| |\n",92,92,92);
	gotoxy(5,10); printf(" |_|  |_/_/    %c_%c/_____|    |_|    |______|_|  %c_%c_____/_____|_____/ %c____/ \n",92,92,92,92,92);
	
	// animación de carga, se rellena un barrita.
	gotoxy(40,17); printf("cargando...");
	for (int i=0; i<5; i++){
		gotoxy((42 + i), 15); printf("%c", 219);
		delay(100);
	}
	
	// luego se limpia la pantalla y se vuelve a imprimir "haz perdido"
	system("cls");
	
	gotoxy(5,5); printf("  _    _          ______      _____  ______ _____  _____ _____ _____   ____  \n");
	gotoxy(5,6); printf(" | |  | |   /%c   |___   /    |  __ %c|  ____|  __ %c/  __ %c_   _|  __ %c / __ %c \n", 92,92,92,92,92,92);
	gotoxy(5,7); printf(" | |__| |  /  %c      / /     | |__) | |__  | |__) | |  | || | | |  | | |  | |\n",92);
	gotoxy(5,8); printf(" |  __  | / /%c %c    / /      |  ___/|  __| |  _  /| |  | || | | |  | | |  | |\n",92,92);
	gotoxy(5,9); printf(" | |  | |/ ____ %c  / /__     | |    | |____| | %c %c| |__| || |_| |__| | |__| |\n",92,92,92);
	gotoxy(5,10); printf(" |_|  |_/_/    %c_%c/_____|    |_|    |______|_|  %c_%c_____/_____|_____/ %c____/ \n",92,92,92,92,92);
	
	// se imprimime este mensaje
	gotoxy(30,17); printf("Presione enter para continuar...");
	// y se espera a que el usuario oprima la tecla correspondiente.
	do{
		tecla = getch();
	} while(tecla != 13); // 13 es el código ascii para "enter"
	
	system("cls");
}
void pedir_nombre(struct _jugador puntuaciones[], struct _jugador *pjugador){
	
	char nombre[20]; // para guargar temporalmente el nombre del jugador.
	char caracter; // el nombre se va leyendo caracter por caracter para tener más control sobre el.
	int x, contadorcaracter; // coordenada x, y contador de caracteres.
	
	// inicializamos el contador y la x.
	contadorcaracter = 0;
	x=68;
	
	// abrimos do-while.
	do{
		// pedimos el nombre usando getch para poder restringir el numero de caracteres.
		// el limite es 15 caracteres.
		fflush(stdin);
		gotoxy(x,16); caracter = getch(); // pedimos el caracter.
		
		if (caracter != 13){ // si es diferente de enter (13 es ascii code para enter).
			
			if (caracter != 8){ // si es diferente de "<---" (borrar letra).
				if (isalnum(caracter) != 0 && caracter != 72 && caracter!= 75 && caracter != 80 && caracter != 77 ){
					// si el caracter es alfanumerico, y diferente de todas las teclas de dirección.
					// sabemos que las teclas de dirección no son valores alfanumericos pero
					// causaba problemas, así que pusimos las restricciones a parte.
					gotoxy(x,16); printf("%c", caracter); // mostramos el caracter en pantalla.
					// pues la función getch no lo hace. 
					nombre[contadorcaracter] = caracter; // pasamos ese caracter a la cadena.
					contadorcaracter++; // aumentamos contador de caracteres.
					x++; //aumentamos la x para que el siguiente caracter no se sobreponga al actual.
				}
				else{
					// si el usuario trata de ingresar un caracter no valido.
					// se le mostrará el siguiente mensaje y no será tomado en cuenta.
					gotoxy(67,18); printf("¡Ingresa solo valores");
					gotoxy(67,19); printf("alfanumericos!");
				}
			}
			else{
				if(contadorcaracter != 0){ 
					// la parte de borrar una letra solo funcionará si el contador de caracteres es mayor a cero. 
					// pues si es cero, no hay caracteres para borrar.
					
					x--; // restamos en x.
					contadorcaracter--; // restamos en y.
					
					nombre[contadorcaracter] = 00; // borramos el valor de la cadena (00 = nulo).
					gotoxy(x,16); printf(" "); // imprimimos un espacio en blanco.
					
				}
			}
		}
		else{
			break; // si es enter, rompemos el ciclo. 
		}
	} while(contadorcaracter < 15);	
	// si el contador de caracteres llega a 15, termina el ciclo. Aunque el jugador no haya oprimido enter.
	
	nombre[contadorcaracter] = '\0'; 
	// agregamos el fin de linea una posición despues del último caracter ingresado por el usuario.
	// contadorcaracter de hecho representa esta posición. 
	
	strcpy(pjugador->nombre, nombre); // copiamos el nombre a la estrutura del jugador. 
	
}
