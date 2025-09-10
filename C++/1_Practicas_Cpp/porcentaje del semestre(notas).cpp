#include <iostream>
#include <string>

using namespace std;

int main()
{
	double nota1 , nota2 , nota3 , porcentaje ;
	string materia;
	
		
		cout<<"\t \t \t Hola !! Bienvenid@...";	
		cout<<endl<<endl<<"Esta aplicacion esta creada para calcular las materias de cada semestre academico..";
		cout<<endl<<" a continuacion necesitamos  los siguientes datos para calcular tu semestre"<< endl;
		cout<<endl<<"Ingrese el nombre de la materia: "<<endl;
		getline (cin, materia);
	
		cout<<endl<<"Ingrese la nota 1 del 30% : "<<endl;
		cin>>nota1;
		cout<<endl<<"Ingrese la nota 2 del 30% : "<<endl;
		cin>>nota2;
		cout<<endl<<"Ingrese la nota 3 del 40% : "<<endl;
		cin>>nota3;
		
		porcentaje=(nota1*0.30)+(nota2*0.30)+(nota3*0.40);
		
		cout<<endl<<"La nota final de la materia:  "<< materia <<"\tes: " <<porcentaje<<endl;
		
		cout<<endl<<endl<<"Programa desarrollado por Juan Camilo, ";
		cout<<"presione ENTER para salir.... ";
		cin.ignore();
		cin.get();
		
		
		return 0;
		
		
}
