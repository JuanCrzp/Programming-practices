#include<iostream>

using namespace std;
//en un estacionamiento cobran $2000 determine cuanto debe pagar un cliente por el estacionamiento se su vehiculo,conociendo el tiempo de estacionamiento en horas y minutos

int main(){
	double valorhora,horas,minutos,total;
	
	cout<<"ingrese el tiempo en horas: "<<endl;
	cin>>horas;
		cout<<"ingrese el tiempo en minutos: "<<endl;
	cin>>minutos;
	
	if(minutos > 0){
		horas++; //horas = horas +1;
	}
	total = horas * 2000;
	
	cout<<"el total a pagar es: "<<endl<<total;
}
