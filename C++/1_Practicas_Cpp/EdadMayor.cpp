
#include <iostream>
using namespace std;
int pediri(const string& mensaje);
int main()
{
    int EdadMayor=0,i,cant,edad,b;
    cant=pediri("Ingrese el numero de personas:");
    for(i=0;i<cant;i++)
    {
       edad=pediri("Ingrese la edad: ");
       if(edad>EdadMayor)
       {
        EdadMayor=edad;
       }
        
    }
    cout<<"La edad mayor es:"<<EdadMayor;
    return 0;
}
int pediri(const string& mensaje)
{
    int a;
    cout<<mensaje;
    cin>>a;
    return a;
    
}
