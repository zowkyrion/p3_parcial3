/* Autor: Pasantes Bucio Jaime 31/03/2022
	Hacer un programa que utilice la estructura de Alumno y almacene los datos de 100 alumnos
	Debe tener el siguiente menu:
	0. salir
	1. Agregar alumnos
	2. imprimir
	3. Alumnos Aoribados
	4. Alumnos Reprobados
	5. Promedio del grupo
	6. Porcentaje de alumnos Aprobados
	NOTA: Para hacer operaciones con las calif de los alumnos se siguen las siguientes reglas
			si el numero de faltas es <=6, la calificacion es la capturada
											Pero si no, la calificacion que se toma es 5
*/
#include<stdio.h>
#include<stdlib.h>
#include "milibreria.h"
//Declaraciones globales
#define MAX 100
struct alumno {
	char nombre[30];
	float promedio;
	int faltas;
};
int n=0; //variable que dice cuantos alumnos hay en el arreglo
//Prototipos
int menu();
void agregar(struct alumno x[]);
void imprimir(struct alumno x[], int tipo);
void guardar(struct alumno x[]);
void cargar(struct alumno x[]);

int main(){
	int op;
	struct alumno grupo[MAX];
	do{
		op=menu();
		switch(op){
			case 0: printf("Adios...\n");
					break;
			case 1: agregar(grupo);
					break;
			case 2: imprimir(grupo,0);
					break;
			case 3: imprimir(grupo,1);
					break;
			case 4: imprimir(grupo,2);
					break;
			case 5: //Promedio
					break;
			case 6: //Porcentaje
					break;
			case 7: guardar(grupo);
					break;
			case 8: cargar(grupo);
					break;												
		}
	}while(op!=0);
	return 0;
}
//funciones
int menu() {
	int opcion;
	printf("------ MENU -------\n");
	printf("0. Salir\n");
	printf("1. Agregar alumnos\n");
	printf("2. Imprimir\n");
	printf("3. Alumnos Aprobados\n");
	printf("4. Alumnos Reprobados\n");
	printf("5. Promedio del grupo\n");
	printf("6. Porcentaje de alumnos Aprobados\n");
	printf("7. Guardar datos\n");
	printf("8. Cargar datos\n");
	opcion=leerd("Selecciona una opcion: ",0,8);	
	return opcion;
}

void guardar(struct alumno x[]){
	FILE *f;
	f=fopen("alumnos.txt","w");
	if (f==NULL){
		printf("Error al intentar guardar los datos!!!\n");
	}
	else {
		for(int i=0;i<n;i++){
			fprintf(f,"%s\t%f\t%d\n",x[i].nombre,x[i].promedio,x[i].faltas);			
		}
		fclose(f);
		printf("-->Se guardaron %d registros\n",n);
		system("PAUSE");
	}
}

void cargar(struct alumno x[]) {
	FILE *f;
	struct alumno a;
	f=fopen("alumnos.txt","r");
	n=0;
	if (f==NULL) {
		printf("Error al intentar cargar los datos!!\n");
	}
	else {
		printf("Leyendo.....\n");
		while(fscanf(f,"%30[^\t]%f\t%d\n",a.nombre,&a.promedio,&a.faltas)!=EOF){
			x[n]=a;
			n++;
			printf("%3d\t%-30s\t%4.1f\t%2d\n",n,a.nombre,a.promedio,a.faltas);
		}
		fclose(f);
		printf("-->%d registros leidos\n",n);
		system("PAUSE");
	}
}


void agregar(struct alumno x[]) {
	int pregunta;
	while (n<MAX) {
		leers("Nombre: ",x[n].nombre,30);
		x[n].promedio=leerf("Promedio: ",0,10);
		x[n].faltas=leerd("Faltas: ",0,32);
		n++;
		pregunta=leerd("Agregar otro alumno? (1-SI, 0-NO): ",0,1);
		if (pregunta==0) {
			break;
		}
	}
	if (n==MAX) {
		printf("Arreglo lleno!!\n");
		system("PAUSE");
	}
}
// La funcion imprimir en el parametro tipo se le indica que va a imprimir
// 0 a todos, 1 aprobados, 2 reprobados
void imprimir (struct alumno x[],int tipo) {
	char mensaje[20];
	switch (tipo){
	case 0: strcpy(mensaje,"TOTALES   ");
			break;
	case 1: strcpy(mensaje,"APROBADOS   ");
			break;
	case 2: strcpy(mensaje,"REPROBADOS   ");
			break;				
	}
	printf("--------ALUMNOS %s------------------\n",mensaje);
	printf("No.\tNOMBRE 					\tFALTAS\tPROM\n");
	printf("-------------------------------------------------\n");
	for (int i=0;i<n;i++) {
		switch(tipo) {
			case 0: printf("%2d\t%-30s\t%2d\t%4.1f\n",i+1,x[i].nombre,x[i].faltas,x[i].promedio);
					break;
			case 1: if (x[i].promedio>=7) {
						printf("%2d\t%-30s\t%2d\t%4.1f\n",i+1,x[i].nombre,x[i].faltas,x[i].promedio);
					}
					break;
			case 2: if (x[i].promedio<7) {
						printf("%2d\t%-30s\t%2d\t%4.1f\n",i+1,x[i].nombre,x[i].faltas,x[i].promedio);
					}
					break;					
		}
	}
	printf("---------------------------------------\n");
	system("PAUSE");
}

