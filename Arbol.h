#ifndef ARBOL
#define ARBOL
#include "Datos.h"

class Arbol {
    Nodo *raiz;
    Nodo *principio;
    Nodo *final;
    int orden;

public:
    Arbol(int o);

    Info buscar(int k);
    bool agregar(int k);

    void imprimirArbol();

protected:

    Nodo *buscar_hoja(Nodo *n, int k);

    void agregar_en_nodo_lleno(Nodo *n, int k, int i, Registro *r);
    void agregar_en_nodo_no_lleno(Nodo *n, int k, int i, Registro *r);
    bool agregar_y_partir_hoja(Nodo *n, int k, int i, Registro *r, Nodo *&n_s, int &k_s);
    bool agregar_y_partir_intermedio(Nodo *n, Nodo *&n_s, int &k_s);
    void agregar_y_partir_raiz(Nodo *n, int k, int i, Registro *r);

    void inicializar();
};

#endif

//----------------------------------------------------------------------------------------------------------

#ifndef METODOS
#define METODOS

#include <iostream>
#include "Datos.h"

Registro *crearRegistro(int k);

bool nodo_lleno(Nodo *n);

int buscar_hijo_en_nodo(Nodo *n, int k);
int buscar_llave_en_nodo(Nodo *n, int k);

void desplazar_en_hoja_a_la_derecha(Nodo *n, int desde, int hasta, int e);
void desplazar_en_intermedio_a_la_derecha(Nodo *n, int desde, int hasta, int e);

void copiar_hoja(Nodo *origen, Nodo *destino, int desde, int hasta, int e);
void copiar_intermedio(Nodo *origen, Nodo *destino, int desde, int hasta, int e);

void imprimirNodo(Nodo *n);
void imprimirNivel(Nodo *n);

#endif
