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

	FILE *archivoE;
	FILE *archivoS;
	printf("------ Analizador Lexico --------------\n");
	printf("Preparando archivo   \n");
	archivoE=fopen("Entrada.txt","r");
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

		printf("\n");
		printf("\n  ARCHIVO DE SALIDA LISTO");
		printf("\n");
		system("pause");
		
}

void AnalizadorDeCaracter(char letra){
	
	
	if(letra=='{'|| letra=='}'){
		if(Estado==e0){
			Estado=e1;
		}
		if(Estado==e2 || Estado==e3){
			Estado=e0;
		}
		Estados();
	}
	if (letra=='('||letra==')'){
		if(Estado==e2 || Estado==e3||Estado==e0||Estado==e4||Estado==e5||Estado==e6){
			Estado=e2;
		}else if(Estado==e17){
			Estado=e0;
		}
		Estados();

	}
	if(letra==';'||letra==','){
		if(Estado==e2||Estado==e3||Estado==e4||Estado==e5||Estado==e6){
			Estado=e0;
		}
		Estados();
		
	}
	

	if( letra>='A' && letra<='Z' ){
		if(Estado==e0){
			Estado=e1;
		}else if(Estado==e1||Estado==e2||Estado==e3||Estado==e19){
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
		else if(Estado ==e1 || Estado == e2||Estado==e12|| Estado==e14||Estado==e18)
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
			else if(Estado == e1 || Estado == e2||Estado==e3)
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
	
	if(letra=='/'||letra=='*'){
		if(Estado==e0||Estado==e2||Estado==e3){
			Estado=e18;
		}else{
			exit(-1);
		}
	}
	
	if(letra=='<'){
		if(Estado==e0||Estado==e3||Estado==e2){
			Estado=e12;
		}else{
			exit(-1);
		}
	}
	if(letra=='>'){
		if(Estado==e0||Estado==e2||Estado==e3){
			Estado=e14;
		}else{
			exit(-1);
		}
	}
	
	
	if(letra=='!'){
		if(Estado==e0){
			Estado=e18;
		}else{
			exit(-1);
		}
	}
}
		
		
	void Reservadas(){
		for(int i=0;i<IndicadorTam;i++){
			//strcmp se encarga de comparar caracter por caracter dos Strings
			//reservadas[i] son las palabras reservadas que declaramos como variable global al inicio del programa
			//identificados es la palabra que el analizador lexico encontro
			if(strcmp(reservadas[i],palabraIngresada)==0){
				//Contar Encender
				if(strcmp(reservadas[0],palabraIngresada)==0)
					contadorEncender++;
				//Contar Apagar
				if(strcmp(reservadas[1],palabraIngresada)==0)
					contadorApagado++;
				
				//Contar Ciclo Repetir
				if(strcmp(reservadas[4],palabraIngresada)==0)
					contadorCiclos++;
				
				//Contar Ciclo Mientras
				if(strcmp(reservadas[6],palabraIngresada)==0)
					contadorCiclos++;
				
				//Contar Condicional
				if(strcmp(reservadas[7],palabraIngresada)==0)
					contadorCondicional++;
				
				//Cuenta las palabras reservadas que encuentre
				contadorPalabrasReservadas++;
				palabraIngresada[0]='\0';
				break;
			}
			if(i==(IndicadorTam)-1){
				exit(-1);
			}
		}
    }
	
	void Estados(){
		
		switch(Estado){
			case 1:contadorVariables++;
				break;
			case 2:contadorVariables++;
				break;
			case 3:contadorPalabrasReservadas++;
				break;
			case 4:contadorNumeros++;
				break;
			case 5:contadorNumeros++;
				break;
			case 6:contadorNumeros++;
				break;
			case 7:contadorSignos++;
				break;
			case 8:contadorSignos++;
				break;
			case 9:contadorSimbolos++;
				break;
			case 10:contadorSignos++;
				break;
			case 11:contadorSimbolos++;
				break;
			case 12:contadorSimbolos++;
				break;
			case 13:contadorSimbolos++;
				break;
			case 14:contadorSimbolos++;
				break;
			case 15:contadorSimbolos++;
				break;
			case 16:contadorSimbolos++;
				break;
			case 17:contadorSignos++;
				break;
			case 18:contadorSignos++;
				break;
			case 19:contadorSimbolos++;
				break;
			case 20:contadorNumeros++;
				break;
				default:
					break;
		}
		Estado =e0;
	}   


//Metodo para verificar si el token formado corresponde a una palabra reservada
/*bool verificarReservada(char palabra[]){
	int comp;
	bool esReservada=false;
	string str(palabra);
	for(int i=0; i<MAX_RES; i++)
	{
		comp = strcmp(PalabrasReservadas[i],palabra);
		if(comp == 0)
		{
			esReservada = true;
		break;
		}
	}
	return esReservada;
}*/
//fin void


