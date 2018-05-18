#include <iostream>
#include <fstream>
#include "Arbol.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

void menu(){

    system("cls");
    int i = 0;
	//Inicio cabecera
	printf("\n        %c",218);
	for(i = 1; i < 55; i++)
	{
		printf("%c",196);
	}
	printf("%c",191);
	printf("\n        %c                     MEN%c DE OPCIONES", 179,233);
	for(i = 1; i<18; i++)
	{
		printf(" ");
	}
	printf("%c\n", 179);
	//fin semicabecera
	printf("        %c",201);
	for(i = 1; i < 55; i++)
	{
		printf("%c",205);
	}
	printf("%c",187);
	printf("\n           (1) Insertar un elemento en el Arbol.");
	printf("\n           (2) Mostrar el Arbol.");
	printf("\n           (3) Salir. \n");
	printf("        %c",200);
	for(i = 1; i < 55; i++)
	{
		printf("%c",205);
	}
	printf("%c\n\n",188);
	//Fin cabecera
}

int main(int argc, char **argv)
{
    system("color 02");
    Arbol *a = new Arbol(3);

    menu();
    int optMenu;
    int numero = 0;
    while(optMenu != -1){
        printf("        Ingrese una opcion: ");
        cin >> optMenu;

        switch(optMenu){
            case 0:
                menu();
                break;
            case 1:
                printf("\n        ------------------------------------------\n");
                printf("\n        Numero a ingresar: ");
                cin >> numero;

                if(a->agregar(numero)){
                    printf("        Se ha agregado el elemento!\n");
                    a->imprimirArbol();
                }
                else
                    printf("\n        Elemento repetido, no se ha agregado el elemento!\n");
                printf("        ------------------------------------------\n");
                break;
            case 2:
                a->imprimirArbol();
                break;
            case 3:
                optMenu = -1;
            default:
                break;
        }
    }
}
