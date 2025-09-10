#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float AN;
	cout<<"ingrese un angulo en grados: ";
	cin>>AN;
	
	
	if (AN >0 && AN <90){
		cout<<"El angulo: "<<AN <<" es Agudo";
	}
	else if (AN == 90){
		cout<<"El angulo: "<<AN <<" es Recto";
	}
	else if (AN >90 && AN <180){
		cout<<"El angulo: "<<AN <<" es Obtuzo";
	}
	else if (AN == 180){
		cout<<"El angulo: "<<AN <<" es Llano";
	}
	else {
		cout<<"El valor no es valido";
	}


	return 0;
}

