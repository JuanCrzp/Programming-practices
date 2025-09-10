// Serie de FIBONACCI/

#include <iostream>
using namespace std;
int pediri(const string& mensaje);
int main()
 {
  int n, a=0,b=1,cont=2;
  long int fib;
  n=pediri("Ingrese la cantidad de secuencia:");
  if(n<=0)
  {
      cout<<"Ingrese un numero mayor a 0";
      
  }
  if(n==1)
  {
   cout<<"Fibonacci: "<<a;
  }
  else
  {
     cout<<"Fibonacci: "<<a<<" "<<b; 
  }
  while(cont<n)
  {
      fib=a+b;
      cout<<","<<fib;
      a=b;
      b=fib;
      cont++;
  }
 
  return 0;
}
int pediri(const string& mensaje)
{
    int a;
    cout<<mensaje;
    cin>>a;
    return a;
    
}

