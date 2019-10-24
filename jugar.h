#include <stdio.h>
#include <conio.h>
#include "game_over.h"		 

// Valores del código ASCII para los controles del juego.
#define SALIR 27 // ESC.

#define DERECHA 100 // 'd'
#define DERECHA2 68 // 'D'

#define IZQUIERDA 97 // 'a'
#define IZQUIERDA2 65 // 'A'

#define ABAJO 115 // 's'
#define ABAJO2 83 // 'S'

#define ROTAR 111 // 'o'
#define ROTAR2 79 // 'O'

#define BAJAR 119 //'w'
#define BAJAR2 87 //'W'

#define GUARDAR 112 // 'p'
#define GUARDAR2 80 // 'P'

#define LIBERAR 109 // 'm'
#define LIBERAR2 77 // 'M'

#define NINGUNA 50

// Dimensiones para la matriz del tablero principal.
#define ALTOTABLERO 20
#define ANCHOTABLERO 20
// Dimensiones para la matriz que guardará las coordenadas
// de la pieza actualmente en juego.
#define AlTOCOORDENADAS 3
#define ANCHOCOORDENADAS 4

// Funciones para imprimir. 
void imprimir_interface(); // Imprime el tablero del juego. 
void imprimir_pieza(int M[ALTOTABLERO][ANCHOTABLERO]); // Imprime un cuadro donde haya 1 en la matriz.
void imprimir_siguiente_pieza(int P[]); 
void imprimir_matriz(int M[ALTOTABLERO][ANCHOTABLERO]); 
void imprimir_coordenadas(int M[AlTOCOORDENADAS][ANCHOCOORDENADAS], int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS]);
void imprimir_pieza_guardada(int P[]);
void imprimir_puntaje(int P[]); // Imprime el puntaje en pantalla.

// Actualiza las coordenadas de una pieza. Estas coordenadas son relativas a la matriz del tablero principal.
void actualizar_coordenadas(int M[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion); 
// Llena la matriz del juego con '1' en función de las coordenadas generadas por la función "actualizar_coordenadas"
void llenar_matriz(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]);
// Llena la matriz del juego con '0' en función de las coordenadas generadas por la función "actualizar_coordenadas"
void borrar_matriz(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]);
// Se encarga de cambiar las coordenadas 'x' o 'y' dependiendo de la tecla de control que haya oprimido el jugador.
// También puede cambiar el valor "rotacion" si el jugador desea rotar la pieza. 
// devuelve 0 si el usuario quiere salir del juego.
int control_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS], int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion, char tecla);
// Determina si la pieza debe "pegarse".
// También nos dice si la pieza puede o no moverse (o rotar) al lugar donde el jugador quiere. 
// Esta funcion devuelve '1' si no se puede realizar el movimiento o '0' si sí.
int pegar_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]);
// Evalúa si debe borrarse una línea.
void borrar_linea(int M[ALTOTABLERO][ANCHOTABLERO], int P[]);

// función para bajar la pieza de manera inmediata con una tecla. 
void bajar_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS],int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion);
// permite guardar una pieza para usarla en otro momento, se activa con una tecla. 
void guardar_pieza(int P[]);
// Lanza el menú de pausa. Desde ahí puedes, reanudar, reiniciar el juego, o salir del juego.
// devuelve 0 si el usuario quiere reanudar, 1 si el usuario elige salir y 2 si el usuario elije reiniciar.
int pausa(int T[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]);
// lleva el nivel del jugador.
void nivel(int P[]);
// Permite reiniciar el juego, se lanza desde la función pausa. 
void reiniciar(int M[ALTOTABLERO][ANCHOTABLERO], int P[]);

void jugar() {
	
	/// Función main de jugar.h
	// Declaramos los dos vectores y los inicializamos con ceros.
	int T[ALTOTABLERO][ANCHOTABLERO] = {{0}}; // Tablero
	int C[AlTOCOORDENADAS][ANCHOCOORDENADAS] = {{0}}; // Coordenadas
	int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS] = {{0}}; // Es una matriz "gemela" de la matriz 'C'.
	// sirve para poder "predecir" los movimientos de la pieza y evaluar si el movimientos es válido o no, antes de mostrarlo al jugador. 
	// es decir, antes de pasar las coordenadas a la Matriz 'C'.
	int P[8]={0}; // Vector para guardar datos importantes. Puntaje en posición 0, pieza actual en posición 1, pieza siguiente en posición 2 y 
	// pieza guardada en posición 3. La posición 4 es una condición para saber si la función "guardar_pieza" está disponible. 
	// la posición 5 es para salvar la pieza siguiente al momento de guardar una pieza.(intercambiar pieza actual y pieza guardada).
	// Posición 6 es para saber la velocidad a la que debe bajar la pieza automaticamente.
	// Posición 7 es el nivel del juego.
	
	// Declaramos variables a utilizar.
	int rotacion; // Valores de las piezas. 
	int x, y; // variables para las coordenadas.
	int continuar = 1; // Variable para saber cuando detener bucle principal del juego.
	char tecla; // Variable para identificar las teclas de control.
	
	P[6] = 12800; // velocidad inicial. Disminuye mediante avanzan los niveles, esto aumenta la velocidad.
	// hay un contador que lleva el tiempo, cuando este contador alcanza este valor, la pieza baja.
	P[7] = 1; // el nivel inicial es 1.
	P[4] = 1; // 1: función disponible, 0: función no dispoible.
	P[1] = generar_pieza();
	P[2] = generar_pieza_siguiente();
	// Generamos una pieza inicial de forma aleatoria.
	do{
		// si pieza actual es igual a la pieza siguiente, se genera otra pieza siguiente. 
		if (P[2] == P[1]){
			P[2] = generar_pieza();
		}
		// Esto se repite mientras la pieza actual sea igual a la pieza siguiente. 
	} while(P[2] == P[1]);
	
	while (continuar == 1){
		
		/// Establecemos valores iniciales para variables importantes.
		y = 1; // La 'y' inicial siempre es 1.
		x = random_x(); // La 'x' inicial es un número par aleatorio en un rango definido. 
		rotacion = 1; // La rotación inicial es igual 1. 
		P[2] = generar_pieza_siguiente(); // Generamos la pieza para el siguiente ciclo.
		
		/// Sección para evaluar el intercambio de piezas.
		if (P[4] == 0){ // si se intercambiaron la pieza guardada con la pieza actual. 
			P[2] = P[5]; // La pieza siguiente para este nuevo ciclo será la misma que el del anterior
			// de esta forma de mantiene la pieza siguiente. 
		}
		/*
		else{
			// Este ciclo es para que la primera pieza y la pieza siguiente no sean igual. 
			// Ya que la función generar_pieza tiende a dar el mismo número dos veces al iniciar el juego. 
			do{
				// si pieza actual es igual a la pieza siguiente, se genera otra pieza siguiente. 
				if (P[2] == P[1]){
					P[2] = generar_pieza();
				}
				// Esto se repite mientras la pieza actual sea igual a la pieza siguiente. 
			} while(P[2] == P[1]);
		}
		*/
		
		/// Sección para evaluar si el jugador ha perdido.
		// actualizamos las coordenadas en C2 para poder evaluar la posición de la pieza al inicio.
		// si no hay ningun lugar disponible para la pieza, entonces el jugador ha perdido.
		actualizar_coordenadas(C2,P,x,y,rotacion);
		continuar = 0; // continua = 0 para poder evaluar.
		if (pegar_pieza(T,C2) == 1){ // si la pieza no se puede colocar en la posición asignada.
			for (int i=0; i<ANCHOTABLERO; i=i+2){ // coordenada x.
				for (int j=0; j<2; j++){ // coordenada y.
					for(int r=1; r<5; r++){ // valor de rotacion.
						x = i; 
						y = j;
						rotacion = r;
						// probamos las posiciones posibles.
						// actualizamos las coordenadas en C2 para evaluar. 
						actualizar_coordenadas(C2, P, x, y, rotacion);
						
						// si se puede colocar la pieza en alguna posición...
						if(pegar_pieza(T,C2)==0){
							continuar = 1; // hacemos continuar igual a 1 y terminamos el ciclo de la rotacion.
							break;
						}
					}
					if(continuar == 1){
						break; // si al salir del ciclo anterior, continuar es igual a 1, rompemos el ciclo de las y.
					}
				}
				if(continuar == 1){
					break; // rompemos el ciclo de las x.
				}
			}
		}
		else{
			continuar = 1; // si la pieza se puede colocar, hacemos continuar = 1;
		}
		
		if (continuar == 0){ // si al salir de todos los ciclos anteriores, la pieza no se pudo colocar en ninguna posición.
			game_over(P[0]); // entonces el jugador a perdido, entramos a la función game_over.
			break; // terminamos el juego para regresar a la pantalla principal. 
		}
		
		// si el jugador no ha perdido.
		actualizar_coordenadas(C,P,x,y,rotacion);
		llenar_matriz(T,C);
		
		// La pantalla se limpia cada vez que se vaya a imprimir algo nuevo. 
		system("cls");
		imprimir_interface();
		imprimir_pieza(T);
		imprimir_siguiente_pieza(P);
		imprimir_puntaje(P);
		imprimir_pieza_guardada(P);
		
		// la primera tecla será siempre "NINGUNA".
		tecla = NINGUNA;
			// entramos a la función control_pieza.
		if (control_pieza(T, C, C2, P, x, y, rotacion, tecla) == 0){
			// si la función devuelve '0', se rompe el ciclo y termina el juego. 
			break;
		}
		
		// Se evalua si se debe borrar alguna línea, con la función borrar_linea.
		borrar_linea(T, P);
		nivel(P);
		// Se interambia la pieza siguiente con la pieza actual. 
		P[1] = P[2];
	}
}

int control_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS], int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion, char tecla){
	
	int pegar = 0;
	// Variable para saber si la pieza se pegó o no. Es decir, que el ciclo tiene que terminar para la pieza en juego. 
	// 0 significa que la pieza no se ha pegado. 
	int tiempo = 0;
	// tiempo para que la pieza baje sola. cuando el timempo alcanza la velocidad del juego, la pieza baja.
	
	// Entonces, mientras la pieza no se haya pegado. 
	while (pegar==0){
		
		tiempo=tiempo + 50; // aumentamos el tiempo. 
		
		// Borramos los datos de la pieza en la matriz. 
		borrar_matriz(M,C);
		
		// si el tiempo el mayor que la velocidad del juego.
		if (tiempo > P[6]){
			tecla = ABAJO;
			// para simular el movimiento de la pieza hacia abajo.
			tiempo = 0; 
			// reiniciamos el tiempo.
		}
		
		/// Sección donde se evalúan los controles del juego.
		switch (tecla){
		case DERECHA: case DERECHA2:
			x=x+2; // Se suma dos a las x para que la pieza se mueva a la derecha. 
			actualizar_coordenadas(C2, P, x, y, rotacion);
			// se actualizan las coordenadas en la matriz C2.
			
			//Se se evalúa si la pieza puede o no realizar ese movimiento. 
			if (pegar_pieza(M,C2) == 1){
				// Si no se puede, se reestablecen los cambios en la x. 
				x=x-2;
			}
			break;
			
		case IZQUIERDA: case IZQUIERDA2:
			x=x-2; // se resta dos a x para que la pieza se mueva a la izquierda.
			actualizar_coordenadas(C2, P, x, y, rotacion);
			// se actualizan las coordenadas en la matriz C2.
			
			//Se se evalúa si la pieza puede o no realizar ese movimiento. 
			if (pegar_pieza(M,C2) == 1){
				x=x+2; // sino, se reestablecen los cambios en x.
			}
			break;
			
		case ABAJO: case ABAJO2:
			y++; // para bajar se suma uno a las y.
			actualizar_coordenadas(C2, P, x, y, rotacion);
			// se actualizan las coordenadas en la matriz C2.
			
			//Se se evalúa si la pieza puede o no realizar ese movimiento. 
			if (pegar_pieza(M,C2) == 1){
				// si no se puede realizar el movimiento.
				// hacemos que la pieza se pegue.
				llenar_matriz(M,C); // llenamos la matriz.
				P[4] = 1; // hacemos que la función guardar pieza vuelva a estar disponible.
				pegar=1; // para que no se vuelva a actualizar la pantalla.
			}
			break;
			
		case ROTAR: case ROTAR2: 
			// si la rotación es 4, la cambiamos a 1, pues rotación 5 no existe.
			if (rotacion == 4){
				rotacion = 1;
			}
			else{
				rotacion++; // sino, simplemente aumentamos 1 a la rotación.
			}
			actualizar_coordenadas(C2, P, x, y, rotacion);
			// se actualizan las coordenadas en la matriz C2.
			
			//Se se evalúa si la pieza puede o no realizar ese movimiento.
			if (pegar_pieza(M,C2) == 1){
				// si no se puede realizar el movimiento, reestablecemos los cambios.
				if (rotacion == 1){
					rotacion = 4;
				}
				else {
					rotacion--;
				}
			}
			break;
			
		case BAJAR: case BAJAR2:
			// entramos a la función bajar_pieza.
			bajar_pieza(M,C,C2,P,x,y,rotacion);
			llenar_matriz(M,C);
			// llenamos la matriz.
			P[4] = 1; // hacemos que la función guardar pieza vuelva a estar disponible.
			pegar = 1; // para que la pieza se pegue y no se vuelva a actualizar la pantalla.
			break;
		
		case GUARDAR: case GUARDAR2:
			// si la función está disponible.
			if (P[4] == 1){
				guardar_pieza(P);
				P[4] = 0; // la función guardar ya no está disponible para usarse.
				pegar = 1; // para que termine el ciclo de la pieza.
			}
			break;
			
		case NINGUNA:
			break; // hacemos nada.
			
		case SALIR:
			// entramos al menú de pausa.
			switch(pausa(M,C)){ // evaluamos lo que nos devuelve la función pausa.
			case 0:
				break; // para reanudar hacemos nada.
			case 1:
				return 0; // para salir retornamos cero.
				break;
			case 2: 
				// para reiniciar se borra toda la información.
				reiniciar(M,P);
				pegar = 1; // para que se acabe el ciclo de la pieza actual.
				break;
			}	
			break;
		}
		
		if (pegar == 0){
			// si pegar vale 0 y la pieza es diferente de NINGUNA
			if (tecla != NINGUNA){
				// actualizamos la información en la pantalla.
				system("cls");
				imprimir_interface();
				imprimir_siguiente_pieza(P);
				imprimir_pieza_guardada(P);
				
				actualizar_coordenadas(C, P, x, y,rotacion);
				llenar_matriz(M,C);
				
				imprimir_pieza(M);
				imprimir_puntaje(P);
			}
			
			tecla = NINGUNA;
			delay(5); // pequeña pausa para mejor control de la pieza.
			if(kbhit()){ // si se oprime una pieza
				tecla = getch(); // la guardamos en la variable tecla usando la función getch.
			}
		}
		else{
			break; // si pegar es igual a 1, rompemos el ciclo while.
		}
	}	
	return 1; // retornamos uno si se llega al final.
}

void imprimir_interface(){
	
	//Tablero Principal.
	//líneas horizontales.
	for (int i=5; i<=26; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,26); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=26; j++){
		gotoxy(5,j); printf("%c", 186);
		gotoxy(26,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(5,5); printf("%c", 201);
	gotoxy(26,5); printf("%c", 187);
	gotoxy(5,26); printf("%c", 200);
	gotoxy(26,26); printf("%c", 188);
	
	
	// Tablero para mostrar pieza siguiente y guardada.
	// líneas horizontales.
	for (int i=28; i<=50; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,20); printf("%c", 205);
	}
	
	// líneas verticales.
	for (int j=5; j<=20; j++){
		gotoxy(28,j); printf("%c", 186);
		gotoxy(50,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(28,5); printf("%c", 201);
	gotoxy(50,5); printf("%c", 187);
	gotoxy(28,20); printf("%c", 200);
	gotoxy(50,20); printf("%c", 188);
	
	// Texto.
	gotoxy(31,6); printf ("Siguiente pieza:");
	gotoxy(31,13); printf ("Pieza guardada:");
	
	
	// Tablero para mostrar el Puntaje.
	for (int i=28; i<=50; i++){
		gotoxy(i,21); printf("%c", 205);
		gotoxy(i,26); printf("%c", 205);
	}
	
	// Líneas verticales.
	for (int j=21; j<=26; j++){
		gotoxy(28,j); printf("%c", 186);
		gotoxy(50,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(28,21); printf("%c", 201);
	gotoxy(50,21); printf("%c", 187);
	gotoxy(28,26); printf("%c", 200);
	gotoxy(50,26); printf("%c", 188);
	
	// Texto.
	gotoxy(31, 22); printf("Puntaje:");
	gotoxy(41, 22); printf("Nivel:");
}


void imprimir_pieza(int M[ALTOTABLERO][ANCHOTABLERO]){
	
	// escaneamos la matriz del tablero. se imprime un cuadro en donde se encuentre un 1.
	for (int i=0; i<ALTOTABLERO; i++){
		for (int j=0; j<ANCHOTABLERO; j++){
			if (M[i][j] == 1){
				gotoxy(j+6,i+6); printf("%c", 219);
				// se hace una correción en las coordendas. 
			}
		}
	}
}

void imprimir_siguiente_pieza(int P[]){
	
	// coordenadas para imprimir la pieza.
	int x = 36, y = 9;
	
	// a cada pieza le corresponden dos números.
	switch(P[2]){
	case 1: case 10: //cuadrado
		// cuadro principal (Eje de rotación).
		cuadro(x,y);
		
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x+2, y-1);
		cuadro(x, y-1);
		break;
	case 2: case 8://línea
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x, y+2);
		break;
	case 3: case 11:// 'S' invertida
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x, y-1);
		cuadro(x-2, y-1);
		break;
	case 4: case 13:// 'S' 
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x-2, y);
		cuadro(x, y-1);
		cuadro(x+2, y-1);			
		break;
	case 5: case 9:// 'L' invertida 1
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x-2, y-1);
		break;
	case 6: case 14://'L' invertida 2
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x+2, y-1);
		break;
	case 7: case 12:// 'T' invertida
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x-2, y);
		cuadro(x, y-1);
		break;
	} 
	
}


void actualizar_coordenadas(int M[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion){
	
	int auxintercambio; // para coordenadas al momento de rotar.
	
	int R[3][2]; // matriz auxiliar para manipular las coordenadas antes de pasarlas a la matriz real.
	
	if (P[1] == 1 || P[1] == 10){ 
		// si el número corresponde a la pieza cuadrado.
		
		// establecemos las coordenadas en la matriz auxiliar.
		R[0][0] = x+2;
		R[0][1] = y;
		// cada par de coordeanadas representa una cuadro adyacente al centro de la pieza.
		R[1][0] = x+2;
		R[1][1] = y-1;
		
		R[2][0] = x;
		R[2][1] = y-1;
		
		// y las copiamos a la matriz real.
		poner_coordenadas(M,x,y,0); // las coordenadas del centro se mantienen. 
		poner_coordenadas(M,R[0][0],R[0][1],1);
		poner_coordenadas(M,R[1][0],R[1][1],2);
		poner_coordenadas(M,R[2][0],R[2][1],3);
	}
	else{
		switch(P[1]){
		// de otro modo, establecemos las coordenas de la pieza correspondiente en la matriz auxiliar.
		// usamos un switch para evaluar.
		case 2: case 8://línea
			// cuadros adyacentes. 
			R[0][0] = x;
			R[0][1] = y-1;
			
			R[1][0] = x;
			R[1][1] = y+1;
			
			R[2][0] = x;
			R[2][1] = y+2;
			break;
		case 3: case 11:// 'S' invertida
			// cuadros adyacentes. 
			R[0][0] = x+2;
			R[0][1] = y;
			
			R[1][0] = x;
			R[1][1] = y-1;
			
			R[2][0] = x-2;
			R[2][1] = y-1;
			break;
		case 4: case 13:// 'S' 
			// cuadros adyacentes. 
			R[0][0] = x-2;
			R[0][1] = y;
			
			R[1][0] = x;
			R[1][1] = y-1;
			
			R[2][0] = x+2;
			R[2][1] = y-1;
			break;
		case 5: case 9:// 'L' invertida 1
			// cuadros adyacentes. 
			R[0][0] = x;
			R[0][1] = y-1;
			
			R[1][0] = x;
			R[1][1] = y+1;
			
			R[2][0] = x-2;
			R[2][1] = y-1;
			break;
		case 6: case 14://'L' invertida 2
			// cuadros adyacentes. 
			R[0][0] = x;
			R[0][1] = y-1;
			
			R[1][0] = x;
			R[1][1] = y+1;
			
			R[2][0] = x+2;
			R[2][1] = y-1;
			break;
		case 7: case 12:// 'T' invertida
			// cuadros adyacentes. 
			R[0][0] = x+2;
			R[0][1] = y;
			
			R[1][0] = x-2;
			R[1][1] = y;
			
			R[2][0] = x;
			R[2][1] = y-1;
			break;
		} 
		
		/// ALGORITMO DE ROTACIÓN
		if (rotacion == 1){
			// si la rotación es uno, solo copiamos las coordenadas a la matriz real.
			poner_coordenadas(M,x,y,0);
			poner_coordenadas(M,R[0][0],R[0][1],1);
			poner_coordenadas(M,R[1][0],R[1][1],2);
			poner_coordenadas(M,R[2][0],R[2][1],3);
		}
		else{ // sino, entramos a un for para rotar tantas veces como sea necesario.
			for (int d=1; d<rotacion; d++){ // desde uno hasta rotación-1.
				for (int k=0; k<3; k++){ 
					/// sección para hacer ajuste a las coordenadas
					// estos ajustes se hacen porque las 'x' van de dos en dos, y las 'y' de uno en uno.
					// repetimos 3 veces, una vez para cada cuadro adyacente al centro de la pieza.
					//restamos 'x' y 'y' a las coordenadas;
					// para dejar la pieza en el "origen", es decir, el centro estará en (0,0).
					// esto es para que el algoritmo funcione correctamente.
					R[k][0] = R[k][0] - x;
					R[k][1] = R[k][1] - y;
					
					// Ajustamos para las 'x'.
					if (R[k][0] != 0){ // si coordenada x es diferente de cero.
						R[k][0] = R[k][0] / 2; // las x se dividen entre dos.
					}
					// Ajustamos para las 'y'.
					if (R[k][1] != 0){ // si coordenada y es diferente de cero.
						R[k][1]=R[k][1] * 2; // las y se multiplican por dos.
					}
				}
				// una vez ajustadas todas las coordenadas.
				// Rotamos las coordenadas.
				for(int j=0; j<3; j++){
					auxintercambio=R[j][0];
					R[j][0]=(R[j][1])*(-1);
					R[j][1]=auxintercambio;
				}
				// Volvemos a sumar 'x' y 'y'. 
				for (int k=0; k<3; k++){
					R[k][0] = R[k][0] + x;
					R[k][1] = R[k][1] + y;
				}	
			}
			// listas las coordenadas rotadas, las pasamos a la matriz de coordenadas real.
			poner_coordenadas(M,x,y,0);
			poner_coordenadas(M,R[0][0],R[0][1],1);
			poner_coordenadas(M,R[1][0],R[1][1],2);
			poner_coordenadas(M,R[2][0],R[2][1],3);
		}
	}
}

void llenar_matriz(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]){
	
	for(int i=0; i<ANCHOCOORDENADAS;  i++){
		poner_unos(M, C[0][i], C[2][i]);
		// se llena la matriz de unos, en función de las coordenadas de la pieza.
	}
}


void borrar_matriz(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]){
	
	for(int i=0; i<ANCHOCOORDENADAS;  i++){
		poner_ceros(M, C[0][i], C[2][i]);
		// se borran los unos de la pieza actual, en función de las coordenadas.
		// solo se borran los unos que corresponden a la pieza actual en juego
		// no se borran los unos de las piezas que ya se hayan pegado.
	}
}







void imprimir_matriz(int M[ALTOTABLERO][ANCHOTABLERO]){
	/// función para pruebas, no importante en el trabajo final.
	int x = 53;
	int y = 6;
	for (int i=0; i<ALTOTABLERO; i++){
		gotoxy(x,y);
		for (int j=0; j<ANCHOTABLERO; j++){
			printf ("%d", M[i][j]);
		}
		y++;
		printf ("\n\n");
	}
}

void imprimir_coordenadas(int M[AlTOCOORDENADAS][ANCHOCOORDENADAS], int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS]){
	/// función para pruebas, no importante en el trabajo final.
	int x = 75;
	int y = 6;
	
	for (int i=0; i<AlTOCOORDENADAS; i++){
		gotoxy(x,y);
		for (int j=0; j<ANCHOCOORDENADAS; j++){
			printf (" %d ", M[i][j]);
		}
		y++;
		printf ("\n\n");
	}
	
	y = 12;
	
	for (int i=0; i<AlTOCOORDENADAS; i++){
		gotoxy(x,y);
		for (int j=0; j<ANCHOCOORDENADAS; j++){
			printf (" %d ", C2[i][j]);
		}
		y++;
		printf ("\n\n");
	}
}

int pegar_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]){
	
	/// restricciones para saber cuando no se puede mover la pieza o cuando debe pegarse.
	for(int i=0; i<ANCHOCOORDENADAS;  i++){
		
		// si hay un 1, en las posición a la que va a moverse la pieza.
		if (M[C[2][i]][C[0][i]] == 1){
			return 1;
		}
	}	
	
	// Si las 'y' son mayores a 19. 
	for (int j=0; j<ANCHOCOORDENADAS; j++){
		if (C[2][j] > 19 || C[2][j] < 0 ){
			return 1;
		}
	}
	
	// si las 'x' son menores que 0 o mayores a 19. 
	for (int k=0; k<ANCHOCOORDENADAS; k++){
		if (C[0][k] < 0 || C[0][k] > 19 ){
			return 1;
		}
	}
	return 0;
}
void borrar_linea(int M[ALTOTABLERO][ANCHOTABLERO], int P[]){
	
	/// función para borrar una linea, si esta se ha llenado.
	int contador; 
	int y=19; // y inicial igual a 19, es decir, la linea más baja del tablero.
	
	// mientras y>=0, se escanea la matriz (tablero) de abajo hacia arriba.
	while (y>=0){
		contador = 0; // resetamos para cada linea.
		for (int j=0; j<ANCHOTABLERO; j++){
			if (M[y][j] == 1){
				contador++; 
				// aumentamos el contador cada que se encuentre un uno en la línea. 
			}
		}
		if (contador == 20){ // si el contador es 20, entonces la línea está completa y debe borrarse.
			P[0] = P[0] + 50; // aumentamos la puntuación.
			//borras la linea
			for (int k=0; k<ANCHOTABLERO; k++){
				M[y][k] = 0; 
			}
			//bajas las otras lineass
			for (int m=y-1; m>=0; m--){
				for (int n=0; n<ANCHOTABLERO; n++){
					if (M[m][n] == 1){ // si la posición de arriba tiene un uno.
						M[m+1][n] = 1; // lo bajamos.
						M[m][n] = 0; // y convertimos ese uno en cero.
					}
				}
			}
		}
		else{
			y--; // sino se llenó la linea, disminuimos la y para evaluar la línea de arriba. 
		}
	}
}
void imprimir_puntaje(int P[]){
	/// imprime el puntaje en pantalla.
	gotoxy(31,24); printf("%d", P[0]);
	gotoxy(41,24); printf("%d", P[7]);
}
void bajar_pieza(int M[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS],int C2[AlTOCOORDENADAS][ANCHOCOORDENADAS], int P[], int x, int y, int rotacion){
	
	/// se aumenta la coordenada y de la pieza hasta que se pegue.
	do{
		actualizar_coordenadas(C, P, x, y,rotacion); 
		y++;
		actualizar_coordenadas(C2,P,x,y,rotacion);
		
	} while (pegar_pieza(M,C2)==0);
	
}
void guardar_pieza(int P[]){
	
	int auxintercambio; // para hacer el intercambio de la pieza actual y la guardada. 
	
	if (P[3] != 0){ // si ya hay una pieza guardada.
		auxintercambio = P[3]; // guardamos la pieza guardada en un auxiliar.
		P[3] = P[1]; // pieza guardada igual a la pieza actual. 
		P[5] = P[2]; // guardamos la pieza siguiente en otro lugar del vector.
		P[2] = auxintercambio; // pieza siguiente igual a la pieza guardada.
	}
	else{
		P[3] = P[1]; // pieza guardada igual a la pieza actual. 
		P[5] = generar_pieza(); // se genera una nueva pieza siguiente.  
	}
}
void imprimir_pieza_guardada(int P[]){
	
	// coordenadas para imprimir la pieza.
	int x = 36, y = 16;
	
	switch(P[3]){
	case 1: case 10: //cuadrado
		// cuadro principal (Eje de rotación).
		cuadro(x,y);
		
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x+2, y-1);
		cuadro(x, y-1);
		break;
	case 2: case 8://línea
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x, y+2);
		break;
	case 3: case 11:// 'S' invertida
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x, y-1);
		cuadro(x-2, y-1);
		break;
	case 4: case 13:// 'S' 
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x-2, y);
		cuadro(x, y-1);
		cuadro(x+2, y-1);			
		break;
	case 5: case 9:// 'L' invertida 1
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x-2, y-1);
		break;
	case 6: case 14://'L' invertida 2
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x, y-1);
		cuadro(x, y+1);
		cuadro(x+2, y-1);
		break;
	case 7: case 12:// 'T' invertida
		// cuadro principal (Eje de rotación).
		cuadro(x, y);
		// cuadros adyacentes. 
		cuadro(x+2, y);
		cuadro(x-2, y);
		cuadro(x, y-1);
		break;
	} 
}
int pausa(int T[ALTOTABLERO][ANCHOTABLERO], int C[AlTOCOORDENADAS][ANCHOCOORDENADAS]){
	
	char tecla;
	
	//imprimir menú.
	system("cls");
	
	// imprimimos interface para menú
	//líneas horizontales.
	for (int i=5; i<=50; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,26); printf("%c", 205);
	}
	
	//líneas verticales.
	for (int j=5; j<=26; j++){
		gotoxy(5,j); printf("%c", 186);
		gotoxy(50,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(5,5); printf("%c", 201);
	gotoxy(50,5); printf("%c", 187);
	gotoxy(5,26); printf("%c", 200);
	gotoxy(50,26); printf("%c", 188);
	
	llenar_matriz(T,C);

	gotoxy(19, 13);	 printf (" Reanudar(a) ");
	gotoxy(19, 15);  printf ("Reiniciar (s)");
	gotoxy(19, 17);  printf (" Salir(esc)  ");
	
	// se pide una tecla.
	do{
		tecla = getch();
		// si la tecla es diferente a alguna de las teclas de control del menú, no se evalúan.
	} while(tecla != SALIR && tecla != ABAJO && tecla != ABAJO2 && tecla != IZQUIERDA && tecla != IZQUIERDA2);
	
	// se evalua la tecla.
	switch (tecla){
	case SALIR:
		return 1;
		break;
	case ABAJO: case ABAJO2: // reiniciar.
		return 2;
		break;
	default: // reanudar.
		return 0;
		break;
	}
}

void nivel(int P[]){
	
	int puntaje = P[0]; // copiamos el valor que le pasamos a la función en una variable puntaje.
	
	if (puntaje >=100 && puntaje<500){
		if (/*nivel*/P[7] == 1){
			/*velocidad*/ P[6] = P[6]/2;
			P[7] = 2; // NIVEL 
		}
	}
	else{
		if (puntaje >=500 && puntaje < 1000){
			if (/*nivel*/P[7] == 2){
				/*velocidad*/ P[6] = P[6]/2;
				P[7] = 3; // NIVEL 
			}
		}
		else{
			if ( puntaje >= 1000 && puntaje < 2000){
				if (/*nivel*/P[7] == 3){
					/*velocidad*/ P[6] = P[6]/2;
					P[7] = 4; // NIVEL 
				}
			}
			else{
				if (puntaje >= 2000 && puntaje < 4000){
					if (/*nivel*/P[7] == 4){
						/*velocidad*/ P[6] = P[6]/2;
						P[7] = 5; // NIVEL 
					}
				}
				else{
					if (puntaje >=4000){
						if (/*nivel*/P[7] == 5){
							/*velocidad*/ P[6] = P[6]/2;
							P[7] = 6; // NIVEL 	
						}
					}
				}
			}
		}
	}
}

void reiniciar(int M[ALTOTABLERO][ANCHOTABLERO], int P[]){
	
	// borramos la matriz del tablero completamente.
	for (int i=0; i<ALTOTABLERO; i++){
		for (int j=0; j<ANCHOTABLERO; j++){
			M[i][j] = 0;
		}
	}
	
	// borramos los varoles en el vector P.
	for (int i=0; i<8; i++){
		P[i] = 0;
	}
	
	// establecemos valores necesarios en el vector P.
	P[6] = 12800;
	P[7] = 1;
	P[4] = 1; // 1: función disponible, 0: función no dispoible.
	P[2] = generar_pieza(); 
	// Generamos una pieza inicial de forma aleatoria.
}


