#include <iostream>
using namespace std;
int main()
{
    int cantidad, acum;
    double precio_p, valortotal;
    acum = 0;
    valortotal = 0;
    cout << "ingrese la cantidad del producto" << endl;
    cin >> cantidad;
    while (acum < cantidad) 
    { cout << "ingrese el precio del producto" << endl;
    cin >> precio_p;
    valortotal = valortotal + precio_p;
    acum = acum + 1 ;
    }
 cout << "el valor total es:" << valortotal << endl;
    

    return 0;
}
