/* ESCRIBA UN PROGRAMA QUE LEA DOS NUMEROS Y 
DETERMINE CUAL DE ELLOS ES EL MAYOR */



#include <iostream>


using namespace std;

int main() {
	
	int a, b;
	
	cout << "ingrese el primer numero:  ";
	cin >> a;
	
	cout << "ingrese el segunso numero:  ";
	cin >> b;
	
	//  SENTENCIA IF SI (A ES MAYOR QUE B)  IMPRIME (ELSE IF) SI SON IGUALES O NO ES MAYOR QUE (B) IMPRIME QUE EL SEGUNDO ES MAYOR 
	
	if( a > b){
		cout <<"el PRIMER numero es MAYOR ";
	}
		else if ( a == b ){
			cout <<"Los numeros son IGUALES";
		}
	else {
		cout <<"el SEGUNDO numero es MAYOR ";
	}	
	
	
	return 0;
}
