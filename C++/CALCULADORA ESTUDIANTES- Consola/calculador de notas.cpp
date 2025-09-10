#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <locale>
#include <vector>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

// Colores para el texto
#define AZUL_VIVO "\033[38;5;33m"
#define VIOLETA "\033[38;5;93m"
#define NARANJA "\033[38;5;214m"
#define ROJO "\033[38;5;196m"
#define RESET "\033[0m"
#define VERDE "\033[32m"
#define ROJO_BRILLANTE "\033[38;5;196m"
#define CIAN " \033[36m"
#define GRIS " \033[90m"

// Control de plataforma para limpiar la consola
#if defined(_WIN32) || defined(_WIN64)
#define LIMPIAR_CONSOLA system("cls")
#else
#define LIMPIAR_CONSOLA system("clear")
#endif

// Declaración anticipada de funciones
string trim(const string& s);
struct Materia;
vector<Materia> cargarHistorial();
void guardarHistorial(const vector<Materia>& materias);
void guardarMateria(vector<Materia>& materias, const Materia& nuevaMateria);
void dibujarGraficoBarras(vector<Materia>& materias);
void calcularPromedioGeneral(const vector<Materia>& materias);
string obtenerFechaActual();
bool manejarSalida();
Materia calcularMateria(const vector<Materia>& materiasExistentes);

// Estructura para almacenar la información de cada materia
struct Materia {
    string nombre;
    double notaFinal;
    double nota100;
    double porcentajeTotal;
    string estado;
    string estadoAprobacion;
    string fecha; // "dd-mm-yyyy hh:mm:ss"
    string notaNecesaria;
};

// Función auxiliar para eliminar espacios en blanco
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

// Función para obtener la fecha y hora actual como string
string obtenerFechaActual() {
    auto ahora = chrono::system_clock::now();
    auto tiempo = chrono::system_clock::to_time_t(ahora);
    struct tm localTime;
    localtime_s(&localTime, &tiempo);
    stringstream ss;
    ss << put_time(&localTime, "%d-%m-%Y %H:%M:%S");
    return ss.str();
}

// Función para ingresar y calcular una materia, teniendo en cuenta el porcentaje acumulado (si la materia ya existe)
Materia calcularMateria(const vector<Materia>& materiasExistentes) {
    int cantidadNotas;
    double nota, tmpPorcentaje, porcentaje;
    double porcentajeTotalNuevo = 0, notaFinalNuevo = 0, nota100Nuevo = 0;
    string nombreMateria;

    cout << endl << AZUL_VIVO << "Por favor ingrese el nombre de la materia: " << RESET;
    getline(cin, nombreMateria);

    // Verificar si la materia ya existe
    double porcentajeExistente = 0;
    for (const auto& mat : materiasExistentes) {
        if (trim(mat.nombre) == trim(nombreMateria)) {
            porcentajeExistente = mat.porcentajeTotal;
            break;
        }
    }
    if (porcentajeExistente > 0)
        cout << NARANJA << "La materia ya tiene " << porcentajeExistente << "% acumulado." << RESET << endl;

    cout << endl << AZUL_VIVO << "¿Cuántas notas desea ingresar?: " << RESET;
    cin >> cantidadNotas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Ingresar cada nota
    for (int i = 1; i <= cantidadNotas; i++) {
        cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << AZUL_VIVO << "Ingrese la nota " << i << ": " << RESET;
        cin >> nota;
        while (nota < 0 || nota > 5) {
            cout << ROJO << "¡ADVERTENCIA! La nota debe estar entre 0 y 5. Intente nuevamente: " << RESET;
            cin >> nota;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar entrada

        // Bucle para solicitar el porcentaje sin exceder el 100% (incluyendo lo acumulado)
        while (true) {
            cout << AZUL_VIVO << "Ingrese el porcentaje de la nota " << i << " (sin el %): " << RESET;
            string input;
            getline(cin, input);
            try {
                tmpPorcentaje = stod(input);
            }
            catch (...) {
                cout << ROJO << "Entrada inválida. Intente nuevamente." << RESET << endl;
                continue;
            }
            if (porcentajeExistente + porcentajeTotalNuevo + tmpPorcentaje > 100) {
                double disponible = 100 - (porcentajeExistente + porcentajeTotalNuevo);
                cout << ROJO << "El porcentaje acumulado (incluyendo lo existente) es "
                    << (porcentajeExistente + porcentajeTotalNuevo)
                    << "%. Solo te falta " << disponible
                    << "% para llegar a 100%. Por favor, ingrese un porcentaje menor o igual a "
                    << disponible << "%." << RESET << endl;
                continue;
            }
            else {
                porcentaje = tmpPorcentaje;
                break;
            }
        }

        porcentajeTotalNuevo += porcentaje;
        // Forzamos la división en punto flotante usando 100.0
        notaFinalNuevo += (nota * porcentaje / 100.0);
    }

    if (porcentajeTotalNuevo > 0)
        nota100Nuevo = (notaFinalNuevo / porcentajeTotalNuevo) * 100.0;

    Materia mat;
    mat.nombre = nombreMateria;
    mat.notaFinal = notaFinalNuevo;
    mat.nota100 = nota100Nuevo;
    mat.porcentajeTotal = porcentajeTotalNuevo;
    mat.fecha = obtenerFechaActual();
    // Los campos "estado" y "estadoAprobacion" se actualizarán en guardarMateria()
    return mat;
}

// Función para cargar el historial consolidado desde el archivo
vector<Materia> cargarHistorial() {
    vector<Materia> materias;
    ifstream archivo("historial_notas.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de historial." << endl;
        return materias;
    }
    string linea;
    map<string, Materia> materiasMap;
    while (getline(archivo, linea)) {
        if (linea.find("Materia: ") == 0) {
            Materia materia;
            materia.nombre = trim(linea.substr(9));
            if (getline(archivo, linea) && linea.find("Fecha: ") == 0)
                materia.fecha = trim(linea.substr(7));
            if (getline(archivo, linea) && linea.find("Nota acumulada: ") == 0)
                materia.notaFinal = stod(trim(linea.substr(17)));
            if (getline(archivo, linea) && linea.find("nota parcial (100%): ") == 0)
                materia.nota100 = stod(trim(linea.substr(20)));
            if (getline(archivo, linea) && linea.find("Porcentaje total: ") == 0) {
                size_t pos = linea.find('%');
                if (pos != string::npos)
                    materia.porcentajeTotal = stod(trim(linea.substr(18, pos - 18)));
            }
            if (getline(archivo, linea) && linea.find("Estado: ") == 0)
                materia.estado = trim(linea.substr(8));
            if (getline(archivo, linea) && linea.find("Aprobacion: ") == 0)
                materia.estadoAprobacion = trim(linea.substr(12));
            if (getline(archivo, linea) && linea.find("Nota necesaria para aprobar: ") == 0)
                materia.notaNecesaria = trim(linea.substr(28));

            if (materia.nota100 >= 3.0)
                materia.estadoAprobacion = "  Aprobando";
            else
                materia.estadoAprobacion = "  Reprobado";
            if (materia.porcentajeTotal == 100) {
                if (materia.nota100 >= 3.0)
                    materia.estado = "Aprobado";
                else
                    materia.estado = "Reprobado";
            }
            else {
                materia.estado = "Semestre Incompleto";
            }
            if (materiasMap.find(materia.nombre) != materiasMap.end()) {
                if (materiasMap[materia.nombre].porcentajeTotal < 100) {
                    double nuevoPorcentaje = materiasMap[materia.nombre].porcentajeTotal + materia.porcentajeTotal;
                    if (nuevoPorcentaje > 100)
                        nuevoPorcentaje = 100;
                    materiasMap[materia.nombre].notaFinal += materia.notaFinal;
                    materiasMap[materia.nombre].porcentajeTotal = nuevoPorcentaje;
                    if (nuevoPorcentaje > 0)
                        materiasMap[materia.nombre].nota100 = (materiasMap[materia.nombre].notaFinal / nuevoPorcentaje) * 100.0;
                    if (materiasMap[materia.nombre].porcentajeTotal == 100) {
                        if (materiasMap[materia.nombre].nota100 >= 3.0)
                            materiasMap[materia.nombre].estado = "Aprobado";
                        else
                            materiasMap[materia.nombre].estado = "Reprobado";
                    }
                    else {
                        materiasMap[materia.nombre].estado = "Semestre Incompleto";
                    }
                    if (materiasMap[materia.nombre].nota100 >= 3.0)
                        materiasMap[materia.nombre].estadoAprobacion = "  Aprobando";
                    else
                        materiasMap[materia.nombre].estadoAprobacion = "  Reprobado";
                }
            }
            else {
                materiasMap[materia.nombre] = materia;
            }
        }
    }
    archivo.close();
    for (const auto& pair : materiasMap)
        materias.push_back(pair.second);
    return materias;
}

void guardarHistorial(const vector<Materia>& materias) {
    ofstream archivo("historial_notas.txt", ios::trunc);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de historial para guardar." << endl;
        return;
    }
    map<string, Materia> materiasMap;
    for (const auto& materia : materias) {
        if (materiasMap.find(materia.nombre) != materiasMap.end()) {
            if (materiasMap[materia.nombre].porcentajeTotal < 100) {
                double nuevoPorcentaje = materiasMap[materia.nombre].porcentajeTotal + materia.porcentajeTotal;
                if (nuevoPorcentaje > 100)
                    nuevoPorcentaje = 100;
                materiasMap[materia.nombre].notaFinal += materia.notaFinal;
                materiasMap[materia.nombre].porcentajeTotal = nuevoPorcentaje;
                if (nuevoPorcentaje > 0)
                    materiasMap[materia.nombre].nota100 = (materiasMap[materia.nombre].notaFinal / nuevoPorcentaje) * 100.0;
            }
        }
        else {
            materiasMap[materia.nombre] = materia;
        }
    }
    for (const auto& pair : materiasMap) {
        const Materia& materia = pair.second;
        archivo << "Materia:  " << materia.nombre << endl;
        archivo << "Fecha:  " << materia.fecha << endl;
        archivo << "Nota acumulada:  " << fixed << setprecision(2) << materia.notaFinal << endl;
        archivo << "nota parcial (100%):  " << fixed << setprecision(2) << materia.nota100 << endl;
        archivo << "Porcentaje total:  " << fixed << setprecision(2) << materia.porcentajeTotal << "%" << endl;
        archivo << "Estado:  " << materia.estado << endl;
        archivo << "Aprobacion: " << materia.estadoAprobacion << endl;
        if (!materia.notaNecesaria.empty())
            archivo << "Nota necesaria para aprobar: " << materia.notaNecesaria << endl;
        archivo << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
    archivo.close();
}


void borrarMateriaEspecifica(vector<Materia>& materias) {
    cout << AZUL_VIVO << "Ingrese el nombre de la materia que desea borrar: " << RESET;
    string nombre;
    getline(cin, nombre);
    auto it = remove_if(materias.begin(), materias.end(), [&nombre](const Materia& m) {
        return trim(m.nombre) == trim(nombre);
        });
    if (it != materias.end()) {
        materias.erase(it, materias.end());
        guardarHistorial(materias);
        cout << VERDE << "Materia eliminada correctamente." << RESET << endl;
    }
    else {
        cout << ROJO << "No se encontró ninguna materia con ese nombre." << RESET << endl;
    }
    cout << "Presione Enter para continuar...";
    cin.ignore();
}


void guardarMateria(vector<Materia>& materias, const Materia& nuevaMateria) {
    auto it = find_if(materias.begin(), materias.end(), [&nuevaMateria](const Materia& m) {
        return trim(m.nombre) == trim(nuevaMateria.nombre);
        });
    if (it != materias.end()) {
        double available = 100 - it->porcentajeTotal;
        if (nuevaMateria.porcentajeTotal > available) {
            cout << ROJO << "No se puede ingresar " << nuevaMateria.porcentajeTotal
                << "%, ya que solo quedan " << available
                << "% para completar el 100%." << RESET << endl;
            return;
        }
        it->notaFinal += nuevaMateria.notaFinal;
        it->porcentajeTotal += nuevaMateria.porcentajeTotal;
        if (it->porcentajeTotal > 100)
            it->porcentajeTotal = 100;
        if (it->porcentajeTotal > 0)
            it->nota100 = (it->notaFinal / it->porcentajeTotal) * 100.0;
        it->fecha = nuevaMateria.fecha;
        if (it->porcentajeTotal == 100) {
            if (it->nota100 >= 3.0)
                it->estado = "Aprobado";
            else
                it->estado = "Reprobado";
        }
        else {
            it->estado = "Semestre Incompleto";
        }
        if (it->nota100 >= 3.0)
            it->estadoAprobacion = "  Aprobando";
        else
            it->estadoAprobacion = "  Reprobado";
    }
    else {
        Materia materiaNueva = nuevaMateria;
        if (materiaNueva.porcentajeTotal == 100) {
            if (materiaNueva.nota100 >= 3.0)
                materiaNueva.estado = "Aprobado";
            else
                materiaNueva.estado = "Reprobado";
        }
        else {
            materiaNueva.estado = "Semestre Incompleto";
        }
        if (materiaNueva.nota100 >= 3.0)
            materiaNueva.estadoAprobacion = "  Aprobando";
        else
            materiaNueva.estadoAprobacion = "  Reprobado";
        materias.push_back(materiaNueva);
    }
}

void dibujarGraficoBarras(vector<Materia>& materias) {
    if (materias.empty()) {
        cout << NARANJA << "No hay materias en el historial para graficar." << RESET << endl;
        return;
    }
    cout << VIOLETA << " Gráfico de Rendimiento" << RESET << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    double notaMaxima = 5.0;
    cout << " Este gráfico representa visualmente el desempeño en cada materia, ofreciendo una perspectiva general del rendimiento " << endl;
    cout << " académico y facilitando la identificación de áreas que requieren atención." << endl;
    cout << VERDE " Verde Si vas bien en tus notas █████████" << RESET
        << NARANJA " Naranja si necesitas mejorar █████████" << RESET
        << ROJO " Rojo si vas mal o Reprobaste █████████ " << RESET << endl << endl;
    cout << VIOLETA "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CIAN << " \tMATERIAS" << RESET << setw(20)
        << VIOLETA "\t\tNOTA(0 A 5)" << RESET << setw(15) << AZUL_VIVO
        << "  PORCENTAJE(%)" << setw(15) << RESET
        << GRIS "ESTADO" << setw(15) << RESET
        << NARANJA "NOTA PARA APROBAR " << setw(15) << RESET << endl;
    cout << VIOLETA "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;

    map<string, Materia> matMap;
    for (auto mat : materias) {
        mat.nombre = trim(mat.nombre);
        if (matMap.find(mat.nombre) != matMap.end()) {
            double nuevoPorcentaje = matMap[mat.nombre].porcentajeTotal + mat.porcentajeTotal;
            if (nuevoPorcentaje > 100)
                nuevoPorcentaje = 100;
            double nuevaNotaFinal = matMap[mat.nombre].notaFinal + mat.notaFinal;
            matMap[mat.nombre].notaFinal = nuevaNotaFinal;
            matMap[mat.nombre].porcentajeTotal = nuevoPorcentaje;
            if (nuevoPorcentaje > 0)
                matMap[mat.nombre].nota100 = (nuevaNotaFinal / nuevoPorcentaje) * 100.0;
            if (matMap[mat.nombre].porcentajeTotal == 100) {
                if (matMap[mat.nombre].nota100 >= 3.0)
                    matMap[mat.nombre].estado = "  Aprobado";
                else
                    matMap[mat.nombre].estado = "  Reprobado";
            }
            else {
                matMap[mat.nombre].estado = "  Semestre Incompleto";
            }
            if (matMap[mat.nombre].nota100 >= 3.0)
                matMap[mat.nombre].estadoAprobacion = "  Aprobando";
            else
                matMap[mat.nombre].estadoAprobacion = "  Reprobado";
        }
        else {
            matMap[mat.nombre] = mat;
        }
    }

    for (const auto& pair : matMap) {
        const Materia& mat = pair.second;
        cout << CIAN << std::left << mat.nombre << RESET << "  ";
        int longitudBarra = static_cast<int>((mat.nota100 / notaMaxima) * 30);
        if (mat.nota100 >= 3.0)
            cout << VERDE;
        else if (mat.nota100 >= 2.0)
            cout << NARANJA;
        else
            cout << ROJO;
        for (int i = 0; i < longitudBarra; i++)
            cout << "█";
        cout << RESET;
        cout << VIOLETA << std::right << setw(15) << fixed << setprecision(2) << mat.nota100 << RESET;
        cout << AZUL_VIVO << std::right << setw(15) << fixed << setprecision(2) << mat.porcentajeTotal << "%" << RESET;

        // Se imprime el estado en una columna separada (ancho 20)
        cout << std::right << setw(20) << mat.estado << RESET;

        // Si la materia no está completa, se calcula y se muestra la nota necesaria para aprobar en NARANJA.
        if (mat.porcentajeTotal < 100) {
            double porcentajeRestante = 100 - mat.porcentajeTotal;
            double notaNecesariaCalc = (3.0 - mat.notaFinal) / (porcentajeRestante / 100.0);
            cout << NARANJA << std::right << setw(20) << fixed << setprecision(2) << notaNecesariaCalc << RESET;
        }
        else {
            if (!mat.notaNecesaria.empty())
                cout << std::right << setw(20) << mat.notaNecesaria;
        }

        cout << endl << " Fecha: " << mat.fecha << endl;
        cout << VIOLETA "------------------------------------------------------------------------------------------------------------------------" << RESET;
    }
}


void calcularPromedioGeneral(const vector<Materia>& materias) {
    if (materias.empty()) {
        cout << NARANJA << "No hay materias en el historial para calcular el promedio." << RESET << endl;
        return;
    }
    size_t anchoMaximo = 20;
    for (const auto& materia : materias) {
        anchoMaximo = max(anchoMaximo, materia.nombre.length());
    }
    cout << CIAN << "Aca encontraras un resumen de tus materias y un promedio total de las notas acumuladas.. " << RESET << endl;
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << setw(anchoMaximo) << left << "    MATERIA" << setw(10) << right << "    NOTA" << setw(12) << right << "\t\tPORCENTAJE(%)" << setw(15) << right << "    \tEstado" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
    double sumaNotas = 0, notaMax = -1, notaMin = 6;
    string materiaMax, materiaMin;
    int aprobadas = 0, reprobadas = 0, enProceso = 0;
    for (const auto& materia : materias) {
        stringstream ss;
        ss << setw(anchoMaximo) << left << materia.nombre;
        ss << setw(11) << right << fixed << setprecision(2) << materia.nota100;
        ss << setw(22) << right << AZUL_VIVO << fixed << setprecision(0) << materia.porcentajeTotal << "%" << RESET;
        string estadoResumen;
        if (materia.estadoAprobacion.find("Reprobado") != string::npos) {
            estadoResumen = string(ROJO) + "\t\t\tReprobado" + RESET;
            reprobadas++;
        }
        else if (materia.nota100 >= 3.0 && materia.porcentajeTotal == 100) {
            estadoResumen = string(VERDE) + "\t\t\tAprobado" + RESET;
            aprobadas++;
        }
        else if (materia.porcentajeTotal < 100) {
            estadoResumen = string(NARANJA) + "\t\t\tEn proceso.." + RESET;
            enProceso++;
        }
        else {
            estadoResumen = string(ROJO) + "\t\t\tReprobado" + RESET;
            reprobadas++;
        }
        ss << setw(15) << left << estadoResumen;
        cout << ss.str() << endl;
        sumaNotas += materia.nota100;
        if (materia.nota100 > notaMax) {
            notaMax = materia.nota100;
            materiaMax = materia.nombre;
        }
        if (materia.nota100 < notaMin) {
            notaMin = materia.nota100;
            materiaMin = materia.nombre;
        }
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    double promedioGeneral = sumaNotas / materias.size();
    cout << endl << "  El promedio general de tus notas es: " << fixed << setprecision(2) << promedioGeneral << endl << endl;
    if (promedioGeneral >= 4.0)
        cout << VERDE << "\t\t\t\t\t¡Excelente trabajo! ¡Sigue así!" << RESET << endl;
    else if (promedioGeneral >= 3.0)
        cout << NARANJA << "\t\t\t\t\t¡Buen trabajo!" << RESET << endl;
    else
        cout << ROJO << "\t\t\t\t\t¡Aún puedes mejorar!" << RESET << endl;
    cout << endl << "Estadísticas adicionales:" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(30) << left << "Materia con la nota más alta:" << VIOLETA << materiaMax << " (" << fixed << setprecision(2) << notaMax << ")" << RESET << endl;
    cout << setw(30) << left << "Materia con la nota más baja:" << VIOLETA << materiaMin << " (" << fixed << setprecision(2) << notaMin << ")" << RESET << endl;
    cout << setw(30) << left << "Materias aprobadas:" << VERDE << aprobadas << RESET << endl;
    cout << setw(30) << left << "Materias reprobadas:" << ROJO << reprobadas << RESET << endl;
    cout << setw(30) << left << "Materias en proceso:" << NARANJA << enProceso << RESET << endl << endl << endl;
    cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
}

bool manejarSalida() {
    char opcionSalida;
    cout << "Presione Enter para volver ATRAS o 1 para SALIR: ";
    cin.get(opcionSalida);
    if (opcionSalida == '1') {
        cout << VIOLETA << endl
            << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
        cout << VIOLETA << "                                             ¡GRACIAS POR USAR LA APLICACION!                       " << RESET << endl << endl;
        cout << ROJO_BRILLANTE << "    Programa diseñado por Juan Camilo...  *_*                     " << RESET << endl;
        cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
        cin.ignore();
        cin.get();
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    // Forzamos el uso del punto como separador decimal:
    setlocale(LC_NUMERIC, "C");

    char opcion;
    vector<Materia> materias = cargarHistorial();
    do {
        LIMPIAR_CONSOLA;
        cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
        cout << VIOLETA << "║                                                                                                                      ║" << RESET << endl;
        cout << VIOLETA << "║                                          BIENVENIDO AL CALCULADOR DE NOTAS                                           ║" << RESET << endl;
        cout << VIOLETA << "║                                                                                                                      ║" << RESET << endl;
        cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl << endl << endl;
        cout << AZUL_VIVO << "                                                   MENU PRINCIPAL                                               " << RESET << endl << endl << endl << endl;
        cout << "          1. Calculadora de notas     2. Historial de notas    3. Promedio general    4. Gráfico de rendimiento" << endl << endl << endl;

        cout << "                                    5. Instrucciones de uso        6. Salir" << endl << endl << endl;

        cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl << endl;
        cout << "JC " << endl;
        cout << "Seleccione una opción (1 a 6): ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (opcion) {
        case '1': {
            char subopcion;
            do {
                LIMPIAR_CONSOLA;
                cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                cout << AZUL_VIVO << "                                                 CALCULARDORA DE NOTAS                                    " << RESET << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl << endl;
                cout << "1.  Realizar cálculos de notas" << endl << endl;
                cout << "2.  Salir " << endl << endl << endl << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                cout << "Seleccione una opción (1 a 2): ";
                cin >> subopcion;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (subopcion == '1') {
                    LIMPIAR_CONSOLA;
                    Materia nuevaMateria = calcularMateria(materias);
                    guardarMateria(materias, nuevaMateria);
                    guardarHistorial(materias);
                    materias = cargarHistorial();
                    Materia materiaConsolidada;
                    for (const auto& m : materias) {
                        if (trim(m.nombre) == trim(nuevaMateria.nombre)) {
                            materiaConsolidada = m;
                            break;
                        }
                    }
                    cout << fixed << setprecision(2);
                    cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                    cout << VIOLETA << "                                                  RESULTADOS DE LA MATERIA                                     " << RESET << endl;
                    cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                    cout << "MATERIA: " << materiaConsolidada.nombre << endl << endl;
                    cout << "Porcentaje ingresado: " << fixed << setprecision(0) << materiaConsolidada.porcentajeTotal << "%" << endl;
                    cout << NARANJA << "Nota acumulada : " << RESET << fixed << setprecision(2) << materiaConsolidada.notaFinal;
                    cout << "    " << NARANJA << "Nota parcial (100%) : " << RESET << fixed << setprecision(2) << materiaConsolidada.nota100 << endl << endl;
                    if (materiaConsolidada.porcentajeTotal == 100) {
                        if (materiaConsolidada.nota100 >= 3)
                            cout << "------------------------------------------------------------------------------------------------------------------------" << endl
                            << "Resultado final de la materia: " << materiaConsolidada.nombre << endl
                            << VERDE << "                                             ¡Semestre Aprobado FELICIDADES!" << RESET << endl;
                        else
                            cout << "------------------------------------------------------------------------------------------------------------------------" << endl
                            << "Resultado final de la materia: " << materiaConsolidada.nombre << endl
                            << ROJO << "                                              ¡Semestre Reprobado! ¡MUCHO ANIMO!" << RESET << endl;
                    }
                    else {
                        if (materiaConsolidada.nota100 >= 3)
                            cout << "------------------------------------------------------------------------------------------------------------------------" << endl
                            << "Resultado final de la materia: " << materiaConsolidada.nombre << endl
                            << VERDE << "                                              ¡Vas muy Bien !" << RESET << endl;
                        else
                            cout << "------------------------------------------------------------------------------------------------------------------------" << endl
                            << "Resultado final de la materia: " << materiaConsolidada.nombre << endl
                            << ROJO_BRILLANTE << "                                              ¡Vas MAL ponte pilas!" << RESET << endl;
                    }
                    if (materiaConsolidada.porcentajeTotal == 100)
                        cout << endl << "Estado: " << AZUL_VIVO << "Semestre Completado 100%" << RESET << endl << endl;
                    else {
                        cout << endl << "Estado: " << VIOLETA << "Semestre Incompleto " << RESET << endl << endl;
                        double porcentajeRestante = 100 - materiaConsolidada.porcentajeTotal;
                        double notaNecesaria = (3.0 - materiaConsolidada.notaFinal) / (porcentajeRestante / 100.0);
                        if (notaNecesaria > 5.0) {
                            materiaConsolidada.estadoAprobacion = "  Reprobado";
                            materiaConsolidada.notaNecesaria = "Imposible aprobar con la nota actual.";
                            cout << NARANJA << endl << "Aprobacion: " << materiaConsolidada.estadoAprobacion << RESET << endl;
                            cout << NARANJA << "Nota necesaria para aprobar: " << materiaConsolidada.notaNecesaria << RESET << endl;
                        }
                        else if (notaNecesaria > 0) {
                            cout << NARANJA << endl << "Para aprobar, necesitas obtener al menos " << fixed << setprecision(2)
                                << notaNecesaria << " en el " << fixed << setprecision(0) << porcentajeRestante << "% restante." << RESET << endl << endl << endl;
                        }
                    }
                    guardarHistorial(materias);
                    cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                    cout << endl << "Presione Enter para volver ...";

                    cin.ignore();
                }
                else if (subopcion != '2') {
                    cout << "Opción no válida." << endl;
                }
            } while (subopcion != '2');
            break;
        }
        case '2': {
            char subopcionHistorial;
            do {
                LIMPIAR_CONSOLA;
                cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                cout << AZUL_VIVO << "                                                   HISTORIAL DE NOTAS                             " << RESET << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                cout << "1. Mostrar historial" << endl << endl;
                cout << "2. Borrar todo el historial" << endl << endl;
                cout << "3. Borrar una materia en específico" << endl << endl;
                cout << "4. Salir" << endl << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                cout << "Seleccione una opción (1 a 4): ";
                cin >> subopcionHistorial;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (subopcionHistorial == '1') {
                    // Mostrar historial (código existente)
                    LIMPIAR_CONSOLA;
                    cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                    cout << AZUL_VIVO << "                                                   HISTORIAL                      " << RESET << endl;
                    cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                    if (materias.empty()) {
                        cout << NARANJA << "Lo SIENTO No hay materias guardadas en el historial." << RESET << endl << endl << endl;
                    }
                    else {
                        cout << fixed << setprecision(2);
                        for (const auto& materia : materias) {
                            cout << CIAN << "MATERIA:    " << materia.nombre << RESET << endl;
                            cout << "Fecha de ingreso:    " << materia.fecha << endl << endl;
                            cout << "Nota acumulada:    " << fixed << setprecision(2) << materia.notaFinal << endl;
                            cout << NARANJA << "Nota parcial (100%):     " << fixed << setprecision(2) << materia.nota100 << RESET << endl;
                            cout << VERDE << "Porcentaje total:    " << materia.porcentajeTotal << "%" << RESET << endl << endl;
                            cout << "Estado:      " << materia.estado << endl;
                            cout << "Aprobacion:  " << materia.estadoAprobacion << endl << endl;
                            if (!materia.notaNecesaria.empty()) {
                                cout << NARANJA << "Nota necesaria para aprobar:  " << materia.notaNecesaria << RESET << endl << endl;
                            }
                            cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
                        }
                        cout << fixed << setprecision(0);
                    }
                    cout << endl << "Presione Enter para volver ...";
                    cin.ignore();
                }
                else if (subopcionHistorial == '2') {
                    char confirmacion;
                    cout << ROJO << endl << "               ¡ ADVERTENCIA !" << RESET << endl;
                    cout << endl << ROJO_BRILLANTE << "¿Estás seguro de que deseas borrar todo el historial? (S/N): " << RESET;
                    cin >> confirmacion;
                    if (confirmacion == 'S' || confirmacion == 's') {
                        materias.clear();
                        guardarHistorial(materias);
                        cout << NARANJA << endl << "   Historial borrado EXITOSAMENTE." << RESET << endl;
                    }
                    else {
                        cout << NARANJA << endl << "   El historial NO se borró." << RESET << endl;
                    }
                    cout << endl << "Presione Enter para volver...";
                    cin.get();
                    cin.ignore();
                }
                else if (subopcionHistorial == '3') {
                    borrarMateriaEspecifica(materias);
                }
                else if (subopcionHistorial != '4') {
                    cout << "Opción no válida." << endl;
                }
            } while (subopcionHistorial != '4');
            break;
        }

        case '3': {
            char subopcionPromedio;
            do {
                LIMPIAR_CONSOLA;
                cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                cout << AZUL_VIVO << "                                            PROMEDIO GENERAL                               " << RESET << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                calcularPromedioGeneral(materias);
                cout << endl << "1. Volver al menú principal" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcionPromedio;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while (subopcionPromedio != '1');
            break;
        }
        case '4': {
            char subopcionGrafico;
            do {
                LIMPIAR_CONSOLA;
                cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
                cout << AZUL_VIVO << "                                               GRAFICO DE RENDIMIENTO                               " << RESET << endl;
                cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl << endl;
                dibujarGraficoBarras(materias);
                cout << VIOLETA << endl << endl << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << endl << "1. Volver al menú principal" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcionGrafico;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while (subopcionGrafico != '1');
            break;
        }
        case '5': {
            LIMPIAR_CONSOLA;
            cout << AZUL_VIVO << "" << RESET << endl;
            cout << VIOLETA << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
            cout << VIOLETA << "                                             Instrucciones de la Aplicación" << RESET << endl;
            cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
            cout << "                Este programa esta diseñado para calcular tus notas academicas." << endl;
            cout << "                Permite conocer el estado del semestre y la nota necesaria para aprobar," << endl;
            cout << "                ideal para estudiantes que calculan sus notas en porcentajes." << endl;
            cout << VIOLETA << "------------------------------------------------------------------------------------------------------------------------" << RESET << endl;
            cout << AZUL_VIVO << "    Menú Principal:" << RESET << endl;
            cout << "  1. Calcular Notas:     Ingresa notas y porcentajes, la app calcula el promedio." << endl;
            cout << "  2. Historial:     Consulta o borra las notas guardadas." << endl;
            cout << "  3. Calcular promedio general:     Muestra el promedio de todas las materias." << endl;
            cout << "  4. Gráfico de rendimiento:     Visualiza un gráfico de barras de las notas." << endl;
            cout << "  5. Instrucciones:     Muestra esta información." << endl;
            cout << "  6. Salir:     Cierra la aplicación." << endl << endl;
            cout << AZUL_VIVO << "Submenú: Cálculo de Notas" << RESET << endl;
            cout << "  1. Ingresar Datos:     Introduce las notas y porcentajes." << endl;
            cout << "  2. Volver:     Regresa al Menú Principal." << endl << endl;
            cout << AZUL_VIVO << "    Submenú: Historial de Notas" << RESET << endl;
            cout << "  1. Ver Historial:     Consulta todas las notas guardadas." << endl;
            cout << "  2. Borrar Historial:     Elimina todas las notas." << endl;
            cout << "  3. Volver:     Regresa al Menú Principal." << endl << endl;
            cout << AZUL_VIVO << "    Información Adicional" << RESET << endl;
            cout << "  - El historial se guarda automáticamente después de cada cálculo." << endl;
            cout << "  - La app verifica que los porcentajes sumen 100 y que las notas sean válidas." << endl;
            cout << "  - Las notas aprobadas y reprobadas se resaltan con colores diferentes." << endl;
            cout << "  - Presiona 'Enter' para volver al menú en cualquier momento." << endl;
            cout << VIOLETA << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
            cout << NARANJA << " TE DESEO MUCHOS EXITOS EN TUS ESTUDIOS. ESTE PROGRAMA FUE CREADO POR JUAN CAMILO *_*" << RESET << endl;
            cout << "Presione Enter para continuar..." << endl;

            cin.ignore();
            break;
        }
        case '6': {
            if (manejarSalida())
                break;
            break;
        }
        default:
            cout << "Opción no válida, por favor seleccione una opción entre 1 y 6." << endl;
            break;
        }
    } while (opcion != '6');
    return 0;
}
