#include <stdio.h>
#include <time.h>

#include "movimientos.h"

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
    if(fwrite(&nuevoMovimiento, sizeof(Movimiento), 1, archivo))
        printf("\n>> Movimiento almacenados correctamente\n");
    else
        printf("\n>> Error al guardar movimiento\n");
    fclose (archivo);
}

void consultarMovimiento(char const *numeroDeCuenta){
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
