#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

//Funciones
void imprimir();
void extra();
void AnalizadorDeCaracter(char letra);
void Estados();
void Reservados();


//Palabras Reservadas
const char *reservadas[] = {"inicio","encender","apagar","definir","repetir","fin","mientras","si","sino","string","int","boolean","decimal","true","false","para","posicion"};

int IndicadorTam=sizeof(reservadas)/sizeof(char *);
int i;
char palabraIngresada[50];
char temp[2];
enum TEstados{e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16,e17,e18,e19,e20};

enum TEstados Estado=e0;


//Estos son los contadores de los elementos de la tabla
int contadorVariables=0;
int contadorNumeros=0;
int contadorPalabrasReservadas=0;
int contadorSimbolos=0;
int contadorSignos=0;
int contadorEncender=0;
int contadorApagado=0;
int contadorCiclos=0;
int contadorCondicional=0;



int main() {
	//system(COLOR B0);
	printf("Hola, Mundo!\n");
	FILE *archivoE;
	FILE *archivoS;
	printf("------ Analizador Lexico --------------\n");
	printf("Preparando archivo   \n");
	archivoE=fopen("nombre de texto entrada.txt","r");
	archivoS=fopen("nombre de texto salida.txt","wt");
	
	char caracter;
	//validar archivo existente
	if(archivoE == NULL){
		perror ("ARCHIVO NO ENCONTRADO \n");
		return 1;
	}
	printf("ARCHIVO ENCONTRADO \n");
	
	//------------------------------
	while(1){
		//itera caracter por caracter
		caracter=fgetc(archivoE);
		if(caracter==EOF){
			break;
		}
		AnalizadorDeCaracter(caracter);
		if(caracter==';'){
			contadorSimbolos++;
		}
	}
	i++;
	//
	//System("COLOR OA");
	//
	//documento de salida
	fputs("\n\n------Analisis de salida-------------\n\n",archivoS);
	fprintf(archivoS, "Palabras Reservadas: %d", contadorPalabrasReservadas);
	fprintf(archivoS, "\nCiclos: %d", contadorCiclos/2);
	fprintf(archivoS, "\nVariables: %d", contadorVariables);
	fprintf(archivoS, "\nNumeros: %d", contadorNumeros);
	fprintf(archivoS, "\nAritmeticos: %d", contadorSignos);
	fprintf(archivoS, "\nSimbolos: %d", contadorSimbolos);
	fprintf(archivoS, "\nEncender: %d", contadorEncender);
	fprintf(archivoS, "\nApagado: %d", contadorApagado);
	fprintf(archivoS, "\nCondicional: %d", contadorCondicional/2);
	
	return 0;
}
