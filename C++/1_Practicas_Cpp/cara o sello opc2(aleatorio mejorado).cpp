#include <iostream>
#include <ctime>
#include <cstdlib>"

using namespace std;

int main(int ) {
	
	cout<<"\tMENU"<<endl;
cout<<"1. PIEDRA\n";
cout<<"2. PAPEL\n";
cout<<"3. TIJERA\n";
cout<<"4. Salir";
cout<<endl;

cout<<"Ingrese una opcion del menu: ";
cin>>opc;
 	switch(opc)

	
	string e_usuario,e_aux;
	int e_computadora;
	
	
	srand(time(NULL));
	
	e_computadora=rand()%2;
	cout<<"Escriba su eleccion PIEDRA, PAPEL  o TIJERA:";
	cin>>e_usuario;
	
	if(e_computadora==1)
	{
	  e_aux=piedra;
	}
    if(e_computadora==0)
	{
	  e_aux=papel;
	}
		if(e_computadora==1)
	{
	  e_aux=tijera;
	}
	

	
	if (e_usuario==PIEDRA|| e_usuario==PAPEL ||e_usuario==TIJERA )
   { 
     if(e_usuario==e_aux)
     {
      cout<<"Usted gano ya que el resultado fue "<<e_aux;

	 }
	else
	 {
     cout<<"Usted perdio ya que el resultado fue "<<e_aux;

	 }
   }
	else
	{
	    cout<<"\n";
		cout<<e_usuario<<" NO ES UNA OPCION VALIDA";
	
	}
	
	return 0;
}


