.
/*    Se compra un artículo en tres establecimientos con descuentos e impuestos
diferentes.El primer establecimiento tiene un impuesto de 10 % y un descuento
del 5 %, el segundo establecimiento tiene un impuesto de 12 % y un descuento de
5 % y el tercer establecimiento un impuesto de 15 % y un descuento de 7 % .Solicitar
el valor de los artículos por teclado.Entregar el valor total de la compra
discriminando el valor del impuesto y del descuento independientemente por
cada artículo.    */

#include<iostream>

using namespace std;

int main()
{
	float tienda1, tienda2, tienda3, descuento1, descuento2, descuento3, impuesto1, impuesto2, impuesto3, total1, total2, total3;

	cout << "ingrese precio primer tienda :" << endl;
	cin >> tienda1;
	cout << "ingrese precio segunda tienda :" << endl;
	cin >> tienda2;
	cout << "ingrese precio tercera tienda :" << endl;
	cin >> tienda3;


	descuento1 = tienda1 * 0.05;
	descuento2 = tienda2 * 0.05;
	descuento3 = tienda3 * 0.07;
	
	impuesto1 = tienda1 * 0.10;
	impuesto2 = tienda2 * 0.12;
	impuesto3 = tienda3 * 0.15;
	
	total1 = tienda1 - descuento1 + impuesto1;
	total2 = (tienda2 - descuento2) + impuesto2;
	total3 = tienda3 - descuento3 + impuesto3;
	
	cout << "El total de la compra tienda 1 es  "<<total1<<endl;
	cout << "El total de la compra tienda 2 es  "<<total2<<endl;
	cout << "El total de la compra tienda 3 es  "<<total3<<endl<<endl;
	
	cout <<"El descuento de tienda 1 es: "<<descuento1<<endl;
	cout <<"El descuento de tienda 2 es: "<<descuento2<<endl;
	cout <<"El descuento de tienda 3 es: "<<descuento3<<endl<<endl;
	
	cout <<"En tienda 1 el precio mas el impuesto es : "<<impuesto1<<endl;
	cout <<"En tienda 2 el precio mas el impuesto es : "<<impuesto2<<endl;
	cout <<"En tienda 3 el precio mas el impuesto es : "<<impuesto3<<endl;
	
	
	cin.ignore();
	 cin.get();
	return 0;

}
