#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *bebidas[8] = {
    "Agua natural", "Refrescos", "Vino", "Cerveza", 
    "Whisky", "Licores", "Energéticos", "Combinados"
};

// Inicializa la matriz con ceros
void limpiarMatriz(int m[100][8]) {
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 8; j++)
            m[i][j] = 0;
    printf("Listo. Matriz limpia.\n\n");
}

// Pide datos al usuario para llenar la matriz
void meterDatos(int m[100][8]) {
    int tipo, litros;
    
    printf("Tipos de bebida:\n");
    for (int i = 0; i < 8; i++)
        printf("[%d] %s\n", i, bebidas[i]);
    printf("(-1 para dejar de registrar un pueblo)\n\n");

    for (int p = 0; p < 100; p++) {
        printf("=== Pueblo #%d ===\n", p + 1);
        while (1) {
            printf("Tipo de bebida: ");
            scanf("%d", &tipo);
            if (tipo == -1) break;
            if (tipo < 0 || tipo > 7) {
                printf("Ups... ese no existe.\n");
                continue;
            }
            printf("Litros consumidos: ");
            scanf("%d", &litros);
            m[p][tipo] = litros;
        }
        printf("\n");
    }
}

// Busca la bebida más popular (sin importar si es alcohol o no)
int masPopular(int m[100][8]) {
    int suma[8] = {0};

    for (int b = 0; b < 8; b++)
        for (int p = 0; p < 100; p++)
            suma[b] += m[p][b];

    int top = suma[0], cual = 0;
    for (int i = 1; i < 8; i++) {
        if (suma[i] > top) {
            top = suma[i];
            cual = i;
        }
    }

    printf("Bebida más consumida: %s (%d litros)\n", bebidas[cual], top);
    return cual;
}

// Solo bebidas alcohólicas
int masPopularAlcohol(int m[100][8]) {
    int suma[8] = {0};

    for (int b = 0; b < 8; b++) {
        if (b != 0 && b != 1 && b != 6) {
            for (int p = 0; p < 100; p++) {
                suma[b] += m[p][b];
            }
        }
    }

    int top = 0, cual = -1;
    for (int i = 0; i < 8; i++) {
        if (i != 0 && i != 1 && i != 6 && suma[i] > top) {
            top = suma[i];
            cual = i;
        }
    }

    if (cual != -1)
        printf("Bebida alcohólica más consumida: %s (%d litros)\n", bebidas[cual], suma[cual]);
    else
        printf("No se registró consumo alcohólico.\n");

    return cual;
}

// Pueblo con más alcohol
int puebloBorracho(int m[100][8]) {
    int suma[100] = {0};

    for (int p = 0; p < 100; p++) {
        for (int b = 0; b < 8; b++) {
            if (b != 0 && b != 1 && b != 6)
                suma[p] += m[p][b];
        }
    }

    int max = suma[0], cual = 0;
    for (int i = 1; i < 100; i++) {
        if (suma[i] > max) {
            max = suma[i];
            cual = i;
        }
    }

    printf("Pueblo que más bebe alcohol: #%d con %d litros\n", cual + 1, max);
    return cual;
}

int main() {
    int datos[100][8];

    printf("=== Registro de Consumo de Bebidas ===\n\n");

    limpiarMatriz(datos);
    meterDatos(datos);

    printf("Procesando datos...\n\n");

    masPopular(datos);
    masPopularAlcohol(datos);
    puebloBorracho(datos);

    printf("\nListo. Fin del análisis.\n");
    return 0;
}
