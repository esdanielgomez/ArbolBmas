#include <iostream>
#include "Arbol.h"
#include "Datos.h"
#include <stdlib.h>
#include <stdio.h>

bool Arbol::agregar(int k)
{
    Info info = buscar(k);
    //Lugar donde se debe insertar el elemento.
    int i = info.indice;

    //Repeticion
    bool encontrado = info.encontrado;

    //Direccion
    Nodo *n = info.donde;

    //El elemento se encuentra repetido en el arbol
    if(encontrado)
        return false;

    //Se crea un registro con la llave a ingresar
    Registro *r = crearRegistro(k);

    //En la ubicacion obtenida anterioremte, se especifica si ese nodo esta lleno o no

    //printf("---> %d",info.indice);

    //printf("\nK: %d", k);
    //printf("\nI: %d", i);

    if(nodo_lleno(n))
        agregar_en_nodo_lleno(n, k, i, r);
    else
        agregar_en_nodo_no_lleno(n, k, i, r);

    //Nodo insertado
    return true;
}

void Arbol::agregar_en_nodo_no_lleno(Nodo *n, int k, int i, Registro *r)
{
    //Mover los elementos a la derecha desde i
    desplazar_en_hoja_a_la_derecha(n, i, n->cuantas_llaves-1, 1);

    //Agregar el registro en i
    n->llaves[i] = k;
    n->datos[i] = r;
    //Nueva llave en el nodo
    ++(n->cuantas_llaves);
}

void Arbol::agregar_en_nodo_lleno(Nodo *n, int k, int i, Registro *r)
{
    Nodo *p, *n_s;
    int k_s;
    bool parar;

    if(n == raiz){
        //Dividir el primer y unico nodo cuando este lleno
        agregar_y_partir_raiz(n, k, i, r);
    }else{
        do{
            p = n->padre;

            if(n->es_hoja){
                //Dividir el nodo de las hojas
                parar = agregar_y_partir_hoja(n, k, i, r, n_s, k_s);

                //true: Se inserto la hoja, se dividio el padre y el padre no se lleno
                //false: el padre se lleno

            }
            else{
                //Dividir el nodo padre de las hojas y/o nodos abuelos
                parar = agregar_y_partir_intermedio(n, n_s, k_s);
            }
            n = p;
        }while(parar == false);
    }
}

void Arbol::agregar_y_partir_raiz(Nodo *n, int k, int i, Registro *r)
{
    //En copia se inserta el nuevo registro, pero toca dividir ya que esta en orden +1
    Nodo *copia = new Nodo;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->datos = new Registro*[orden+1];
    copiar_hoja(n, copia, 0, orden-1, 0);

    desplazar_en_hoja_a_la_derecha(copia, i, orden-1, 1);

    copia->llaves[i] = k;
    copia->datos[i] = r;

    //Se crea el nuevo nodo para agregarlo a la izquierda del ultimo nivel
    Nodo *hermano = new Nodo;
    hermano->llaves = new int[orden];
    hermano->datos = new Registro*[orden];

    //Con mitad, se definen las hojas que van a un nodo y las otras que van al nuevo nodo
    int mitad = (orden+1)/2;

    //Primer nodo
    copiar_hoja(copia, n, 0, mitad-1, 0);

    //Segundo nodo
    copiar_hoja(copia, hermano, mitad, orden, 0);
    n->cuantas_llaves = mitad;
    hermano->cuantas_llaves = orden+1 - mitad;

    hermano->siguiente = n->siguiente;
    //Puntero del primer nodo hacia el segundo nuevo nodo
    n->siguiente = hermano;
    hermano->anterior = n;

    //Nuevo padre que a la final tambien es la actualizacion de la raiz
    Nodo *nueva_raiz = new Nodo;
    nueva_raiz->es_hoja = false;
    nueva_raiz->llaves = new int[orden];
    nueva_raiz->hijos = new Nodo*[orden+1];

    nueva_raiz->llaves[0] = hermano->llaves[0];
    nueva_raiz->cuantas_llaves = 1;
    nueva_raiz->hijos[0] = n;
    nueva_raiz->hijos[1] = hermano;
    n->padre = nueva_raiz;
    hermano->padre = nueva_raiz;

    raiz = nueva_raiz;
    principio = n;
    final = hermano;

    delete copia;
}

bool Arbol::agregar_y_partir_hoja(Nodo *n,int k,int i,Registro *r,Nodo *&n_s,int &k_s)
{
    Nodo *p = n->padre;

    //Valor del indice menor del nodo padre
    int i_padre = buscar_hijo_en_nodo(p, n->llaves[0]);

    //En copia se inserta el nuevo registro, pero toca dividir ya que esta en orden +1
    Nodo *copia = new Nodo;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->datos = new Registro*[orden+1];

    //Se inserta el registro en el nodo
    copiar_hoja(n, copia, 0, orden-1, 0);
    desplazar_en_hoja_a_la_derecha(copia, i, orden-1, 1);
    copia->llaves[i] = k;
    copia->datos[i] = r;

    //Se crea el nuevo nodo para agregarlo a la izquierda del ultimo nivel
    Nodo *hermano = new Nodo;
    hermano->llaves = new int[orden];
    hermano->datos = new Registro*[orden];

    //Con mitad, se definen las hojas que van a un nodo y las otras que van al nuevo nodo
    int mitad = (orden+1)/2;
    copiar_hoja(copia, n, 0, mitad-1, 0);
    copiar_hoja(copia, hermano, mitad, orden, 0);
    n->cuantas_llaves = mitad;
    hermano->cuantas_llaves = orden+1 - mitad;

    hermano->siguiente = n->siguiente;
    n->siguiente = hermano;
    hermano->anterior = n;

    //El nodo antes de la insercion era el ultimo de la izquierda
    if(n == final)
        final = hermano;
    else
        hermano->siguiente->anterior = hermano;//No era el ultimo de la izquierda

    k_s = hermano->llaves[0];
    n_s = hermano;

    delete copia;

    //Si el nodo no esta lleno se inserta el indice en el padre
    if(!nodo_lleno(p)){
        desplazar_en_intermedio_a_la_derecha(p, i_padre, p->cuantas_llaves-1, 1);
        p->llaves[i_padre] = k_s;
        p->hijos[i_padre+1] = n_s;
        ++(p->cuantas_llaves);
        n_s->padre = p;
        return true; //Insercion completa
    }
    return false;
}

bool Arbol::agregar_y_partir_intermedio(Nodo *n, Nodo *&n_s, int &k_s)
{
    Nodo *p = n->padre;
    int i_padre;

    //Con copia se tendra el nuevo nodo dividido (desde el intermedio del nodo)
    Nodo *copia = new Nodo;
    copia->es_hoja = false;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->hijos = new Nodo*[orden+2];
    copiar_intermedio(n, copia, 0, orden-1, 0);

    //Valor del indice menor del nodo padre (el abuelo de las hojas, el visabuelo, etc.. Segun el while del agregar)
    i_padre = buscar_hijo_en_nodo(copia, k_s);

    //Desplazar a la derecha para poder insertar el nuevo indice en la posicion del i_padre
    desplazar_en_intermedio_a_la_derecha(copia, i_padre, orden-1, 1);
    copia->llaves[i_padre] = k_s;//Primer elemento del nodo en las hojas y elemento que asciende
    copia->hijos[i_padre+1] = n_s;

    Nodo *hermano = new Nodo;
    hermano->es_hoja = false;
    hermano->llaves = new int[orden];
    hermano->hijos = new Nodo*[orden+1];

    int mitad = (orden+1)/2;
    //El nodo de la izquierda
    copiar_intermedio(copia, n, 0, mitad-1, 0);

    //El nodo de la derecha
    copiar_intermedio(copia, hermano, mitad+1, orden, 0);

    //Llaves del primer nodo
    n->cuantas_llaves = mitad;

    //Llaves del segundo nodo (derecha)
    hermano->cuantas_llaves = orden - mitad;

    //Actualizacion de los padres de los hijos del nodo izquierdo
    for(int j=0; j<=n->cuantas_llaves; ++j)
        n->hijos[j]->padre = n;
    //Actualizacion de los padres de los hijos del nodo derecho
    for(int j=0; j<=hermano->cuantas_llaves; ++j)
        hermano->hijos[j]->padre = hermano;

    hermano->siguiente = n->siguiente;
    n->siguiente = hermano;
    hermano->anterior = n;

    if(hermano->siguiente != NULL)
        hermano->siguiente->anterior = hermano;
    n_s = hermano;
    k_s = copia->llaves[mitad];

    delete copia;


    if(p != NULL && !nodo_lleno(p)){
        i_padre = buscar_hijo_en_nodo(p, k_s);
        desplazar_en_intermedio_a_la_derecha(p, i_padre, p->cuantas_llaves-1, 1);
        p->llaves[i_padre] = k_s;
        p->hijos[i_padre+1] = n_s;
        n_s->padre = p;
        ++(p->cuantas_llaves);
        return true;
    }


    if(n == raiz){
        Nodo *nueva_raiz = new Nodo;
        nueva_raiz->es_hoja = false;
        nueva_raiz->llaves = new int[orden];
        nueva_raiz->hijos = new Nodo*[orden+1];

        nueva_raiz->llaves[0] = k_s;
        ++(nueva_raiz->cuantas_llaves);
        nueva_raiz->hijos[0] = n;
        nueva_raiz->hijos[1] = n_s;
        n->padre = nueva_raiz;
        n_s->padre = nueva_raiz;

        raiz = nueva_raiz;
        return true;
    }
    //Aun falta por dividir
    return false;
}
