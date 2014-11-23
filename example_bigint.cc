#define CALCULATOR_BIGINT
#include<iostream>
#include"calculator.hpp"
#include"bigint.h"
using namespace std;
int main()
{
	cout<<tiny::calculate<tiny::bigint>("111111111111111111111111111111111*99999999999999999999999999999999991234567/(123456789-3333333333333333333333)")<<endl;
	return 0;
}
