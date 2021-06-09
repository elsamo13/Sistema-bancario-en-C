#include <stdio.h>
#include <stdbool.h>
#include <time.h>
// Establecer el idioma a español
#include <locale.h>
// Para limpiar consola
#ifdef _WIN32
  #include<windows.h>
#endif

typedef struct{
    char IDCliente[20];
    char nombre[20];
    char ciudad[20];
    char direccion[20];
    char edad[20];
    char telefono[20];
} Cliente;

typedef struct{
    char IDCuenta[20];
    char IDCliente[20];
    char NIP[5];
    char NTipoCuenta;
    float Saldo;
} Cuenta;

typedef struct{
    char IDCuenta[20];
    char tipoDeMovimiento[20];
    float monto;
    time_t fecha;
} Movimiento;

void limpiarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void establecerIdiomaAEspanol(){
    // Establecer el idioma a español
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows
}

bool volverAlMenuPrincipal(){
    printf("\n¿Desea volver al menú principal? (s/n): ");
    char volverAlMenuPrincipal1;
    fflush(stdin);
    scanf("%c", &volverAlMenuPrincipal1);
    if(volverAlMenuPrincipal1 == 's')
        return true;
    else return false;
}

bool validarCliente(char const *nombreDelCliente){
    bool clienteExiste;
    FILE *archivo;
    Cliente clienteRegistrado;
    archivo = fopen ("clientes.dat", "rb");
    if (archivo == NULL){
        fprintf(stderr, "\n>> Error al abrir el archivo\n");
        exit(1);
    }
    while(fread(&clienteRegistrado, sizeof(Cliente), 1, archivo)){
        if(strcmp(nombreDelCliente, clienteRegistrado.nombre) == 0){
            clienteExiste = true;
            break;
        }
    }
    fclose(archivo);

    if(clienteExiste == true) printf("\n>> Cliente encontrado\n");
    else printf("\n>> Cliente no encontrado\n");
    return clienteExiste;
}

bool validarCuenta(char const *numeroDeCuenta){
    bool cuentaExiste;
    FILE *archivo;
    Cuenta cuentaRegistrada;
    archivo = fopen ("cuentas.dat", "rb");
    if (archivo == NULL){
        fprintf(stderr, "\n>> Error al abrir el archivo\n");
        exit(1);
    }
    while(fread(&cuentaRegistrada, sizeof(Cuenta), 1, archivo)){
        if(strcmp(numeroDeCuenta, cuentaRegistrada.IDCuenta) == 0){
            cuentaExiste = true;
            break;
        }
    }
    fclose(archivo);

    if(cuentaExiste) printf("\n>> Cuenta encontrada\n");
    else printf("\n>> Cuenta no encontrada\n");
    return cuentaExiste;
}

/*bool validarCuentaMovimiento(char const *numeroDeCuenta){
    bool cuentaExiste;
    FILE *archivo;
    Movimiento cuentaRegistrada;
    archivo = fopen ("movimientos.dat", "rb");
    if (archivo == NULL){
        fprintf(stderr, "\n>> Error al abrir el archivo\n");
        exit(1);
    }
    while(fread(&cuentaRegistrada, sizeof(Movimiento), 1, archivo)){
        if(strcmp(numeroDeCuenta, cuentaRegistrada.IDCuenta) == 0){
            cuentaExiste = true;
            break;
        }
    }
    fclose(archivo);

    if(cuentaExiste) printf("\n>> Cuenta movimientos encontrada\n");
    else printf("\n>> Cuenta movimientos no encontrada\n");
    return cuentaExiste;
}*/

void registarMovimiento(char const *IDCuenta, char const *tipoDeMovimiento, float monto){
    time_t fechaAhora;
    time(&fechaAhora);

    Movimiento nuevoMovimiento;
    strcpy(nuevoMovimiento.IDCuenta, IDCuenta);
    strcpy(nuevoMovimiento.tipoDeMovimiento, tipoDeMovimiento);
    nuevoMovimiento.monto = monto;
    nuevoMovimiento.fecha = fechaAhora;

    FILE *archivo = fopen ("movimientos.dat", "ab");
    if (archivo == NULL){
        fprintf(stderr, "\n>> Error al abrir el archivo\n");
        exit(1);
    }
    fwrite(&nuevoMovimiento, sizeof(Movimiento), 1, archivo);
    if(fwrite != 0)
        printf("\n>> Movimiento almacenados correctamente\n");
    else
        printf("\n>> Error al guardar movimiento\n");
    fclose (archivo);
}

void consultarMovimiento(char const *numeroDeCuenta){
    /*validarCuentaMovimiento(numeroDeCuenta);*/

    //Abriendo archivo para lectura
    FILE *archivo = fopen ("movimientos.dat", "rb");
    if (archivo == NULL){
        fprintf(stderr, "\n>> Error al abrir el archivo\n");
        exit(1);
    }
    //Leyendo el contenido del archivo hasta su final
    Movimiento movimientoRegistrado;
    while(fread(&movimientoRegistrado, sizeof(Movimiento), 1, archivo)){
        if(strcmp(numeroDeCuenta, movimientoRegistrado.IDCuenta) == 0){
            printf("\n\nNúmero de cuenta: %s\n"
                "Tipo de movimiento: %s\n"
                "Monto: %.2f\n"
                "Fecha: %s\n"
                "----------------------------------------",
                movimientoRegistrado.IDCuenta, movimientoRegistrado.tipoDeMovimiento, movimientoRegistrado.monto, ctime(&movimientoRegistrado.fecha));
        }
    }
    //Cerrando el archivo
    fclose(archivo);
}

int main(){
    establecerIdiomaAEspanol();

    //Menú del sistema
    MenuPrincipal:
    limpiarPantalla();

    printf("<-SISTEMA BANCARIO->"
        "\n |-MENÚ PRINCIPAL-|\n"
        "\n1.Clientes\n2.Cuentas\n3.Depósitos/Retiros\n4.Pagos\n5.Transferencia\n6.Inversión\n7.Estado de Cuenta\n8.Salir\n"
        "\nSu opción: ");
    int opcionElegidaMenu;
    scanf("%d", &opcionElegidaMenu);

    limpiarPantalla();

    //Submenús del sistema
    switch(opcionElegidaMenu){
        //Submenú Clientes
        { case 1:
            printf("|-CLIENTES:-|\n"
                   "\n1.Registro\n2.Consulta\n3.Regresar al menú principal\n"
                   "\nSu opción: ");
            int opcionElegidaSubmenu;
            scanf("%d", &opcionElegidaSubmenu);

            limpiarPantalla();

            switch(opcionElegidaSubmenu){
                case 1:
                    printf("|-REGISTRO DEL CLIENTE-|\n\n");

                    //Registro del cliente
                    Cliente nuevoCliente;
                    printf("ID: ");
                    scanf("%s", nuevoCliente.IDCliente);
                    printf("Nombre: ");
                    fflush(stdin);
                    scanf("%[^\n]s", nuevoCliente.nombre);
                    printf("Ciudad: ");
                    scanf("%s", nuevoCliente.ciudad);
                    printf("Dirección: ");
                    fflush(stdin);
                    scanf("%[^\n]s", nuevoCliente.direccion);
                    printf("Edad: ");
                    scanf("%s", nuevoCliente.edad);
                    printf("Teléfono: ");
                    scanf("%s", nuevoCliente.telefono);
                    limpiarPantalla();
                    printf("|-REGISTRO DEL CLIENTE-|\n");
                    printf("\nLos datos del cliente registrado son: \nID: %s\nNombre: %s\nCiudad: %s\nDirección: %s\nEdad: %s\nTeléfono: %s\n", nuevoCliente.IDCliente, nuevoCliente.nombre, nuevoCliente.ciudad, nuevoCliente.direccion, nuevoCliente.edad, nuevoCliente.telefono);

                    //Abriendo archivo para escribir
                    FILE *archivoClientesRegistro = fopen ("clientes.dat", "ab");
                    if (archivoClientesRegistro == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Escribiendo estructura en el archivo
                    fwrite(&nuevoCliente, sizeof(Cliente), 1, archivoClientesRegistro);
                    if(fwrite != 0)
                        printf("\n>> Datos almacenados correctamente\n");
                    else
                        printf("\n>> Error al guardar datos\n");

                    //Cerrando el archivo
                    fclose (archivoClientesRegistro);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;
                break;
                case 2:
                    printf("|-CONSULTA DEL CLIENTE-|\n\n");

                    printf("Introduce el nombre del cliente: ");
                    char nombreDelCliente[20];
                    fflush(stdin);
                    scanf("%[^\n]s", nombreDelCliente);

                    //Validando cliente
                    validarCliente(nombreDelCliente);

                    //Abriendo el archivo para leer
                    FILE *archivoClientesConsulta = fopen ("clientes.dat", "rb");
                    if (archivoClientesConsulta == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Leyendo el contenido del archivo hasta su final
                    Cliente clienteRegistrado;
                    while(fread(&clienteRegistrado, sizeof(Cliente), 1, archivoClientesConsulta)){
                        if(strcmp(nombreDelCliente, clienteRegistrado.nombre) == 0)
                            printf("\nLos datos del cliente solicitado son:\nID: %s\nNombre: %s\nCiudad: %s\nDirección: %s\nEdad: %s\nTeléfono: %s\n", clienteRegistrado.IDCliente, clienteRegistrado.nombre, clienteRegistrado.ciudad, clienteRegistrado.direccion, clienteRegistrado.edad, clienteRegistrado.telefono);
                    }
                    //Cerrando el archivo
                    fclose(archivoClientesConsulta);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;
                break;
                case 3:
                    goto MenuPrincipal;
                break;
            }
        break; }

        //Submenú Cuentas
        { case 2:
            printf("|-CUENTAS:-|\n"
                "\n1.Registro\n2.Consulta\n3.Regresar al menú principal\n"
                "\nSu opción: ");
            int opcionElegidaSubmenu;
            scanf("%d", &opcionElegidaSubmenu);

            limpiarPantalla();

            switch(opcionElegidaSubmenu){
                case 1:
                    printf("|-REGISTRO DE CUENTA-|\n\n");

                    //Registro de cuenta
                    Cuenta nuevaCuenta;
                    printf("Número de cuenta: ");
                    scanf("%s", nuevaCuenta.IDCuenta);
                    printf("ID del cliente: ");
                    scanf("%s", nuevaCuenta.IDCliente);
                    printf("Clave: ");
                    scanf("%s", nuevaCuenta.NIP);
                    fflush(stdin);
                    printf("Tipos de cuenta (d/c): ");
                    scanf("%c", &nuevaCuenta.NTipoCuenta);
                    printf("Saldo: ");
                    scanf("%f", &nuevaCuenta.Saldo);
                    limpiarPantalla();
                    printf("|-REGISTRO DE CUENTA-|\n");
                    printf("\nLos datos de la cuenta registrada son: \nNúmero de cuenta: %s \nID del cliente: %s \nClave: %s \nTipo de cuenta: %c \nSaldo: %.2f\n", nuevaCuenta.IDCuenta, nuevaCuenta.IDCliente, nuevaCuenta.NIP, nuevaCuenta.NTipoCuenta, nuevaCuenta.Saldo);

                    //Abriendo archivo para escribir
                    FILE *archivoCuentasRegistro = fopen ("cuentas.dat", "ab");
                    if (archivoCuentasRegistro == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Escribiendo estructura en el archivo
                    fwrite(&nuevaCuenta, sizeof(Cuenta), 1, archivoCuentasRegistro);
                    if(fwrite != 0)
                        printf("\n>> Datos almacenados correctamente\n");
                    else
                        printf("\n>> Error al guardar datos\n");

                    //Cerrando el archivo
                    fclose (archivoCuentasRegistro);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;
                break;
                case 2:
                    printf("|-CONSULTA DE CUENTA-|\n\n");

                    printf("Introduce el número de cuenta: ");
                    char numeroDeCuenta[20];
                    fflush(stdin);
                    scanf("%s", numeroDeCuenta);

                    //Validando cuenta
                    validarCuenta(numeroDeCuenta);

                    //Abriendo archivo para lectura
                    FILE *archivoCuentasConsulta = fopen ("cuentas.dat", "rb");
                    if (archivoCuentasConsulta == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Leyendo el contenido del archivo hasta su final
                    Cuenta cuentaRegistrada;
                    while(fread(&cuentaRegistrada, sizeof(Cuenta), 1, archivoCuentasConsulta)){
                        if(strcmp(numeroDeCuenta, cuentaRegistrada.IDCuenta) == 0){
                            printf("\nLos datos de la cuenta solicitada son: \nNúmero de cuenta: %s \nID del cliente: %s \nClave: %s \nTipo de cuenta: %c \nSaldo: %.2f\n", cuentaRegistrada.IDCuenta, cuentaRegistrada.IDCliente, cuentaRegistrada.NIP, cuentaRegistrada.NTipoCuenta, cuentaRegistrada.Saldo);
                        }
                    }
                    //Cerrando el archivo
                    fclose(archivoCuentasConsulta);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;
                break;
                case 3:
                    goto MenuPrincipal;
                break;
            }
        break; }

        //Submenú Depósito/Retiro
        { case 3:
            printf("|-DEPÓSITO/RETIRO:-|\n"
                "\n1.Depósito\n2.Retiro\n3.Regresar al menú principal\n"
                "\nSu opción: ");
            int opcionElegidaSubmenu;
            scanf("%d", &opcionElegidaMenu);

            limpiarPantalla();

            switch(opcionElegidaMenu){
                case 1:{
                    printf("|-DEPÓSITO-|\n\n");
                    printf("Introduzca el número de la cuenta a la que desea depositar: ");
                    char numeroDeCuentaDeposito[20];
                    fflush(stdin);
                    scanf("%s", numeroDeCuentaDeposito);

                    //Validando cuenta
                    validarCuenta(numeroDeCuentaDeposito);

                    //Abriendo archivo para lectura y escritura
                    FILE *archivoCuentasDeposito = fopen ("cuentas.dat", "rb+");
                    if (archivoCuentasDeposito == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Guardando posición del cursor
                    long int posDeposito = ftell(archivoCuentasDeposito);
                    //Leyendo y modificando el contenido del archivo hasta su final
                    Cuenta cuentaRegistrada;
                    while(fread(&cuentaRegistrada, sizeof(Cuenta), 1, archivoCuentasDeposito)){
                        if(strcmp(numeroDeCuentaDeposito, cuentaRegistrada.IDCuenta) == 0){
                            printf("\nIngresar el monto a depositar: ");
                            float montoADepositar;
                            scanf("%f", &montoADepositar);

                            printf("Confirmar transacción (s/n): ");
                            char confirmarTransaccion;
                            fflush(stdin);
                            scanf("%c", &confirmarTransaccion);

                            if(confirmarTransaccion == 's'){
                                cuentaRegistrada.Saldo += montoADepositar;
                                registarMovimiento(numeroDeCuentaDeposito, "Depósito", montoADepositar);
                                fseek(archivoCuentasDeposito, -sizeof(Cuenta), SEEK_CUR);
                                fwrite(&cuentaRegistrada, sizeof(Cuenta), 1, archivoCuentasDeposito);
                                printf("\n>> Depositados %.2f al número de cuenta %s\n", montoADepositar, numeroDeCuentaDeposito);
                                break;
                            } else printf("\n>> Transacción cancelada\n");
                        }
                    }
                    //Reestableciendo posición del cursor
                    fseek(archivoCuentasDeposito, posDeposito, SEEK_SET);
                    //Cerrando el archivo
                    fclose(archivoCuentasDeposito);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;}
                break;
                case 2:
                    printf("|-RETIRO-|\n\n");
                    printf("Introduzca el número de la cuenta de la que desea retirar: ");
                    char numeroDeCuentaRetiro[20];
                    fflush(stdin);
                    scanf("%s", numeroDeCuentaRetiro);

                    //Validando cuenta
                    validarCuenta(numeroDeCuentaRetiro);

                    //Abriendo archivo para lectura y escritura
                    FILE *archivoCuentasRetiro = fopen ("cuentas.dat", "rb+");
                    if (archivoCuentasRetiro == NULL){
                        fprintf(stderr, "\n>> Error al abrir el archivo\n");
                        exit(1);
                    }
                    //Guardando posición del cursor
                    long int posRetiro = ftell(archivoCuentasRetiro);
                    //Leyendo y modificando el contenido del archivo hasta su final
                    Cuenta cuentaRegistradaRetiro;
                    while(fread(&cuentaRegistradaRetiro, sizeof(Cuenta), 1, archivoCuentasRetiro)){
                        if(strcmp(numeroDeCuentaRetiro, cuentaRegistradaRetiro.IDCuenta) == 0){
                            printf("\nIntroduzca la clave de la cuenta de la que desea retirar: ");
                            char contrasenia[5];
                            fflush(stdin);
                            scanf("%s", contrasenia);

                            if(strcmp(contrasenia, cuentaRegistradaRetiro.NIP) == 0){
                                printf("Ingresar el monto a retirar: ");
                                float montoARetirar;
                                scanf("%f", &montoARetirar);

                                printf("Confirmar transacción (s/n): ");
                                char confirmarTransaccion;
                                fflush(stdin);
                                scanf("%c", &confirmarTransaccion);

                                if(confirmarTransaccion == 's'){
                                    if(cuentaRegistradaRetiro.Saldo >= montoARetirar && cuentaRegistradaRetiro.Saldo > 0){
                                        cuentaRegistradaRetiro.Saldo -= montoARetirar;
                                        registarMovimiento(numeroDeCuentaRetiro, "Retiro", montoARetirar);
                                    } else {
                                        printf("\n>> Saldo insuficiente\n");
                                        break;
                                    }
                                    fseek(archivoCuentasRetiro, -sizeof(Cuenta), SEEK_CUR);
                                    fwrite(&cuentaRegistradaRetiro, sizeof(Cuenta), 1, archivoCuentasRetiro);
                                    printf("\n>> Retirados %.2f del número de cuenta %s\n", montoARetirar, numeroDeCuentaRetiro);
                                    break;
                                } else {
                                    printf("\n>> Transacción cancelada\n");
                                    break;
                                }
                            } else {
                                printf("\n>> Contraseña inválida\n");
                                break;
                            }
                        }
                    }
                    //Reestableciendo posición del cursor
                    fseek(archivoCuentasRetiro, posRetiro, SEEK_SET);
                    //Cerrando el archivo
                    fclose(archivoCuentasRetiro);

                    if(volverAlMenuPrincipal())
                        goto MenuPrincipal;
                break;
                case 3:
                    goto MenuPrincipal;
                break;
            }
        break;}

        //Submenú Pagos
        { case 4:
            printf("|-PAGOS:-|\n\n");
            printf("Ingrese su número de cuenta (crédito): ");
            char numeroDeCuentaPagos[20];
            scanf("%s", numeroDeCuentaPagos);

            //Validando cuenta
            validarCuenta(numeroDeCuentaPagos);

            //Abriendo archivo para lectura y escritura
            FILE *archivoCuentasPagos = fopen ("cuentas.dat", "rb+");
            if (archivoCuentasPagos == NULL){
                fprintf(stderr, "\n>> Error al abrir el archivo\n");
                exit(1);
            }
            //Guardando posición del cursor
            long int posPagos = ftell(archivoCuentasPagos);
            //Leyendo y modificando el contenido del archivo hasta su final
            Cuenta cuentaRegistradaPagos;
            while(fread(&cuentaRegistradaPagos, sizeof(Cuenta), 1, archivoCuentasPagos)){
                if(strcmp(numeroDeCuentaPagos, cuentaRegistradaPagos.IDCuenta) == 0 && cuentaRegistradaPagos.NTipoCuenta == 'c'){
                    printf("\nIntroduzca la clave de la cuenta con la que desea pagar: ");
                    fflush(stdin);
                    char contrasenia[5];
                    scanf("%s", contrasenia);

                    if(strcmp(contrasenia, cuentaRegistradaPagos.NIP) == 0){
                        printf("Ingresar el monto a pagar: ");
                        float montoAPagar;
                        scanf("%f", &montoAPagar);

                        printf("Confirmar transacción (s/n): ");
                        char confirmarTransaccion;
                        fflush(stdin);
                        scanf("%c", &confirmarTransaccion);

                        if(confirmarTransaccion == 's'){
                            if(cuentaRegistradaPagos.Saldo >= montoAPagar && cuentaRegistradaPagos.Saldo > 0){
                                cuentaRegistradaPagos.Saldo -= montoAPagar;
                                registarMovimiento(numeroDeCuentaPagos, "Pago", montoAPagar);
                            } else {
                                printf("\n>> Límite de crédito excedido\n");
                                break;
                            }
                            fseek(archivoCuentasPagos, -sizeof(Cuenta), SEEK_CUR);
                            fwrite(&cuentaRegistradaPagos, sizeof(Cuenta), 1, archivoCuentasPagos);
                            printf("\n>> Pagados %.2f con el número de cuenta %s\n", montoAPagar, numeroDeCuentaPagos);
                            break;
                        } else {
                            printf("\n>> Transacción cancelada\n");
                            break;
                        }
                    } else {
                        printf("\n>> Contraseña inválida\n");
                        break;
                    }
                }
            }
            //Reestableciendo la posición del cursor
            fseek(archivoCuentasPagos, posPagos, SEEK_SET);
            //Cerrando el archivo
            fclose(archivoCuentasPagos);

            if(volverAlMenuPrincipal())
                goto MenuPrincipal;
        break; }

        //Submenú Transferencia
        { case 5:
            printf("|-TRANSFERENCIA-|\n\n");

            //Cuenta destino
            printf("Introduzca el número de la cuenta destino: ");
            char numeroDeCuentaTransferenciaDestino[20];
            fflush(stdin);
            scanf("%s", numeroDeCuentaTransferenciaDestino);
            //Validando cuenta destino
            validarCuenta(numeroDeCuentaTransferenciaDestino);

            //Cuenta origen
            printf("\nIntroduzca el número de la cuenta origen: ");
            char numeroDeCuentaTransferenciaOrigen[20];
            fflush(stdin);
            scanf("%s", numeroDeCuentaTransferenciaOrigen);
            float montoATransferir;
            //Validando cuenta origen
            validarCuenta(numeroDeCuentaTransferenciaOrigen);

            //Abriendo archivo para lectura y escritura
            FILE *archivoCuentasTransferenciaOrigen = fopen ("cuentas.dat", "rb+");
            if (archivoCuentasTransferenciaOrigen == NULL){
                fprintf(stderr, "\n>> Error al abrir el archivo\n");
                exit(1);
            }
            //Guardando posición del cursor
            long int posTransferenciaOrigen = ftell(archivoCuentasTransferenciaOrigen);
            //Leyendo y modificando el contenido del archivo hasta su final
            Cuenta cuentaRegistradaOrigen;
            while(fread(&cuentaRegistradaOrigen, sizeof(Cuenta), 1, archivoCuentasTransferenciaOrigen)){
                if(strcmp(numeroDeCuentaTransferenciaOrigen, cuentaRegistradaOrigen.IDCuenta) == 0){
                    printf("\nIntroduzca la clave de la cuenta de la cuenta origen: ");
                    char contrasenia[5];
                    fflush(stdin);
                    scanf("%s", contrasenia);

                    if(strcmp(contrasenia, cuentaRegistradaOrigen.NIP) == 0){
                        printf("Ingresar el monto a transferir: ");
                        scanf("%f", &montoATransferir);

                        printf("Confirmar transacción (s/n): ");
                        char confirmarTransaccion;
                        fflush(stdin);
                        scanf("%c", &confirmarTransaccion);

                        if(confirmarTransaccion == 's'){
                            if(cuentaRegistradaOrigen.Saldo >= montoATransferir && cuentaRegistradaOrigen.Saldo > 0){
                                cuentaRegistradaOrigen.Saldo -= montoATransferir;
                                registarMovimiento(numeroDeCuentaTransferenciaOrigen, "Transferencia", montoATransferir);
                            } else {
                                printf("\n>> Saldo insuficiente\n");
                                break;
                            }
                            fseek(archivoCuentasTransferenciaOrigen, -sizeof(Cuenta), SEEK_CUR);
                            fwrite(&cuentaRegistradaOrigen, sizeof(Cuenta), 1, archivoCuentasTransferenciaOrigen);
                            printf("\n>> Retirados %.2f del número de cuenta %s\n", montoATransferir, numeroDeCuentaTransferenciaOrigen);
                            break;
                        } else {
                            printf("\n>> Transacción cancelada\n");
                            break;
                        }
                    } else {
                        printf("\n>> Contraseña inválida\n");
                        break;
                    }
                }
            }
            //Reestableciendo posición del cursor
            fseek(archivoCuentasTransferenciaOrigen, posTransferenciaOrigen, SEEK_SET);
            //Cerrando el archivo
            fclose(archivoCuentasTransferenciaOrigen);

            //Abriendo archivo para lectura y escritura
            FILE *archivoCuentasTransferenciaDestino = fopen ("cuentas.dat", "rb+");
            if (archivoCuentasTransferenciaDestino == NULL){
                fprintf(stderr, "\n>> Error al abrir el archivo\n");
                exit(1);
            }
            //Guardando posición del cursor
            long int posTransferenciaDestino = ftell(archivoCuentasTransferenciaDestino);
            //Leyendo y modificando el contenido del archivo hasta su final
            Cuenta cuentaRegistradaDestino;
            while(fread(&cuentaRegistradaDestino, sizeof(Cuenta), 1, archivoCuentasTransferenciaDestino)){
                if(strcmp(numeroDeCuentaTransferenciaDestino, cuentaRegistradaDestino.IDCuenta) == 0){
                    cuentaRegistradaDestino.Saldo += montoATransferir;
                    fseek(archivoCuentasTransferenciaDestino, -sizeof(Cuenta), SEEK_CUR);
                    fwrite(&cuentaRegistradaDestino, sizeof(Cuenta), 1, archivoCuentasTransferenciaDestino);
                    printf("\n>> Transferidos %.2f al número de cuenta %s\n", montoATransferir, numeroDeCuentaTransferenciaDestino);
                    break;
                }
            }
            //Reestableciendo posición del cursor
            fseek(archivoCuentasTransferenciaDestino, posTransferenciaDestino, SEEK_SET);
            //Cerrando el archivo
            fclose(archivoCuentasTransferenciaDestino);

            if(volverAlMenuPrincipal())
                goto MenuPrincipal;
        break; }

        //Submenú Inversión
        { case 6:
            printf("|-INVERSIÓN-|\n\n");

            float capital, montoMensual, montoTotal;
            int meses, interes;
            printf("Ingrese el capital que se desea invertir: ");
            scanf("%f", &capital);
            fflush(stdin);
            printf("Ingrese la cantidad de meses en los que colocará la inversión: ");
            fflush(stdin);
            scanf("%d", &meses);
            printf("Ingrese la tasa de interés (%%): ");
            fflush(stdin);
            scanf("%d", &interes);

            montoMensual = (capital+(capital/100)*interes)/meses;
            montoTotal = montoMensual*meses;

            printf("\nRecibirá %.2f durante %d meses\n", montoMensual, meses);
            printf("Beneficios: %.2f\n", montoTotal-capital);
            printf("Total recibido: %.2f\n", montoTotal);

            if(volverAlMenuPrincipal())
                goto MenuPrincipal;
        break; }

        //Submenú Estado de Cuenta
        { case 7:
            printf("|-Estado de Cuenta-|\n\n");
            printf("Ingrese su número de cuenta (crédito): ");
            char numeroDeCuentaMovimientos[20];
            scanf("%s", numeroDeCuentaMovimientos);

            printf("Mostrando movimientos:\n\n"
                   "----------------------------------------");
            consultarMovimiento(numeroDeCuentaMovimientos);
            printf("\n\n");

            if(volverAlMenuPrincipal())
                goto MenuPrincipal;
        break; }

        case 8:
            exit(0);
        break;

        default: printf("\n>> Opción inválida\n"); break;
    }
    return 0;
}
