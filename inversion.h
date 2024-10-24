#ifndef INVERSION_H_INCLUDED
#define INVERSION_H_INCLUDED

#include "funciones.h"
#include "clientes.h"
#include "empresa.h"

#define MAX_INVERSIONES_CLIENTE 500

// Estructura de inversion
typedef struct{
    char empresa_id[5];  //Apunto ID unico de la estructura empresa
    int cantidad_acciones;
    float precio_compra;
    char fecha[11];
    float precio_empresa_comprado;
} inversion;

#endif // INVERSION_H_INCLUDED
