#define CALCULATOR_FLOAT
#include"calculator.hpp"
#include<iostream>
using namespace std;
int main()
{
	cout<<tiny::calculate<float>("2.14*3.18/((123-3.8*1.9)+0.13)")<<endl;
	cout<<tiny::calculate<double>("2.14*3.18/((123-3.8*1.9)+0.13)")<<endl;
	cout<<tiny::calculate<long double>("2.14*3.18/((123-3.8*1.9)+0.13)")<<endl;
}
