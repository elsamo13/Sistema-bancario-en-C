typedef struct{
    char IDCliente[20];
    char nombre[20];
    char ciudad[20];
    char direccion[20];
    char edad[20];
    char telefono[20];
} Cliente;

bool validarCliente(char const *nombreDelCliente);
