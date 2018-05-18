#ifndef DATOS_H_
#define DATOS_H_

struct Registro{
    int valor;
};

struct Nodo
{
    Nodo *padre;
    Nodo *siguiente;
    Nodo *anterior;

    static int max_llaves;

    //Numero de llaves del nodo
    int  cuantas_llaves;

    bool es_hoja;

    //Posiciones llaves
    int *llaves;
    struct {
        Registro **datos;
        Nodo **hijos;
    };

    Nodo();
    Nodo(int o);
};

struct Info
{
    bool encontrado;
    Nodo *donde;
    int indice;

    Info();
};

#endif
