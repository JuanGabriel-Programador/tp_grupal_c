#ifndef EMPRESA_H_INCLUDED
#define EMPRESA_H_INCLUDED

#include "funciones.h"
#include "clientes.h"
#include "inversion.h"

#define MAX_EMPRESAS 100

// Estructura de empresa
typedef struct{
    char id[5]; //ID unico de empresa
    char nombre[51];
    float precio_actual;
    float precio_anterior;
} empresa;

//Funciones para cargar y guardar empresas
void cargar_empresas (empresa empresas[], int *num_empresas);
void guardar_empresas (empresa empresas[], int *num_empresas);

//Funcion de alta de empresa
void alta_empresa (empresa empresas[], int *num_empresas);

//Funcion para eliminar empresa
void baja_empresa (empresa empresas[], int *num_empresas);

//Funcion para ver el listado de empresas
void listado_empresas(empresa empresas[], int *num_empresas);

//Funcion para modificar una empresa del sistema
void modificar_empresa(empresa empresas[],int *num_empresas);

#endif // EMPRESA_H_INCLUDED
