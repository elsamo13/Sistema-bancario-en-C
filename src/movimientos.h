typedef struct{
    char IDCuenta[20];
    char tipoDeMovimiento[20];
    float monto;
    time_t fecha;
} Movimiento;

void registarMovimiento(char const *IDCuenta, char const *tipoDeMovimiento, float monto);
void consultarMovimiento(char const *numeroDeCuenta);
