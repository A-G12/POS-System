#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Administrador();
void Ventas();
void Ticket(int c);
void Corte_caja();
void Mostrar_Inventario();
void Altas();
void Bajas();
void Consultas();
void Modificaciones();
void Menu_Usuarios();
void Altas_usuarios();
void Bajas_usuarios();
void Consultas_usuarios();
void Modificaciones_usuarios();
void Mostrar_usuarios();
void bubbleSort_inventario(int tipo);
void Cargar_datos();
void Guardar_datos();
void Actualizar_array_a_struct();
void Actualizar_struct_a_array();
void Actualizar_array_a_linked_list();
void Actualizar_linked_list_a_array();
int Buscar(char array_de_busqueda[][30], char *cosa_a_buscar, int tipo);
int Autentificacion(int tipo_usuario_a_acceder);

int Contador_productos;
int Contador_usuarios;
float Ventas_por_vendedor = 0;
float Ventas_de_vendedores = 0;

int Id[20];
char Producto[20][30];
float Pc[20];
float Pv[20];
int Existencias[20];
int Reorden[20];
int Estatus[20];

char Usuario[5][30];
char Password[5][30];
int Tipo_usuario[5];
int Estatus_usuario[5];

typedef struct {
    char producto[30];
    int cantidad;
    float costo;
    float unidad;
} Venta;
Venta venta[15];

typedef struct {
    char nombre[30];
    int id;
    float pc;
    float pv;
    int existencias;
    int reorden;
    int estatus;
} Inventario;
Inventario Articulo[10];

typedef struct Nodo{
    char usuario[30];
    char password[30];
    int tipo;
    int estatus;
    struct Nodo *sig;
} Nodo;

Nodo *inicio = NULL;
Nodo *nuevo = NULL;
Nodo *fin = NULL;
Nodo *temp = NULL;

int main(){
    int opcion, resultado;
    Cargar_datos();
    Actualizar_array_a_struct();
    Actualizar_array_a_linked_list();
    do{
        printf("Main menu\n");
        printf("1. Administrator\n");
        printf("2. Sales\n");
        printf("3. Exit\n");
        printf("Option: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: if(Autentificacion(opcion) == -1)
                    	Administrador();
                	break;
            case 2: if(Autentificacion(opcion) == -1)
                    	Ventas();
                	break;
            case 3: printf("Closing system ...\n");
                	break;
            default: printf("Invalid option\n");
        }
    } while(opcion != 3);
    Guardar_datos();
    return 0;
}

int Autentificacion(int tipo_usuario_a_acceder){
    int i;
    char usuario_tmp[30], pass_tmp[30];
    printf("User: ");
    scanf("%s", usuario_tmp);
    printf("Password: ");
    scanf("%s", pass_tmp);
    i = Buscar(Usuario, usuario_tmp, 2);
    if(i != -1){
        if(strcmp(Password[i], pass_tmp) == 0){
            if(Tipo_usuario[i] == tipo_usuario_a_acceder && Estatus_usuario[i] == 1)
                return -1;
            else{
                printf("The type of user you are looking to access is invalid or is unsubscribed\n");
                return 1;
            }
        }
		else{
            printf("Invalid user or password\n");
            return 1;
        }
    }
	else{
        printf("Invalid user or password\n");
        return 1;
    }
}

void Ticket(int c){
    float total_de_caja = 0;
    printf("Ticket:\n");
    printf("%15s%15s%25s%25s\n", "Product", "Quantity", "Unitary Price", "Subtotal");
    for(int i = 0; i < c; i++){
        if(strcmp(venta[i].producto, "") != 0){
            printf("%15s%15d%25.2f%25.2f\n", venta[i].producto, venta[i].cantidad, venta[i].unidad, venta[i].costo);
            total_de_caja += venta[i].costo;
            strcpy(venta[i].producto, "");
        }
    }
    Ventas_por_vendedor += total_de_caja;
    printf("Total: %.2f\n", total_de_caja);
}

void Ventas(){
    char opcion[10], producto[30];
    int cantidad, c = 0, i = 0;
    while(1){
        printf("Product: ");
        scanf("%s", producto);
        if(producto[0] == '*' && producto[1] == '*'){
            printf("Cash cut: %.2f\n", Ventas_por_vendedor);
            Ventas_de_vendedores += Ventas_por_vendedor;
            Ventas_por_vendedor = 0;
            break;
        }
        else if(producto[0] == '*'){
            Ticket(c + 1);
            c = 0;
            continue;
        }
        i = Buscar(Producto, producto, 1);
        if(i != -1 && Estatus[i] != 0){
            printf("Amount: ");
            scanf("%d", &cantidad);
            if(Existencias[i] < cantidad){
                printf("There are not %d product(s) of %s, there are only %d. Do you want to sell %d? (yes/no): ",cantidad, producto, Existencias[i], Existencias[i]);
                scanf("%s", opcion);
                if(strcmp(opcion, "no") == 0 || strcmp(opcion, "NO") == 0 || strcmp(opcion, "No") == 0)
                    continue;
                else
                    cantidad = Existencias[i];
            }
            strcpy(venta[c].producto, producto);
            venta[c].cantidad = cantidad;
            venta[c].unidad = Pv[i];
            venta[c].costo = cantidad * Pv[i];
            c++;
            Existencias[i] -= cantidad;
            Actualizar_array_a_struct();
            continue;
        }
		else{
            printf("Non-existent or discontinued product\n");
        }
    }
}

void Altas(){
    int i = 0;
    char prototipo_producto[50];
    while (1){
        printf("Product: ");
        scanf("%s", prototipo_producto);
        if (strcmp(prototipo_producto, "*") == 0)
            break;
        else if(Contador_productos < 50){
            i = Buscar(Producto, prototipo_producto, 1);
            if(i == -1){
                strcpy(Articulo[Contador_productos].nombre, prototipo_producto);
                printf("Id: ");
                scanf("%d", &Articulo[Contador_productos].id);
                while(1){
                    printf("Purchase price: ");
                    scanf("%f", &Articulo[Contador_productos].pc);
                    printf("Selling price: ");
                    scanf("%f", &Articulo[Contador_productos].pv);
                    if(Articulo[Contador_productos].pc < Articulo[Contador_productos].pv)
                        break;
                    printf("The purchase price cannot be greater than the selling price\n");
                }
                while(1){
                    printf("Stock: ");
                    scanf("%d", &Articulo[Contador_productos].existencias);
                    printf("Reorder level: ");
                    scanf("%d", &Articulo[Contador_productos].reorden);
                    if(Articulo[Contador_productos].existencias > Articulo[Contador_productos].reorden)
                        break;
                    printf("Stock must be greater than reorder level\n");
                }
                Articulo[Contador_productos].estatus = 1;
                Contador_productos++;
                Actualizar_struct_a_array();
                printf("Product successfully registered\n");
            }
			else if(Articulo[i].estatus == 0){
                Articulo[i].estatus = 1;
                Actualizar_struct_a_array();
                printf("The product \"%s\" is already registered, the product status has changed to active\n", prototipo_producto);
            }
			else
                printf("The product already exists and already had active status\n");
        }
        else
            printf("The maximum limit of products to be registered has been reached\n");
    }
}

void Bajas(){
    char producto_eliminar[50];
    while(1){
        int i = 0;
        printf("Product: ");
        scanf("%s", producto_eliminar);
        if(strcmp(producto_eliminar, "*") == 0)
            break;
        else{
            i = Buscar(Producto, producto_eliminar, 1);
            if (i == -1 || Articulo[i].estatus == 0)
                printf("Product not found or already discontinued\n");
            else{
                Articulo[i].estatus = 0;
                Actualizar_struct_a_array();
                printf("Product is already disabled\n");
            }
        }
    }
}

void Consultas(){
    char producto_a_buscar[50];
    while(1){
        int indice = 0;
        printf("Product: ");
        scanf("%s", producto_a_buscar);
        if(strcmp(producto_a_buscar, "*") == 0)
            break;
        else{
            indice = Buscar(Producto, producto_a_buscar, 1);
            if(indice == -1 || Articulo[indice].estatus == 0)
                printf("Product not found or discontinued\n");
            else{ 
                printf("%-5s%-20s%-25s%-25s%-10s%-20s%-10s\n", "Id", "Product", "Purchase price", "Selling price", "Stock", "Reorder level", "Status");
                printf("%-5d%-20s%-25.2f%-25.2f%-10d%-20d%-10d\n", Articulo[indice].id, Articulo[indice].nombre, Articulo[indice].pc, Articulo[indice].pv, Articulo[indice].existencias, Articulo[indice].reorden, Articulo[indice].estatus);
            }
        }
    }
}

void Modificaciones(){
    int opcion;
    char producto[50];
    while(1){
        int i = 0;
        printf("Product: ");
        scanf("%s", producto);
        if(strcmp(producto, "*") == 0)
            break;
        else{
            i = Buscar(Producto, producto, 1);
            if(i == -1 || Estatus[i] == 0)
                printf("Product not found or discontinued\n");
            else{
                do{
                    printf("Select an option\n1. Purchase price\n2. Selling price\n3. Stock\n4. Reorder level\n5. Exit\nOption: ");
                    scanf("%d", &opcion);
                    switch(opcion){
                        case 1: printf("Enter the new purchase price: ");
                            	scanf("%f", &Pc[i]);
                            	printf("The purchase price was successfully changed\n");
                            	Actualizar_array_a_struct();
                            	break;
                        case 2: printf("Enter the new selling price: ");
                            	scanf("%f", &Pv[i]);
                            	printf("The selling price was successfully changed\n");
                            	Actualizar_array_a_struct();
                            	break;
                        case 3: printf("Enter the new stock value: ");
                            	scanf("%d", &Existencias[i]);
                            	printf("The stock value was successfully changed\n");
                            	Actualizar_array_a_struct();
                            	break;
                        case 4: printf("Enter the new reorder value:");
                            	scanf("%d", &Reorden[i]);
                            	printf("The reorder value was changed successfully\n");
                            	Actualizar_array_a_struct();
                            	break;
                        case 5: break;
                        default: printf("Invalid option\n");
                    }
                } while(opcion != 5);
            }
        }
    }
}

int Buscar(char array_de_busqueda[][30], char *cosa_a_buscar, int tipo){
    int i = 0, contador;
    if(tipo == 1){
        contador = Contador_productos;
    }
	else if(tipo == 2){
        contador = Contador_usuarios;
    }
	else
        return -1;
    while(i < contador){
        if(strcmp(cosa_a_buscar, array_de_busqueda[i]) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

void Mostrar_Inventario(){
    int opcion = 0;
    while(opcion != 3){
        printf("Show sorted by:\n1.Id\n2.Alphabetically\n3.Exit\nOption: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: bubbleSort_inventario(1);
                	break;
            case 2: bubbleSort_inventario(2);
                	break;
            case 3: break;
            default: printf("Select a valid option\n");
        }
    }
}

void Administrador(){
    int opcion;
    do{
        printf("1. Additions\n2. Deletions\n3. Queries\n4. Modifications\n5. Show inventory\n6. User administration menu\n7. General cash cut \n8. Exit \nOption: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: Altas();
                    break;
            case 2: Bajas();
                    break;
            case 3: Consultas();
                    break;
            case 4: Modificaciones();
                    break;
            case 5: Mostrar_Inventario();
                    break;
            case 6: Menu_Usuarios();
                    break;
            case 7: printf("General cash cut: %.2f\n", Ventas_de_vendedores);
					break;
			case 8: break;
            default: printf("Invalid option\n");
        }
    } while(opcion != 8);
}

void Menu_Usuarios(){
    int opcion;
    do{
        printf("1. Registrations\n2. Deregistrations\n3. Queries\n4. Modifications\n5. Show users\n6. Exit \nOption: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: Altas_usuarios();
                    break;
            case 2: Bajas_usuarios();
                    break;
            case 3: Consultas_usuarios();
                    break;
            case 4: Modificaciones_usuarios();
                    break;
            case 5: Mostrar_usuarios();
                    break;
            case 6: break;
            default: printf("Invalid option\n");
        }
    } while(opcion != 6); 
}

void Altas_usuarios(){
    int i = 0, prototipo_int;
    char prototipo_usuario[50];
    while(1){
        printf("User: ");
        scanf("%s", prototipo_usuario);
        if(strcmp(prototipo_usuario, "*") == 0)
            break;
        else if(Contador_usuarios < 5){
            i = Buscar(Usuario, prototipo_usuario, 1);
            if(i == -1){
                nuevo = malloc(sizeof(Nodo));
                strcpy(nuevo->usuario, prototipo_usuario);
                printf("Password: ");
                scanf("%s", nuevo->password);
                while(1){
                    printf("Type: ");
                    scanf("%d", &prototipo_int);
                    if(prototipo_int == 1 || prototipo_int == 2){
                        nuevo->tipo = prototipo_int;
                        break;
                    }
                    printf("Incorrect type. Type should be 1 or 2\n");
                }
                nuevo->estatus = 1;
                nuevo->sig = NULL;
                if(fin == NULL){
                    inicio = nuevo;
                    fin = nuevo;
                }
                else{
                    fin->sig = nuevo;
                    fin = fin->sig;
                }
                Contador_usuarios++;
                printf("User successfully registered\n");
                Actualizar_linked_list_a_array();
            }
            else if(Estatus_usuario[i] == 0){
                Nodo *temp = inicio;
                for(int j = 0; j != i; j++)
                    temp = temp->sig;
                temp->estatus = 1;
                Actualizar_linked_list_a_array();
                printf("The user already existed, its status was changed to active\n");
            }
            else
                printf("The user already existed and already had active status\n");
        }
        else
            printf("The limit of users to register has been reached\n");
    }
}

void Bajas_usuarios(){
    char usuario_eliminar[50];
    while(1){
        int i = 0;
        printf("Users: ");
        scanf("%s", usuario_eliminar);
        if(strcmp(usuario_eliminar, "*") == 0)
            break;
        else{
            i = Buscar(Usuario, usuario_eliminar, 1);
            if(i == -1)
                printf("User not found\n");
            else{
                Nodo *temp = inicio;
                for(int j = 0; j != i; j++)
                    temp = temp->sig;
                if(temp->estatus == 0)
                    printf("The user has already disabled status\n");
                else{
                    temp->estatus = 0;
                    Actualizar_linked_list_a_array();
                    printf("The user status was already disabled\n");
                }
            }
        }
    }
}

void Consultas_usuarios(){
    char usuario_a_buscar[50];
    while(1){
        int i = 0;
        printf("User: ");
        scanf("%s", usuario_a_buscar);
        if(strcmp(usuario_a_buscar, "*") == 0)
            break;
        else{
            i = Buscar(Usuario, usuario_a_buscar, 1);
            if(i == -1)
                printf("User not found or user's status is disabled\n");
            else{
                Nodo *temp = inicio;
                for(int j = 0; j != i; j++)
                    temp = temp->sig;
                if(temp->estatus != 0){
                    printf("%-15s %-15s %-15s %-10s\n", "User", "Password", "Type", "Status");
                    printf("%-15s %-15s %-15d %-10d\n", temp->usuario, temp->password, temp->tipo, temp->estatus);
                }
				else
                    printf("User not found or user's status is disabled\n");
            }
        }
    }
}

void Modificaciones_usuarios(){
    char usuario[50];
    int i = 0, int_tmp;
    printf("User: ");
    scanf("%s", usuario);
    i = Buscar(Usuario, usuario, 1);
    if(i == -1)
        printf("User not found or user's status is disabled\n");
    else{
        Nodo *temp = inicio;
        for(int j = 0; j != i; j++)
            temp = temp->sig;
        if(temp->estatus != 0){
            int opcion;
            while(1){
                temp = inicio;
                for(int j = 0; j != i; j++)
                    temp = temp->sig;
                printf("Select an option\n1. Password\n2. Type\n3. Exit\nOption: ");
                scanf("%d", &opcion);
                switch(opcion){
                    case 1: printf("Enter the new password: ");
	                        scanf("%s", temp->password);
	                        Actualizar_linked_list_a_array();
	                        printf("Password changed successfully\n");
	                        break;
                    case 2: while(1){
	                            printf("Enter the new user type (1 for administrator and 2 for sales): ");
	                            scanf("%d", &int_tmp);
	                            if(int_tmp == 1 || int_tmp == 2){
	                                if(int_tmp == temp->tipo){
	                                    printf("The user was already of that type\n");
	                                }
									else{
	                                    temp->tipo = int_tmp;
	                                    Actualizar_linked_list_a_array();
	                                    printf("User type changed successfully\n");
	                                }
	                                break;
	                            }
								else{
	                                printf("Incorrect type\n");
	                            }
	                        }
	                        break;
                    case 3: break;
                    default: printf("Invalid option\n");
                }
                if(opcion == 3)
                    break;
            }
        }
		else
            printf("User not found or user's status is disabled\n");
    }
}

void Mostrar_usuarios(){
    printf("%-15s %-15s %-15s %-10s\n", "User", "Password", "Type", "Status");
    for(int i = 0; i < Contador_usuarios; i++){
        if(Estatus_usuario[i] == 1)
            printf("%-15s %-15s %-15d %-10d\n", Usuario[i], Password[i], Tipo_usuario[i], Estatus_usuario[i]);
    }
}

void bubbleSort_inventario(int tipo){
    int indices_reorden[Contador_productos], c = 0;
    Inventario copia[Contador_productos];
    for(int i = 0; i < Contador_productos; i++)
        copia[i] = Articulo[i];
    if(tipo == 1){
        for(int j = 0; j < Contador_productos - 1; ++j){
            for(int i = 0; i < Contador_productos - j - 1; ++i){
                if(copia[i].id > copia[i + 1].id){
                    Inventario temp = copia[i];
                    copia[i] = copia[i + 1];
                    copia[i + 1] = temp;
                }
            }
        }
    }
	else{
        for(int j = 0; j < Contador_productos - 1; ++j){
            for(int i = 0; i < Contador_productos - j - 1; ++i){
                if(copia[i].nombre[0] > copia[i + 1].nombre[0]){
                    Inventario temp = copia[i];
                    copia[i] = copia[i + 1];
                    copia[i + 1] = temp;
                }
            }
        }
    }
    printf("%-5s%-20s%-25s%-25s%-10s%-20s%-10s\n", "Id", "Product", "Purchase price", "Selling price", "Stock", "Reorder level", "Status");
    for(int i = 0; i < Contador_productos; ++i){
        if(copia[i].estatus == 1)
            printf("%-5d%-20s%-25.2f%-25.2f%-10d%-20d%-10d\n", copia[i].id, copia[i].nombre, copia[i].pc, copia[i].pv, copia[i].existencias, copia[i].reorden, copia[i].estatus);
        if(Existencias[i] <= Reorden[i]){
            indices_reorden[c] = i;
            c++;
        }
    }
    if(c != 0){
        printf("Reorder of the following product(s) is required:\n");
        for(int j = 0; j < c; j++)
            printf("%s\n", Producto[indices_reorden[j]]);
    }
}

void Actualizar_array_a_struct(){
    for(int i = 0; i < Contador_productos; i++){
        Articulo[i].id = Id[i];
        strcpy(Articulo[i].nombre, Producto[i]);
        Articulo[i].pc = Pc[i];
        Articulo[i].pv = Pv[i];
        Articulo[i].existencias = Existencias[i];
        Articulo[i].reorden = Reorden[i];
        Articulo[i].estatus = Estatus[i];
    }
}

void Actualizar_struct_a_array(){
    for(int i = 0; i < Contador_productos; i++){
        Id[i] = Articulo[i].id;
        strcpy(Producto[i], Articulo[i].nombre);
        Pc[i] = Articulo[i].pc;
        Pv[i] = Articulo[i].pv;
        Existencias[i] = Articulo[i].existencias;
        Reorden[i] = Articulo[i].reorden;
        Estatus[i] = Articulo[i].estatus;
    }
}

void Actualizar_array_a_linked_list(){
    for(int i = 0; i < Contador_usuarios; i++){
        Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
        strcpy(nuevo->usuario, Usuario[i]);
        strcpy(nuevo->password, Password[i]);
        nuevo->tipo = Tipo_usuario[i];
        nuevo->estatus = Estatus_usuario[i];
        nuevo->sig = NULL;
        if(inicio == NULL){
            inicio = nuevo;
            fin = nuevo;
        }
		else{
            fin->sig = nuevo;
            fin = fin->sig;
        }
    }
}

void Actualizar_linked_list_a_array(){
    int i = 0;
    Nodo *temp = inicio;
    while(temp != NULL){
        strcpy(Usuario[i], temp->usuario);
        strcpy(Password[i], temp->password);
        Tipo_usuario[i] = temp->tipo;
        Estatus_usuario[i] = temp->estatus;
        temp = temp->sig;
        i++;
    }
}

void Cargar_datos(){
    FILE *file;
    file = fopen("data/productos.txt", "r");
    if(file){
        fscanf(file, "%d", &Contador_productos);
        for(int i = 0; i < Contador_productos; i++)
            fscanf(file, "%d %s %f %f %d %d %d", &Id[i], Producto[i], &Pc[i], &Pv[i], &Existencias[i], &Reorden[i], &Estatus[i]);
        fclose(file);
    }
    file = fopen("data/usuarios.txt", "r");
    if(file){
        fscanf(file, "%d", &Contador_usuarios);
        for(int i = 0; i < Contador_usuarios; i++)
            fscanf(file, "%s %s %d %d", Usuario[i], Password[i], &Tipo_usuario[i], &Estatus_usuario[i]);
        fclose(file);
    }
}

void Guardar_datos() {
    FILE *file;
    file = fopen("data/productos.txt", "w");
    if(file){
        fprintf(file, "%d\n", Contador_productos);
        for(int i = 0; i < Contador_productos; i++)
            fprintf(file, "%d %s %f %f %d %d %d\n", Id[i], Producto[i], Pc[i], Pv[i], Existencias[i], Reorden[i], Estatus[i]);
        fclose(file);
    }
    file = fopen("data/usuarios.txt", "w");
    if(file){
        fprintf(file, "%d\n", Contador_usuarios);
        for(int i = 0; i < Contador_usuarios; i++)
            fprintf(file, "%s %s %d %d\n", Usuario[i], Password[i], Tipo_usuario[i], Estatus_usuario[i]);
        fclose(file);
    }
}
