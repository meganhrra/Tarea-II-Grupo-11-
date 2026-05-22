#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


/*
    Clase Empleado

    Cada objeto representa un nodo
    de la lista enlazada.
*/
class Empleado
{
private:

    // ===== DATOS PRINCIPALES =====

    string nombre;
    double salarioBase;

    // ===== DESCUENTOS =====

    double impuestoRenta;
    double descuentoAFP;
    double descuentoARS;

    // ===== HORAS ADICIONALES =====

    double horasExtras;
    double horasFeriadas;
    double horasNocturnas;

    // ===== RESULTADOS =====

    double totalIngresosExtras;
    double totalDescuentos;
    double salarioNeto;

    // ===== PUNTERO =====

    Empleado* siguiente;

public:

    /*
        =====================================================
        CONSTANTES DEL SISTEMA
        =====================================================
    */

    // Porcentajes
    static constexpr double PORCENTAJE_AFP = 2.87;
    static constexpr double PORCENTAJE_ARS = 3.04;

    // Tarifas por horas
    static constexpr double PAGO_HORA_EXTRA = 307.40;
    static constexpr double PAGO_HORA_FERIADA = 187.62;
    static constexpr double PAGO_HORA_NOCTURNA = 28.49;

    // Constructor vacio
    Empleado()
    {
        nombre = "";

        salarioBase = 0;

        impuestoRenta = 0;
        descuentoAFP = 0;
        descuentoARS = 0;

        horasExtras = 0;
        horasFeriadas = 0;
        horasNocturnas = 0;

        totalIngresosExtras = 0;
        totalDescuentos = 0;
        salarioNeto = 0;

        siguiente = NULL;
    }

    // Constructor con parametros
    Empleado(
        string nombre,
        double salarioBase,

        double horasExtras,
        double horasFeriadas,
        double horasNocturnas
    )
    {
        this->nombre = nombre;

        this->salarioBase = salarioBase;

        this->horasExtras = horasExtras;
        this->horasFeriadas = horasFeriadas;
        this->horasNocturnas = horasNocturnas;

        /*
            =================================================
            CALCULO AUTOMATICO AFP Y ARS
            =================================================
        */

        descuentoAFP = salarioBase * (PORCENTAJE_AFP / 100);

        descuentoARS = salarioBase * (PORCENTAJE_ARS / 100);

        /*
            =================================================
            CALCULO DE ISR
            =================================================
        */

        double salarioAnual = salarioBase * 12;

        // Exento
        if (salarioAnual <= 416220)
        {
            impuestoRenta = 0;
        }

        // 15%
        else if (salarioAnual <= 624329)
        {
            impuestoRenta = ((salarioAnual - 416220) * 0.15) / 12;
        }

        // 20%
        else if (salarioAnual <= 867123)
        {
            impuestoRenta = (31216 + ((salarioAnual - 624329) * 0.20)) / 12;
        }

        // 25%
        else
        {
            impuestoRenta = (79776 + ((salarioAnual - 867123) * 0.25)) / 12;
        }

        /*
            =================================================
            CALCULO DE INGRESOS EXTRAS
            =================================================
        */

        totalIngresosExtras =

            (horasExtras * PAGO_HORA_EXTRA) +

            (horasFeriadas * PAGO_HORA_FERIADA) +

            (horasNocturnas * PAGO_HORA_NOCTURNA);

        /*
            =================================================
            CALCULO TOTAL DE DESCUENTOS
            =================================================
        */

        totalDescuentos = impuestoRenta + descuentoAFP + descuentoARS;

        /*
            =================================================
            CALCULO SALARIO NETO
            =================================================
        */

        salarioNeto = (salarioBase + totalIngresosExtras) - totalDescuentos;

        siguiente = NULL;
    }

    // ===== GETTERS =====

    string getNombre() const
    {
        return nombre;
    }

    double getSalarioBase() const
    {
        return salarioBase;
    }

    double getImpuestoRenta() const
    {
        return impuestoRenta;
    }

    double getDescuentoAFP() const
    {
        return descuentoAFP;
    }

    double getDescuentoARS() const
    {
        return descuentoARS;
    }

    double getHorasExtras() const
    {
        return horasExtras;
    }

    double getHorasFeriadas() const
    {
        return horasFeriadas;
    }

    double getHorasNocturnas() const
    {
        return horasNocturnas;
    }

    double getTotalIngresosExtras() const
    {
        return totalIngresosExtras;
    }

    double getTotalDescuentos() const
    {
        return totalDescuentos;
    }

    double getSalarioNeto() const
    {
        return salarioNeto;
    }

    Empleado* getSiguiente() const
    {
        return siguiente;
    }

    // Setter del siguiente nodo
    void setSiguiente(Empleado* siguiente)
    {
        this->siguiente = siguiente;
    }
};


/*
    Clase ListaEmpleados

    Maneja toda la lista enlazada.
*/
class ListaEmpleados
{
private:

    Empleado* cabeza;

public:

    // Constructor
    ListaEmpleados()
    {
        cabeza = NULL;

        precargarEmpleados();
    }

    /*
        =====================================================
        INSERTAR EMPLEADO AUTOMATICAMENTE
        =====================================================

        Complejidad:
        O(1)
    */
    void insertarEmpleadoAutomatico(
        string nombre,
        double salarioBase,

        double horasExtras,
        double horasFeriadas,
        double horasNocturnas
    )
    {
        Empleado* nuevoEmpleado =

            new Empleado(
                nombre,
                salarioBase,

                horasExtras,
                horasFeriadas,
                horasNocturnas
            );

        nuevoEmpleado->setSiguiente(cabeza);

        cabeza = nuevoEmpleado;
    }

    /*
        =====================================================
        EMPLEADOS PRECARGADOS
        =====================================================
    */
    void precargarEmpleados()
    {
        // ===== EMPLEADOS MAYORES A RD$50,000 =====

        insertarEmpleadoAutomatico(
            "Carlos Martinez",
            85000,
            10.5,
            5.0,
            8.5
        );

        insertarEmpleadoAutomatico(
            "Laura Fernandez",
            72000,
            8.5,
            4.0,
            6.5
        );

        insertarEmpleadoAutomatico(
            "Miguel Rodriguez",
            95000,
            12.0,
            6.5,
            10.5
        );

        // ===== EMPLEADOS MENORES A RD$50,000 =====

        insertarEmpleadoAutomatico(
            "Ana Garcia",
            32000,
            2.5,
            1.0,
            3.5
        );

        insertarEmpleadoAutomatico(
            "Pedro Reyes",
            28000,
            1.5,
            1.0,
            2.0
        );

        insertarEmpleadoAutomatico(
            "Maria Lopez",
            40000,
            3.5,
            2.0,
            4.5
        );

        insertarEmpleadoAutomatico(
            "Jose Ramirez",
            35000,
            2.0,
            2.5,
            3.0
        );

        insertarEmpleadoAutomatico(
            "Luisa Torres",
            30000,
            1.5,
            1.0,
            2.5
        );

        insertarEmpleadoAutomatico(
            "Rosa Pena",
            37000,
            2.0,
            1.5,
            4.0
        );

        insertarEmpleadoAutomatico(
            "Juan Tavarez",
            42000,
            3.0,
            2.5,
            5.0
        );

        insertarEmpleadoAutomatico(
            "Sofia Mendez",
            39000,
            2.5,
            1.0,
            3.5
        );

        insertarEmpleadoAutomatico(
            "Pablo Gonzalez",
            31000,
            1.0,
            1.5,
            2.0
        );

        insertarEmpleadoAutomatico(
            "Daniel Cruz",
            25000,
            1.0,
            0.5,
            1.5
        );

        insertarEmpleadoAutomatico(
            "Elena Vargas",
            45000,
            3.5,
            2.0,
            5.5
        );

        insertarEmpleadoAutomatico(
            "Luis Santos",
            47000,
            4.0,
            2.5,
            6.5
        );
    }

    /*
        =====================================================
        INCISO A
        INSERTAR EMPLEADO
        =====================================================

        Complejidad:
        O(1)
    */
    void insertarEmpleado()
    {
        cout << "\n========== REGISTRAR EMPLEADO ==========" << endl;

        string nombre;

        double salarioBase;

        double horasExtras;
        double horasFeriadas;
        double horasNocturnas;

        cin.ignore();

        cout << "Nombre del empleado: ";
        getline(cin, nombre);

        cout << "Salario base: RD$";
        cin >> salarioBase;

        cout << "Cantidad de horas extras: ";
        cin >> horasExtras;

        cout << "Cantidad de horas feriadas: ";
        cin >> horasFeriadas;

        cout << "Cantidad de horas nocturnas: ";
        cin >> horasNocturnas;

        // Crear nodo
        Empleado* nuevoEmpleado =

            new Empleado(
                nombre,
                salarioBase,

                horasExtras,
                horasFeriadas,
                horasNocturnas
            );

        /*
            El nuevo nodo apunta
            al antiguo inicio.
        */
        nuevoEmpleado->setSiguiente(cabeza);

        // Actualizar cabeza
        cabeza = nuevoEmpleado;

        cout << "\nEmpleado registrado correctamente." << endl;
    }

    /*
        =====================================================
        INCISO B
        MOSTRAR NOMINA
        =====================================================

        Complejidad:
        O(n)
    */
    void mostrarNomina() const
    {
        if (cabeza == NULL)
        {
            cout << "\nNo hay empleados registrados." << endl;
            return;
        }

        cout << fixed << setprecision(2);

        cout << "\n========== NOMINA DE EMPLEADOS ==========" << endl;

        Empleado* auxiliar = cabeza;

        int contador = 1;

        while (auxiliar != NULL)
        {
            cout << "\nEmpleado #" << contador << endl;

            cout << "Nombre: "
                 << auxiliar->getNombre() << endl;

            cout << "Salario base: RD$"
                 << auxiliar->getSalarioBase() << endl;

            cout << "ISR: RD$"
                 << auxiliar->getImpuestoRenta() << endl;

            cout << "AFP: RD$"
                 << auxiliar->getDescuentoAFP() << endl;

            cout << "ARS: RD$"
                 << auxiliar->getDescuentoARS() << endl;

            cout << "Horas extras: "
                 << auxiliar->getHorasExtras() << endl;

            cout << "Horas feriadas: "
                 << auxiliar->getHorasFeriadas() << endl;

            cout << "Horas nocturnas: "
                 << auxiliar->getHorasNocturnas() << endl;

            cout << "Ingresos extras: RD$"
                 << auxiliar->getTotalIngresosExtras() << endl;

            cout << "Descuentos totales: RD$"
                 << auxiliar->getTotalDescuentos() << endl;

            cout << "Salario neto: RD$"
                 << auxiliar->getSalarioNeto() << endl;

            auxiliar = auxiliar->getSiguiente();

            contador++;
        }
    }

    /*
        =====================================================
        INCISO C
        MOSTRAR EMPLEADOS MAYORES A RD$50,000
        =====================================================

        Complejidad:
        O(n)
    */
    void mostrarMayores50Mil() const
    {
        if (cabeza == NULL)
        {
            cout << "\nNo hay empleados registrados." << endl;
            return;
        }

        cout << fixed << setprecision(2);

        cout << "\n========== EMPLEADOS CON SALARIO MAYOR A RD$50,000 ==========" << endl;

        Empleado* auxiliar = cabeza;

        bool encontrado = false;

        while (auxiliar != NULL)
        {
            if (auxiliar->getSalarioNeto() > 50000)
            {
                encontrado = true;

                cout << "\nNombre: "
                     << auxiliar->getNombre() << endl;

                cout << "Salario neto: RD$"
                     << auxiliar->getSalarioNeto() << endl;
            }

            auxiliar = auxiliar->getSiguiente();
        }

        if (!encontrado)
        {
            cout << "\nNingun empleado supera RD$50,000." << endl;
        }
    }

    /*
        =====================================================
        MOSTRAR TODOS LOS EMPLEADOS
        =====================================================

        Complejidad:
        O(n)
    */
    void mostrarTodosLosEmpleados() const
    {
        if (cabeza == NULL)
        {
            cout << "\nNo hay empleados registrados." << endl;
            return;
        }

        cout << "\n========== LISTADO GENERAL DE EMPLEADOS ==========" << endl;

        Empleado* auxiliar = cabeza;

        int contador = 1;

        while (auxiliar != NULL)
        {
            cout << contador << ". "
                 << auxiliar->getNombre()
                 << endl;

            auxiliar = auxiliar->getSiguiente();

            contador++;
        }
    }

    /*
        =====================================================
        DESTRUCTOR
        =====================================================

        Libera memoria dinamica.
    */
    ~ListaEmpleados()
    {
        Empleado* auxiliar;

        while (cabeza != NULL)
        {
            auxiliar = cabeza;

            cabeza = cabeza->getSiguiente();

            delete auxiliar;
        }
    }
};


int main()
{
    ListaEmpleados lista;

    int opcion;

    do
    {
        cout << "\n======================================================" << endl;
        cout << "          SISTEMA DE GESTION DE NOMINA" << endl;
        cout << "======================================================" << endl;

        cout << "1. Registrar empleado" << endl;
        cout << "2. Mostrar listado de empleados" << endl;
        cout << "3. Mostrar nomina y salario neto" << endl;
        cout << "4. Mostrar empleados con salario mayor a RD$50,000" << endl;
        cout << "0. Salir" << endl;

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                lista.insertarEmpleado();
                break;

            case 2:
                lista.mostrarTodosLosEmpleados();
                break;

            case 3:
                lista.mostrarNomina();
                break;

            case 4:
                lista.mostrarMayores50Mil();
                break;

            case 0:
                cout << "\nSaliendo del sistema..." << endl;
                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }

    } while (opcion != 0);

    return 0;
}