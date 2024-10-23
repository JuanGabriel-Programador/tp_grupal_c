#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"
#include "clientes.h"
#include "empresa.h"
#include "inversion.h"

//Funcion para cargar clientes
void cargar_clientes (cliente clientes[], int *num_clientes) {
    FILE *archivo = fopen("clientes.bin", "r+");
    if (archivo == NULL) {
        printf("Archivo de clientes no encontrado. Se creara uno nuevo.\n\n");
        return;
    }

    int i = 0;
    while (fscanf(archivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%f\n",
                   clientes[i].nombre, clientes[i].apellido,
                   clientes[i].correo, clientes[i].cuit,
                   clientes[i].password, &clientes[i].saldo_cuenta) != EOF) {
        i++;
    }
    *num_clientes = i;

    fclose(archivo);
}

//Funcion para guardar clientes
void guardar_clientes(cliente clientes[], int *num_clientes) {
    FILE *archivo = fopen("clientes.bin", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < *num_clientes; i++) {
        fprintf(archivo, "%s,%s,%s,%s,%s,%.2f\n",
                clientes[i].nombre, clientes[i].apellido,
                clientes[i].correo, clientes[i].cuit,
                clientes[i].password, clientes[i].saldo_cuenta);
    }

    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}

void cargar_inversion (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){
    FILE *archivo = fopen("inversiones.bin", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char cuit[15];
    char fecha[11];
    char empresa_id[5];
    int cantidad_acciones;
    float precio_compra;

    while (fscanf(archivo, "%[^,],%[^,],%[^,],%d,%f\n", cuit, fecha, empresa_id, &cantidad_acciones, &precio_compra) != EOF) {
        // Busca el cliente con el CUIT leído
        for (int i = 0; i < *num_clientes; i++) {
            if (strcmp(clientes[i].cuit, cuit) == 0) {
                // Agrega la inversión a la lista de inversiones del cliente
                int num_inversiones = clientes[i].num_inversiones;
                strcpy(clientes[i].inversiones[num_inversiones].fecha, fecha);
                strcpy(clientes[i].inversiones[num_inversiones].empresa_id, empresa_id);
                clientes[i].inversiones[num_inversiones].cantidad_acciones = cantidad_acciones;
                clientes[i].inversiones[num_inversiones].precio_compra = precio_compra;
                clientes[i].num_inversiones++;
                //printf("Inversion cargada: %s, %s, %d, %.2f\n", fecha, empresa_id, cantidad_acciones, precio_compra); // Verifica los datos cargados
                //sleep(1);
                break; // Se encontró y actualizó el cliente, no es necesario seguir buscando
            }
        }
    }

    fclose(archivo);
}

void guardar_inversion(cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){
    FILE *archivo = fopen("inversiones.bin", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < *num_clientes; i++) {
        for (int k = 0; k < clientes[i].num_inversiones; k++){
            fprintf(archivo, "%s,%s,%s,%d,%.2f\n",
            clientes[i].cuit,
            clientes[i].inversiones[k].fecha,
            clientes[i].inversiones[k].empresa_id,
            clientes[i].inversiones[k].cantidad_acciones,
            clientes[i].inversiones[k].precio_compra);
        }
    }
    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}

void cargar_inversion_historial (cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){
    FILE *archivo = fopen("inversiones_h.bin", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo. Inversiones_h\n");
        sleep(3);
        return;
    }

    char cuit[15];
    char fecha[11];
    char empresa_id[5];
    int cantidad_acciones;
    float precio_compra;

    while (fscanf(archivo, "%[^,],%[^,],%[^,],%d,%f\n", cuit, fecha, empresa_id, &cantidad_acciones, &precio_compra) != EOF) {
        // Busca el cliente con el CUIT leído
        for (int i = 0; i < *num_clientes; i++) {
            if (strcmp(clientes[i].cuit, cuit) == 0) {
                // Agrega la inversión a la lista de inversiones del cliente
                int num_inversiones_historial = clientes[i].num_inversiones_historial;
                strcpy(clientes[i].inversiones_historial[num_inversiones_historial].fecha, fecha);
                strcpy(clientes[i].inversiones_historial[num_inversiones_historial].empresa_id, empresa_id);
                clientes[i].inversiones_historial[num_inversiones_historial].cantidad_acciones = cantidad_acciones;
                clientes[i].inversiones_historial[num_inversiones_historial].precio_compra = precio_compra;
                clientes[i].num_inversiones_historial++;
                //printf("Inversion cargada: %s, %s, %d, %.2f\n", fecha, empresa_id, cantidad_acciones, precio_compra); // Verifica los datos cargados
                //sleep(1);
                break; // Se encontró y actualizó el cliente, no es necesario seguir buscando
            }
        }
    }

    fclose(archivo);
}

void guardar_inversion_historial(cliente clientes[], int *num_clientes, empresa empresas[], int *num_empresas){
    FILE *archivo = fopen("inversiones_h.bin", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < *num_clientes; i++) {
        for (int k = 0; k < clientes[i].num_inversiones_historial; k++){
            fprintf(archivo, "%s,%s,%s,%d,%.2f\n",
            clientes[i].cuit,
            clientes[i].inversiones_historial[k].fecha,
            clientes[i].inversiones_historial[k].empresa_id,
            clientes[i].inversiones_historial[k].cantidad_acciones,
            clientes[i].inversiones_historial[k].precio_compra);
        }
    }
    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}

//FUNCION PARA EL ALTA DEL CLIENTE
void alta_cliente(cliente clientes[], int *num_clientes) {

    if (*num_clientes >= MAX_CLIENTES) {
        printf("No se pueden agregar mas clientes ya que supero el limite de clientes del sistema.\n");
        sleep(3);
        limpiar_consola();
        return;
    }

    cliente nuevo_cliente; //Creamos la variable local
    bool cuit_duplicado = false; //Creo la variable duplicado cuit

    printf ("MENU BROKER >> ALTA DE CLIENTES\n\n");

    printf("Ingrese nombre: ");
    getchar();  // Limpiar el buffer
    fgets(nuevo_cliente.nombre, 51, stdin);
    nuevo_cliente.nombre[strcspn(nuevo_cliente.nombre, "\n")] = 0; // Eliminar el salto de línea

    printf("Ingrese apellido: ");
    fgets(nuevo_cliente.apellido, 51, stdin);
    nuevo_cliente.apellido[strcspn(nuevo_cliente.apellido, "\n")] = 0; // Eliminar el salto de línea

    printf("Ingrese correo: ");
    fgets(nuevo_cliente.correo, 51, stdin);
    nuevo_cliente.correo[strcspn(nuevo_cliente.correo, "\n")] = 0; // Eliminar el salto de línea


    do{  //ENTRAMOS EN BUCLE PARA DETECTAR SI EL CUIT INGRESADO ES IGUAL QUE EL GUARDADO EN SISTEMA
        char revisar_cuit[15];
        cuit_duplicado = false;

        printf("Ingrese CUIT: ");
        fgets(revisar_cuit, 15, stdin);
        revisar_cuit[strcspn(revisar_cuit, "\n")] = 0; // Eliminar el salto de línea

        for (int i = 0; i < *num_clientes; i++) {  //Empezamos a recorrer el array de clientes en cuit para averiguar si el cuit ingresado son iguales
            if (strcmp(clientes[i].cuit, revisar_cuit) == 0) {
                printf ("\n");
                printf("ERROR: Ha ingresado un CUIT que ya fue cargado en el sistema, por favor revise los datos y vuelva a intentar.\n");
                cuit_duplicado = true;
                break;
                }
            }

        if (!cuit_duplicado){
            strcpy (nuevo_cliente.cuit, revisar_cuit);
            nuevo_cliente.cuit[strcspn(nuevo_cliente.cuit, "\n")] = 0;
            cuit_duplicado = false;
        }
    } while (cuit_duplicado);  //FIN DEL BUCLE

    printf("Ingrese password: ");
    fgets(nuevo_cliente.password, 20, stdin);
    nuevo_cliente.password[strcspn(nuevo_cliente.password, "\n")] = 0; // Eliminar el salto de línea

    printf("Ingrese saldo de cuenta: ");
    scanf("%f", &(nuevo_cliente.saldo_cuenta));

    nuevo_cliente.num_inversiones = 0; // Inicializar el número de inversiones a 0

    // Añadir el nuevo cliente al array estático
    clientes[*num_clientes] = nuevo_cliente;
    (*num_clientes)++;
    printf("\n"); //Salto de linea

    guardar_clientes(clientes, num_clientes); //Guardo los clientes
    limpiar_consola();

    printf("Cliente agregado con exito.\n");
    printf ("Volviendo al menu Broker en 3 segundos.");
    sleep(3);
    limpiar_consola();
    return;
}

//MOSTRAR POR PANTALLA EL LISTADO DE CLIENTES ACTUALES
void listado_clientes(cliente clientes[], int *num_clientes){

    if (*num_clientes == 0){
        printf ("No hay clientes en el sistema.\n\n");
        printf ("Volviendo al menu Broker en 3 segundos.");
        sleep(3);
        limpiar_consola();
        return;
    }
    else{

    int total_clientes = 0; //Variable para contar cuantos clientes hay

    printf ("MENU BROKER >> LISTADO DE CLIENTES\n\n");

    for (int i = 0; i < *num_clientes; i++){
        printf ("-----------\n");
        printf ("Cliente %d: \n", (total_clientes + 1));
        printf ("-----------");
        printf ("\n\nNombre: %s\n", clientes[i].nombre);
        printf ("Apellido: %s\n", clientes[i].apellido);
        printf ("CUIT: %s\n", clientes[i].cuit);
        printf ("Correo electronico: %s\n", clientes[i].correo);
        printf ("Saldo actual del cliente: $%.2f\n\n", clientes[i].saldo_cuenta);

        total_clientes++;
    }

    printf ("\n\nTOTAL DE CLIENTES: %d\n\n", total_clientes);
    system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
    limpiar_consola();
    return;
    }
}

// FUNCION PARA ELIMINAR UN CLIENTE DEL SISTEMA
void baja_cliente (cliente clientes[], int *num_clientes){

    char cuit[15];
    char opcion[5];
    int cliente = 0; //Variable para guardar la posicion del cliente cuando se encuentra

    printf ("MENU BROKER >> BAJA DE CLIENTES\n\n");
    getchar();
    printf ("Por favor, ingrese el CUIT para eliminar al cliente del sistema: ");
    fgets(cuit, 15, stdin);
    cuit[strcspn(cuit, "\n")] = 0;

    //PODRIA SER MAS EFICIENTE QUE HAGA UN CORTE CUANDO ENCUENTRE AL CLIENTE
    bool encontrado = false;
    for (int i = 0; i < *num_clientes; i++) {
        if (strcmp(clientes[i].cuit, cuit) == 0) {
            encontrado = true;
            cliente = i;
        }
    }

    if (encontrado){
         printf ("\nSe encontro el CUIT del siguiente cliente:\n");
         printf ("Nombre: %s\n", clientes[cliente].nombre);
         printf ("Apellido: %s\n", clientes[cliente].apellido);
         printf ("CUIT: %s\n\n", clientes[cliente].cuit);
         printf ("Desea eliminar al cliente del sistema?\n");
         printf ("Escriba si para eliminar, o no para cancelar.\n\n");

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
            if (clientes[cliente].num_inversiones >= 1){
                limpiar_consola();
                printf ("ERROR: No se puede eliminar al cliente del sistema, ya que tiene inversiones en su cuenta. Asegurese de que no tenga inversiones.\n\n");
                system ("pause");
                limpiar_consola();
                return;
            }

            if (clientes[cliente].saldo_cuenta > 0.00){
                limpiar_consola();
                printf ("ERROR: No se puede eliminar al cliente del sistema, ya que tiene saldo disponible en su cuenta. Asegurese de que no tenga saldo.\n\n");
                system ("pause");
                limpiar_consola();
                return;
            }

            for (int i = cliente; i < *num_clientes - 1; i++) {
                clientes[cliente] = clientes[cliente + 1];
            }

         (*num_clientes)--;

         printf("\n");
         guardar_clientes(clientes, num_clientes);  //Guardo al archivo
         limpiar_consola();
         printf("Cliente eliminado del sistema\n\n");
         system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
         limpiar_consola();
         return;
         }
         else{
            if (strcmp(opcion, "no") == 0){
                limpiar_consola();
                printf("Baja del cliente cancelada.\n\n");
                system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
                limpiar_consola();
                return;
            }
         }
    }
    else{
        printf ("No se encontro el CUIT en el sistema, por favor revise los datos y luego intentelo de nuevo.\n\n");
        system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
        limpiar_consola();
        return;
    }
}

void modificar_cliente(cliente clientes[],int *num_clientes){
    char cuit[15];
    char opcion[5];
    int cliente_actual = 0; //Variable para guardar la posicion del cliente cuando se encuentra

    printf ("MENU BROKER >> MODIFICACION DE CLIENTES\n\n");
    getchar();
    printf ("Por favor, ingrese el CUIT para modificar al cliente del sistema: ");
    fgets(cuit, 15, stdin);
    cuit[strcspn(cuit, "\n")] = 0;

    //PODRIA SER MAS EFICIENTE QUE HAGA UN CORTE CUANDO ENCUENTRE AL CLIENTE
    bool encontrado = false;
    for (int i = 0; i < *num_clientes; i++) {
        if (strcmp(clientes[i].cuit, cuit) == 0) {
            encontrado = true;
            cliente_actual = i;
        }
    }

    if (encontrado){
        printf ("Se encontro el siguiente cliente: \n\n");
        printf ("Nombre: %s\n", clientes[cliente_actual].nombre);
        printf ("Apellido: %s\n", clientes[cliente_actual].apellido);
        printf ("CUIT: %s\n", clientes[cliente_actual].cuit);
        printf ("Correo electronico: %s\n\n", clientes[cliente_actual].correo);
        printf ("Esta seguro de modificar este cliente?\n\n");

        int seleccion = 1;

        while (seleccion != 0){
            printf ("Elija una opcion: ");
            printf ("\n[ 1 ] Modificar cliente\n");
            printf ("[ 0 ] Cancelar\n");
            printf("Ingrese una opcion: ");
            scanf ("%d", &seleccion);

        switch (seleccion){

            case 1:
                limpiar_consola();

                int seleccion_modificar = 1;

                while (seleccion_modificar != 0){
                    printf ("MODIFICACION DE CLIENTE %s, %s\n\n", clientes[cliente_actual].apellido, clientes[cliente_actual].nombre);
                    printf ("[ 1 ] Modificar nombre\n");
                    printf ("[ 2 ] Modificar apellido\n");
                    printf ("[ 3 ] Modificar CUIT\n");
                    printf ("[ 4 ] Modificar correo electronico\n");
                    printf ("[ 0 ] Cancelar\n");
                    printf ("\n\nElija una opcion para modificar el cliente actual: ");
                    scanf ("%d", &seleccion_modificar);

                switch (seleccion_modificar){

                    case 1:
                        limpiar_consola();
                        char nuevo_nombre[51];
                        getchar();
                        printf ("Ingrese el nuevo nombre: ");
                        fgets(nuevo_nombre, 51, stdin);
                        nuevo_nombre[strcspn(nuevo_nombre, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (clientes[cliente_actual].nombre, nuevo_nombre); //Copiar el nuevo nombre al cliente

                        guardar_clientes(clientes, num_clientes);
                        limpiar_consola();

                        printf ("Nombre del cliente modificado.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();

                        return menu_broker;

                    case 2:
                        limpiar_consola();
                        char nuevo_apellido[51];
                        getchar();
                        printf ("Ingrese el nuevo apellido: ");
                        fgets(nuevo_apellido, 51, stdin);
                        nuevo_apellido[strcspn(nuevo_apellido, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (clientes[cliente_actual].apellido, nuevo_apellido); //Copiar el nuevo apellido al cliente

                        guardar_clientes(clientes, num_clientes);
                        limpiar_consola();

                        printf ("Apellido del cliente modificado.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();
                        return menu_broker;

                     case 3:
                        limpiar_consola();
                        char nuevo_cuit[15];
                        getchar();
                        printf ("Ingrese el nuevo CUIT: ");
                        fgets(nuevo_cuit, 15, stdin);
                        nuevo_cuit[strcspn(nuevo_cuit, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (clientes[cliente_actual].cuit, nuevo_cuit); //Copiar el nuevo CUIT al cliente

                        guardar_clientes(clientes, num_clientes);
                        limpiar_consola();

                        printf ("CUIT del cliente modificado.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();
                        return menu_broker;

                      case 4:
                        limpiar_consola();
                        char nuevo_correo[51];
                        getchar();
                        printf ("Ingrese el nuevo apellido: ");
                        fgets(nuevo_correo, 51, stdin);
                        nuevo_correo[strcspn(nuevo_correo, "\n")] = 0; // Eliminar el salto de línea

                        strcpy (clientes[cliente_actual].correo, nuevo_correo); //Copiar el nuevo correo electronico al cliente

                        guardar_clientes(clientes, num_clientes);
                        limpiar_consola();

                        printf ("Correo electronico del cliente modificado.\n");
                        printf ("Volviendo al menu Broker en 3 segundos.\n");

                        sleep(3);
                        limpiar_consola();
                        return menu_broker;

                      case 0:
                        limpiar_consola();
                        return menu_broker;

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
                    return menu_broker;

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
        printf("ERROR: Ingreso un CUIT erroneo, por favor revise los datos y vuelva a intentarlo nuevamente.\n");
        system("pause");  //Hasta que el usuario no oprima una tecla, queda congelada la pantalla
        limpiar_consola();
        return;
    }
}

// Funcion que retorna la posicion del cliente para su auntenticacion
int autenticacion_cliente (cliente clientes[], int *num_clientes){

    int posicion_cliente = -1;
    int posicion_cliente_password = -1; //Para buscar al cliente para su recuperacion de password
    int opcion = 1;
    char correo_ingresado[51];
    char cuit_ingresado[15];
    bool cliente_encontrado = false;

    while (opcion != 0){
        getchar();
        printf ("INICIO DE SESION DEL CLIENTE\n\n");

        printf ("[ 1 ] Iniciar sesion\n");
        printf ("[ 2 ] Me olvide mi password\n");
        printf ("[ 0 ] Volver al menu principal\n\n");

        printf ("Elija una opcion: ");
        scanf ("%d", &opcion);

        switch (opcion){

        case 1:
            limpiar_consola();
            printf ("INICIO DE SESION DEL CLIENTE\n\n");
            getchar();
            printf ("Ingrese su correo electronico: ");
            fgets (correo_ingresado, 51, stdin);
            correo_ingresado[strcspn(correo_ingresado, "\n")] = 0;

            char password_ingresado[20];
            printf ("Ingrese su password: ");
            fgets (password_ingresado, 20, stdin);
            password_ingresado[strcspn(password_ingresado, "\n")] = 0;

            for (int i = 0; i < *num_clientes; i++){
                if ((strcmp (password_ingresado, clientes[i].password) == 0) && (strcmp(correo_ingresado, clientes[i].correo) == 0)){
                posicion_cliente = i;
                break;
            }
        }

        if (posicion_cliente == -1){
            limpiar_consola();
            printf ("ERROR: Ingreso algun dato erroneo, por favor, vuelva a intentarlo.\n");
            printf ("Volviendo al menu principal en 3 segundos.");
            sleep(3);
            limpiar_consola();
            return -1;
        }
        else {
            return posicion_cliente;
        }

        case 2:
            limpiar_consola();
            printf ("RECUPERACION DE PASSWORD\n\n");
            getchar();
            printf ("Ingrese su correo electronico: ");
            fgets (correo_ingresado, 51, stdin);
            correo_ingresado[strcspn(correo_ingresado, "\n")] = 0;

            printf ("Ingrese su CUIT: ");
            fgets (cuit_ingresado, 15, stdin);
            cuit_ingresado[strcspn(cuit_ingresado, "\n")] = 0;

            for (int i = 0; i < *num_clientes; i++) {  //Empezamos a recorrer el array de clientes en cuit para averiguar si el cuit ingresado son iguales
                if ((strcmp(clientes[i].cuit, cuit_ingresado) == 0) && (strcmp(clientes[i].correo, correo_ingresado) == 0)){
                    cliente_encontrado = true;
                    posicion_cliente_password = i;
                    break;
                }
            }

            if (cliente_encontrado){
                limpiar_consola ();
                printf ("RECUPERACION DE PASSWORD\n\n");
                printf ("Ingrese su nueva password: ");

                fgets (clientes[posicion_cliente_password].password, 20, stdin);
                clientes[posicion_cliente_password].password[strcspn(clientes[posicion_cliente_password].password, "\n")] = 0;

                guardar_clientes(clientes, num_clientes);
                limpiar_consola();
                printf ("Su password ha sido actualizado. Por favor, inicie sesion. Volviendo al menu principal en 3 segundos.\n");
                sleep(3);
                limpiar_consola();
                return -1;
            }
            else{
                printf ("ERROR: No se encontro ningun cliente con los datos ingresados. Por favor vuelva a revisar los datos e intentelo nuevamente.\n");
                sleep(3);
                limpiar_consola();
                return -1;
            }

            case 0:
                limpiar_consola();
                return -1;

            default:
                printf ("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
                sleep(2);  //Esperar dos segundos antes de continuar
                limpiar_consola();
                break;

        }  //Switch
    } //While

} //Cierre de funcion

//Ingreso al menu cliente una vez logeado en la funcion autenticar_cliente
void menu_cliente (cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas){

    limpiar_consola();

    int seleccion = 1;

    while (seleccion != 0){
        printf ("MENU DEL CLIENTE\n");
        printf ("Bienvenido/a %s, %s\n\n", clientes[posicion_cliente].apellido, clientes[posicion_cliente].nombre);
        printf ("INVERSIONES\n");
        printf ("[ 1 ] Ingresar al menu de inversiones\n");
        printf ("[ 2 ] Ver rendimiento\n\n");
        printf("SU CUENTA\n");
        printf ("[ 3 ] Ver su saldo actual\n");
        printf ("[ 4 ] Cargar saldo\n");
        printf ("[ 5 ] Extraer saldo\n");
        printf ("[ 6 ] Ver portafolio\n");
        printf ("[ 7 ] Cambiar mi password\n\n");
        printf ("[ 0 ] Cerrar sesion y volver al menu principal\n");
        printf ("\n\nElija una opcion: ");
        scanf ("%d", &seleccion);

    switch (seleccion){
        case 1:

            limpiar_consola();
            menu_inversion (clientes, posicion_cliente, num_clientes, empresas, num_empresas);
            break;

        case 2:
            limpiar_consola();
            break;

        case 3:
            limpiar_consola();
            printf ("Su saldo actual es de: $%.2f\n\n", clientes[posicion_cliente].saldo_cuenta);  //Muestra el saldo actual del cliente
            system("pause");
            limpiar_consola();
            break;

        case 4:
            limpiar_consola();
            carga_saldo(clientes, posicion_cliente, num_clientes);
            break;

        case 5:
            limpiar_consola();
            extraer_saldo(clientes, posicion_cliente, num_clientes);
            break;

        case 6:
            limpiar_consola();
            ver_portafolio(clientes, posicion_cliente);
            break;

        case 7:
            limpiar_consola();
            getchar();
            printf ("Ingrese su nueva password: ");
            fgets (clientes[posicion_cliente].password, 20, stdin);
            clientes[posicion_cliente].password[strcspn(clientes[posicion_cliente].password, "\n")] = 0;
            guardar_clientes(clientes, num_clientes);
            limpiar_consola();
            printf ("Su password ha sido actualizado. Por favor, inicie sesion. Volviendo al menu principal en 3 segundos.\n");
            sleep(3);
            limpiar_consola();
            return menu_principal;

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

//Funcion para cargar saldo al cliente
void carga_saldo (cliente clientes[], int posicion_cliente, int *num_clientes){

    limpiar_consola();

    float saldo_nuevo = 0;

    do{
        printf ("MENU CLIENTE -> INGRESO DE SALDO\n\n");
        printf ("Su saldo actual es de: $ %.2f\n", clientes[posicion_cliente].saldo_cuenta);
        printf ("Ingrese el nuevo saldo para su cuenta: ");
        scanf("%f", &saldo_nuevo);

        if (saldo_nuevo <= 0){
            printf ("ERROR: Ingreso un saldo negativo, por favor ingrese un saldo mayor a $1.\n");
            sleep(3);
            limpiar_consola();
        }
        else{
            limpiar_consola();
            clientes[posicion_cliente].saldo_cuenta = (clientes[posicion_cliente].saldo_cuenta + saldo_nuevo);  //Ingreso el nuevo saldo al cliente
            guardar_clientes (clientes, num_clientes);
            limpiar_consola();
            printf ("Procesando carga. Aguarde por favor.");
            sleep(4);
            printf ("\nSu saldo se actualizo con exito. Volviendo al menu en 3 segundos.\n");
            sleep(3);
            limpiar_consola();
            return;
        }
    }
    while (saldo_nuevo <= 0);
}

//Funcion para extraer saldo del cliente

void extraer_saldo (cliente clientes[], int posicion_cliente, int *num_clientes){

    limpiar_consola();

    if (clientes[posicion_cliente].saldo_cuenta == 0){
        limpiar_consola();
        printf ("MENU CLIENTE -> EXTRACCION DE SALDO\n\n");
        printf ("Usted no tiene saldo para extraer.\n\n");
        system ("pause");
        limpiar_consola();
        return;
    }

    float saldo_retirar = 0;

    do{
        printf ("MENU CLIENTE -> EXTRACCION DE SALDO\n\n");
        printf ("Su saldo actual es de: $ %.2f\n\n", clientes[posicion_cliente].saldo_cuenta);
        printf ("Ingrese el saldo para extraer de su cuenta: ");
        scanf("%f", &saldo_retirar);

        if ((clientes[posicion_cliente].saldo_cuenta < saldo_retirar) || (saldo_retirar == 0)){
            printf ("ERROR: Ha querido retirar mas saldo de su cuenta, por favor revise su saldo e intentelo nuevamente.\n");
            sleep(3);
            limpiar_consola();
        }
        else{
            limpiar_consola();
            clientes[posicion_cliente].saldo_cuenta = (clientes[posicion_cliente].saldo_cuenta - saldo_retirar);  //Ingreso el nuevo saldo al cliente
            guardar_clientes (clientes, num_clientes);
            limpiar_consola();
            printf ("Procesando extraccion. Aguarde por favor.");
            sleep(4);
            printf ("\nSe retiro el saldo correctamente. Volviendo al menu en 3 segundos.\n");
            sleep(3);
            limpiar_consola();
            return;
        }
    }
    while ((clientes[posicion_cliente].saldo_cuenta < saldo_retirar) || (saldo_retirar == 0));
}

void ver_portafolio (cliente clientes[], int posicion_cliente){

    if (clientes[posicion_cliente].num_inversiones == 0){
        limpiar_consola();
        printf ("Usted no posee ninguna inversion.\n\n");
        system ("pause");
        limpiar_consola();
        return;
    }

    limpiar_consola();
    printf("MENU CLIENTE -> SU PORTAFOLIO\n\n");
    printf("-----------------------------------------------\n");
    printf("| FECHA | EMPRESA | CANTIDAD COMPRADA | TOTAL |\n");
    printf("-----------------------------------------------\n\n");
    for (int i = 0; i < clientes[posicion_cliente].num_inversiones; i++){
        printf("%s | %s | %d | $%.2f\n",
               clientes[posicion_cliente].inversiones[i].fecha,
               clientes[posicion_cliente].inversiones[i].empresa_id,
               clientes[posicion_cliente].inversiones[i].cantidad_acciones,
               clientes[posicion_cliente].inversiones[i].precio_compra);
    }
    printf ("\n");
    system("pause");
    limpiar_consola();
    return;
}

void vender_acciones (cliente clientes[], int posicion_cliente, int *num_clientes, empresa empresas[], int *num_empresas) {
    if (clientes[posicion_cliente].num_inversiones == 0) {
        limpiar_consola();
        printf("SISTEMA DE INVERSIONES -> VENTA DE ACCIONES\n\n");
        printf("Usted no posee ninguna accion para vender.\n\n");
        system("pause");
        limpiar_consola();
        return;
    }

    limpiar_consola();
    printf("SISTEMA DE INVERSIONES -> VENTA DE ACCIONES\n\n");
    printf("SU PORTAFOLIO\n");
    printf("-----------------------------------------------\n");
    printf("| FECHA | EMPRESA | CANTIDAD COMPRADA | TOTAL |\n");
    printf("-----------------------------------------------\n\n");
    for (int i = 0; i < clientes[posicion_cliente].num_inversiones; i++) {
        printf("%s | %s | %d | $%.2f\n",
               clientes[posicion_cliente].inversiones[i].fecha,
               clientes[posicion_cliente].inversiones[i].empresa_id,
               clientes[posicion_cliente].inversiones[i].cantidad_acciones,
               clientes[posicion_cliente].inversiones[i].precio_compra);
    }

    char seleccion[5];
    bool empresa_encontrada = false;
    int posicion_empresa_inversion = 0;
    int posicion_empresa = 0;

    printf("\n\nIngrese la empresa para vender las acciones: ");
    fflush(stdin);
    fgets(seleccion, 5, stdin);
    seleccion[strcspn(seleccion, "\n")] = 0;

    for (int i = 0; i < clientes[posicion_cliente].num_inversiones; i++) {
        if (strcmp(clientes[posicion_cliente].inversiones[i].empresa_id, seleccion) == 0) {
            empresa_encontrada = true;
            posicion_empresa_inversion = i;
            break;
        }
    }

    if (!empresa_encontrada) {
        printf("ERROR: No tiene acciones en esa empresa para vender. Revise los datos e intente nuevamente\n");
        sleep(3);
        limpiar_consola();
        return;
    }

    for (int i = 0; i < *num_empresas; i++) {
        if (strcmp(empresas[i].id, seleccion) == 0) {
            posicion_empresa = i;
            break;
        }
    }

    limpiar_consola();
    int opcion = 1;
    printf("SISTEMA DE INVERSIONES -> VENTA DE ACCIONES -> %s (%s)\n\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].empresa_id, empresas[posicion_empresa].nombre);
    printf("ID Empresa: %s\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].empresa_id);
    printf("Precio por accion a la fecha: $ %.2f\n", empresas[posicion_empresa].precio_actual);
    printf("Cantidad de acciones que posee: %d\n\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones);

    while (opcion != 0) {
        printf("[ 1 ] Vender acciones\n");
        printf("[ 0 ] Cancelar venta\n\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                limpiar_consola();
                int cantidad_acciones_vender = 0;
                printf("SISTEMA DE INVERSIONES -> VENTA DE ACCIONES -> %s (%s)\n\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].empresa_id, empresas[posicion_empresa].nombre);
                printf("ID Empresa: %s\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].empresa_id);
                printf("Precio por accion a la fecha: $ %.2f\n", empresas[posicion_empresa].precio_actual);
                printf("Cantidad de acciones que posee: %d\n\n", clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones);

                do {
                    printf("Cuantas acciones quiere vender: ");
                    scanf("%d", &cantidad_acciones_vender);
                    if (cantidad_acciones_vender <= 0) {
                        printf("ERROR: Usted ingreso una cantidad erronea. Por favor reintente nuevamente.\n\n");
                    }
                    if (cantidad_acciones_vender > clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones) {
                        printf("ERROR: Usted quiere vender mas acciones de lo que posee. Por favor verifique los datos e intente nuevamente.\n\n");
                    }
                } while ((cantidad_acciones_vender <= 0) || (cantidad_acciones_vender > clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones));

                float total = 0;
                total = (cantidad_acciones_vender * empresas[posicion_empresa].precio_actual);
                limpiar_consola();

                printf("Se van a vender %d acciones.\n", cantidad_acciones_vender);
                printf("TOTAL: $ %.2f\n\n", total);
                printf("Procesando transaccion. Aguarde por favor.");
                sleep(4);

                // Actualizar los datos del cliente
                clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones -= cantidad_acciones_vender;
                clientes[posicion_cliente].saldo_cuenta += total;

                // Eliminar la inversión si ya no quedan acciones
                if (clientes[posicion_cliente].inversiones[posicion_empresa_inversion].cantidad_acciones == 0) {
                    for (int i = posicion_empresa_inversion; i < clientes[posicion_cliente].num_inversiones - 1; i++) {
                        clientes[posicion_cliente].inversiones[i] = clientes[posicion_cliente].inversiones[i + 1];
                    }
                    clientes[posicion_cliente].num_inversiones--;
                }

                guardar_clientes(clientes, num_clientes);
                limpiar_consola();
                guardar_inversion(clientes, num_clientes, empresas, num_empresas);
                limpiar_consola();
                printf("Operacion correcta.\n");
                printf("Volviendo al menu en 3 segundos");
                sleep(3);
                limpiar_consola();
                return;

            case 0:
                limpiar_consola();
                break;

            default:
                printf("ERROR: Ingreso una opcion no valida, intente nuevamente.\n\n");
                sleep(2); // Esperar dos segundos antes de continuar
                limpiar_consola();
                break;
        }
    }

    return;
}
