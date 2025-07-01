#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void mostrar_tablero(string M[][6], int nfilas, int ncolumnas);
int lanzar_dado();
void mostrarDado(int num);
void casilla_a_coordenadas(int casilla, int &fila, int &col);
bool juego_finalizado(int pos_jugador);
void jugador_avanza(string M[][6], int &pos_jugador, int dado, int nfilas, int ncolumnas, string simbolo);
int mostrar_menu();
void pedir_nombres(string &nombre1, string &nombre2);

int lanzar_dado() {
    cout << "=== Lanzar dado ===\n";
    cout << "Presiona ENTER para lanzar...";
    cin.ignore();
    int resultado = 1 + rand() % 6;
    cout << "Salio el numero: " << resultado << "\n";
    return resultado;
}

void mostrarDado(int num) {
    cout << "\n+-------+\n";
    switch (num) {
        case 1: cout << "|       |\n|   *   |\n|       |\n"; break;
        case 2: cout << "| *     |\n|       |\n|     * |\n"; break;
        case 3: cout << "| *     |\n|   *   |\n|     * |\n"; break;
        case 4: cout << "| *   * |\n|       |\n| *   * |\n"; break;
        case 5: cout << "| *   * |\n|   *   |\n| *   * |\n"; break;
        case 6: cout << "| *   * |\n| *   * |\n| *   * |\n"; break;
    }
    cout << "+-------+\n";
}

void casilla_a_coordenadas(int casilla, int &fila, int &col) {
    if (casilla >= 1 && casilla <= 6) {
        fila = 0;
        col = casilla - 1;
    } else if (casilla >= 7 && casilla <= 10) {
        fila = casilla - 6;
        col = 5;
    } else if (casilla >= 11 && casilla <= 15) {
        fila = 5;
        col = 16 - casilla;
    } else if (casilla >= 16 && casilla <= 20) {
        fila = 21 - casilla;
        col = 0;
    }
}

string valor_original(int casilla) {
    return (casilla < 10 ? " " : "") + to_string(casilla);
}

void jugador_avanza(string M[][6], int &pos_jugador, int dado, int nfilas, int ncolumnas, string simbolo) {
    int fila_ant, col_ant;
    casilla_a_coordenadas(pos_jugador, fila_ant, col_ant);
    M[fila_ant][col_ant] = valor_original(pos_jugador);

    pos_jugador += dado;
    if (pos_jugador > 20)
        pos_jugador = 20;

    int fila, col;
    casilla_a_coordenadas(pos_jugador, fila, col);
    M[fila][col] = " " + simbolo + " ";
}

void mostrar_tablero(string tablero[][6]) {
    for (int i = 0; i < 6; i++) {
        cout << "[ ";
        for (int j = 0; j < 6; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << "]\n";
    }
    cout << endl;
}

bool juego_finalizado(int pos_jugador) {
    return pos_jugador >= 20;
}

int mostrar_menu() {
    int opcion;
    cout << "\n=== MENU DE JUEGO ===\n";
    cout << "1. Nivel facil\n";
    cout << "2. Nivel intermedio\n";
    cout << "3. Nivel dificil\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore(); // limpiar buffer
    return opcion;
}

void pedir_nombres(string &nombre1, string &nombre2) {
    cout << "Ingrese el nombre del Jugador 1 (Policia): ";
    getline(cin, nombre1);
    cout << "Ingrese el nombre del Jugador 2 (Ladron): ";
    getline(cin, nombre2);
}



int main() {
    srand(time(NULL));

    cout << "=== Bienvenidos al juego de carreras Ladron y Policia ===\n\n";
    cout << "                                 ______ \n";   
    cout << "                     --          |     |      |  \n";
    cout << "         --             --     _______\n";
    cout << "              --              |                   |\n";
    cout << "                 --            _______ \n";
    cout << "        --               --      |  |       |   |\n";
    cout << "                    --           ---         ---\n";
    cout << "                  ______ \n";   
    cout << "          --      |     |      |  \n";
    cout << "    --          _______\n";
    cout << "--   --        |                   |\n";
    cout << "          --    _______ \n";
    cout << "  --   --        |  |       |   |\n";
    cout << " --        --     ---         ---\n";

    int opcion = mostrar_menu();

    if (opcion == 4) {
        cout << "Saliendo del juego...\n";
        return 0;
    }

    if (opcion < 1 || opcion > 4) {
        cout << "Opcion no válida. Fin del programa.\n";
        return 0;
    }

    // Ahora sí, pedir nombres después del menú
    string nombre1, nombre2;
    pedir_nombres(nombre1, nombre2);
    string inicial1 = nombre1.substr(0, 1);
    string inicial2 = nombre2.substr(0, 1);

    int pos_jugador1 = 1;
    int pos_jugador2 = 1;
    int turno = 1;

    string tablero[6][6] = {
        {"1 ", "2 ", "3 ", "4 ", "5 ", "6 "},
        {"20", "  ", "  ", "  ", "  ", "7 "},
        {"19", "  ", "  ", "  ", "  ", "8 "},
        {"18", "  ", "  ", "  ", "  ", "9 "},
        {"17", "  ", "  ", "  ", "  ", "10"},
        {"16", "15", "14", "13", "12", "11"}
    };

    int fila1, col1, fila2, col2;
    casilla_a_coordenadas(pos_jugador1, fila1, col1);
    tablero[fila1][col1] = " " + inicial1 + " ";
    casilla_a_coordenadas(pos_jugador2, fila2, col2);
    tablero[fila2][col2] = " " + inicial2 + " ";

    while (true) {
        int dado = lanzar_dado();
        mostrarDado(dado);

        if (turno == 1) {
            cout << "\nTurno de " << nombre1 << " (" << inicial1 << ")\n";
            jugador_avanza(tablero, pos_jugador1, dado, 6, 6, inicial1);
        } else {
            cout << "\nTurno de " << nombre2 << " (" << inicial2 << ")\n";
            jugador_avanza(tablero, pos_jugador2, dado, 6, 6, inicial2);
        }

        mostrar_tablero(tablero);

        if (juego_finalizado(pos_jugador1)) {
            cout << nombre1 << " ha ganado la carrera!\n";
            break;
        }
        if (juego_finalizado(pos_jugador2)) {
            cout << nombre2 << " ha ganado la carrera!\n";
            break;
        }

        turno = (turno == 1) ? 2 : 1;
    }

    return 0;
}
