#include <iostream>
#include <string>
#include <regex>

void analizarExpresion(std::string expresion) {
    // Reglas UNEG: Clasificación de componentes según la prueba diagnóstica
    // NUMERO: Enteros o reales con "."
    // OPERANDO: No inicia con número, sin espacios (ej. VALOR, A, B)
    // OPERADOR: + - * /
    // PARENTESIS: ( )
    
    std::regex token_regex("([0-9]+(\\.[0-9]+)?)|([+\\-*/])|(\\()|(\\))|([a-zA-Z_][a-zA-Z0-9_]*)");
    auto tokens_begin = std::sregex_iterator(expresion.begin(), expresion.end(), token_regex);
    auto tokens_end = std::sregex_iterator();

    int parentesis = 0;
    std::cout << "\nSalida:\n";

    for (std::sregex_iterator i = tokens_begin; i != tokens_end; ++i) {
        std::smatch match = *i;
        std::string s = match.str();

        if (std::regex_match(s, std::regex("[0-9]+(\\.[0-9]+)?"))) {
            std::cout << "NUMERO (" << s << ") ";
        } 
        else if (std::regex_match(s, std::regex("[+\\-*/]"))) {
            std::cout << "OPERADOR (" << s << ") ";
        } 
        else if (s == "(") {
            std::cout << "PAREN_IZQ ( ";
            parentesis++;
        } 
        else if (s == ")") {
            std::cout << "PAREN_DER ) ";
            parentesis--;
        } 
        else if (std::regex_match(s, std::regex("[a-zA-Z_][a-zA-Z0-9_]*"))) {
            std::cout << "OPERANDO (" << s << ") ";
        }
    }
    
    // Verificación de balance de paréntesis según el ejemplo del enunciado
    if (parentesis == 0) {
        std::cout << "PARENTESIS BALANCEADOS.";
    } else {
        std::cout << "ERROR: PARENTESIS NO BALANCEADOS (" << (parentesis > 0 ? "Falta cerrar" : "Sobran cierres") << ").";
    }
    std::cout << "\n" << std::endl;
}

int main() {
    std::string formula;
    
    std::cout << "--- Analizador ---" << std::endl;
    std::cout << "Escriba 'salir' para finalizar el programa." << std::endl;

    while (true) {
        std::cout << "Ingrese la expresion aritmetica: ";
        std::getline(std::cin, formula); // Permite leer la línea completa con espacios

        if (formula == "salir" || formula == "SALIR") {
            break;
        }

        if (formula.empty()) continue;

        analizarExpresion(formula);
    }

	std::cin.get();
    return 0;
}