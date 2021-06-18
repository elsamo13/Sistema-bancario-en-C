typedef struct{
    char IDCuenta[20];
    char IDCliente[20];
    char NIP[5];
    char NTipoCuenta;
    float Saldo;
} Cuenta;

bool validarCuenta(char const *numeroDeCuenta);
