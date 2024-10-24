#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"
#include "clientes.h"
#include "empresa.h"
#include "inversion.h"

//FUNCION LIMPIEZA DE CONSOLA
void limpiar_consola(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//MENU PRINCIPAL
void menu_principal(cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){

    int opcion = 1;

    while (opcion != 0){
        printf ("MENU PRINCIPAL\n\n");
        printf ("Bienvenido, por favor escoja una opcion: \n\n");
        printf ("[ 1 ] Ingresar como broker\n");
        printf ("[ 2 ] Ingresar como usuario\n\n");
        printf ("[ 0 ] Salir\n\n");
        printf("Ingrese una opcion: ");
        scanf ("%d", &opcion);

        switch (opcion){
            case 1:
                limpiar_consola();
                menu_broker(clientes, num_clientes, empresas, num_empresas);
                break;
            case 2:
                limpiar_consola();
                int posicion_cliente = autenticacion_cliente(clientes, num_clientes);
                if (posicion_cliente != -1){
                    limpiar_consola();
                    menu_cliente(clientes, posicion_cliente, num_clientes, empresas, num_empresas);
                }
                break;
            case 0:
                limpiar_consola();
                printf ("Gracias por utilizar el programa! Hasta luego.\n");
                return 0;
            default:
                printf ("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
                sleep(2);  //Esperar dos segundos antes de continuar
                limpiar_consola();
                break;
        }
    }
}

//MENU DEL BROKER
void menu_broker (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){

    int opcion = 1;

    while (opcion != 0){
        printf ("MENU BROKER\n\n");
        printf ("Bienvenido, por favor escoja una opcion: \n\n");
        printf ("CLIENTES\n");
        printf ("[ 1 ] Alta de clientes\n");
        printf ("[ 2 ] Baja de clientes\n");
        printf ("[ 3 ] Modificacion de clientes\n");
        printf ("[ 4 ] Listado de clientes actuales\n");
        printf ("\nEMPRESAS\n");
        printf ("[ 5 ] Alta de empresas\n");
        printf ("[ 6 ] Baja de empresas\n");
        printf ("[ 7 ] Modificacion de empresas\n");
        printf ("[ 8 ] Listado de empresas actuales\n");
        printf ("\nFILTROS\n");
        printf ("[ 9 ] Filtrar operaciones por cliente\n");
        printf ("[ 10 ] Filtrar operaciones por ID ticker\n");
        printf ("\n\n[ 0 ] Volver al menu principal\n\n");
        printf("Ingrese una opcion: ");
        scanf ("%d", &opcion);

        switch (opcion){
            case 1:
                limpiar_consola();
                alta_cliente(clientes, num_clientes);
                break;
            case 2:
                limpiar_consola();
                baja_cliente(clientes, num_clientes);
                break;
            case 3:
                limpiar_consola();
                modificar_cliente(clientes, num_clientes);
                break;
            case 4:
                limpiar_consola();
                listado_clientes(clientes, num_clientes);
                break;
            case 5:
                limpiar_consola();
                alta_empresa(empresas, num_empresas);
                break;
            case 6:
                limpiar_consola();
                baja_empresa(empresas, num_empresas);
                break;
            case 7:
                limpiar_consola();
                modificar_empresa(empresas, num_empresas);
                break;
            case 8:
                limpiar_consola();
                listado_empresas(empresas, num_empresas);
                break;
            case 9:
                limpiar_consola();
                mostrar_inversiones_cliente(clientes, num_clientes);

                break;
            case 10:
                limpiar_consola();
                mostrar_inversiones_empresa (clientes, num_clientes);
                break;
            case 0:
                limpiar_consola();
                return;

            default:
                printf ("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
                sleep(2);  //Esperar dos segundos antes de continuar
                limpiar_consola();
                break;
        }
    }
}

void mostrar_inversiones_cliente (cliente clientes[], int *num_clientes){

    limpiar_consola();

    char cuit[15];
    int cliente_actual = 0;
    bool encontrado = false;
    bool hay_inversion = false;

    printf ("LISTADO DE INVERIONES POR CLIENTE\n\n");

    encontrado = false;
    printf("Ingrese el CUIT del cliente para visualizar las inversiones: ");
    fflush (stdin);
    fgets (cuit, 15, stdin);
    cuit[strcspn(cuit, "\n")] = 0;

    for (int i = 0; i < *num_clientes; i++) {
        if (strcmp(clientes[i].cuit, cuit) == 0) {
            encontrado = true;
            cliente_actual = i;
        }
    }

    if (!encontrado){
        printf("\n\nERROR: No hay ningun CUIT en el sistema, por favor revise los datos e intentelo nuevamente.\n");
        printf("Volviendo al menu Broker en 3 segundos\n");
        sleep(3);
        limpiar_consola();
        return -1;
    }

    limpiar_consola();

    if (clientes[cliente_actual].num_inversiones >= 1){ //Busco si hay una inversion para mostrar del cliente
        hay_inversion = true;
    }

    if (hay_inversion){
        printf("LISTADO DE INVERSIONES DE %s, %s\n\n", clientes[cliente_actual].apellido, clientes[cliente_actual].nombre);
        printf("-----------------------------------------------\n");
        printf("| FECHA | EMPRESA | CANTIDAD COMPRADA | TOTAL | PRECIO COMPRA |\n");
        printf("-----------------------------------------------\n\n");

        for (int i = 0; i < clientes[cliente_actual].num_inversiones; i++){
            printf("%s | %s | %d | $%.2f\n",
                clientes[cliente_actual].inversiones[i].fecha,
                clientes[cliente_actual].inversiones[i].empresa_id,
                clientes[cliente_actual].inversiones[i].cantidad_acciones,
                clientes[cliente_actual].inversiones[i].precio_compra,
                clientes[cliente_actual].inversiones[i].precio_empresa_comprado);
        }
        printf ("\n");
        system("pause");
        limpiar_consola();
        return;
    }
    else{
        limpiar_consola();
        printf ("El cliente no tiene ninguna inversion.\n\n");
        system("pause");
        limpiar_consola();
        return;
    }
}

void mostrar_inversiones_empresa(cliente clientes[], int *num_clientes) {

    limpiar_consola();
    char empresa_id[5];
    int contador = 0;
    bool encontrado = false;

    printf("LISTADO DE INVERSIONES POR EMPRESA\n\n");

    encontrado = false;
    printf("Ingrese la abreviatura de la empresa para visualizar las inversiones: ");
    fflush(stdin);
    fgets(empresa_id, 5, stdin);
    empresa_id[strcspn(empresa_id, "\n")] = 0;  // Eliminar el salto de línea

    for (int i = 0; i < *num_clientes; i++) {
        for (int k = 0; k < clientes[i].num_inversiones; k++) {
            if (strcmp(clientes[i].inversiones[k].empresa_id, empresa_id) == 0) {
                encontrado = true;
                contador++;
            }
        }
    }

    if (!encontrado) {
        printf("\n\nERROR: No hay ninguna empresa con esa abreviatura, por favor revise los datos e intentelo nuevamente.\n");
        printf("Volviendo al menu Broker en 3 segundos\n");
        sleep(3);
        limpiar_consola();
        return -1;
    }


    limpiar_consola();
    printf("---------------------------------------------------------\n");
    printf("| CUIT | FECHA | EMPRESA ID | CANTIDAD COMPRADA | TOTAL |\n");
    printf("---------------------------------------------------------\n\n");

    for (int i = 0; i < *num_clientes; i++) {
        for (int k = 0; k < clientes[i].num_inversiones; k++) {
            if (strcmp(clientes[i].inversiones[k].empresa_id, empresa_id) == 0) {
                printf("%s | %s | %s | %d | $%.2f\n",
                       clientes[i].cuit,
                       clientes[i].inversiones[k].fecha,
                       clientes[i].inversiones[k].empresa_id,
                       clientes[i].inversiones[k].cantidad_acciones,
                       clientes[i].inversiones[k].precio_compra);
            }
        }
    }

    printf("\n\nCantidad total de inversiones de esta empresa: %d\n\n", contador);
    system("pause");
    limpiar_consola();
    return;
}

void menu_inversion(cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas){

    limpiar_consola();

    int seleccion = 1;
    while (seleccion != 0){
        printf ("MENU DE INVERSIONES\n\n");
        printf ("[ 1 ] Comprar acciones\n");
        printf ("[ 2 ] Vender acciones\n");
        printf ("[ 3 ] Ver listado de empresas\n\n");
        printf ("[ 0 ] Volver al menu anterior\n\n");
        printf ("Elija una opcion: ");
        scanf ("%d", &seleccion);

    switch (seleccion){

        case 1:
                printf("%d",clientes[posicion_cliente].num_inversiones);
                system("pause");
                if (clientes[posicion_cliente].num_inversiones >= MAX_INVERSIONES_CLIENTE){
                    limpiar_consola ();
                    printf ("ERROR: Usted supero el maximo permitido de inversiones, por favor trate de vender inversiones y vuelva a intentarlo.\n");
                    printf ("Volviendo al menu anterior en 3 segundos");
                    sleep(3);
                    limpiar_consola ();
                    break;
                }

                limpiar_consola();
                char abreviatura[5];
                getchar();
                bool empresa_encontrada = false;
                int posicion_empresa = -1;
                int cantidad_acciones_comprar = 0;
                float total = 0;

                printf ("SISTEMA DE INVERSIONES -> COMPRA DE ACCIONES\n\n");

                printf ("-------------------------------------\n");
                printf ("ABREVIATURA | EMPRESA | PRECIO ACTUAL\n");
                printf ("-------------------------------------\n\n");

                for (int i = 0; i < *num_empresas; i++){
                    printf ("%s | %s | $ %.2f\n", empresas[i].id, empresas[i].nombre, empresas[i].precio_actual);
                }
                printf("\n");

                do{
                    printf ("Ingrese la abreviatura de la empresa para comprar acciones: ");
                    fflush(stdin);
                    fgets(abreviatura, 5, stdin);
                    abreviatura[strcspn(abreviatura, "\n")] = 0;

                    for (int i = 0; i < *num_empresas; i++){
                        if (strcmp (abreviatura, empresas[i].id) == 0){
                            empresa_encontrada = true;
                            posicion_empresa = i;
                            break;
                        }
                    }

                    if (empresa_encontrada == false){
                        printf ("ERROR: Usted ha ingresado una abreviatura de la empresa no valida, por favor revise los datos e intentelo nuevamente\n");
                        sleep(2);
                        }
                    } while (empresa_encontrada == false);

                    limpiar_consola();
                    char opcion[3];

                    printf ("SISTEMA DE INVERSIONES -> COMPRA DE ACCIONES\n\n");
                    printf ("ABREVIATURA DE EMPRESA: %s\n", empresas[posicion_empresa].id);
                    printf ("NOMBRE DE LA EMPRESA: %s\n", empresas[posicion_empresa].nombre);
                    printf ("PRECIO DE LA EMPRESA POR ACCION: %.2f\n\n", empresas[posicion_empresa].precio_actual);

                    printf ("Ingrese la cantidad de acciones para comprar de la empresa %s: ", empresas[posicion_empresa].nombre);
                    fflush( stdin );
                    scanf ("%d", &cantidad_acciones_comprar);

                    total = (empresas[posicion_empresa].precio_actual * cantidad_acciones_comprar);
                    printf ("\n\nSaldo actual en su cuenta: $ %.2f\n", clientes[posicion_cliente].saldo_cuenta);
                    printf ("Usted va a comprar %d acciones de la empresa %s\n\n", cantidad_acciones_comprar, empresas[posicion_empresa].nombre);
                    printf ("TOTAL: $ %.2f\n\n", total);

                    do{
                        printf ("Escriba si para confirmar la compra, o no para cancelar: ");
                        fflush(stdin);
                        fgets(opcion, 3, stdin);
                        opcion[strcspn(opcion, "\n")] = 0;

                        if ((strcmp(opcion, "si") != 0) && (strcmp(opcion, "no") != 0)){
                        printf ("ERROR: Ingreso una opcion no valida, intentelo nuevamente.\n\n");
                        sleep (3);
                        }
                    } while ((strcmp(opcion, "si") != 0) && (strcmp(opcion, "no") != 0));

                    if (strcmp (opcion, "si") == 0){
                            if (clientes[posicion_cliente].saldo_cuenta < total){
                                printf ("ERROR: Usted no posee saldo suficiente para comprar acciones, por favor, verifique su saldo e intentelo nuevamente.\n");
                                sleep(3);
                                limpiar_consola();
                                break;
                            }
                            else{
                                //Buscamos que si ya tiene acciones compradas en esta empresa
                                int encontro_inversion=-1;
                                for(int i=0; i<clientes[posicion_cliente].num_inversiones;i++){
                                    printf("%s\n",clientes[posicion_cliente].inversiones[i].empresa_id);
                                    system("pause");
                                    if(strcmp(clientes[posicion_cliente].inversiones[i].empresa_id,empresas[posicion_empresa].id)==0){
                                    encontro_inversion=i;
                                    break;
                                    }
                                }
                                printf("%d\n",encontro_inversion);
                                    char fecha[11];
                                    printf ("Ingrese la fecha actual (DD/MM/AAAA): ");
                                    fflush (stdin);
                                    fgets (fecha, 11, stdin);
                                    fecha[strcspn(fecha, "\n")] = 0;
                                //si no encontramos creamos una nueva inversion.
                                if(encontro_inversion==-1){
                                    limpiar_consola();
                                    int nueva_inversion = clientes[posicion_cliente].num_inversiones;
                                    /*
                                    char fecha[11];
                                    printf ("Ingrese la fecha actual (DD/MM/AAAA): ");
                                    fflush (stdin);
                                    fgets (fecha, 11, stdin);
                                    fecha[strcspn(fecha, "\n")] = 0;
                                    */
                                    clientes[posicion_cliente].inversiones[nueva_inversion].cantidad_acciones = cantidad_acciones_comprar; //Guardo las acciones compradas del cliente
                                    strcpy (clientes[posicion_cliente].inversiones[nueva_inversion].empresa_id, empresas[posicion_empresa].id); //Guardo ID empresa (Abreviatura de la empresa)
                                    strcpy (clientes[posicion_cliente].inversiones[nueva_inversion].fecha, fecha); //Guardo fecha
                                    clientes[posicion_cliente].inversiones[nueva_inversion].precio_compra = total; //Guardo el precio comprado
                                    clientes[posicion_cliente].inversiones[nueva_inversion].precio_empresa_comprado=empresas[posicion_empresa].precio_actual;

                                    clientes[posicion_cliente].saldo_cuenta = (clientes[posicion_cliente].saldo_cuenta - total); //Retiro saldo del cliente para la compra

                                    clientes[posicion_cliente].num_inversiones = (clientes[posicion_cliente].num_inversiones + 1); //Guardo el numero de inversion

                                    guardar_inversion(clientes, num_clientes, empresas, num_empresas);
                                    guardar_clientes(clientes, num_clientes);

                                    /*limpiar_consola ();
                                    printf ("Se ha confirmado la compra. Volviendo al menu cliente en 3 segundos.\n");
                                    sleep(3);
                                    limpiar_consola();
                                    */
                                    // break;
                                }else{
                                    //modificamos si encontramos acciones compradas
                                    /*
                                    char fecha[11];
                                    printf ("Ingrese la fecha actual (DD/MM/AAAA): ");
                                    fflush (stdin);
                                    fgets (fecha, 11, stdin);
                                    fecha[strcspn(fecha, "\n")] = 0;
                                    */
                                    clientes[posicion_cliente].inversiones[encontro_inversion].cantidad_acciones+=cantidad_acciones_comprar;//Sumamos la cantidad
                                    clientes[posicion_cliente].inversiones[encontro_inversion].precio_compra+=total; //Sumamos el precio de compra con el total actual
                                    strcpy (clientes[posicion_cliente].inversiones[encontro_inversion].fecha, fecha); //cambiamos la fecha
                                    clientes[posicion_cliente].inversiones[encontro_inversion].precio_empresa_comprado=empresas[posicion_empresa].precio_actual;
                                    clientes[posicion_cliente].saldo_cuenta = (clientes[posicion_cliente].saldo_cuenta - total); //restamos el saldo

                                    guardar_inversion(clientes, num_clientes, empresas, num_empresas);
                                    guardar_clientes(clientes, num_clientes);

                                    //limpiar_consola ();
                                    //printf ("Se ha confirmado la compra. Volviendo al menu cliente en 3 segundos.\n");
                                    //sleep(3);
                                    //limpiar_consola();
                                    // break;
                                }

                                    limpiar_consola();
                                    int nueva_inversion_historial = clientes[posicion_cliente].num_inversiones_historial;
                                    /*
                                    char fecha[11];
                                    printf ("Ingrese la fecha actual (DD/MM/AAAA): ");
                                    fflush (stdin);
                                    fgets (fecha, 11, stdin);
                                    fecha[strcspn(fecha, "\n")] = 0;
                                    */
                                    clientes[posicion_cliente].inversiones_historial[nueva_inversion_historial].cantidad_acciones = cantidad_acciones_comprar; //Guardo las acciones compradas del cliente
                                    strcpy (clientes[posicion_cliente].inversiones_historial[nueva_inversion_historial].empresa_id, empresas[posicion_empresa].id); //Guardo ID empresa (Abreviatura de la empresa)
                                    strcpy (clientes[posicion_cliente].inversiones_historial[nueva_inversion_historial].fecha, fecha); //Guardo fecha
                                    clientes[posicion_cliente].inversiones_historial[nueva_inversion_historial].precio_compra = total; //Guardo el precio comprado
                                    clientes[posicion_cliente].inversiones_historial[nueva_inversion_historial].precio_empresa_comprado=empresas[posicion_empresa].precio_actual;
                                    clientes[posicion_cliente].saldo_cuenta = (clientes[posicion_cliente].saldo_cuenta - total); //Retiro saldo del cliente para la compra

                                    clientes[posicion_cliente].num_inversiones_historial = (clientes[posicion_cliente].num_inversiones_historial + 1); //Guardo el numero de inversion

                                    guardar_inversion_historial(clientes, num_clientes, empresas, num_empresas);
                                    guardar_clientes(clientes, num_clientes);

                                    limpiar_consola ();
                                    printf ("Se ha confirmado la compra. Volviendo al menu cliente en 3 segundos.\n");
                                    sleep(3);
                                    limpiar_consola();
                                    break;
                            }
                    }
                    else{
                        if (strcmp(opcion, "no") == 0){
                        limpiar_consola();
                        printf("La compra no ha sido realizada.\n\n");
                        system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
                        limpiar_consola();
                        return;
                        }
                    }

        case 2:
                limpiar_consola();
                vender_acciones (clientes, posicion_cliente, num_clientes, empresas, num_empresas);
                break;

        case 3:
                limpiar_consola();
                printf ("LISTADO DE EMPRESAS\n\n");
                printf ("-------------------------------------\n");
                printf ("ABREVIATURA | EMPRESA | PRECIO ACTUAL\n");
                printf ("-------------------------------------\n\n");

                for (int i = 0; i < *num_empresas; i++){
                    printf ("%s | %s | $ %.2f\n", empresas[i].id, empresas[i].nombre, empresas[i].precio_actual);
                }
                printf("\n");

                system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
                limpiar_consola();
                break;

        case 0:
                limpiar_consola();
                return;

        default:
                printf ("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
                sleep(2);  //Esperar dos segundos antes de continuar
                limpiar_consola();
                break;
        }
    }
}
