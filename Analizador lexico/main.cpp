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
const char *reservadas[] = {"PRINCIPAL","MIENTRAS","PARA","SI","SINO","IMPRIMIR","ALMACENAR","ENT","DEC","CAD","V_F","VERDADERO","FALSO","SISINO"};
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

void AnalizadorDeCaracter(char letra){
	
	
	if(letra=='{'|| letra=='}'){
		if(Estado==e0){
			Estado=e1;
		}
		if(Estado==e2 || Estado==e3){
			Estado=e0;
		}
	}
	if (letra=='('||letra==')'){
		if(Estado==e2 || Estado==e3){
			Estado=e2;
		}else if(Estado==e17){
			Estado=e0;
		}

	}
	if(letra==';'){
		if(Estado==e2||Estado==e3||Estado==e4||Estado==e5||Estado==e6){
			Estado=e0;
		}
		
	}
	

	if( letra>='A' && letra<='Z' ){
		if(Estado==e0){
			Estado=e1;
		}else if(Estado==e1||Estado==e2){
			Estado=e2;
		}
		else if(Estado!=e0 && Estado!=e1 && Estado!=e2){
			exit(-1);
		}
	}

	


	if(letra >= 'a' && letra <= 'z')
	{
		if(Estado == e0)
		{
			temp[0] = letra;
			strcat(palabraIngresada,temp);
			Estado = e3;
		}
		else if(Estado ==e1 || Estado == e2)
		{
			Estado = e2;
		}
		else if(Estado == e3)
		{
			temp[0] = letra;
			strcat(palabraIngresada,temp);
			Estado = e3;
		}
		else
		{
		exit(-1);
		}

}

	if(letra<= '9' && letra >= '0')
	{
		if(Estado == e0)
		{
			Estado = e4;
		}
			else if(Estado == e4 || Estado == e5)
		{
			Estado = e5;
		}
			else if(Estado == e13 || Estado == e6)
		{
			Estado = e6;
		}
			else if(Estado == e1 || Estado == e2)
		{
			Estado = e2;
		}
			else if(Estado == e7)
		{
			Estado = e4;
		}
		else
		{
			exit(-1);
		}
	}

	if(letra == '+')
	{
		if(Estado == e0)
		{
			Estado = e8;
		}
		else if(Estado == e8)
		{
			Estado = e17;
		}
	}

	if(letra == '.')
	{
		if((letra) < '1' || (letra) >= '9')
		{
			Estado = e19;
		}
		else
		{
			if(Estado == e4 || Estado==e5 && ((letra) == '1' || (letra) == '2' || (letra) == '3' || (letra) == '4' || (letra) == '5' || (letra) == '6' || (letra) == '7' || (letra) == '8' || (letra) == '9'))
			{
				Estado = e20;
			}
			else if(Estado!= e4 && Estado!= e5)
			{
				exit(-1);
			}
		}
	}

	if(letra == '^')
	{
		if(Estado == e0)
		{
			Estado = e18;
		}
		else
		{
			exit(-1);
		}
	}
	
	if(letra == '-')
	{
		if(Estado == e0){
			Estado = e7;
		}else if(Estado == e12){
			Estado = e10;}
	}	else if(Estado == e7){
		Estado = e17;
	}
	
	if(letra == '='){
		if(Estado == e0)
		{
			Estado = e9;
		}
		else if(Estado == e18)
		{
			Estado = e11;
		}
	}
	else if(Estado == e12)
	{
		Estado = e16;
	}else if(Estado == e13)
	{
		Estado = e15;
	}
	
	

}//fin void


