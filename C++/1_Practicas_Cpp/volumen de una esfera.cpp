#include<iostream>
#include<cmath>

using namespace std;

int main(){
	int radio , volumen;
	const double PI = 3.14159;
	
	cout<<"ingrese el radio: "<<endl;
	cin>>radio;
	
	volumen = (4 * PI * pow(radio,3) )/3;     //v=4*pi*radio elevado 3 y / 3
	
	cout<<"el volumen es: "<<endl<<volumen;
	
	
	return 0;
}
