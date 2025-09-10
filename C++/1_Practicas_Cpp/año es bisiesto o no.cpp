#include <iostream>
#include <cmath>
using namespace std;

void pediri(int &A);
int calculari(int A);
void mostrari(int re);

int main() {
    int re, A;
    
    pediri(A);
    
    re = calculari(A);
    
    mostrari(re);
    return 0;
}

void pediri(int &A) {
    cout << "Ingrese un a�o que desee saber si es bisiesto o no: ";
    cin >> A;
}

int calculari(int A) {
    int re = 0; // Inicializamos re a 0
    if (A % 4 == 0) {
        if (A % 100 != 0 || A % 400 == 0) {
            re = A; // Es bisiesto
        }
    }
    return re;
}

void mostrari(int re) {
    if (re == 0) {
        cout << "El a�o es normal." << endl;
    } else {
        cout << "El a�o es bisiesto." << endl;
    }
}

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
