#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "clientes.h"

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
