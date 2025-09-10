/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;
int main()
{
   int num, acum;
   acum=1;
   
   cout <<"Ingrese el valor entero positivo:";
   cin >> num;
   
   do{
       cout <<acum <<endl;
       acum=acum + 1;
   }while (acum <=num);
   
    return 0;
}