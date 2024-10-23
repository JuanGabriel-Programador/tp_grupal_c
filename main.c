#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"
#include "clientes.h"
#include "empresa.h"
#include "inversion.h"

int main()
{

    cliente clientes[MAX_CLIENTES];  //Defino un puntero clientes con maximo 50 clientes.
    int num_clientes = 0;
    cargar_clientes(clientes, &num_clientes);
    limpiar_consola();

    empresa empresas[MAX_EMPRESAS];
    int num_empresas = 0;
    cargar_empresas(empresas, &num_empresas);
    limpiar_consola();

    cargar_inversion(clientes, &num_clientes, empresas, &num_empresas);
    cargar_inversion_historial(clientes, &num_clientes, empresas, &num_empresas);
    limpiar_consola();
    menu_principal(clientes, &num_clientes, empresas, &num_empresas);


    return 0;
}
