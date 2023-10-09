#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

/* 
Un restaurante tiene 25 variedades de platos principales, 12 de postres y 20 de bebidas
Se cuenta con una planilla donde cada fila es un producto, y cada columna se identifica con
stock minimos, stock actual, tipo (plato principal, postre y bebida) y precio (CONSIDERE ENTERO)

Simular un dia de atencion teniendo en cuenta que cada cliente puede adquirir hasta 3 unidades por
tipo de producto

En el caso de que no hubiera stock de alguno de los productos indicarselo al cliente por medio de un
mensaje

Se requiere otra planilla que se actualizara por cada venta donde cada fila es un producto y en la
columna se identifica la cantidad que se va vendiendo y en otras columnas que indiques el tipo de etrega
para el producto (Delivery y Mostador)

Las ventas se ralizan hasta que se indique que se cierra la caja

Se deben visualizar los siguientes resultados:
    - Cuanto se recauda en cada tipo de tipoEntrega (Delivery y Mostrador)
    - Que porcentaje representa los platos, los postres y las bebidas sobre el total de las ventas
    - Armar una planilla de los productos a reponer teniendo en cuenta que el stock actual sea menor al 
    stock minimo, la columna reposicion es el stock minimo +30%
    ( ESTA PLANILLA LA IMPRIMO DIRECTAMENTE PORQUE NO SE CUANTOS PRODUCTOS SON )
 */
/* 
   plato principal = 1
            postre = 2
            bebida = 3
 */

//TODO: TIENE QUE SER 57, PUSE MENOS PARA TESTING
const cantProd = 2;
int carta[2][4]; // tengo todos los productos en la carta
// stock minimos, stock actual, tipo (plato principal, postre y bebida) y precio (CONSIDERE ENTERO)
char productos[2][20]; // tengo los nombres de los productos
int ventas[2][3]; // marco las ventas (total - delivery - mostrador)

int opcion = 1; // para el menu
char tipoEntrega;   // si es 'd' o 'm'
void imprimirCarta();
main(){
for (int i = 0; i < cantProd; i++){
    for (int j = 0; j < 4; j++){
        carta[i][j] = 0;
    }
}
for (int i = 0; i < cantProd; i++){
    for (int j = 0; j < 3; j++){
        ventas[i][j] = 0;
    }
}
/* MENU */
while(opcion != 0){
    printf("MENU - ingrese una opcion:\n");
    printf("1: Cargar carta\n");
    printf("2: Registrar venta\n");
    printf("3: Cerrar Dia\n");
    printf("0: Salir\n");
    scanf("%d", &opcion);
    switch (opcion){
        case 1:
            /* INGRESO DATOS */
            for (int i = 0; i < cantProd; i++){
                printf("Ingrese nombre del producto: ");
                scanf("%s", &productos[i]);

                printf("ingrese stock minimo: ");
                scanf("%d", &carta[i][0]);
                printf("ingrese stock actual: ");
                scanf("%d", &carta[i][1]);
                printf("tipos:\nplato principal = 1\npostre = 2\nbebida = 3\n");
                printf("ingrese tipo (1, 2, 3): ");
                scanf("%d", &carta[i][2]);
                /* siguiente parte de validacion | opcional */
                while(carta[i][2] < 1 || carta[i][2] > 3){
                    printf("valor ingresado incorrecto, intente nuevamente: ");
                    scanf("%d", &carta[i][2]);
                }
                printf("ingrese precio: ");
                scanf("%d", &carta[i][3]);
            }           
        break;
        case 2:
            /* Nueva venta */
            printf("Es por delivery (d) o mostrador (m)? : ");
            scanf(" %c", &tipoEntrega);
            /* validacion */
            //FIXME: NO VALIDA
            /* while(tipoEntrega != "d" || tipoEntrega != "m"){
                printf("opcion invalida, intente nuevamente: ");
                scanf(" %c", &tipoEntrega);
            } */
            registrarVenta(1, tipoEntrega);
            registrarVenta(2, tipoEntrega);
            registrarVenta(3, tipoEntrega);
        break;
        case 3:
            /* Cierro el dia */
            mostrarIngresosPorEntrega();
            mostrarPorcentajePorVenta();
            mostrarPlanillaReposicion();
        break;
        case 0:
            opcion = 0;
        break;

    default:
        /* opcion invalida */
        printf("Opcion invalida, intente nuevamente.\n");
        break;
    }
}





    
}
void mostrarIngresosPorEntrega(){
    int gananciaDelivery = 0; 
    int gananciaMostrador = 0; 
    for(int i = 0; i < cantProd; i++){
        gananciaDelivery += ventas[i][1]*carta[i][3];
        gananciaMostrador += ventas[i][2]*carta[i][3];
    }
    printf("Se recaudo $%d en delivery\n", gananciaDelivery);
    printf("Se recaudo $%d en mostrador\n\n", gananciaMostrador);
}

void mostrarPorcentajePorVenta(){
    float total = 0;
    float porcentajes[3] = {0, 0, 0};
    for(int i = 0; i < cantProd; i++){
        porcentajes[carta[i][2]-1] += ventas[i][0];
        total += ventas[i][0];
    }
    for(int i = 0; i < 3; i++){
        porcentajes[i] = (porcentajes[i] / total) * 100;
    }
    printf("se vendio un %.1f %% de platos principales.\n", porcentajes[0]);
    printf("se vendio un %.1f %% de postres.\n", porcentajes[1]);
    printf("se vendio un %.1f %% de bebidas.\n", porcentajes[2]);
}

void mostrarPlanillaReposicion(){
    printf("\n\nPlanilla de Reposicion:\n");
    for(int i = 0; i < cantProd; i++){
        if(carta[i][1] < carta[i][0]){
            printf("%s\t|\t%.1f\n", productos[i], ceil(carta[i][0]*1.3));
        }
    }
}


void registrarVenta(int tipo, char tipoEntrega){
    char seleccion[20]; // que plato pedire
    int cantPedida = 0; // para que no se pase de los 3 por tipo
    int indice = 0;     // para buscar el plato en la carta
    bool encontro = false;
    char nombreTipo[3][20] = {"plato principal", "postre", "bebida"};
    

    printf("Ingresar %s o 'S' para saltar: ", nombreTipo[tipo-1]);
    scanf("%s", seleccion);
    while(strcmp("S", seleccion)){
        // busca el indice del producto que se pide
        while(indice < cantProd && !encontro){
            if(!strcmp(seleccion, productos[indice])){
                encontro = true;
            }else{
                indice++;
            }
        }
        if (encontro){
            // reviso que sea del tipo deseado
            if(carta[indice][2] != tipo){
                printf("El producto no es %s.\n", nombreTipo[tipo-1]);
            }
            // reviso stock
            else if(carta[indice][1] == 0){ // el stock ya llego al minimo
                printf("No se encuentra stock del producto.\n");
            } else{ // hay stock, entonces hago todo lo demas
                carta[indice][1]--;
                // guardo la venta
                if(tipoEntrega == 'd') ventas[indice][1]++;
                if(tipoEntrega == 'm') ventas[indice][2]++;
                ventas[indice][0]++;
                cantPedida++;
            }
        } else {
            printf("Producto no Encontrado.\n");
        }

        if(cantPedida == 3){
            printf("La cantidad de '%s' llego al maximo.\n", nombreTipo[tipo-1]);
            strcpy(seleccion, "S");
        }else{
            printf("Ingresar %s o 'S' para saltar: ", nombreTipo[tipo-1]);
            scanf("%s", seleccion);
        }
    }
}

void imprimirVentas(){
    for (int i = 0; i < cantProd; i++){
        printf("%d\n", i+1);
        printf("Producto: %s\n", productos[i]);
        printf("total: %d\n", ventas[i][0]);
        printf("delivery: %d\n", ventas[i][1]);
        printf("mostrador: %d\n", ventas[i][2]);
    }
}

void imprimirCarta(){
    for (int i = 0; i < cantProd; i++){
        printf("%d\n", i+1);
        printf("Producto: %s\n", productos[i]);
        printf("stock minimo: %d\n", carta[i][0]);
        printf("stock actual: %d\n", carta[i][0]);
        printf("tipo: %d\n", carta[i][0]);
        printf("precio: %d\n", carta[i][0]);
    }
}