#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <iomanip>

using namespace std;
using namespace chrono;

// ==================== ESTRUCTURAS DE DATOS ====================

// Estructura para representar un vehiculo
struct Vehiculo {
    string placa;
    string tipo;      
    string horaEntrada;
};

// Nodo para lista simplemente enlazada
struct NodoSimple {
    Vehiculo datos;
    NodoSimple* siguiente;
    
    NodoSimple(Vehiculo v) : datos(v), siguiente(nullptr) {}
};

// Nodo para lista doblemente enlazada
struct NodoDoble {
    Vehiculo datos;
    NodoDoble* siguiente;
    NodoDoble* anterior;
    
    NodoDoble(Vehiculo v) : datos(v), siguiente(nullptr), anterior(nullptr) {}
};

// LISTA SIMPLEMENTE ENLAZADA

class ListaSimple {
private:
    NodoSimple* inicio;
    
public:
    ListaSimple() : inicio(nullptr) {}
    
    // a) Insertar vehiculo al final de la lista
    void insertarAlFinal(Vehiculo v) {
        NodoSimple* nuevoNodo = new NodoSimple(v);
        
        if (inicio == nullptr) {
            inicio = nuevoNodo;
        } else {
            NodoSimple* actual = inicio;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }
    
    // b) Mostrar todos los vehiculos en orden de entrada
    void mostrarVehiculos() {
        cout << "\n--------------------------------------------------" << endl;
        cout << setw(10) << "PLACA" << " | " << setw(10) << "TIPO" 
             << " | " << setw(15) << "HORA ENTRADA" << endl;
        cout << "--------------------------------------------------" << endl;
        
        if (inicio == nullptr) {
            cout << "No hay vehiculos registrados" << endl;
            cout << "--------------------------------------------------" << endl;
            return;
        }
        
        NodoSimple* actual = inicio;
        int contador = 1;
        
        while (actual != nullptr) {
            cout << setw(10) << actual->datos.placa << " | "
                 << setw(10) << actual->datos.tipo << " | "
                 << setw(15) << actual->datos.horaEntrada << endl;
            actual = actual->siguiente;
            contador++;
        }
        cout << "--------------------------------------------------" << endl;
    }
    
    // c) Contar motocicletas
    int contarMotocicletas() {
        int contador = 0;
        NodoSimple* actual = inicio;
        
        while (actual != nullptr) {
            // Condicional anidada: verificar si es motocicleta
            if (actual->datos.tipo == "moto") {
                contador++;
            }
            actual = actual->siguiente;
        }
        
        return contador;
    }
    
    // Obtener cantidad total de vehiculos
    int obtenerTotal() {
        int contador = 0;
        NodoSimple* actual = inicio;
        
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        
        return contador;
    }
    
    // Destructor para liberar memoria
    ~ListaSimple() {
        NodoSimple* actual = inicio;
        while (actual != nullptr) {
            NodoSimple* temp = actual;
            actual = actual->siguiente;
            delete temp; 
        }
    }
};

// LISTA DOBLEMENTE ENLAZADA

class ListaDoble {
private:
    NodoDoble* inicio;
    NodoDoble* fin;
    
public:
    ListaDoble() : inicio(nullptr), fin(nullptr) {}
    
    // a) Insertar vehiculo al final de la lista
    void insertarAlFinal(Vehiculo v) {
        NodoDoble* nuevoNodo = new NodoDoble(v);
        
        if (inicio == nullptr) {
            inicio = nuevoNodo;
            fin = nuevoNodo;
        } else {
            fin->siguiente = nuevoNodo;
            nuevoNodo->anterior = fin;
            fin = nuevoNodo;
        }
    }
    
    // b) Mostrar todos los vehiculos en orden de entrada
    void mostrarVehiculos() {
        cout << "\n--------------------------------------------------" << endl;
        cout << setw(10) << "PLACA" << " | " << setw(10) << "TIPO" 
             << " | " << setw(15) << "HORA ENTRADA" << endl;
        cout << "--------------------------------------------------" << endl;
        
        if (inicio == nullptr) {
            cout << "No hay vehiculos registrados" << endl;
            cout << "--------------------------------------------------" << endl;
            return;
        }
        
        NodoDoble* actual = inicio;
        int contador = 1;
        
        while (actual != nullptr) {
            cout << setw(10) << actual->datos.placa << " | "
                 << setw(10) << actual->datos.tipo << " | "
                 << setw(15) << actual->datos.horaEntrada << endl;
            actual = actual->siguiente;
            contador++;
        }
        cout << "--------------------------------------------------" << endl;
    }
    
    // c) Contar motocicletas
    int contarMotocicletas() {
        int contador = 0;
        NodoDoble* actual = inicio;
        
        while (actual != nullptr) {
            // Condicional anidada: verificar si es motocicleta
            if (actual->datos.tipo == "moto") {
                contador++;
            }
            actual = actual->siguiente;
        }
        
        return contador;
    }
    
    // Obtener cantidad total de vehiculos
    int obtenerTotal() {
        int contador = 0;
        NodoDoble* actual = inicio;
        
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        
        return contador;
    }
    
    // Destructor para liberar memoria
    ~ListaDoble() {
        NodoDoble* actual = inicio;
        while (actual != nullptr) {
            NodoDoble* temp = actual;
            actual = actual->siguiente;
            delete temp; 
        }
    }
};

// ==================== SISTEMA DE ESTACION DE PARQUEO ====================

class EstacionParqueo {
private:
    ListaSimple listaSimple;
    ListaDoble listaDoble;
    high_resolution_clock::time_point tiempoInicio;
    
public:
    EstacionParqueo() {
        tiempoInicio = high_resolution_clock::now();
    }
    
    // Funcion para medir tiempo de una operacion
    long long medirTiempo(function<void()> operacion) {
        auto inicio = high_resolution_clock::now();
        operacion();
        auto fin = high_resolution_clock::now();
        return duration_cast<microseconds>(fin - inicio).count();
    }
    
    // Registrar un vehiculo en ambas listas
    void registrarVehiculo(string placa, string tipo, string hora) {
        Vehiculo v;
        v.placa = placa;
        v.tipo = tipo;
        v.horaEntrada = hora;
        
        long long tiempoSimple = medirTiempo([this, v]() {
            listaSimple.insertarAlFinal(v);
        });
        
        long long tiempoDoble = medirTiempo([this, v]() {
            listaDoble.insertarAlFinal(v);
        });
        
        cout << "\n> Vehiculo registrado: " << placa << " (" << tipo << ") a las " << hora << endl;
        cout << "  Tiempo insercion (Lista Simple): " << tiempoSimple << " microsegundos" << endl;
        cout << "  Tiempo insercion (Lista Doble): " << tiempoDoble << " microsegundos" << endl;
    }
    
    // Mostrar reporte del sistema
    void mostrarReporte() {
        cout << "\n\n";
        cout << "=======================================" << endl;
        cout << "    REPORTE DEL SISTEMA DE PARQUEO" << endl;
        cout << "=======================================" << endl;
        
        // ===== LISTA SIMPLE =====
        cout << "\n--- LISTA SIMPLEMENTE ENLAZADA ---\n" << endl;
        
        long long tiempoMostrar1 = medirTiempo([this]() {
            listaSimple.mostrarVehiculos();
        });
        
        int totalVehiculos = 0;
        long long tiempoContar1 = medirTiempo([this, &totalVehiculos]() {
            totalVehiculos = listaSimple.obtenerTotal();
        });
        
        int motos = 0;
        long long tiempoMotos1 = medirTiempo([this, &motos]() {
            motos = listaSimple.contarMotocicletas();
        });
        
        cout << "\n> Total de vehiculos: " << totalVehiculos << endl;
        cout << "> Total de motocicletas: " << motos << endl;
        cout << "> Total de carros: " << (totalVehiculos - motos) << endl;
        cout << "\nTiempos de ejecucion (Lista Simple):" << endl;
        cout << "  - Mostrar vehiculos: " << tiempoMostrar1 << " microsegundos" << endl;
        cout << "  - Contar total: " << tiempoContar1 << " microsegundos" << endl;
        cout << "  - Contar motos: " << tiempoMotos1 << " microsegundos" << endl;
        
        // ===== LISTA DOBLE =====
        cout << "\n--- LISTA DOBLEMENTE ENLAZADA ---\n" << endl;
        
        long long tiempoMostrar2 = medirTiempo([this]() {
            listaDoble.mostrarVehiculos();
        });
        
        int totalVehiculos2 = 0;
        long long tiempoContar2 = medirTiempo([this, &totalVehiculos2]() {
            totalVehiculos2 = listaDoble.obtenerTotal();
        });
        
        int motos2 = 0;
        long long tiempoMotos2 = medirTiempo([this, &motos2]() {
            motos2 = listaDoble.contarMotocicletas();
        });
        
        cout << "\n> Total de vehiculos: " << totalVehiculos2 << endl;
        cout << "> Total de motocicletas: " << motos2 << endl;
        cout << "> Total de carros: " << (totalVehiculos2 - motos2) << endl;
        cout << "\nTiempos de ejecucion (Lista Doble):" << endl;
        cout << "  - Mostrar vehiculos: " << tiempoMostrar2 << " microsegundos" << endl;
        cout << "  - Contar total: " << tiempoContar2 << " microsegundos" << endl;
        cout << "  - Contar motos: " << tiempoMotos2 << " microsegundos" << endl;
        
        // ===== TIEMPO TOTAL =====
        auto tiempoFinal = high_resolution_clock::now();
        long long tiempoTotal = duration_cast<microseconds>(tiempoFinal - tiempoInicio).count();
        
        cout << "\n=======================================" << endl;
        cout << "TIEMPO TOTAL DEL PROGRAMA: " << tiempoTotal << " microsegundos ("
             << fixed << setprecision(2) << tiempoTotal / 1000.0 << " ms)" << endl;
        cout << "=======================================" << endl;
    }
};

// ==================== FUNCION PRINCIPAL ====================

int main() {
    cout << "\n=======================================================" << endl;
    cout << "   SISTEMA DE REGISTRO DE VEHICULOS - ESTACION DE PARQUEO" << endl;
    cout << "=======================================================" << endl;
    
    EstacionParqueo estacion;
    
    // Registrar varios vehiculos (Estructuras repetitivas - while)
    cout << "\n--- REGISTRANDO VEHICULOS ---\n";
    
    estacion.registrarVehiculo("ABD-2024", "carro", "08:30");
    estacion.registrarVehiculo("XYZ-5678", "moto", "08:35");
    estacion.registrarVehiculo("QWE-9012", "carro", "08:40");
    estacion.registrarVehiculo("RTY-3456", "moto", "08:45");
    estacion.registrarVehiculo("UIO-7890", "moto", "08:50");
    estacion.registrarVehiculo("PAS-1234", "carro", "08:55");
    estacion.registrarVehiculo("DFG-5678", "carro", "09:00");
    estacion.registrarVehiculo("HJK-9012", "moto", "09:05");
    
    // Mostrar reporte completo
    estacion.mostrarReporte();
    
    cout << "\n";
    return 0;
}                   