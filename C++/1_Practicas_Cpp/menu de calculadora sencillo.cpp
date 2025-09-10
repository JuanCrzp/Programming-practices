#include <iostream>

using namespace std;

int main(){
	int numero1,numero2,resultado;
	int opc;
	
	cout << "   \t       MENU           "<<endl<<endl<<endl;

	cout << "1.suma  "<<endl;
	cout << "2.resta"<<endl;
	cout << "3.multiplicacion"<<endl;
	cout << "4.division"<<endl<<endl<<endl;
	
	cout << "Ingrese una opcion : ";
	cin >> opc;
	
  switch (opc){
  	
  	case 1: 
  			cout<<endl<<"suma"<<endl;
  			cout <<endl<< "ingrese el primer numero: ";
  			cin >> numero1;
  			cout << "ingrese el segundo numero: ";
  			cin >> numero2;
  			resultado = numero1 + numero2;
  			break;
  			
  	case 2:
  			cout<<endl<<"resta"<<endl;
  			cout <<endl<< "ingrese el primer numero: ";
  			cin >> numero1;
  			cout << "ingrese el segundo numero: ";
  			cin >> numero2;
  			resultado = numero1 - numero2;
  			break;
  	case 3:
  			cout<<endl<<"multiplicacion"<<endl;
  			cout <<endl<< "ingrese el primer numero: ";
  			cin >> numero1;
  			cout << "ingrese el segundo numero: ";
  			cin >> numero2;
  			resultado = numero1 * numero2;
  			break;
  	case 4:
  			cout<<endl<<"division"<<endl;
  			cout <<endl<< "ingrese el primer numero: ";
  			cin >> numero1;
  			cout << "ingrese el segundo numero: ";
  			cin >> numero2;
  			resultado = numero1 / numero2;
  			break;
  	
  	
}

cout <<endl<< "El resultado es : "<<resultado;


return 0;

}
