#define CALCULATOR_INT
#include"calculator.hpp"
#include<iostream>
using namespace std;
int main()
{
	cout<<tiny::calculate<int>("2<<10-(~1*13/5)")<<endl;
	cout<<tiny::calculate<long long>("2**(50-1<<2)-(~1&13)")<<endl;
}
