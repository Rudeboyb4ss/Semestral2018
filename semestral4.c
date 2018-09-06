#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

/***************************************************************

PROYECTO SEMESTRAL MÉTODOS DE PROGRAMACIÓN 1/2018

Integrantes:    Camila Norambuena
                Jorge Sandoval 
                Gonzalo Ordenes    

Profesor:       Miguel Cárcamo

****************************************************************/

//Funciones creadas
void EleccionDispositivo(int **tablero,int **jugadores,int jugador);
void OpcionesMovimiento(int**tablero,int**jugadores, int jugador);
void MostrarOpcionesMaquina(int**jugadores,int PosicionFila1, int PosicionColumna1,int**tablero);
void MostrarOpciones(int **jugadores,int PosicionFila1,int PosicionColumna1, int ** tablero);
void Usuario(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial, int estado);
void InteligenciaArtificial(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial);
void Dispositivos(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial,int jugador);
void delete(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial,int jugador,int opcion);
int MiniJuego3(int jugador);
int MiniJuego1(int jugador);
void PosicionarJugadores(int ** jugadores);
//Se definen variables globales

//valores de filas y columnas del tablero
    int filas= 8;
    int columnas =8;
    int len_dispositivos_usuario=3;
    int len_dispositivos_artificial=3;
    int MetaFila;
    int MetaColumna;

int NumeroAleatorio (){
    int numero;
    //funcion que genera numeros aleatorios rand()%6 en un rango de 0 a 10; 
    // -5 es para que consiga numeros negativos
    // si genera un 7 -5 tendremos 2 pero si genera 1 tendremos -4.
    numero = rand()%11 - 5;
    return numero;
}

void MostrarTablero(int** tablero){
    int i,j;
    for(i = -2; i < filas; i++){
        //columnas
        if (i == -2 || i ==-1) {
            printf("      ");
        } else {
            printf("%3i",i+1);
            printf("%3s","|" );
        }
        for(j = 0; j < columnas; j++){
            //filas
            if (i == -2){
                printf("%3i",j+1);
            }else if (i == -1) {
                printf("%3s","=");
            }else 
                printf("%3d", tablero[i][j]);
        }
        printf("\n");
    }

}

void RellenarTablero(int ** tablero){
    
    for (int i = 0; i < filas; ++i){
        int aux = 0;
        for (int j = 0; j < columnas; ++j){
            if(aux == 0){
                tablero[i][j] = NumeroAleatorio();
                aux =1;
            }
            else{
                int SumaResta = rand()%2;

                if(SumaResta == 0 && tablero[i][j-1] < 5){

                    tablero[i][j] = tablero[i][j-1] +1;
                }
                
                else if(SumaResta ==1 && tablero[i][j-1] > -5){
                    tablero[i][j] = tablero[i][j-1]-1;
                }

                else{
                    tablero[i][j] = NumeroAleatorio();
                    aux = 0;
                }

            }
        }        
    }

    //funcion que deja al menos una posicion en columna es valida
    int contador=0;
    while(contador<2){
        for (int i = 1; i < filas; ++i){
            int ColumnaAzar = rand()%8;
            if (tablero[i-1][ColumnaAzar] < 5){
                tablero[i][ColumnaAzar] = tablero[i-1][ColumnaAzar] +1;
            }
            else if(tablero[i-1][ColumnaAzar] > -5){
                tablero[i][ColumnaAzar] = tablero[i-1][ColumnaAzar] -1;
            }         
        }
        contador++;
    }

    printf("####### TABLERO 3D CON ALTURAS #######\n");
    MostrarTablero(tablero);
}
void PosicionarJugadores(int ** jugadores){
    srand ( time(NULL) );
    //llenamos la matriz de 0.
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            jugadores[i][j] = 0;
        }        
    }

    //posiciona jugador 1 se reserva el numero 1 
    srand ( time(NULL) );
    int k = rand()%8;
    int l = rand()%8;
        jugadores[k][l] = 1;
    //printf("El jugador 1 a quedado en la Posicion(%d,%d).\n",k,l);

    //posiciona jugador 2 se reserva el numero 2
    int n,m,p,o;
    do{
    n = rand()%8;
    m = rand()%8;

    if (jugadores[n][m] != 1)
        jugadores[n][m] = 2;

    } while (jugadores[n][m] != 2);
    //printf("El jugador 2 a quedado en la Posicion(%d,%d).\n",n,m);

    //Posicion meta, se reservara el numero 9 para la meta
    do{
    p = rand()%8;
    o = rand()%8;
    int DistanciaJugador1 = sqrt( ((k-p)*(k-p))+((l-o)*(l-o)) );
    int DistanciaJugador2 = sqrt( ((n-p)*(n-p))+((m-o)*(m-o)) );

    //funcion que verifica que la meta esta al menos a 4 casillas del jugador.

        if (DistanciaJugador1 > 4 && DistanciaJugador2 > 4)
        {
            jugadores[p][o] = 9;
        }
  
    } while (jugadores[p][o] != 9);

    printf("####### TABLERO CON POSICIONES INICIALES #######\n");
    printf("[1] = Jugador 1. [2] = Jugador 2. [9] = META. \n");
    MostrarTablero(jugadores);
}

int MiniJuego1(int jugador){
    if(jugador == 0){
	    char respuesta;
	    int jugador,NPC,empate,contador,especial,random,bajos,medios,altos;
	    jugador = 0;
	    NPC = 0;
	    empate = 0;
	    bajos = 0;
	    medios = 0;
	    altos = 0;
	    especial = 1;
	    contador = 0;
	    char * ordenNPC = (char*)malloc(11*sizeof(char));
	    for (int i = 0; i < 11; i++) {
	        if(especial > 0){
	            random = rand()%5;
	            if(random == 1){
	                ordenNPC[contador] = 'B';
	                bajos += 1;
	            }else if(random == 2){
	                ordenNPC[contador] = 'M';
	                medios += 1;
	            }else if (random == 3){
	                ordenNPC[contador] = 'A';
	                altos += 1;
	            }else{
	                ordenNPC[contador] = 'E';
	                especial -= 1;
	            }
	        }else{
	            random = rand()%4;
	            if (random == 1){
	                ordenNPC[contador] = 'B';
	                bajos += 1;
	            }else if(random == 2){
	                ordenNPC[contador] = 'M';
	                medios += 1;
	            }else{
	                ordenNPC[contador] = 'A';
	                altos += 1;
	            }
	        }
	        contador += 1;
	    }especial = 1;
	    printf("Posees un total de 11 ataques distribuidos de la siguiente manera:\n");
	    printf("Bajos: %i\n",bajos);
	    printf("Medios: %i\n",medios);
	    printf("Altos: %i\n",altos);
	    printf("Especiales: %i\n",especial);
	    
	    printf("Los primeros 5 ataques del NPC seran:\n");
	    for (int j = 0; j < 5; j++) {
	        if (j < 4){
	            printf("%c-",ordenNPC[j]);
	        }else{
	            printf("%c",ordenNPC[j]);
	        }
	    }printf("\n");
	    
	    for (int k = 0; k < 11; k++) {
	        printf("Ingrese el tipo de ataque que desee, Bajo(B), Medio(M), Alto(A), Especial(E): ");
	        scanf(" %c",&respuesta);
	        respuesta = toupper(respuesta);
	        
	        if (respuesta == 'B'){
	            bajos -= 1;
	        }else if(respuesta == 'M'){
	            medios -= 1;
	        }else if(respuesta == 'A'){
	            altos -= 1;
	        }else if(respuesta == 'E'){
	            especial -= 1;
	        }
	        
	        if(ordenNPC[k] == 'B'){
	            if ((respuesta == 'M') || (respuesta == 'E')){
	                jugador += 1;
	            }else if(respuesta == 'A'){
	                NPC += 1;
	            }else{
	                empate += 1;
	            }
	        }else if(ordenNPC[k] == 'M'){
	            if((respuesta == 'A') || (respuesta == 'E')){
	                jugador += 1;
	            }else if (respuesta == 'B'){
	                NPC += 1;
	            }else{
	                empate += 1;
	            }
	        }else if(ordenNPC[k] == 'A'){
	            if((respuesta == 'B') || (respuesta == 'E')){
	                jugador += 1;
	            }else if (respuesta == 'M'){
	                NPC += 1;
	            }else{
	                empate += 1;
	            }
	        }else if(ordenNPC[k] == 'E'){
	            if(respuesta == 'E'){
	                empate += 1;
	            }else{
	                NPC += 1;
	            }
	        }printf("victorias: %i,derrotas: %i,empates: %i\n",jugador,NPC,empate);
	    }
	    
	    printf("Has ganado %i veces.\nHas perdido %i veces.\nHas empatado %i veces.\n",jugador,NPC,empate);
	    
	    if ((bajos < 0)||(medios<0)||(altos<0)||(especial<0)){
	        printf("Has hecho trampa, hay un ataque que tiene coeficiente negativo, has perdido la partida.\n");
	        return 1;
	    }else if(jugador >= NPC){
	        printf("Felicitaciones has ganado la partida.\n");
	        return 0;
	    }else if(jugador < NPC){
	        printf("Has perdido la partida.\n");
	        return 1;
	    }return 0;
   }


   //aquí jugaría inteligencia artificial.
   else{
   		printf("nada\n");
   }
}

int MiniJuego3(int jugador){
	//significa que jugará usuario.
	if(jugador == 0){
    	printf("¡¡Bienvenido al juego de piedra, papel o tijera!!\n");
    	int random = rand()%4;
    	int respuesta;
    	printf("Escoje una opcion:\nOpcion 1: Piedra.\nOpcion 2: Papel.\nOpcion 3: Tijera.\n");
    	scanf("%i",&respuesta);
    	if(respuesta <= 0 ||respuesta >= 4){
        	printf("La opcion ingresada no es valida, el minijuego se reiniciara.\n");
        	return MiniJuego3(0);
    	}
    	if (random == 1 && respuesta == 2){
        	printf("¡¡El CPU ha lanzado piedra!!\n");
        	printf("¡¡Has ganado!!\n");
        	return 0;
    	}else if (random == 2 && respuesta == 3){
        	printf("¡¡El CPU ha lanzado papel!!\n");
        	printf("¡¡Has ganado!!\n");
        	return 0;
    	}else if(random == 3 && respuesta == 1){
        	printf("¡¡El CPU ha lanzado tijera!!\n");
        	printf("¡¡Has ganado!!\n");
        	return 0;
    	}else if(respuesta == 1 && random == 2){
        	printf("¡¡El CPU ha lanzado papel!!\n");
        	printf("¡¡Has perdido!!\n");
        	return 1;
    	}else if (respuesta == 2 && random == 3){
        	printf("¡¡El CPU ha lanzado tijera!!\n");
        	printf("¡¡Has perdido!!\n");
        	return 1;
    	}else if (respuesta == 3 && random == 1){
        	printf("¡¡El CPU ha lanzado piedra!!\n");
        	printf("¡¡Has perdido!!\n");
        	return 1;
    	}else if (random == respuesta){
        	printf("¡¡Oh, han lanzado lo mismo que la maquina, el juego se reiniciara!!\n");
        	return MiniJuego3(0);
    	}return 0;
	}

	//aquí debería jugar la inteligencia artificial.
	else{
		printf("nada\n");
	}
}




void delete(char **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial,int jugador,int opcion){
	if(jugador == 0){
		char * Dispositivos_usuario_actualizados = (char*)malloc(len_dispositivos_usuario * sizeof(char));
		int j=0;

		for(int i=0;i<len_dispositivos_usuario;i++){
			if(i!= opcion){
				Dispositivos_usuario_actualizados[j] = Dispositivos_usuario[i];
				j++;
			}
		}
		len_dispositivos_usuario--;
		Usuario(tablero,jugadores,Dispositivos_usuario_actualizados,Dispositivos_artificial,1);

	}
	else{
		char * Dispositivos_artificial_actualizados = (char*)malloc(len_dispositivos_artificial * sizeof(char));
		int j=0;
		for(int i=0;i<len_dispositivos_artificial;i++){
			if(i!= opcion){
				Dispositivos_artificial_actualizados[j] = Dispositivos_artificial[i];
				j++;
			}
		}
		len_dispositivos_artificial--;
		printf(" en la linea 178 debería entrar a InteligenciaArtificial()");
	
	}

}

void Dispositivos(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial,int jugador){
	if(jugador == 0){ //usuario
		int opcion,Resultado;

		printf("\nSus dispositivos son = ");
		for(int i = 0; i < len_dispositivos_usuario ; i++)
			printf("\n(%i)%c\n",i+1,Dispositivos_usuario[i]);

		printf("Seleccionar dispositivo con el numero que fue indicado en paréntesis = ");
		scanf("%i",&opcion);

		if(len_dispositivos_usuario == 3)
			Resultado = MiniJuego1(0);
		if(len_dispositivos_usuario == 2)
			Resultado = printf("mini juego 2 de jorgito <3 que retorne 0 si gano usuario y 1 si perdió :3\n");
		if(len_dispositivos_usuario == 1)
			Resultado = MiniJuego3(0);
		if(Resultado == 0){
			printf("¡Dispositivo se puede utilizar!");
			//colocamos el nombre de la funcion del dispositivo elegido y en esta funcion llamamos a delete para eliminar
			//dispositivo utilizado.
		}
		if(Resultado == 1)
			delete(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial,jugador,opcion);
	}
	else{
		InteligenciaArtificial(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial);
	}
}


int moneda(){
	char opcion;
	char moneda[2] = {'c','s'};
	printf("Indicar con la primera letra en mayúscula que lado de la moneda quiere ser (C) CARA o (S) SELLO = ");
	scanf("%c%*c",&opcion);

	if(opcion == moneda[rand()%2]){
		printf("\n¡Ganaste!");
		return 0;
	}
	else{
		printf("\nGanó IA ");
		return 1;
	}
}


void InteligenciaArtificial(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial){
	OpcionesMovimiento(tablero,jugadores,1);
	MostrarTablero(jugadores);
	Usuario(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial,0);
}


void Usuario(int **tablero,int **jugadores,char *Dispositivos_usuario,char *Dispositivos_artificial, int estado){
	int opcion;
	
	if(estado == 0){
		printf("¿Qué desea hacer? Indicar con el numero que está en parentesis:\n");
		printf("(1) Moverse\n(2) Utilizar Dispositivo\n(3)Rendirse\nOpcion = ");
		scanf("%i",&opcion);
		if(opcion == 1){
			OpcionesMovimiento(tablero,jugadores,0);
			MostrarTablero(jugadores);
			InteligenciaArtificial(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial);
		}
		if(opcion == 2){
			Dispositivos(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial,0);

		}
		if(opcion == 3){
			printf("Iría a funcion fin\n");
		}
	}
	else{
		printf("\nTe quedán dos opciones = ");
		printf("\n(1)Moverse\n(2)Rendirse\nOpcion = ");
		scanf("%i",&opcion);
		if(opcion == 1){
			OpcionesMovimiento(tablero,jugadores,0);
			MostrarTablero(jugadores);
			InteligenciaArtificial(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial);
		}
			
		else
			printf("Iría a rendirse\n");
	}
}




void MostrarOpciones(int **jugadores,int PosicionFila1,int PosicionColumna1, int ** tablero){
    int i,j;
    //SE CREA LA MATRIZ TRANSICION QUE ALMACENA DATOS DE MOVIMIENTOS.
    char ** transicion = (char**)malloc(filas * sizeof(char*));
    for (int i = 0; i < filas; ++i)
        transicion[i] = (char*)malloc(columnas * sizeof(char));

    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            transicion[i][j] = '.';
        }
    }

                //arriba
    if(PosicionFila1 >0){
    if(transicion[PosicionFila1 -1][PosicionColumna1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]+2) )
            transicion[PosicionFila1 -1][PosicionColumna1] = 'U';
        }
    }
                //abajo
    if(PosicionFila1 <7){
    if(transicion[PosicionFila1 +1][PosicionColumna1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]+2) )
            transicion[PosicionFila1 +1][PosicionColumna1] = 'D';
    }    
    }

                //izquierda
    if(PosicionColumna1<7){
    if(transicion[PosicionFila1][PosicionColumna1 +1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]+2) )
            transicion[PosicionFila1][PosicionColumna1 +1] = 'L';
    }    
    }
                //derecha
    if(PosicionColumna1>0){
    if(transicion[PosicionFila1][PosicionColumna1 -1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]+2) )
            transicion[PosicionFila1][PosicionColumna1 -1] = 'R';
    }
    }

    //SIMBOLO QUE MARCA POSICIÓN ACTUAL.
    transicion[PosicionFila1][PosicionColumna1] = 'J'; 

    printf("Tablero que muestra opciones validas de movimientos.\n");

    for(i = -2; i < filas; i++){
        //columnas
        if (i == -2 || i ==-1) {
            printf("      ");
        }else {
            printf("%3i",i);
            printf("%3s","|" );
        }
        for(j = 0; j < columnas; j++){
            //filas
            if (i == -2){
                printf("%3i",j);
            }else if (i == -1) {
                printf("%3s","=");

            }else{ 
                printf("%3c", transicion[i][j]);
            }
        }
        printf("\n");
    }

    char MovimientoSeleccionado;
    int validez = 0;
    
    while(validez == 0){ 
    printf("ingrese: \n [U] para arriba.\n [D] para abajo.\n [L] para izquierda.\n [R] para derecha.\n");
    printf("Ingrese el movimiento que desea hacer en el tablero :");
    scanf("%c%*c",&MovimientoSeleccionado);

    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            if (transicion[i][j] == MovimientoSeleccionado){
                printf("El movimiento ingresado es valido!\n");
                //guardo nueva posicion del jugador.
                jugadores[i][j] = 1;
                validez++;
            }
        }    
    }
    if(validez == 0)
    printf("Ha ingresado una opcion invalida, por favor reintente !\n");

    }
    //elimino la posicion anterior.
    jugadores[PosicionFila1][PosicionColumna1] = 0;
}

void MostrarOpcionesMaquina(int**jugadores,int PosicionFila1, int PosicionColumna1,int**tablero){
    int i,j;

    char MovimientoSeleccionado;
       //SE CREA LA MATRIZ TRANSICION QUE ALMACENA DATOS DE MOVIMIENTOS.
    char ** transicion = (char**)malloc(filas * sizeof(char*));
    for (int i = 0; i < filas; ++i)
        transicion[i] = (char*)malloc(columnas * sizeof(char));

    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            transicion[i][j] = '.';
        }
    }

                //arriba
    if(PosicionFila1 >0){
    if(transicion[PosicionFila1 -1][PosicionColumna1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1-1][PosicionColumna1]+2) )
            transicion[PosicionFila1 -1][PosicionColumna1] = 'U';
            //MovimientoSeleccionado = 'U';
        }
    }
                //abajo
    if(PosicionFila1 <7){
    if(transicion[PosicionFila1 +1][PosicionColumna1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1+1][PosicionColumna1]+2) )
            transicion[PosicionFila1 +1][PosicionColumna1] = 'D';
            //MovimientoSeleccionado = 'D';
    }    
    }

                //izquierda
    if(PosicionColumna1<7){
    if(transicion[PosicionFila1][PosicionColumna1 +1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1+1]+2) )
            transicion[PosicionFila1][PosicionColumna1 +1] = 'L';
            //MovimientoSeleccionado = 'L';
    }    
    }
                //derecha
    if(PosicionColumna1>0){
    if(transicion[PosicionFila1][PosicionColumna1 -1] == '.'){
        if( (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]-1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]-2) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]+1) || (tablero[PosicionFila1][PosicionColumna1]) == (tablero[PosicionFila1][PosicionColumna1-1]+2) )
            transicion[PosicionFila1][PosicionColumna1 -1] = 'R';
            //MovimientoSeleccionado = 'R';
    }
    }

    //SIMBOLO QUE MARCA POSICIÓN ACTUAL.
    transicion[PosicionFila1][PosicionColumna1] = 'M'; 

    //se crea la variable que guardara la distancia del punto a la meta.
    //la distancia jamas sera mayor a 10 ;)
    int u= 10;
    int d= 10;
    int l= 10;
    int r= 10; 

    //funcion que determina el movimiento que mas acerca a la maquina a la meta.
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            if(transicion[i][j] == 'U'){
                u = sqrt( ((MetaFila-i)*(MetaFila-i))+((MetaColumna-j)*(MetaColumna-j)));
            }
            if(transicion[i][j] == 'D'){
                d = sqrt( ((MetaFila-i)*(MetaFila-i))+((MetaColumna-j)*(MetaColumna-j)));
            }
            if(transicion[i][j] == 'L'){
                l = sqrt( ((MetaFila-i)*(MetaFila-i))+((MetaColumna-j)*(MetaColumna-j)));
            }
            if(transicion[i][j] == 'R'){
                r = sqrt( ((MetaFila-i)*(MetaFila-i))+((MetaColumna-j)*(MetaColumna-j)));
            }
        }
    }    

    //TOMA DECISION MAQUINA
    
    if(u <= d && u<=l && u<=r && u != 0)
        MovimientoSeleccionado = 'U';
    else if(d <= u && d<=l && d<=r && d != 0)
        MovimientoSeleccionado = 'D';
    else if(l <= u && l<=d && l<=r && l != 0)
        MovimientoSeleccionado = 'L';
    else if(r <= d && r<=l && r<=u && r != 0)
        MovimientoSeleccionado = 'R';


    printf("Tablero que muestra opciones validas de movimientos.\n");

    for(i = -2; i < filas; i++){
        //columnas
        if (i == -2 || i ==-1) {
            printf("      ");
        }else {
            printf("%3i",i);
            printf("%3s","|" );
        }
        for(j = 0; j < columnas; j++){
            //filas
            if (i == -2){
                printf("%3i",j);
            }else if (i == -1) {
                printf("%3s","=");

            }else{ 
                printf("%3c", transicion[i][j]);
            }
        }
        printf("\n");
    }
    

    //printf("ingrese: \n [U] para arriba.\n [D] para abajo.\n [L] para izquierda.\n [R] para derecha.\n");
    printf("LA MAQUINA ESTA REALIZANDO SU JUGADA\n");

    printf("La computadora eligio el movimiento %c.\n",MovimientoSeleccionado);
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            if (transicion[i][j] == MovimientoSeleccionado){
                printf("El movimiento ingresado por la computadora es valido!\n");
                //guardo nueva posicion del jugador.
                jugadores[i][j] = 2;

            }
        }    
    }

    //elimino la posicion anterior.
    jugadores[PosicionFila1][PosicionColumna1] = 0;

}

//funcion que valida movimiento de usuarios.
void OpcionesMovimiento(int**tablero,int**jugadores, int jugador){
    //jugador 1
    if (jugador == 0){
        int aux =0;
        int PosicionFila1 = 0;
        int PosicionColumna1 = 0;

        while(aux == 0){
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < columnas; ++j){
                    if(jugadores[i][j] == 1){
                        PosicionFila1 = i;
                        PosicionColumna1 = j;
                        aux++;
                    }

                }
            }
        }

        printf("El jugador 1 se encuentra en la poscion (%i,%i). \n",PosicionFila1,PosicionColumna1);
        printf("El objetivo se encuentra en la posicion (%i,%i).\n",MetaFila,MetaColumna);
        MostrarOpciones(jugadores,PosicionFila1,PosicionColumna1,tablero);
    }



    //jugador 2
    if(jugador == 1){
        int aux =0;
        int PosicionFila2 = 0;
        int PosicionColumna2 = 0;

        while(aux == 0){
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < columnas; ++j){
                    if(jugadores[i][j] == 2){
                        PosicionFila2 = i;
                        PosicionColumna2 = j;
                        aux++;
                    }

                }
            }
        }

        printf("El jugador 2 se encuentra en la posicion (%i,%i). \n",PosicionFila2,PosicionColumna2);
        printf("El objetivo se encuentra en la posicion (%i,%i).\n",MetaFila,MetaColumna);
        MostrarOpcionesMaquina(jugadores,PosicionFila2,PosicionColumna2,tablero);
    }

}

//Funcion que establece un sistema de turnos.
/*void Turnos(int**tablero,int**jugadores){
    //verificar turno jugador 1 [0]; jugador 2 [1].
    int turno = 0;

    //se debe preguntar si desea ocupar un dispositivo
    //se debe preguntar si desea rendirse 
    //debe mostrar opciones validas de movimiento.

    OpcionesMovimiento(tablero, jugadores,turno);
    MostrarTablero(jugadores);
    turno = 1;
    OpcionesMovimiento(tablero, jugadores,turno);
    MostrarTablero(jugadores);

}*/

/*void EleccionDispositivos(int **tablero, int **jugadores){

    Turnos(tablero, jugadores);
}*/

void EleccionDispositivo(int **tablero,int **jugadores,int jugador){
	char D1,D2,D3;
	char Dispositivos[5]= {'G','Q','H','P','A'};
	int PosicionAzar = rand()%5;

	printf("\n\n");
	printf("¡ Jugador 1 ! Deberas elegir ahora tus  3 dispositivos. Las opciones son:\n");
	printf("(G) Gaius: Seleccionas hasta tres módulos y eliges si estos suben o bajan un metro de altura.\n");
	printf("(Q) Quadratus: Puedes nombrar uno de los dispositivos del oponente para impedir su uso durante todo el juego.\n");
	printf("(H) Hydrus: Impides el movimiento del oponente, pero podrá seleccionar un dispositivo para utilizarlo en el próximo turno.\n");
	printf("(P) Phalanx: Puedes subir de un módulo a otro mientras estos tengan una diferencia de hasta 3 metros siendo el último el de mayor altura.\n");
	printf("(A) Argus: Tienes la posibilidad de elegir un dispositivo que el oponente no seleccionó y otro que no haya utilizado en toda la partida, para intercambiarlos.\n ");
	char * Dispositivos_usuario = (char *)malloc(3 * sizeof(char));
	char * Dispositivos_artificial = (char *)malloc(3 * sizeof(char));

	printf("¿Cuál es su primer dispositivo? Indicar con la primera letra de su nombre en mayuscula = ");
	scanf("%c%*c",&D1);
		int a=0;
		while(a==0){
			if(D1 == Dispositivos[0] || D1 == Dispositivos[1] || D1 == Dispositivos[2] || D1 == Dispositivos[3] || D1 == Dispositivos[4])
				a++;
			else{
				printf("\nEntregar una letra que esté en las opciones = ");
				scanf("%c%*c",&D1);
			}
		}

	printf("\nSegundo dispositivo = ");
	scanf("%c%*c",&D2);

	a--;

	while(a==0){
			if(D2 == Dispositivos[0] || D2 == Dispositivos[1] || D2 == Dispositivos[2] || D2 == Dispositivos[3] || D2 == Dispositivos[4])
				a++;
			else{
				printf("\nEntregar una letra que esté en las opciones = ");
				scanf("%c%*c",&D2);
			}
		}

	while(D1 == D2){
    	printf("Elegir un dispositivo distinto al primero por favor = ");
    	scanf("%c%*c",&D2);
	}

	printf("\nTercer dispositivo = ");
	scanf("%c%*c",&D3);

	a--;

	while(a==0){
			if(D3 == Dispositivos[0] || D3 == Dispositivos[1] || D3 == Dispositivos[2] || D3 == Dispositivos[3] || D3 == Dispositivos[4])
				a++;
			else{
				printf("\nEntregar una letra que esté en las opciones = ");
				scanf("%c%*c",&D3);
			}
		}

	while(D1 == D3 || D2 == D3){
    	printf("Elegir un dispositivo distinto al primero y segundo por favor = ");
    	scanf("%c%*c",&D3);
		}

	Dispositivos_usuario[0] = D1;
	Dispositivos_usuario[1] = D2;
	Dispositivos_usuario[2] = D3;

    if(jugador == 1){

    	Dispositivos_artificial[0] = Dispositivos[PosicionAzar];
    	PosicionAzar = rand()%5;

    	while (Dispositivos_artificial[0] == Dispositivos[PosicionAzar]){
        	PosicionAzar = rand()%5;
    	}

    	Dispositivos_artificial[1] = Dispositivos[PosicionAzar];

    	PosicionAzar = rand()%5;
    
    	while (Dispositivos_artificial[0] == Dispositivos[PosicionAzar] || Dispositivos_artificial[1] == Dispositivos[PosicionAzar]){
        	PosicionAzar = rand()%5;
    	}

    	Dispositivos_artificial[2] = Dispositivos[PosicionAzar];

    	printf(" los dispositivos de artificial son %c , %c, %c \n",Dispositivos_artificial[0],Dispositivos_artificial[1],Dispositivos_artificial[2]);
	}

	else{
		PosicionAzar = rand()%4;
		Dispositivos_artificial[0] = Dispositivos_usuario[PosicionAzar];

		PosicionAzar = rand()%5;
		int a = 0;
		while (a==0){
			if(Dispositivos[PosicionAzar] == Dispositivos_usuario[0] || Dispositivos[PosicionAzar] == Dispositivos_usuario[1] || Dispositivos[PosicionAzar] == Dispositivos_usuario[2])
				PosicionAzar = rand()%5;
			
			else
				a++;
		}

		Dispositivos_artificial[1] = Dispositivos[PosicionAzar];

		PosicionAzar = rand()%5;
		a--;
		while(a == 0){
			if(Dispositivos[PosicionAzar] == Dispositivos_artificial[0] || Dispositivos[PosicionAzar] == Dispositivos_artificial[1]){
				PosicionAzar = rand()%5;
			}
			else
				a++;
		}

		Dispositivos_artificial[2] = Dispositivos[PosicionAzar]; 

		printf("los valores de los dispositivos de IA son %c , %c , %c", Dispositivos_artificial[0],Dispositivos_artificial[1],Dispositivos_artificial[2]);
	}

	if(jugador == 0)
		Usuario(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial,0);

	else{
		InteligenciaArtificial(tablero,jugadores,Dispositivos_usuario,Dispositivos_artificial);
	}
}




void Simulacion(){

    //inicializar filas
    int ** jugadores = (int**)malloc(filas * sizeof(int*));
    int ** tablero = (int**)malloc(filas * sizeof(int*));

    //inicializar columnas
    for (int i = 0; i < filas; ++i){
        jugadores[i] = (int*)malloc(columnas * sizeof(int));
        tablero[i] = (int*)malloc(columnas * sizeof(int));
    }
    //printf("El tablero ha sido creado con exito.\n");

    RellenarTablero(tablero);
    PosicionarJugadores(jugadores);
    int jugador = moneda();
    EleccionDispositivo(tablero,jugadores,jugador);
}

int main(int argc, char const *argv[])
{   
    srand ( time(NULL) );
    Simulacion();
    
    return 0;
}