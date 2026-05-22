/*
   Navegacion de historial web con lista doble
*/

#include <iostream>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

// Devuelve la fecha y hora actual en hora de Republica Dominicana (UTC-4)
// como texto (dd/mm/aaaa hh:mm). Se usa gmtime (hora UTC) y se le restan
// 4 horas, asi la hora sale correcta aunque el servidor (por ejemplo
// OnlineGDB) este configurado en otra zona horaria.
string fechaHoraActual()
{
    time_t ahora = time(0);
    ahora = ahora - 4 * 3600;   // ajuste a la zona horaria de RD (UTC-4)
    tm* t = gmtime(&ahora);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", t);

    return string(buffer);
}

// Cada pagina visitada es un nodo de la lista. Guarda la URL,
// la fecha y hora, y los punteros a la pagina anterior y la siguiente.
class Pagina
{
public:
    string url;
    string fechaHora;
    Pagina* siguiente;
    Pagina* anterior;

    Pagina(string u, string fh)
    {
        url = u;
        fechaHora = fh;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

class Historial
{
private:
    Pagina* cabeza;
    Pagina* cola;
    Pagina* actual;   // pagina donde esta parado el usuario en este momento

public:
    Historial()
    {
        cabeza = nullptr;
        cola = nullptr;
        actual = nullptr;
    }

    // Agrega una visita al final del historial
    void insertarVisita(string url, string fechaHora)
    {
        // Validar que la URL no este vacia
        if (url == "")
        {
            cout << " La URL no puede estar vacia. Visita no registrada." << endl;
            return;
        }

        // Creamos el nodo de la nueva pagina visitada
        Pagina* nueva = new Pagina(url, fechaHora);

        // Si la lista esta vacia, la nueva pagina es cabeza y cola a la vez
        if (cabeza == nullptr)
        {
            cabeza = nueva;
            cola = nueva;
        }
        // Si ya hay paginas, la enganchamos al final usando el puntero cola
        else
        {
            cola->siguiente = nueva;
            nueva->anterior = cola;
            cola = nueva;
        }

        // Al visitar, el usuario queda parado en la pagina nueva
        actual = nueva;
    }

    // Muestra en que pagina esta parado el usuario
    void mostrarActual()
    {
        if (actual == nullptr)
            cout << " Pagina actual: (historial vacio)" << endl;
        else
            cout << " Pagina actual: " << actual->url << " (" << actual->fechaHora << ")" << endl;
    }

    // Mueve la pagina actual una posicion hacia atras
    void irAtras()
    {
        if (actual == nullptr)
        {
            cout << " El historial esta vacio." << endl;
            return;
        }

        if (actual->anterior == nullptr)
        {
            cout << " No hay paginas anteriores." << endl;
            return;
        }

        actual = actual->anterior;
        cout << " Pagina actual: " << actual->url << " (" << actual->fechaHora << ")" << endl;
    }

    // Mueve la pagina actual una posicion hacia adelante
    void irAdelante()
    {
        if (actual == nullptr)
        {
            cout << " El historial esta vacio." << endl;
            return;
        }

        if (actual->siguiente == nullptr)
        {
            cout << " No hay paginas siguientes." << endl;
            return;
        }

        actual = actual->siguiente;
        cout << " Pagina actual: " << actual->url << " (" << actual->fechaHora << ")" << endl;
    }

    // Muestra las URLs numeradas, para elegir cual eliminar por su numero
    void mostrarURLsNumeradas()
    {
        if (cabeza == nullptr)
        {
            cout << " El historial esta vacio." << endl;
            return;
        }

        cout << " URLs en el historial:" << endl;

        Pagina* temp = cabeza;
        int n = 1;
        while (temp != nullptr)
        {
            // Mostramos la fecha y hora para distinguir visitas repetidas
            cout << "   " << n << ". " << temp->url << " (" << temp->fechaHora << ")" << endl;
            temp = temp->siguiente;
            n++;
        }
    }

    // Devuelve cuantas paginas hay en el historial
    int contarPaginas()
    {
        int total = 0;
        Pagina* temp = cabeza;
        while (temp != nullptr)
        {
            total++;
            temp = temp->siguiente;
        }
        return total;
    }

    // Quita un nodo concreto de la lista, reenlazando sus vecinos.
    // Lo usa el borrado por numero para no repetir el reenlace de punteros.
    void desenlazar(Pagina* nodo)
    {
        // Unimos la pagina anterior con la siguiente para no romper la lista.
        // Si la pagina era la cabeza o la cola, esas referencias se actualizan.
        if (nodo->anterior != nullptr)
            nodo->anterior->siguiente = nodo->siguiente;
        else
            cabeza = nodo->siguiente;

        if (nodo->siguiente != nullptr)
            nodo->siguiente->anterior = nodo->anterior;
        else
            cola = nodo->anterior;

        // Si se elimina la pagina actual, movemos el puntero a una valida
        if (actual == nodo)
        {
            if (nodo->anterior != nullptr)
                actual = nodo->anterior;
            else
                actual = nodo->siguiente;
        }

        delete nodo;
    }

    // Elimina la pagina que ocupa la posicion indicada (1, 2, 3...).
    // Borra exactamente esa pagina, aunque su URL este repetida.
    void eliminarPorNumero(int posicion)
    {
        if (posicion < 1 || posicion > contarPaginas())
        {
            cout << " Numero invalido." << endl;
            return;
        }

        // Avanzamos hasta la pagina en esa posicion
        Pagina* temp = cabeza;
        for (int i = 1; i < posicion; i++)
            temp = temp->siguiente;

        string urlBorrada = temp->url;
        desenlazar(temp);
        cout << " URL " << urlBorrada << " eliminada del historial." << endl;
    }

    // Recorre el historial desde la ultima visita hasta la primera
    void mostrarInverso()
    {
        if (cola == nullptr)
        {
            cout << " El historial esta vacio." << endl;
            return;
        }

        cout << " >> HISTORIAL (de la ultima a la primera visita)" << endl;

        Pagina* temp = cola;
        while (temp != nullptr)
        {
            cout << "   " << temp->url << " (" << temp->fechaHora << ")" << endl;
            temp = temp->anterior;
        }
    }

    // Libera la memoria de todos los nodos al cerrar el programa
    ~Historial()
    {
        Pagina* temp = cabeza;
        while (temp != nullptr)
        {
            Pagina* aux = temp;
            temp = temp->siguiente;
            delete aux;
        }
    }
};

int main()
{
    Historial navegador;
    int opcion, numURL;
    string url;

    // Datos de prueba para arrancar con un historial de ejemplo
    navegador.insertarVisita("uapa.edu.do", "16/05/2026 09:00");
    navegador.insertarVisita("google.com", "16/05/2026 09:05");
    navegador.insertarVisita("youtube.com", "16/05/2026 09:10");

    do
    {
        // Menu con marco para una presentacion mas ordenada y clara
        cout << "\n==================================================" << endl;
        cout << "            NAVEGADOR - HISTORIAL WEB" << endl;
        cout << "==================================================" << endl;

        // Mostramos la pagina donde esta parado el usuario
        navegador.mostrarActual();

        cout << "--------------------------------------------------" << endl;
        cout << "   [1] Registrar nueva visita" << endl;
        cout << "   [2] Ir hacia atras" << endl;
        cout << "   [3] Ir hacia adelante" << endl;
        cout << "   [4] Eliminar una URL" << endl;
        cout << "   [5] Mostrar historial (orden inverso)" << endl;
        cout << "   [0] Salir" << endl;
        cout << "==================================================" << endl;

        cout << " Seleccione una opcion: ";
        cin >> opcion;

        // Si el usuario escribe algo que no es un numero, cin falla.
        // Limpiamos el error y descartamos la entrada para no entrar en bucle.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Entrada invalida. Debe ingresar un numero." << endl;
            continue;
        }

        cin.ignore();

        switch (opcion)
        {
            case 1:
                cout << " >> REGISTRAR NUEVA VISITA" << endl;
                cout << " URL visitada (escriba 0 para cancelar): ";
                getline(cin, url);

                // El usuario puede arrepentirse: si escribe 0 o deja vacio,
                // cancelamos el registro y volvemos al menu principal.
                if (url == "0" || url == "")
                {
                    cout << " Registro cancelado. Volviendo al menu." << endl;
                }
                // Cada visita se registra con la fecha y hora del momento,
                // ya que siempre se agrega al final como la mas reciente.
                else
                {
                    string ahora = fechaHoraActual();
                    navegador.insertarVisita(url, ahora);
                    cout << " URL " << url << " registrada con fecha y hora actual (" << ahora << ")." << endl;
                }
                break;
            case 2:
                navegador.irAtras();
                break;
            case 3:
                navegador.irAdelante();
                break;
            case 4:
                cout << " >> ELIMINAR UNA URL" << endl;
                navegador.mostrarURLsNumeradas();
                if (navegador.contarPaginas() > 0)
                {
                    cout << " Numero de la URL a eliminar (0 para cancelar): ";
                    cin >> numURL;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << " Entrada invalida. Debe ingresar un numero." << endl;
                    }
                    // Si el usuario ya no quiere borrar, escribe 0 y volvemos al menu
                    else if (numURL == 0)
                    {
                        cin.ignore();
                        cout << " Eliminacion cancelada. Volviendo al menu." << endl;
                    }
                    else
                    {
                        cin.ignore();
                        navegador.eliminarPorNumero(numURL);
                    }
                }
                break;
            case 5:
                navegador.mostrarInverso();
                break;
            case 0:
                cout << " Cerrando el navegador." << endl;
                break;
            default:
                cout << " Opcion invalida." << endl;
        }

        // Linea en blanco despues de cada accion, para que el resultado
        // no se pegue con el menu que vuelve a aparecer. Asi cada bloque respira.
        cout << endl;

    } while (opcion != 0);

    return 0;
}

/*
   Analisis de complejidad (Big O)

   Aqui n es la cantidad de paginas que hay en el historial.

   Hay funciones que no recorren la lista, solo mueven unos punteros, asi
   que su tiempo no cambia aunque la lista crezca. Esas son O(1):
   insertarVisita (engancha al final con el puntero cola), mostrarActual,
   irAtras, irAdelante y desenlazar.

   Otras si tienen que recorrer la lista de principio a fin, por lo que su
   tiempo crece con la cantidad de paginas. Esas son O(n): contarPaginas,
   mostrarURLsNumeradas, eliminarPorNumero (en el peor caso llega hasta el
   ultimo nodo), mostrarInverso y el destructor que libera los nodos.

   Sumando todas, las O(1) no aumentan con el tamano de la lista pero las
   O(n) si, asi que el total lo marcan estas:

   Tiempo total = O(n)

   Es decir, el programa es de complejidad lineal: el tiempo de ejecucion
   crece de forma proporcional a la cantidad de paginas del historial.
*/