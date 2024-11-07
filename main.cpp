#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Clase Cliente
class Cliente {
public:
    string nombre;
    string apellido;
    string direccion;
    string nit;
    string contacto;
    string tipoCliente; // "Particular" o "Empresarial"
    string planActual;

    Cliente(string nombre, string apellido, string direccion, string nit, string contacto, string tipoCliente)
        : nombre(nombre), apellido(apellido), direccion(direccion), nit(nit), contacto(contacto), tipoCliente(tipoCliente) {}

    void mostrarInformacion() const { // Marcada como const
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "Dirección: " << direccion << "\n";
        cout << "NIT: " << nit << "\n";
        cout << "Contacto: " << contacto << "\n";
        cout << "Tipo de Cliente: " << tipoCliente << "\n";
        cout << "Plan Actual: " << planActual << "\n";
    }
};

// Clase Servicio
class Servicio {
public:
    string nombre;
    string tipo; // Ej: Telefonía móvil, Internet, TV, etc.
    double costo;

    Servicio(string nombre, string tipo, double costo)
        : nombre(nombre), tipo(tipo), costo(costo) {}
};

// Clase Plan
class Plan {
public:
    string nombre;
    vector<Servicio> servicios;
    double costo;

    Plan(string nombre, double costo) : nombre(nombre), costo(costo) {}

    void agregarServicio(Servicio servicio) {
        servicios.push_back(servicio);
    }

    void mostrarPlan() const {
        cout << "Plan: " << nombre << " - Costo: " << costo << "\n";
        cout << "Servicios incluidos:\n";
        for (auto &servicio : servicios) {
            cout << "- " << servicio.nombre << " (" << servicio.tipo << ")\n";
        }
    }
};

// Clase Ticket para quejas
class Ticket {
public:
    int id;
    string descripcion;
    string estado; // Abierto, En progreso, Cerrado

    Ticket(int id, string descripcion) : id(id), descripcion(descripcion), estado("Abierto") {}

    void mostrarTicket() const {
        cout << "ID: " << id << " - " << descripcion << " - Estado: " << estado << "\n";
    }
};

// Función para registrar un cliente nuevo
void registrarCliente(vector<Cliente>& clientes) {
    string nombre, apellido, direccion, nit, contacto, tipoCliente;

    cout << "Ingrese nombre: ";
    cin >> nombre;
    cout << "Ingrese apellido: ";
    cin >> apellido;
    cout << "Ingrese direccion: ";
    cin >> direccion;
    cout << "Ingrese NIT: ";
    cin >> nit;
    cout << "Ingrese contacto: ";
    cin >> contacto;
    cout << "Ingrese tipo de cliente (Particular o Empresarial): ";
    cin >> tipoCliente;

    Cliente nuevoCliente(nombre, apellido, direccion, nit, contacto, tipoCliente);
    clientes.push_back(nuevoCliente);

    cout << "Cliente registrado exitosamente!\n";
}

// Función para buscar y mostrar un cliente registrado
void buscarCliente(const vector<Cliente>& clientes) {
    string nombre, apellido;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el apellido del cliente: ";
    cin >> apellido;

    for (const auto& cliente : clientes) {
        if (cliente.nombre == nombre && cliente.apellido == apellido) {
            cout << "Cliente encontrado:\n";
            cliente.mostrarInformacion();
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}

// Función para contratar un plan para un cliente registrado
void contratarPlan(vector<Cliente>& clientes, const vector<Plan>& planes) {
    string nombre, apellido, nombrePlan;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el apellido del cliente: ";
    cin >> apellido;

    for (auto& cliente : clientes) {
        if (cliente.nombre == nombre && cliente.apellido == apellido) {
            cout << "Planes disponibles:\n";
            for (const auto& plan : planes) {
                plan.mostrarPlan();
            }
            cout << "Ingrese el nombre del plan que desea contratar: ";
            cin >> nombrePlan;

            for (const auto& plan : planes) {
                if (plan.nombre == nombrePlan) {
                    cliente.planActual = nombrePlan;
                    cout << "Plan contratado exitosamente!\n";
                    return;
                }
            }
            cout << "Plan no encontrado.\n";
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}

// Función para registrar una queja y generar un ticket
void registrarQueja(vector<Ticket>& tickets) {
    static int ticketID = 1;
    string descripcion;

    cout << "Ingrese la descripción de la queja: ";
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, descripcion);

    Ticket nuevoTicket(ticketID++, descripcion);
    tickets.push_back(nuevoTicket);

    cout << "Ticket de queja generado exitosamente!\n";
}

// Función para mostrar todos los tickets de quejas
void mostrarTickets(const vector<Ticket>& tickets) {
    cout << "Tickets de quejas:\n";
    for (const auto& ticket : tickets) {
        ticket.mostrarTicket();
    }
}

// Función principal
int main() {
    vector<Cliente> clientes;
    vector<Plan> planes;
    vector<Ticket> tickets;

    // Ejemplo de creación de servicios y planes
    Servicio servicio1("Telefonia Movil", "Telefonia", 100);
    Servicio servicio2("Internet Residencial", "Internet", 200);
    Servicio servicio3("TV Basico", "Television", 150);

    Plan planBasico("Plan Básico", 100);
    planBasico.agregarServicio(servicio1);

    Plan planPremium("Plan Premium", 250);
    planPremium.agregarServicio(servicio1);
    planPremium.agregarServicio(servicio2);

    Plan planVIP("Plan VIP", 400);
    planVIP.agregarServicio(servicio1);
    planVIP.agregarServicio(servicio2);
    planVIP.agregarServicio(servicio3);

    planes.push_back(planBasico);
    planes.push_back(planPremium);
    planes.push_back(planVIP);

    int opcion;
    do {
        cout << "\n--- Menu de Opciones ---\n";
        cout << "1. Registrar Cliente Nuevo\n";
        cout << "2. Buscar Cliente Registrado\n";
        cout << "3. Contratar Plan\n";
        cout << "4. Registrar Queja\n";
        cout << "5. Mostrar Tickets de Quejas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCliente(clientes);
                break;
            case 2:
                buscarCliente(clientes);
                break;
            case 3:
                contratarPlan(clientes, planes);
                break;
            case 4:
                registrarQueja(tickets);
                break;
            case 5:
                mostrarTickets(tickets);
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}