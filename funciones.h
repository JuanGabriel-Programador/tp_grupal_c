#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "clientes.h"
#include "empresa.h"
#include "inversion.h"

//UTILIDADES
void limpiar_consola(); //Limpieza de consola

//FUNCIONES DE MENUS
void menu_principal (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas); //Mostrar el menu principal
void menu_broker (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas); //Mostrar el menu de broker
void menu_inversion (cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas);  //Mostrar el menu de inversiones

//FUNCIONES DE FILTROS
void mostrar_inversiones_cliente (cliente clientes[], int *num_clientes); //Muestra las inversiones por cliente
void mostrar_inversiones_empresa (cliente clientes[], int *num_clientes); //Muestra las inversiones por ID empresa

#endif // FUNCIONES_H_INCLUDED
