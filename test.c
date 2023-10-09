#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>



void main(){
    int mesas[5][2]; // columna 1 : disponibilidad | columna 2 : monto | columna 3 : cantidad max personas si lo veo necesario
    float a;
    float b;
    for(int i=0; i<5; i++){
        for(int j=0; j<2; j++){
            mesas[i][j] = 0;
        }
    }
    int on = 1;
    int cantComensales; // cada cubierto vale $100
    int monto;
    int opcion;
    while(on != 0){
        printf("1 - Nuevo pedido\n");
        printf("2 - Liberar Mesa\n");
        printf("3 - Cerrar dia\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:  
                bool encontro = false;
                int i = 0;
                while(i < 5 && !encontro){
                    if(mesas[i][0] == 0 /* && mesas[i][2] >= cantComensales */){ // por si tengo mesas con diferentes sillas
                        encontro = true;
                    }else{
                        i++;
                    }
                }
                if(encontro){
                    printf("mesa %d disponible.\n", i+1);

                    printf("Cantidad de comensales: "); // si tengo mesas con diferentes sillas, esto lo pongo al inicio del case
                    scanf("%d", &cantComensales);
                    printf("Monto: ");
                    scanf("%d", &monto);
                    monto = monto + cantComensales*100;

                    mesas[i][0] = 1;
                    mesas[i][1] = mesas[i][1] + monto;
                }else{
                    printf("no hay mesas disponibles.\n");
                }
            break;
            case 2:
                int nMesa;
                printf("Ingrese numero de mesa a liberar: ");
                scanf("%d", &nMesa);
                mesas[nMesa-1][0] = 0;
            break;
            case 3:
                for(int i=0; i<5; i++){
                    printf("%d\t", mesas[i][0]);
                    printf("%d\n", mesas[i][1]);
                }
                on = 0;
            break;
            default:
                /* opcion invalida */
                printf("Opcion invalida, intente nuevamente.\n");
            break;
        }
    }
    
 
 /*    printf("La suma de los numeros es: %f\n", suma(a, b));
printf("la resta de los numeros es: %f\n", resta(a , b));
printf("la division de los numeros es: %f\n", division(a , b)); */
}

/* float suma(float a, float b){
    float c = a + b;
    return c;
}
float resta(float a, float b){
    //float c = a - b;
    return 0; 
}

float division(float a, float b){
    float c = a / b;
    return c;
}

float multiplicacion(float a, float b){
    float c = a * b;
    return c;
} */