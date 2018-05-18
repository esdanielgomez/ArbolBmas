#include <iostream>
#include "Datos.h"
#include "Arbol.h"

int Nodo::max_llaves;

// Constructor info
Info::Info(){
    encontrado = false;
    donde = NULL;
    indice = -1;
}

// Construccion nodo
Nodo::Nodo()
{
    cuantas_llaves = 0;
    es_hoja = true;
    padre = siguiente = anterior = NULL;
}

Nodo::Nodo(int o)
{
    cuantas_llaves = 0;
    es_hoja = true;
    padre = siguiente = anterior = NULL;
    max_llaves = o;
}

//Constructor del arbol de orden O
Arbol::Arbol(int o)
{
    orden = o;
    inicializar();
}

// Inicializacion del arbol
void Arbol::inicializar()
{
    raiz = new Nodo(orden);
    raiz->llaves = new int[orden];
    raiz->datos  = new Registro*[orden];
    principio = final = raiz;
}
