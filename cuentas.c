#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cuentas.h"

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

