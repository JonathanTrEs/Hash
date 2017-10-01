#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class aleatorio{
    private:
        int* vect_;
        int nelem_; //nº de elementos totales
    public:
        aleatorio(int);
        ~aleatorio();
        int get_nelem(int);
        void imprimir();
};

class celda
{
    private:
        int* bloques_;
        int bloq_ocupados_;
        int tam_; //tamaño de la celda para saber si está llena
        bool desbordada_; //indica que se ha intentado insertar en ella cuando estaba llena
    public:
        celda(int);
        ~celda();
        int get_tam();
        bool get_desbordada();
        void set_desbordada();
        bool llena(); //te dice si la celda esta llena
        int insertar(int, int);
        void imprimir();
        int buscar(int);
        int contar_llenas();
};

class tabla
{
    private:
        int nceldas_; // nº de celdas totales
        int tam_bloque_;
        int ocupadas_; // nº de celdas ocupadas
        int ncomparaciones_; //nº de comparaciones efectuadas
        celda** tabla_; // array de punteros a Celda (construcción dinámica)
    public:
        tabla(int numcel, int tambloq);
        ~tabla();
        int get_ocupadas();
        void imprimir();
        int hash(int dni);
	int hash_aux(int dni);
	int hash_aux_2(int dni, int r);
        int in_lineal(int dni, int modo);
        int busq_lineal(int dni);
        int in_cuadratica(int dni, int modo);
        int busq_cuadratica(int dni);
        int in_doble(int dni, int modo);
        int busq_doble(int dni);
        int in_redispersion(int dni, int modo);
        int busq_redispersion(int dni);
        void estadisticas(int busquedas, int comp, int min, float media, int max, int tipo);
        int casillasllenas();
};
