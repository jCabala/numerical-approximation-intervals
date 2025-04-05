#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;


double funkcja_double1(double x)
{
	double wynik = pow(x, 4.0) - 4.0 * pow(x, 3.0) + 6.0 * x * x - 4.0 * x + 1.0;
	return wynik;
}

double funkcja_double2(double x)
{
	double wynik = pow(x - 1.0, 4.0);
	return wynik;
}

float funkcja_float1(float x)
{
	float wynik = pow(x, 4.0) - 4.0 * pow(x, 3.0) + 6.0 * x * x - 4.0 * x + 1.0;
	return wynik;
}

float funkcja_float2(float x)
{
	float wynik = pow(x - 1.0, 4.0);
	return wynik;
}

void test()
{
	for (float i = 0.99965; i <= 1.0002; i += 0.000005)
	{

			float wynik = funkcja_float2(i);
			std::cout << std::fixed << std::setprecision(6);
			cout << i << " ";
			std::cout << std::fixed << std::setprecision(25);
			cout << wynik << endl;
		/*cout << "Funkcja double2 dla i = " << i << " " << funkcja_double2(i) << endl;
		cout << "Funkcja float1 dla i = " << i << " " << funkcja_float1(i) << endl;
		cout << "Funkcja float2 dla i = " << i << " " << funkcja_float2(i) << endl;*/


	}
}