#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

void limpiarPantalla()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

typedef struct
{
    int idStruct;
} ID;

typedef struct
{
    ID id;
    char nombre[49];
    float precio;
    int cantidad;
    bool activo;
} Producto;

void validarNombre(char *nombre,Producto *producto, FILE *archivo, int *bandera)
{
    if (strlen(nombre) == 0)
    {
        printf("El nombre del producto no puede estar vacío.\n");
        *bandera = 1;
    }
    for(int i = 0; i < strlen(nombre); i++)
    {
        if (!isalnum((unsigned char)nombre[i]) && nombre[i] != ' ')
        {
            
            printf("El nombre del producto solo no puede contener caracteres especiales.\n");
            *bandera = 1;
            break;
        }
    }
    if(strlen(nombre) > 49)
    {
        printf("El nombre del producto no puede exceder los 50 caracteres.\n");
        *bandera = 1;
    }
    if(*bandera == 0)
    {

        rewind(archivo);

        Producto productoAuxiliar;

        while(fread(&productoAuxiliar, sizeof(Producto), 1, archivo) == 1)
        {
            if(strcmp(productoAuxiliar.nombre, nombre) == 0 && productoAuxiliar.activo == true)
            {
                printf("El nombre del producto ya existe en el archivo intente con otro nombre.\n");
                *bandera = 1;
                break;
            }
        }

    }
    if(*bandera == 0)
    {
        printf("Nombre del producto válido.\n");
        strcpy(producto->nombre, nombre);
    }
}

void agregarProducto(FILE *archivo)
{
    Producto nuevoProducto;
    char nombreProducto[49];
    int bandera = 0, banderaPrecio = 0, banderaCantidad = 0;

    nuevoProducto.activo = true;

    while(bandera == 0)
    {
    printf("\nIngrese el nombre del producto: ");
    scanf("%s", nombreProducto);
    getchar(); // Limpiar el buffer
    validarNombre(nombreProducto, nuevoProducto, archivo, &bandera);
    if(bandera == 1){
        limpiarPantalla();
        continue;
    }
    while(banderaPrecio == 0)
    {
    printf("\nIngrese el precio del producto: ");
    scanf("%f", &nuevoProducto.precio);
    getchar(); // Limpiar el buffer
    if(nuevoProducto.precio < 0)
    {
        printf("El precio del producto no puede ser negativo.\n");
        banderaPrecio = 0;
        limpiarPantalla();
        continue;

    }else{
        banderaPrecio = 1;
    }
    }
    while(banderaCantidad == 0)
    {
    printf("\nIngrese la cantidad del producto: ");
    scanf("%d", &nuevoProducto.cantidad);
    getchar(); // Limpiar el buffer
    if(nuevoProducto.cantidad < 0)
    {
        printf("La cantidad del producto no puede ser negativa.\n");
        banderaCantidad = 0;
        limpiarPantalla();
        continue;
    }else{
        banderaCantidad = 1;
    }
    }

    /*if(fseek(archivo, -1, * sizeof(ID), SEEK_END) == 0){
        ID idAuxiliar;
        if(fread(&idAuxiliar, sizeof(ID), 1, archivo) == 1)
        {
            nuevoProducto.id.idStruct = idAuxiliar.idStruct + 1;
        }
    }else{
        nuevoProducto.id.idStruct = 1;
    }*/ //SE TIENE QUE REVISAR EL ID YA QUE NO SE ESTA GUARDANDO EN EL ARCHIVO FISICO Y HACER CODIGO DEL NEGOCIO
}    
int main()
{   
    int bandera = 1;
    FILE *archivo = fopen("productos.txt", "ab");
        if(archivo==NULL)
        {
            printf("Error al abrir el archivo de productos.\n");
            return bandera = 0;
        }


            int opcion;
    do
    {
        
        printf("Ingrese una opción:\n");
        printf("1. Agregar Producto\n");
        printf("2. Modificar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Listar Productos\n");
        printf("5. Salir\n");    
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion)
        {
        case '1':
            agregarProducto(archivo);
            break;
        case '2':
            printf("Opción 2 seleccionada\n");
            break;
        case '3':
            printf("Opción 3 seleccionada\n");
            break;
        case '4':
            printf("Opción 4 seleccionada\n");
            break;
        case '5':
            printf("Opción 5 seleccionada\n");
            break;
        default:
            printf("Opción inválida. Intente nuevamente.\n");
            break;




    } while (bandera==1 && opcion != '5');
    return 0;
}
        }
    
