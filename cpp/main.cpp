#include <iostream>
#include <iomanip>

using namespace std;

// Prototipos

void Administrador();
void Ventas();
void Ticket(int c);
void Corte_caja();
void Mostrar_Inventario();
void Altas();
void Bajas();
void Consultas();
void Modificaciones();
void Administracion_Usuarios();
void Alta_usuarios();
void Bajas_usuarios();
void Consultas_usuarios();
void Modificaciones_usuarios();
void Mostrar_usuarios();
void bubbleSort_inventario(int tipo);
void Actualizar_array_a_struct();
void Actualizar_struct_a_array();
void Actualizar_array_a_linked_list();
void Actualizar_linked_list_a_array();
int Buscar(string array_de_busqueda[], string producto, int tipo);
int Autentificacion(int tipo_usuario_a_acceder);

// Datos predefinidos

int Contador_productos = 5;
int Id[10] = {2,4,1,3,5};
string Producto[10] = {"leche", "pan", "agua", "huevos", "refresco"};
float Pc[10] = {12.35,5.5,13.39,22.4,10.99};
float Pv[10] = {15.5,7.95,18.55,30.39,14.75};
int Existencias[10] = {16,18,12,5,5};
int Reorden[10] = {5,6,4,7,8};
int Estatus[10] = {1,1,1,1,1};

string Usuario[5] = {"admin1","ventas1", "ventas2"};
string Password[5] = {"1234","1234","1234"}; // Estas contraseñas hardcodeadas son solo para testeo
int Tipo_usuario[5] = {1,2,2};
int Estatus_usuario[5] = {1,0,1};
int Contador_usuarios = 3;
float Ventas_por_vendedor = 0;
float Ventas_de_vendedores = 0;


// Estructuras y punteros
struct Venta{
    string producto;
    int cantidad;
    float costo;
    float unidad;
} venta[15];

struct Inventario{
    string nombre;
    int id;
    float pc;
    float pv;
    int existencias;
    int reorden;
    int estatus;
};

Inventario Articulo[10];

struct Nodo{
    string usuario;
    string password;
    int tipo;
    int estatus;
    Nodo *sig;
};

Nodo *inicio = NULL;
Nodo *nuevo = NULL;
Nodo *fin = NULL;
Nodo *temp = NULL;

int main(){ // Funcion principal que llama al resto del codigo
    int opcion, resultado;
    Actualizar_array_a_struct(); // Genera las listas de estructuras de los productos en base a arrays
    Actualizar_array_a_linked_list(); // Genera las linked list de los usuarios en base a los arrays
    do{
        cout << "Menu principal" << endl;
        cout << "1. Administrador" << endl;
        cout << "2. Ventas" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        cin>> opcion;
        switch (opcion){
            case 1: if(Autentificacion(opcion) == -1)
                        Administrador();          
                    break;
            case 2: if(Autentificacion(opcion) == -1)
                        Ventas();
                    break;
            case 3: cout << "Cerrando sistema" << endl;
                    break;
            default: cout << "Opción inválida."<< endl;
        }
    }while(opcion != 3);
    return 0;
}

int Autentificacion(int tipo_usuario_a_acceder){ // Verifica credenciales
    int i;
    string usuario_tmp, pass_tmp;
    cout << "Usuario: ";
    cin >> usuario_tmp;
    cout << "Contraseña: ";
    cin >> pass_tmp;
    i = Buscar(Usuario, usuario_tmp, 2); // Busca el usuario que se introdujo en los arrays
    if(i != -1){ // Si lo encuentra continua en este proceso
        if(Password[i] == pass_tmp){ // Verifica que la contraseña del usuario encontrado sea la que se introdujo
            if(Tipo_usuario[i] == tipo_usuario_a_acceder && Estatus_usuario[i] == 1)
                return -1;
            else 
                cout << "El tipo de usuario al que se busca acceder es invalido o se encuentra dado de baja" << endl;
                return 1;
        }
        else
            cout << "Usuario o contraseña invalidos" << endl;
            return 1;
    }
    else
        cout << "Usuario o contraseña invalidos" << endl;
        return 1;
}

void Administrador(){ // Menu del Administrador
    int opcion;
    do{
        cout << "1. Altas" << endl;
        cout << "2. Bajas" << endl;
        cout << "3. Consultas" << endl;
        cout << "4. Modificaciones" << endl;
        cout << "5. Mostrar Inventario" << endl;
        cout << "6. Administracion de cuentas de usuarios" << endl;
        cout << "7. Corte de caja general" << endl;
        cout << "8. Regresar al menú anterior" << endl;
        cout << "Opcion: ";
        cin>> opcion;
        switch (opcion){
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
            case 6: Administracion_Usuarios();
                    break;
            case 7: cout << "Corte de caja general: " << Ventas_de_vendedores << endl;
                    break;
            case 8: cout << "Regresando al menú anterior" << endl;
                    break;
            default: cout << "Opción inválida."<< endl;
        }
    }while(opcion != 8);
}

void Ventas(){
    string opcion, producto;
    int cantidad, c = 0, i = 0;
    while(true){
        cout << "Producto: ";
        cin >> producto;
        if (producto[0] == '*' && producto[1] == '*'){ // Verificar que no se pida un corte de caja
            cout << "Corte de caja: " << Ventas_por_vendedor << endl;
            Ventas_de_vendedores += Ventas_por_vendedor; // Añade las ventas de la caja a las totales
            Ventas_por_vendedor = 0; // Reinicia las ventas de la caja
            break; // Rompe el ciclo
        }
        else if(producto[0] == '*'){ // Verifica que no se pida una finalizacion de compra
            Ticket(c+1); // Le pasa como argumento la cantidad de productos vendidos mas 1 para que coincida con el ciclo for en ticket
            c = 0; // Reinicia la cantidad de productos vendidos a 0
            continue; // Vuelve a repetir el ciclo
        }
        else{
            i = Buscar(Producto, producto, 1); // Busca el producto
            if(i != -1 || Estatus[i] != 0){ // Verifica la existencia y estatus de activo
                cout << "Cantidad: ";
                cin >> cantidad;
                if(Existencias[i] < cantidad){ // Verifica si la cantidad es mayor a las existencias
                    cout << "No hay " << cantidad << " productos de " << producto << ", solo hay " << Existencias[i] << 
                    " ¿relizar la venta de " << Existencias[i] << "?" << endl; // Pregunta si se compra lo que exista
                    cin >> opcion;
                    if(opcion == "No" || opcion == "NO" || opcion == "no") // Se omite esta compra
                        continue; // Vuelve a repetir el ciclo
                    else
                        cantidad = Existencias[i]; // Se cambia la cantidad a la existencia
                }
                venta[c].producto = producto;
                venta[c].cantidad = cantidad;
                venta[c].unidad = Pv[i];
                venta[c].costo = cantidad*Pv[i]; // Se registran en la lista de estructuras venta
                c++; // Aumenta el conador de productos vendidos
                Existencias[i] = Existencias[i] - cantidad; // Se actualizan las existencia de productos
                Actualizar_array_a_struct(); // El array actualiza la lista de estructuras de los productos
                continue; // Vuelve a repetir el ciclo
            }
            else
                cout << "Producto inexistente o dado de baja" << endl;
        }
    }
}

void Ticket(int c){
    float total_de_caja = 0; // Reinicia el valor
    cout << "Ticket: " << endl;
    cout << setw(15) << "Producto" << setw(15) << "Cantidad" << setw(25) << "Precio unitario" << setw(25) << "Subtotal" << setw(15) << endl; 
    for(int i=0; i<c; i++){
        if(venta[i].producto != ""){ // Continia con los productos si el nombre no esta vacio
            cout << setw(15) << venta[i].producto << setw(15) << venta[i].cantidad << setw(25) << venta[i].unidad << setw(25) << venta[i].costo << setw(15) << endl;
            total_de_caja += venta[i].costo; // Añade el precio de los productos al generado por la venta
            venta[i].producto = ""; // Actualiza los espacios del nombre producto a vacios, para evitar problemas 
        }
    }
    Ventas_por_vendedor += total_de_caja; // Añade el dinero generado por la venta al generado por el vendedor
    cout << "Total: " << total_de_caja << endl;
}

void Altas(){
    int i = 0;
    string prototipo_producto;
    while(true){
        cout << "Producto: ";
        cin >> prototipo_producto;
        if (prototipo_producto == "*")
            break;
        else{
            i = Buscar(Producto, prototipo_producto, 1); // Busca el producto
            if(i== -1){ // Si no existe
                Articulo[Contador_productos].nombre = prototipo_producto;
                cout << "Id: ";
                cin >> Articulo[Contador_productos].id;
                while(true){ // Bucle para verificar que el precio de compra no sea mayor al de venta
                    cout << "Precio de compra: ";
                    cin >> Articulo[Contador_productos].pc;
                    cout << "Precio de venta: ";
                    cin >> Articulo[Contador_productos].pv;
                    if(Articulo[Contador_productos].pc<Articulo[Contador_productos].pv)
                        break;
                    cout << "El precio de compra no puede ser mayor al precio de venta" << endl;
                }
                while(true){ // Bucle para verificar que las existencias sean mayor al reorden
                    cout << "Existencias: ";
                    cin >> Articulo[Contador_productos].existencias;
                    cout << "Reorden: ";
                    cin >> Articulo[Contador_productos].reorden;
                    if(Articulo[Contador_productos].existencias>Articulo[Contador_productos].reorden)
                        break;
                    cout << "Las existencias deben ser mayores al reorden" << endl;
                }
                Articulo[Contador_productos].estatus = 1;
                Contador_productos += 1; // Actualiza el numero de productos
                Actualizar_struct_a_array(); // Actualiza el array con la lista de estructuras
                cout << "Producto registrado con exito" << endl;
            }
            else if (Articulo[i].estatus == 0){ // Si ya existe y esta de baja, cambia el estatus
                Articulo[i].estatus = 1;
                Actualizar_struct_a_array();
                cout << "El producto \""<< prototipo_producto 
                <<"\" ya se encuentra registrado, el estatus del producto cambio a activo" << endl;
            }
            else cout << "El producto ya existe y ya contaba con estatus de activo" << endl;
        }
    }
}

void Bajas(){
    string producto_eliminar;
    while(true){
        int i = 0;
        cout << "Producto: ";
        cin >> producto_eliminar;
        if (producto_eliminar == "*")
            break;
        else{
            i = Buscar(Producto, producto_eliminar, 1); // Verifica que exista
            if(i == -1 || Articulo[i].estatus == 0) // Si no existe o esta de baja
                cout << "Producto no encontrado o ya dado de baja" << endl;
            else{
                Articulo[i].estatus = 0; // Lo da de baja
                Actualizar_struct_a_array(); // Actualiza el array con la estructura
                cout << "Articulo dado de baja exitosamente" << endl;
            }
        }
    }
}

void Consultas(){
    string producto_a_buscar;
    while(true){
        int indice = 0;
        cout << "Producto: ";
        cin >> producto_a_buscar;
        if (producto_a_buscar == "*")
            break;
        else{
            indice = Buscar(Producto, producto_a_buscar, 1); // Verifica que exista
            if(indice == -1 || Articulo[indice].estatus == 0) // Filtra si no existe o esta de baja
                cout << "Producto no encontrado o dado de baja" << endl;
            else{
                cout << setw(5) << "Id" << setw(10) << "Producto" << setw(10) << "Pc" << setw(10)  << "Pv" << setw(15) << "Existencias" << setw(10) << "Reorden" << setw(10) << "Estatus" << setw(10) << endl;
                cout << setw(5) << Articulo[indice].id << setw(10) << Articulo[indice].nombre << setw(10) << Articulo[indice].pc << setw(10) << Articulo[indice].pv << setw(15) << Articulo[indice].existencias << setw(10) << Articulo[indice].reorden << setw(10) << Articulo[indice].estatus << setw(10) << endl;
            }
        }
    }
}

void Modificaciones(){
    int opcion;
    string producto;
    while(true){
        int i = 0;
        cout << "Producto: ";
        cin >> producto;
        if (producto == "*")
            break;
        else{
            i = Buscar(Producto, producto, 1); // Verifica que exista
            if(i == -1 || Estatus[i] == 0)
                cout << "Producto no encontrado o dado de baja" << endl;
            else{
                while(opcion !=5){
                    cout << "Seleccione una opcion" << endl << "1. Precio de compra" << endl  << "2. Precio de venta" << endl 
                    << "3. Existencias" << endl << "4. Reorden" << endl << "5. Salir" << endl << "Opcion: ";
                    cin >> opcion;
                    switch(opcion){
                        case 1: cout << "Escriba el nuevo precio de compra: ";
                                cin >> Pc[i];
                                cout << "El precio de compra se cambio con exito" << endl;
                                Actualizar_array_a_struct(); // Actualiza la estructura con el array
                                break;
                        case 2: cout << "Escriba el nuevo precio de venta: ";
                                cin >> Pv[i];
                                cout << "El precio de venta se cambio con exito" << endl;
                                Actualizar_array_a_struct(); // Actualiza la estructura con el array
                                break;
                        case 3: cout << "Escriba el nuevo valor de las existencias: ";
                                cin >> Existencias[i];
                                cout << "El valor de las existencias se cambiaron con exito" << endl;
                                Actualizar_array_a_struct(); // Actualiza la estructura con el array
                                break;
                        case 4: cout << "Escriba el nuevo valor de reorden :";
                                cin >> Reorden[i];
                                cout << "El valor de reorden fue cambiado con exito" << endl;
                                Actualizar_array_a_struct(); // Actualiza la estructura con el array
                                break;
                        case 5: break;
                        default: cout << "Opcion invalida" << endl;
                    }
                }
            }
        }
    }
}

int Buscar(string array_de_busqueda[], string cosa_a_buscar, int tipo){ // Recibe el array donde se va a buscar, la cosa y el tipo
    int i=0, contador;
    if(tipo = 1) // Es para la busqueda de productos
        contador = Contador_productos; // Actualiza el contador segun los productos
    else
        contador = Contador_usuarios; // Actualiza el contador segun los usuarios
        
    while(cosa_a_buscar != array_de_busqueda[i] && i < contador) // Itera entre el array hasta buscar el nombre o terminar con los espacios
                i++;
    if(i >= Contador_productos) // Si termino con los espacios y no lo encontro retorna -1
        return -1;
    else // Si lo encontro retorna la posicion donde esta
        return i;
}

void Mostrar_Inventario(){
    int opcion = 0;
    while(opcion != 3){
        cout << "Mostrar ordenados por:" << endl << "1.Id" << endl << "2.Alfabeticamente" << endl << "3.Salir" << endl << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 1: bubbleSort_inventario(1);
                    break;
            case 2: bubbleSort_inventario(2);
                    break;
            case 3: break;
            default:
                cout << "Selecciona una opcion valida";
        }
    }
}

void Administracion_Usuarios(){ // Menu de Administracion de usuarios
    int opcion;
    do{
        cout << "1. Altas" << endl;
        cout << "2. Bajas" << endl;
        cout << "3. Consultas" << endl;
        cout << "4. Modificaciones" << endl;
        cout << "5. Mostrar cuentas de usuarios" << endl;
        cout << "6. Regresar al menu anterior" << endl;
        cout << "Opción: ";
        cin>> opcion;
        switch (opcion){
            case 1: Alta_usuarios();
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
            default: cout << "Opción inválida."<< endl;
        }
    }while(opcion != 6);
}

void Alta_usuarios(){
    int i = 0, prototipo_int;
    string prototipo_usuario;
    while(true){
        cout << "Usuario: ";
        cin >> prototipo_usuario;
        if (prototipo_usuario == "*")
            break;
        else{
            i = Buscar(Usuario, prototipo_usuario, 2); // Valida no exista
            if(i== -1){
                nuevo = new(Nodo); // Crea un espacio en la memoria para los datos
                nuevo -> usuario = prototipo_usuario;
                cout << "Contraseña: ";
                cin >> nuevo -> password;
                while(true){ // Verifica que el tipo sea 1 o 2
                    cout << "Tipo: ";
                    cin >> prototipo_int;
                    if(prototipo_int == 1 || prototipo_int == 2){
                        nuevo -> tipo = prototipo_int;
                        break;
                    }
                    cout << "El tipo introducido no es correcto. El tipo 1 para Administrador o 2 para ventas" << endl;
                }
                nuevo -> estatus = 1;
                nuevo -> sig = NULL;
                fin -> sig = nuevo; // Conecta con las otras linked list
                fin = fin -> sig; // Actualiza el final
                Contador_usuarios++; // Actualiza la cantidad de usuarios
                cout << "Usuario registrado con exito" << endl;
                Actualizar_linked_list_a_array(); // Actualiza el array con la linked list
            }
            else{
                temp = inicio;
                for(int j = 0; j != i ; j++) // Busca llegar al usuario encontrado
                    temp = temp -> sig;
                if(temp -> estatus == 0){ // Si esta de baja lo cambia a alta
                    temp -> estatus = 1;
                    cout << "El usuario \""<< prototipo_usuario <<"\" ya se encuentra registrado, el estatus del usuario se cambio a activo" << endl;
                    Actualizar_linked_list_a_array(); // Actualiza el array con la linked list
                }
                else{
                    cout << "El usuario \""<< prototipo_usuario <<"\" ya se encuentra registrado y su estatus ya era activo" << endl;
                }
            }
        }
    }
}

void Bajas_usuarios(){
    string usuario_eliminar;
    while(true){
        int i = 0;
        cout << "Usuario: ";
        cin >> usuario_eliminar;
        if (usuario_eliminar == "*")
            break;
        else{
            i = Buscar(Usuario, usuario_eliminar, 2); // Verifica su existencia
            if(i == -1)
                cout << "Usuario no encontrado" << endl;
            else{
                temp = inicio;
                for(int j = 0; j != i ; j++) // Busca llegar al usuario encontrado
                    temp = temp -> sig;
                if(temp-> estatus == 0) // Señala si ya estaba dado de baja
                    cout << "Usuario ya se encontraba dado de baja" << endl;
                else{
                    temp -> estatus = 0; // Da al usuario de baja
                    Actualizar_linked_list_a_array(); // Actualiza el array con la linked list
                    cout << "Usuario dado de baja exitosamente" << endl;
                }
            }
        }
    }
}

void Consultas_usuarios(){
    string usuario_a_buscar;
    while(true){
        int i = 0;
        cout << "Usuario: ";
        cin >> usuario_a_buscar;
        if (usuario_a_buscar == "*")
            break;
        else{
            i = Buscar(Usuario, usuario_a_buscar, 2); // Verifica existencias
            if(i == -1)
                cout << "Usuario no encontrado o dado de baja" << endl;
            else{
                temp = inicio;
                for(int j = 0; j != i ; j++) // Busca el usuario encontrado
                    temp = temp -> sig;
                if(temp-> estatus != 0){ // Si no esta de baja lo muestra
                    cout << setw(5) << "Usuario" << setw(15) << "Contraseña" << setw(15) << "Tipo" << setw(10) << "Estatus" << setw(10) << endl;
                    cout << setw(5) << temp -> usuario << setw(15) << temp -> password << setw(15) << temp -> tipo << setw(10) << temp -> estatus << setw(10) << endl;
                }
                else{
                    cout << "Usuario no encontrado o dado de baja" << endl;
                }
            }
        }
    }
}

void Modificaciones_usuarios(){
    string usuario;
    int i = 0, int_tmp;
    cout << "Usuario: ";
    cin >> usuario;
    i = Buscar(Usuario, usuario, 2); // Busca que exista
    if(i == -1)
        cout << "Usuario no encontrado o inexistente" << endl;
    else{
        temp = inicio;
        for(int j = 0; j != i ; j++) // Busca el usuario encontrado
            temp = temp -> sig;
        if(temp->estatus != 0){ // Si no esta dado de baja prosigue
            int opcion;
            while(true){
                temp = inicio;
                for(int j = 0; j != i ; j++) // Busca el usuario encontrado
                    temp = temp -> sig;
                cout << "Seleccione una opción" << endl << "1. Contraseña" << endl << "2. Tipo" << endl  
                     << "3. Salir" << endl << "Opción: ";
                cin >> opcion;
                switch(opcion){
                    case 1: 
                        cout << "Escriba la nueva contraseña: ";
                        cin >> temp->password;
                        Actualizar_linked_list_a_array(); // Actualiza el array con la linked list
                        cout << "Contraseña cambiada con éxito" << endl;
                        break;
                    case 2: 
                        while(true){
                            cout << "Escriba el nuevo tipo de usuario (1 para administrador y 2 para ventas): ";
                            cin >> int_tmp;
                            if(int_tmp == 1 || int_tmp == 2){ // Verifica que el tipo sea 1 o 2
                                if(int_tmp == temp->tipo){ // Señala si ya era de ese tipo
                                    cout << "El usuario ya era de ese tipo" << endl;
                                }
                                else{
                                    temp->tipo = int_tmp; // Cambia el tipo
                                    Actualizar_linked_list_a_array(); // Actualiza el array con la linked list
                                    cout << "Tipo de usuario cambiado con éxito" << endl;
                                }
                                break;
                            }
                            else{
                                cout << "Tipo de usuario no válido, ingrese 1 para administrador o 2 para ventas" << endl;
                            }
                        }
                        break;
                    case 3: break;
                    default: 
                        cout << "Opción inválida" << endl;
                }
                if(opcion == 3)
                    break;
            }
        }
        else{
            cout << "Usuario no encontrado o dado de baja" << endl;
        }
    }
}

void Mostrar_usuarios(){
    cout << setw(5) << "Usuario" << setw(15) << "Contraseña" << setw(15) << "Tipo" << setw(10) << "Estatus" << setw(10) << endl;
    for(int i = 0; i<Contador_usuarios; i++){ // Imprime hasta el final
        if(Estatus_usuario[i] == 1) // Imprime solo si esta activo
            cout << setw(5) << Usuario[i] << setw(15) << Password[i] << setw(15) << Tipo_usuario[i] << setw(10) << Estatus_usuario[i] << setw(10) << endl;
    }
}

void bubbleSort_inventario(int tipo){ // Funcion de ordenamiento e impresion de inventario
    int indices_reorden[Contador_productos], c=0;
    Inventario copia[Contador_productos]; // Copia para el array
    for (int i = 0; i < Contador_productos; i++) { // Se genera un array de copia de los productos
        copia[i] = Articulo[i];
    }
    if(tipo == 1){ // Acomodar el array copia por ID usando bubble sort
        for (int j = 0; j < Contador_productos - 1; ++j){
            for (int i = 0; i < Contador_productos - j - 1; ++i){
                if (copia[i].id > copia[i + 1].id){ // Intercambia los elementos si no estan en orden
                    Inventario temp = copia[i];
                    copia[i] = copia[i + 1];
                    copia[i + 1] = temp;
                }
            }
        }
    }
    else{ // Acomodar el array copia alfabeticamente
        for (int j = 0; j < Contador_productos - 1; ++j){
            for (int i = 0; i < Contador_productos - j - 1; ++i){
                if (copia[i].nombre[0] > copia[i + 1].nombre[0]){ // Intercambia los elementos si no están en orden alfabético, atraves de su numero ASCII
                    Inventario temp = copia[i];
                    copia[i] = copia[i + 1];
                    copia[i + 1] = temp;
                }
            }
        }
    }
    cout << setw(5) << "Id" << setw(10) << "Producto" << setw(10) << "Pc" << setw(10)  << "Pv" << setw(15) 
    << "Existencias" << setw(10) << "Reorden" << setw(10) << "Estatus" << setw(10) << endl;
    for (int i = 0; i < Contador_productos; ++i) {
        if (copia[i].estatus == 1){ // Imprime los productos si estan activos
            cout << setw(5) << copia[i].id << setw(10) << copia[i].nombre << setw(10) << copia[i].pc << setw(10) 
            << copia[i].pv << setw(15) << copia[i].existencias << setw(10) << copia[i].reorden << setw(10) << copia[i].estatus 
            << setw(10) << endl;
        }
        if (Existencias[i] <= Reorden[i]){
            indices_reorden[c] = i; // Guarda el indice de estos productos
            c++; // Añade uno mas al contador de productos que esten en nivel de reorden
        }
    }
    if (c != 0){
        cout << "Se requiere hacer reorden del siguiente producto(s): " << endl;
        for( int j = 0; j < c; j++){ // Imprime los productos que esten en nivel de reorden
            cout << Producto[indices_reorden[j]] << endl;
        }
    }
}

void Actualizar_array_a_struct(){ // Actualiza la lista de estructuras con el array
    for(int i = 0; i < Contador_productos; i++){
        Articulo[i].id = Id[i];
        Articulo[i].nombre = Producto[i];
        Articulo[i].pc = Pc[i];
        Articulo[i].pv = Pv[i];
        Articulo[i].existencias = Existencias[i];
        Articulo[i].reorden = Reorden[i];
        Articulo[i].estatus = Estatus[i]; 
    }
}

void Actualizar_struct_a_array(){ // Actualiza el array con la lista de estructuras
    for(int i = 0; i < Contador_productos; i++){
        Id[i] = Articulo[i].id;
        Producto[i] = Articulo[i].nombre;
        Pc[i] = Articulo[i].pc;
        Pv[i] = Articulo[i].pv;
        Existencias[i] = Articulo[i].existencias;
        Reorden[i] = Articulo[i].reorden;
        Estatus[i] = Articulo[i].estatus; 
    }
}

void Actualizar_array_a_linked_list(){ // Actualiza el array con la linked list
    for(int i = 0; i < Contador_usuarios; i++){
        nuevo = new(Nodo);
        nuevo -> usuario = Usuario[i];
        nuevo -> password = Password[i];
        nuevo -> tipo = Tipo_usuario[i];
        nuevo -> estatus = Estatus_usuario[i];
        nuevo -> sig = NULL;
        if (inicio == NULL){
            inicio = nuevo;
            fin = nuevo;
        }
        else {
            fin -> sig = nuevo;
            fin = fin -> sig;
        }
    }
}

void Actualizar_linked_list_a_array(){ // Actualiza la linked list con el array
    int i=0;
    temp  = inicio;
    while(temp != NULL){
        Usuario[i] = temp -> usuario;
        Password[i] = temp -> password;
        Tipo_usuario[i] = temp -> tipo;
        Estatus_usuario[i] = temp -> estatus;
        temp = temp -> sig;
        i++;
    }
}
