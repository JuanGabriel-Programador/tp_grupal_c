#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include "funciones.h"
#include "empresa.h"
#include "inversion.h"

#define MAX_CLIENTES 50  //Definimos globalmente una constante para un maximo de 50 clientes en sistema

// ESTRUCTURA DE CLIENTE

typedef struct{
    char nombre[51];
    char apellido[51];
    char correo[51];
    char cuit[15];
    char password[20];
    float saldo_cuenta;
    inversion inversiones[500]; //Solo puede tener 500 inversiones por cliente
    int num_inversiones;
    inversion inversiones_historial[500];
    int num_inversiones_historial;
} cliente;


//FUNCIONES DE CLIENTE
void alta_cliente (cliente clientes[], int *num_clientes); //Funcion para agregar clientes al sistema
void listado_clientes (cliente clientes[], int *num_clientes); //Listado de clientes actuales
void baja_cliente (cliente clientes[], int *num_clientes); //Funcion para eliminar clientes del sistema
void cargar_clientes (cliente clientes[], int *num_clientes); //Funcion para cargar clientes
void guardar_clientes (cliente clientes[], int *num_clientes); //Funcion para guardar clientes
void modificar_cliente (cliente clientes[], int *num_clientes); //Funcion para modificar clientes
int autenticacion_cliente (cliente clientes[], int *num_clientes); //Funcion que retorna la posicion del cliente para su auntenticacion
void menu_cliente (cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas); //Ingreso al menu cliente una vez logeado en la funcion autenticar_cliente
void carga_saldo (cliente clientes[], int posicion_cliente, int *num_clientes);  //Funcion para cargar saldo al cliente
void extraer_saldo (cliente clientes[], int posicion_cliente, int *num_clientes); //Funcion para extraer saldo del cliente

//FUNCIONES PARA LAS INVERSIONES DEL CLIENTE

void cargar_inversion (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas);
void guardar_inversion(cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas);
void cargar_inversion_historial (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas);
void guardar_inversion_historial(cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas);
void ver_portafolio (cliente clientes[], int posicion_cliente);
void vender_acciones (cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas); //Funcion para la venta de acciones del cliente


#endif // CLIENTES_H_INCLUDED
