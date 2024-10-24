#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "funciones.h"
#include "clientes.h"
#include "empresa.h"

void menu_ver_rendimiento(cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas){

    limpiar_consola();

    int seleccion = 1;

    while (seleccion != 0){
        printf ("VER RENDIMIENTO\n");
        printf ("\n");
        printf ("[ 1 ] Rendimiento diario valor\n");
        printf ("[ 2 ] Rendimiento diario porcentaje\n\n");
        printf ("[ 3 ] Rendimiento Histórico valor\n");
        printf ("[ 4 ] Rendimiento Histórico porcentaje\n\n");

        printf ("[ 0 ] Cerrar sesion y volver al menu principal\n");
        printf ("\n\nElija una opcion: ");
        scanf ("%d", &seleccion);

    switch (seleccion){
        case 1:
            limpiar_consola();
            ver_rendimiento(clientes,posicion_cliente,empresas,num_empresas);
            break;

        case 2:
            limpiar_consola();
            break;

        case 3:
            limpiar_consola();
            break;

        case 4:
            limpiar_consola();
            break;
        case 0:
            limpiar_consola();
            return menu_principal;

        default:
            printf ("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
            sleep(2);  //Esperar dos segundos antes de continuar
            limpiar_consola();
            break;
        }
    }

}


void ver_rendimiento(cliente clientes[], int posicion_cliente, empresa empresas[], int num_empresas) {
    printf("\n--- Ver Rendimiento ---\n");

    // 1. Cálculo del rendimiento diario
    float valor_diario = calcular_valor_diario(clientes, posicion_cliente, empresas, num_empresas);
    float porcentaje_diario = calcular_porcentaje_diario(clientes, posicion_cliente, empresas, num_empresas);

    printf("Rendimiento Diario:\n");
    printf("Valor Diario: %.2f\n", valor_diario);
    printf("Porcentaje Diario: %.2f%%\n\n", porcentaje_diario);
    system("pause");
    limpiar_consola();

}

float calcular_valor_diario(cliente clientes[], int posicion_cliente, empresa empresas[], int num_empresas) {
    float valor_actual = 0, valor_anterior = 0;

    // Sumar el valor actual y el del día anterior de todas las inversiones
    for (int i = 0; i < clientes[posicion_cliente].num_inversiones; i++) {
        char *id_empresa = clientes[posicion_cliente].inversiones[i].empresa_id;
        int indice_empresa = buscar_empresa_por_id(empresas, num_empresas, id_empresa);

        if (indice_empresa != -1) {
            valor_actual += empresas[indice_empresa].precio_actual *
                            clientes[posicion_cliente].inversiones[i].cantidad_acciones;
            valor_anterior += clientes[posicion_cliente].inversiones[i].precio_empresa_comprado *
                              clientes[posicion_cliente].inversiones[i].cantidad_acciones;
        }
    }

    return valor_actual - valor_anterior;  // Cambio en el valor diario
}

float calcular_porcentaje_diario(cliente clientes[], int posicion_cliente, empresa empresas[], int num_empresas) {
    float valor_actual = 0, valor_anterior = 0;

    for (int i = 0; i < clientes[posicion_cliente].num_inversiones; i++) {
        char *id_empresa = clientes[posicion_cliente].inversiones[i].empresa_id;
        int indice_empresa =buscar_empresa_por_id(empresas, num_empresas, id_empresa);
         if (indice_empresa != -1) {
            valor_actual += empresas[indice_empresa].precio_actual *
                            clientes[posicion_cliente].inversiones[i].cantidad_acciones;
            valor_anterior += clientes[posicion_cliente].inversiones[i].precio_empresa_comprado *
                              clientes[posicion_cliente].inversiones[i].cantidad_acciones;
        }
    }

    if (valor_anterior == 0) return 0;  // Evitar división por 0
    return ((valor_actual - valor_anterior) / valor_anterior) * 100;
}





int buscar_empresa_por_id(empresa empresas[], int num_empresas, const char *id_empresa) {
    for (int i = 0; i < num_empresas; i++) {
        if (strcmp(empresas[i].id, id_empresa) == 0) {
            return i; // Retorna el índice si encuentra la empresa
        }
    }
    return -1; // No encontró la empresa
}


