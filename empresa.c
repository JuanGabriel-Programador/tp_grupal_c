#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "funciones.h"
#include "clientes.h"
#include "inversion.h"

//Funcion para cargar empresas
void cargar_empresas (empresa empresas[], int *num_empresas) {
    FILE *archivo = fopen("empresas.bin", "r+");
    if (archivo == NULL) {
        printf("Archivo de empresas no encontrado. Se creara uno nuevo.\n\n");
        return;
    }

    int i = 0;
    while (fscanf(archivo, "%[^,],%[^,],%f\n",
                   empresas[i].id, empresas[i].nombre, &empresas[i].precio_actual) != EOF) {
        i++;
    }
    *num_empresas = i;

    fclose(archivo);
}

//Funcion para guardar empresas
void guardar_empresas(empresa empresas[], int *num_empresas) {
    FILE *archivo = fopen("empresas.bin", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < *num_empresas; i++) {
        fprintf(archivo, "%s,%s,%.2f\n",
                empresas[i].id, empresas[i].nombre, empresas[i].precio_actual);
    }

    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}


void alta_empresa (empresa empresas[], int *num_empresas){

    if (*num_empresas >= MAX_EMPRESAS) {
        printf("No se pueden agregar mas empresas ya que supero el limite de empresas del sistema.\n");
        sleep(3);
        limpiar_consola();
        return;
    }

    empresa nueva_empresa;

    printf ("MENU BROKER >> ALTA DE EMPRESAS\n\n");

    printf("Ingrese nombre de la empresa: ");
    getchar();  // Limpiar el buffer
    fgets(nueva_empresa.nombre, 51, stdin);
    nueva_empresa.nombre[strcspn(nueva_empresa.nombre, "\n")] = 0; // Eliminar el salto de línea

    printf("Ingrese la abreviacion de la empresa: ");
    fgets(nueva_empresa.id, 5, stdin);
    nueva_empresa.id[strcspn(nueva_empresa.id, "\n")] = 0; // Eliminar el salto de línea

    printf("Ingrese precio actual: ");
    scanf ("%f", &nueva_empresa.precio_actual);

    empresas[*num_empresas] = nueva_empresa;
    (*num_empresas)++;

    printf("\n"); //Salto de linea

    guardar_empresas(empresas, num_empresas); //Guardo los clientes

    limpiar_consola();

    printf("Empresa agregado con exito.\n");
    printf ("Volviendo al menu Broker en 3 segundos.");
    sleep(3);
    limpiar_consola();
    return;
}

//Funcion para dar de baja una empresa
void baja_empresa (empresa empresas[], int *num_empresas){

    char nombre_empresa[51];
    int empresa_posicion = 0;
    char opcion[5];

    printf ("MENU BROKER >> BAJA DE EMPRESAS\n\n");
    getchar();
    printf ("Por favor, ingrese el nombre de la empresa para eliminar del sistema: ");
    fgets(nombre_empresa, 51, stdin);
    nombre_empresa[strcspn(nombre_empresa, "\n")] = 0;

    //PODRIA SER MAS EFICIENTE QUE HAGA UN CORTE CUANDO ENCUENTRE AL CLIENTE
    bool encontrado = false;
    for (int i = 0; i < *num_empresas; i++) {
        if (strcmp(empresas[i].nombre, nombre_empresa) == 0) {
            encontrado = true;
            empresa_posicion = i;
        }
    }

    if (encontrado){
         printf ("\nSe encontro la siguiente empresa:\n");
         printf ("Nombre: %s\n", empresas[empresa_posicion].nombre);
         printf ("Abreviacion: %s\n\n", empresas[empresa_posicion].id);
         printf ("Desea eliminar a la empresa del sistema?\n");
         printf ("Escriba si para eliminar, o no para cancelar.\n\n");
         printf ("Ingrese la opcion: ");

         do{
            printf ("Ingrese la opcion: ");
            fgets(opcion, 5, stdin);
            opcion[strcspn(opcion, "\n")] = 0;

            if ((strcmp(opcion, "si") != 0) && (strcmp(opcion, "no") != 0)){
                printf ("ERROR: Ingreso una opcion no valida, intentelo nuevamente.\n\n");
                sleep (3);
            }
        }

        while ((strcmp(opcion, "si") != 0) && (strcmp(opcion, "no") != 0));

        if (strcmp(opcion, "si") == 0){
            for (int i = empresa_posicion; i < *num_empresas - 1; i++) {
                empresas[empresa_posicion] = empresas[empresa_posicion + 1];
            }

         (*num_empresas)--;

         printf("\n");
         guardar_empresas(empresas, num_empresas);  //Guardo al archivo
         limpiar_consola();
         printf("Empresa eliminada del sistema\n\n");
         system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
         limpiar_consola();
         return;
         }

         else{
            if (strcmp(opcion, "no") == 0){
                limpiar_consola();
                printf("Baja de la empresa cancelada.\n\n");
                system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
                limpiar_consola();
                return;
            }
         }
    }
    else{
        printf ("No se encontro la empresa en el sistema, por favor revise los datos y luego intentelo de nuevo.\n\n");
        system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
        limpiar_consola();
        return;
    }
}

//Funcion para ver el listado de empresas en el sistema
void listado_empresas(empresa empresas[], int *num_empresas){

    if (*num_empresas == 0){
        printf ("No hay empresas en el sistema.\n\n");
        printf ("Volviendo al menu Broker en 3 segundos.");
        sleep(3);
        limpiar_consola();
        return;
    }
    else{

    int total_empresas = 0; //Variable para contar cuantos clientes hay

    printf ("MENU BROKER >> LISTADO DE EMPRESAS\n\n");

    for (int i = 0; i < *num_empresas; i++){
        printf ("-----------\n");
        printf ("Empresa %d: \n", (total_empresas + 1));
        printf ("-----------");
        printf ("\n\nNombre: %s\n", empresas[i].nombre);
        printf ("Abreviacion: %s\n", empresas[i].id);
        printf ("Precio actual: $ %.2f\n\n", empresas[i].precio_actual);

        total_empresas++;
    }

    printf ("\n\nTOTAL DE EMPRESAS: %d\n\n", total_empresas);
    system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
    limpiar_consola();
    return;
    }
}


void modificar_empresa(empresa empresas[],int *num_empresas){
    char nombre[51];
    char opcion[5];
    int empresa_actual = 0;

    printf ("MENU BROKER >> MODIFICACION DE EMPRESAS\n\n");
    getchar();
    printf ("Por favor, ingrese el nombre de la empresa para modificarlo en el sistema: ");
    fgets(nombre, 51, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    //PODRIA SER MAS EFICIENTE QUE HAGA UN CORTE CUANDO ENCUENTRE AL CLIENTE
    bool encontrado = false;
    for (int i = 0; i < *num_empresas; i++) {
        if (strcmp(empresas[i].nombre, nombre) == 0) {
            encontrado = true;
            empresa_actual = i;
            break;
        }
    }

    if (encontrado){
        printf ("Se encontro la siguiente empresa: \n\n");
        printf ("Nombre: %s\n", empresas[empresa_actual].nombre);
        printf ("Abreviacion: %s\n\n", empresas[empresa_actual].id);
        printf ("Esta seguro de modificar esta empresa?\n\n");

        int seleccion = 1;

        while (seleccion != 0){
            printf ("Elija una opcion: ");
            printf ("\n[ 1 ] Modificar empresa\n");
            printf ("[ 0 ] Cancelar\n");
            printf("Ingrese una opcion: ");
            scanf ("%d", &seleccion);

        switch (seleccion){

            case 1:
                limpiar_consola();

                int seleccion_modificar = 1;

                while (seleccion_modificar != 0){
                    printf ("MODIFICACION DE EMPRESA %s\n\n", empresas[empresa_actual].nombre);
                    printf ("[ 1 ] Modificar nombre\n");
                    printf ("[ 2 ] Modificar abreviacion\n");
                    printf ("[ 3 ] Modificar el precio actual\n\n");
                    printf ("[ 0 ] Cancelar\n");
                    printf ("\n\nElija una opcion para modificar la empresa actual: ");
                    scanf ("%d", &seleccion_modificar);

                switch (seleccion_modificar){
                    case 1:
                        limpiar_consola();
                        char nuevo_nombre[51];

                        printf ("CAMBIO DE NOMBRE PARA %s\n\n", empresas[empresa_actual].nombre);
                        getchar();
                        printf ("Ingrese el nuevo nombre para la empresa: ");
                        fgets(nuevo_nombre, 51, stdin);
                        nuevo_nombre[strcspn(nuevo_nombre, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (empresas[empresa_actual].nombre, nuevo_nombre); //Copiar el nuevo nombre al cliente
                        guardar_empresas(empresas, num_empresas);
                        limpiar_consola();

                        printf ("Nombre de la empresa modificada.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();

                        return;

                    case 2:
                        limpiar_consola();
                        char nuevo_abreviacion[5];

                        printf ("CAMBIO DE ABREVIACION PARA %s\n\n", empresas[empresa_actual].nombre);
                        getchar();
                        printf ("Ingrese la nueva abreviacion de la empresa: ");
                        fgets(nuevo_abreviacion, 5, stdin);
                        nuevo_abreviacion[strcspn(nuevo_abreviacion, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (empresas[empresa_actual].id, nuevo_abreviacion); //Copiar el nuevo apellido al cliente
                        guardar_empresas(empresas, num_empresas);
                        limpiar_consola();

                        printf ("Abreviacion de la empresa modificada.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();
                        return;

                        case 3:
                        limpiar_consola();
                        float nuevo_precio = 0;

                        printf ("CAMBIO DE PRECIO ACTUAL PARA %s\n\n", empresas[empresa_actual].nombre);
                        printf ("Ingrese el nuevo precio de la empresa: ");
                        scanf ("%f", &nuevo_precio);

                        empresas[empresa_actual].precio_actual = nuevo_precio;
                        guardar_empresas(empresas, num_empresas);

                        limpiar_consola();

                        printf ("El precio actual de la empresa ha sido modificado.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();
                        return;

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

                case 0:
                    limpiar_consola();
                    printf("Operacion cancelada. Volviendo al menu Broker.\n");
                    sleep(3);
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
    else{
        limpiar_consola();
        printf("ERROR: Ingreso un nombre erroneo, por favor revise los datos y vuelva a intentarlo nuevamente.\n");
        system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
        limpiar_consola();
        return;
    }
}
