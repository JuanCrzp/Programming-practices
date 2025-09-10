#include <iostream>
#include <cmath>
using namespace std;

void pediri(int &A);
int calculari(int A);
void mostrari(int re);

int main()
 {
	int re, A;
	
	pediri(A);
	
	re = calculari (A);
	
	mostrari(re);
	return 0;
}
void pediri(int &A)
{
	cout<<"Ingrese un año que desee saber si es bisiesto o no: "<<endl ;
		cin>>A;
}

int calculari (int A)
{
	int re;
	if (A % 4 == 0){
		re = A;
		if (A % 100 !=0 || A % 400 == 0){
			re = A;
		}
	}
	else {
		re ==0;
	}
	return re;
}

void mostrari(int re)
{
	if (re == 0){
		cout <<"el ano es normal";
	}
	else {
		cout <<"el ano es bisiesto";
	}
}

