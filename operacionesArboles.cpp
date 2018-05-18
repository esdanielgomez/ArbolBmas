#include "Datos.h"
#include "Arbol.h"

//Crear dato del tipo Registro
Registro *crearRegistro(int valor) {
    Registro * r = new Registro;
    r->valor = valor;
    return r;
}

Info Arbol::buscar(int k) {
    Info info;


    ////La posicion en el nodo (El numero de la posicion)
    int i;

    //True si se encuentra el indice (el valor)
    bool valEncontrado;

    //El nodo donde se debe insertar el registro UBICACION   n->llaves[i] La posicion a la izquierda
    Nodo * n;

    //Nodo en donde se debe insertar la hoja
    n = buscar_hoja(raiz, k);

    //Posicion en el nodo (El valor donde se debe insertar la hoja)
    i = buscar_llave_en_nodo(n, k);

    //Llave de la derecha
    //n->llaves[i]

    valEncontrado = (i < n->cuantas_llaves && k == n->llaves[i]);
    //valEncontrado = (k == n->llaves[i]);

    info.encontrado = valEncontrado;
    info.indice = i;
    info.donde = n;

    return info;
}

//Buscar en una hoja el valor k
Nodo *Arbol::buscar_hoja(Nodo *n, int k)
{
    int i;

    //Se busca en los nodos
    while(n->es_hoja == false){
        i = buscar_hijo_en_nodo(n, k);
        n = n->hijos[i];
    }
    return n;
}


//Verifica si un nodo ya llega al orden O
bool nodo_lleno(Nodo *n) {
    return n->cuantas_llaves >= n->max_llaves;
}

//El valor k en los hijos del nodo n
int buscar_hijo_en_nodo(Nodo *n, int k){
    int i = 0;

    while(i < n->cuantas_llaves && k >= n->llaves[i])
        ++i;

    return i;
}

int buscar_llave_en_nodo(Nodo *n, int k)
{
    int i = 0;
    while(i < n->cuantas_llaves && k > n->llaves[i])
        ++i;
    return i;
}

void copiar_hoja(Nodo *origen, Nodo *destino, int desde, int hasta, int e)
{
    int j, k;
    for(j=desde, k = e; j <= hasta; ++j, ++k){
        destino->llaves[k] = origen->llaves[j];
        destino->datos[k]  = origen->datos[j];
    }
}

void copiar_intermedio(Nodo *origen, Nodo *destino, int desde, int hasta, int e)
{
    int j, k;
    for(j=desde, k = e; j <= hasta; ++j, ++k){
        destino->llaves[k] = origen->llaves[j];
        destino->hijos[k]  = origen->hijos[j];
    }
    destino->hijos[k] = origen->hijos[j];
}


void desplazar_en_hoja_a_la_derecha(Nodo *n, int desde, int hasta, int e){
    for(int j = hasta+e; j >= desde+e; --j){
        n->llaves[j] = n->llaves[j-e];
        n->datos[j]  = n->datos[j-e];
    }
}

void desplazar_en_intermedio_a_la_derecha(Nodo *n, int desde, int hasta, int e){
    for(int j = hasta+e; j >= desde+e; --j){
        n->llaves[j]  = n->llaves[j-e];
        n->hijos[j+1] = n->hijos[j-e+1];
    }
}

void imprimirNodo(Nodo *n)
{
    if(n->es_hoja)
        std::cout<<"h";
    std::cout<<"( ";
    for(int j=0; j<n->cuantas_llaves; j=j+1)
        std::cout<<n->llaves[j]<<" ";
    std::cout<<") ";
}

void imprimirNivel(Nodo *n)
{
    while(n){
        imprimirNodo(n);
        n = n->siguiente;
    }
    std::cout<<"\n        ";
}

void Arbol::imprimirArbol()
{
    printf("\n        ");
    Nodo *n = raiz;
    if(raiz->cuantas_llaves == 0){
        std::cout<<"\n        El arbol esta vacio.\n";
        return;
    }
    while(!(n->es_hoja)){
        imprimirNivel(n);
        n = n->hijos[0];
    }
    imprimirNivel(principio);
    std::cout<<"\n";
}
