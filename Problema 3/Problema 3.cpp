#include <iostream>

void verificarCollatz(long long p, long long q) {
    
    if (q < 100 * p) {
        std::cout << "Error: El limite superior 'q' (" << q 
                  << ") debe ser al menos 100 veces el limite 'p' (" << p << ")." << std::endl;
        return;
    }

    for (long long n = p; n <= q; n++) {
        long long actual = n;
        std::cout << "n=" << n << ": " << actual;
        while (actual != 1) {
            if (actual % 2 == 0) actual /= 2;
            else actual = 3 * actual + 1;
            std::cout << " -> " << actual;
        }
        std::cout << "\n\n";
        sleep(1);
    }
    std::cout << "Demostrado..." << std::endl;
}

int main() {
    long long p, q;
    std::cout << "Ingrese p (inicio): "; std::cin >> p;
    std::cout << "Ingrese q (fin): "; std::cin >> q;
    
    verificarCollatz(p, q);
    
    std::cin.get();
    return 0;
}