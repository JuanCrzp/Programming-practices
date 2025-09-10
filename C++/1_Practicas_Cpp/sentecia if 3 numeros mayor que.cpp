/* ESCRIBA UN PROGRAMA QUE LEA TRES NUMEROS Y 
DETERMINE CUAL DE ELLOS ES EL MAYOR */

#include <iostream>
		
		
using namespace std;

int main(){
    int n1, n2, n3;
    
    cout << "Ingrese tres numeros: ";
    cin >> n1 >> n2 >> n3;
    
    // Primero verificamos si los tres números son iguales.
    if(n1 == n2 && n1 == n3){
        cout << "Los tres numeros son iguales." << endl;
    }
    // Si no son iguales, comparamos para encontrar el mayor.
    else if(n1 >= n2 && n1 >= n3){
        cout << "El numero mayor es: " << n1 << endl;
    }
    else if(n2 >= n1 && n2 >= n3){
        cout << "El numero mayor es: " << n2 << endl;
    }
    else{
        cout << "El numero mayor es: " << n3 << endl;
    }
    
    return 0;
}

