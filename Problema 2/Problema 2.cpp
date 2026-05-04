#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>

// Genera una fila siguiendo la regla de sumar espacios (ej: r1bk3r)
std::string generarFilaAleatoria() {
    std::string piezas = "rnbqkpRNBQKP";
    std::string fila_fen = "";
    int espacios_consecutivos = 0;
    int c = 0;

    while (c < 8) {
        if (rand() % 2 == 0) { // Decidir si colocar pieza o espacio
            if (espacios_consecutivos > 0) {
                fila_fen += std::to_string(espacios_consecutivos);
                espacios_consecutivos = 0;
            }
            fila_fen += piezas[rand() % piezas.length()];
            c++;
        } else {
            espacios_consecutivos++;
            c++;
        }
    }
    if (espacios_consecutivos > 0) {
        fila_fen += std::to_string(espacios_consecutivos);
    }
    return fila_fen;
}

std::string generarTableroCompleto() {
    std::string tablero = "";
    for (int i = 0; i < 8; i++) {
        tablero += generarFilaAleatoria();
        if (i < 7) tablero += "\n";
    }
    // Añadimos campos obligatorios de FEN: turno, enroque, peon al paso, reloj, nro jugada
    return tablero + " ";
}

void visualizarTablero(std::string fen) {
    size_t pos_espacio = fen.find(' ');
    std::string tablero = fen.substr(0, pos_espacio);
    
    std::cout << "\nVisualizacion (8 Strings con separacion):\n" << std::endl;
    std::string fila_actual = "";
    
    for (char c : tablero) {
        if (c == '/') {
            std::cout << fila_actual << "\n"; // Espacio de separacion entre filas
            fila_actual = "";
        } else if (isdigit(c)) {
            int num_espacios = c - '0';
            for (int i = 0; i < num_espacios; i++) fila_actual += ". "; // Representamos vacio con punto
        } else {
            fila_actual += c;
            fila_actual += " ";
        }
    }
    std::cout << fila_actual << "\n" << std::endl; // Imprimir ultima fila
}

bool validarFEN(std::string fen) {
    // Regex estricto para FEN segun Wikipedia/Wikipedia 2025
    std::regex fen_regex("^([rnbqkpRNBQKP1-8]{1,8}/){7}[rnbqkpRNBQKP1-8]{1,8}\\s[bw]\\s(-|[kqKQ]{1,4})\\s(-|[a-h][36])\\s\\d+\\s\\d+$");
    return std::regex_match(fen, fen_regex);
}

int main() {
    srand(time(0)); 
    
    std::string miFen = generarTableroCompleto();
    std::cout << "FEN Generado : \n" << miFen << "\n" << std::endl;
    
    visualizarTablero(miFen);
    
	std::cin.get();
    return 0;
}