#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// Genera una fila siguiendo la regla de sumar espacios 
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
    return tablero + " ";
}

void visualizarTablero(std::string fen) {
    size_t pos_espacio = fen.find(' ');
    std::string tablero = fen.substr(0, pos_espacio);
    
    std::cout << "\nVisualizacion :\n" << std::endl;
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


int main() {
    srand(time(0)); 
    
    std::string miFen = generarTableroCompleto();
    std::cout << "FEN Generado : \n" << miFen << "\n" << std::endl;
    
    visualizarTablero(miFen);
    
	std::cin.get();
    return 0;
}