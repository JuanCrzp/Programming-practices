#include <iostream>
#include <cmath>
using namespace std;


int main() {
	int f, y;
	cout<<"ingrese el valor de y "<< endl;
	cin>>y;
	
	
	if (y % 4 == 0){
		f = pow(y,3);
	}
	if (y%4==1){
		f = pow(y,2) + 5;
	}
	
	if (y%4==2){
		f = sqrt(y);
	}
				
			
	cout << "f(x) es igual a: "<<f;
	
	return 0;
}

