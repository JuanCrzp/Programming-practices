
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
int menu();
string conversor(int opc);
string ganador(int opc_u, int opc_c);
int main()

 {  int opc_u, opc_c, opc1;
    string conv,conv1,gan;
 
    srand(time(NULL));
    do{
    opc_c=rand()%3+1;
    opc_u=menu();
    
 
    switch (opc_u)
    { case 1:
             conv=conversor(opc_u);
             conv1=conversor(opc_c);
             cout<<"El usuario eligio: "<<conv<<endl;
             cout<<"La computadora eligio: "<<conv1;
             cout<<endl;
             gan=ganador(opc_u,opc_c);
             cout<<gan;
             cout<<endl;
             break;
      case 2: 
             conv=conversor(opc_u);
             conv1=conversor(opc_c);
             cout<<"El usuario eligio: "<<conv<<endl;
             cout<<"La computadora eligio: "<<conv1;
             cout<<endl;
             gan=ganador(opc_u,opc_c);
              cout<<gan;
              cout<<endl;
             break;
      case 3:conv=conversor(opc_u);
             conv1=conversor(opc_c);
             cout<<"El usuario eligio: "<<conv<<endl;
             cout<<"La computadora eligio: "<<conv1;
             cout<<endl;
             gan=ganador(opc_u,opc_c);
             cout<<gan;
             cout<<endl;
             break;
      default:
              break;
    }

    cout<<endl;
    do{
    cout<<"Desea jugar otra vez ingrese 1 para continuar y 0 para salir:";
    cin>>opc1;
    }while(opc1>1||opc1<0);
    cout<<endl;
    if(opc1==0)
    {
      cout<<"¡Gracias por jugar, Hasta la proxima!";  
      break;
    }
    
    }while(opc1==1);
    return 0;
 }
int menu()
{
  int opc;
  do{
  cout<<endl;
  cout<<"\t MENU"<<endl;
  cout<<"1. Piedra"<<endl;
  cout<<"2. Papel"<<endl;
  cout<<"3. Tijera"<<endl;
  cout<<"Ingrese la opcion que desea:";
  cin>>opc;
  if(opc>4 || opc<=0)
  {
    cout<<"¡Por favor, Ingrese una opcion valida!"<<endl;
    cout<<endl;
  }
  }while(opc<1||opc>3);
  cout<<endl;
  return opc;
}
string conversor(int opc)
{
   switch (opc) 
   {
     case 1: return "Piedra";
     case 2: return "Papel";
     case 3: return "Tijera";
     default: return "Opcion invalida";
       
   }
    
}
string ganador(int opc_u, int opc_c)
{
    if(opc_u==opc_c)
    {
        return "ES UN EMPATE";
    }
    
    else{
        if ((opc_u==1 && opc_c==3)||(opc_u==2 && opc_c==1)||(opc_u==3 && opc_c==2))
          {
             return "USTED GANA"; 
          }
        else{
             return "LA COMPUTADORA GANA";
            }
        
        }
    
}
