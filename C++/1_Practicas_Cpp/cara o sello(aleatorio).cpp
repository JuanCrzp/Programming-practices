#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

using namespace std;
int main() {     
int e_usuario;
int m_computadora;
srand(time(NULL)); // Inicializar la semilla del generador de n�meros aleatorios 
m_computadora= rand() % 2; // Generar un n�mero aleatorio entre 0 y 1    
cout << "Por favor ingrese 1 si usted va elegir CARA, ingrese 0 si usted va elegir SELLO:"; 
cin>> e_usuario;
cout <<"\n"; 

if (e_usuario==0 ||e_usuario==1)
{
	if(e_usuario==m_computadora)
	{
	cout << "Felicitaciones, usted gana"; 
	}
	else
	{
	 cout << "Lo siento, usted pierde";
	}
}
else{
	
	cout << "USTED ELIGIO UNA OPCION INVALIDA"<<endl; 
    }
 // Mostrar el n�mero aleatorio generado   
return 0;}

