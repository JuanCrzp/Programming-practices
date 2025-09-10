#include <iostream>
using namespace std;
int main() {    
int num;    
int suma = 0;   
 int contador = 0;    
double prom;   
 do { cout << "Ingresa un numero: ";        
      cin >> num;      
       if (num != 0) {  suma += num;            
                       contador++;        
                     }    
      } while (num != 0);    
if(contador!=0)    
{prom = static_cast<double>(suma)/contador;    
cout << "El promedio es: " << prom << endl;   
 }   
else{ 
cout << "Por favor ingrese un numero valido "<< endl;
    }     return 0;
           }
