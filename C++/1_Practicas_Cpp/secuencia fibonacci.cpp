#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    int n,f1,f2,i;
   do
   {
         cout << "Introduce un numero:";
         cin >> n;
   }while(n<=1); 
  
    cout << "Los " << n << " los numeros son:" << endl;
   f1=1;
   f2=1;
   cout << f1 << " ";
   for(i=2;i<=n;i++)
   {
       cout << f2 << " ";
       f2 = f1 + f2;
       f1 = f2 - f1;
   }
   cout << endl << endl;
    system("pause");
}

