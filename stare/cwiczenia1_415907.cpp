#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;


//Zadanie nr 1
double mc_pi(int n) {
	srand(time(NULL));
	int losowa = 0;
	for (int i = 1; i <= n; i++) {
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		
		if (x * x + y * y <= 1) {
			losowa++;
		}
	}

	double pi = 4.0 * losowa / n;
	return pi;
}

void mc_pi_test()
{
	for (int i = 100; i <= 20000; i = i + 100)
	{
		double pi = mc_pi(i);

		cout << "Dla n = " << i << " pi = " << pi << "\n";
	}
}

//Zadanie nr 2
double mc_int(double a, double b, int n, double(*f)(double))
{
	if (b - a < 0) {
		cout << "b musi byæ wieksze ni¿ a";
		return 0;
	}
	double z = b - a;
	srand(time(0));
	double c = 0;
	for (int i = 0; i < n; i++)
	{
		double x = a + (double)rand() / RAND_MAX * z;
		c += f(x);
	}

	return z * c / n;
}

double funkcja_test(double x)
{
	return (x * x * x + 3 * x * x + 8);
}

void mc_int_test()
{
	double a = 1.0;
	double b = 4.0;
	double wynik = mc_int(a, b, 10000, funkcja_test);
	cout <<"\n\n\nCa³ka oznaczona funkcji x^3+3x^2+8  na przedziale od 1 do 4 to: " <<wynik<<"\n\n\n\n";
}

// Zadanie nr 4
string CalkNaBin(int n)
{
	string wynik = "";

	while (n > 0)
	{
		int k = n % 2;
		wynik = wynik + to_string(k);

		n = n / 2;
	}

	reverse(wynik.begin(), wynik.end()); 
	return wynik;
}

void CalkNaBinTest()
{
	for (int i = 5; i <= 137; i += 9)
	{
		string wynik = CalkNaBin(i);
		cout << "Liczba " << i << " w postaci binarnej to " << wynik<<"\n";
	}
}

int BinNaCalk(string bin)
{
	int wynik = 0;

	for (char cyfra : bin) {
		wynik = wynik * 2 + (cyfra - '0'); 
	}

	return wynik;
}

void BinNaCalkTest()
{
	string test1 = "10101110";
	string test2 = "00101101";
	string test3 = "0111101";

	cout << "\n\n\n\nLiczba binarna " << test1 << " to w systemie dziesiêtnym " << BinNaCalk(test1)<<"\n";
	cout << "Liczba binarna " << test2 << " to w systemie dziesiêtnym " << BinNaCalk(test2) << "\n";
	cout << "Liczba binarna " << test3 << " to w systemie dziesiêtnym " << BinNaCalk(test3) << "\n";
}



string DoubleNaBin(double x) {
	string wynik = "";


	if (x >= 0) {
		wynik = "0";
	}
	else {
		wynik = "1";
		x = -x;
	}

	int wykladnik = 0;
	double mantysa = x;

	if (x != 0) {
		wykladnik = log2(x); 
		mantysa = x / pow(2, wykladnik); 
		wykladnik += 1023; 
	}


	string bin_wykladnik = "";
	for (int i = 10; i >= 0; i--) {
		bin_wykladnik += (wykladnik & (1 << i)) ? "1" : "0";
	}


	string bin_mantysa = "";
	mantysa -= 1; 

	for (int i = 0; i < 52; i++) {
		mantysa *= 2;
		if (mantysa >= 1) {
			bin_mantysa += "1";
			mantysa -= 1;
		}
		else {
			bin_mantysa += "0";
		}
	}

	wynik += bin_wykladnik + bin_mantysa;

	return wynik;
}

void DoubleNaBinTest()
{

	double test1 = 1.432;
	double test2 = -4.525;
	double test3 = 4323.4325434542;
	cout << "\n\n\nLiczba zmiennoprzecinkowa " << test1 << " to w systemie binarnym " << DoubleNaBin(test1) << "\n";
	cout << "Liczba zmiennoprzecinkowa " << test2 << " to w systemie binarnym " << DoubleNaBin(test2) << "\n";
	cout << "Liczba zmiennoprzecinkowa " << test3 << " to w systemie binarnym " << DoubleNaBin(test3) << "\n";
}

double BinNaDouble(string bin) {

	int znak = (bin[0] == '1') ? -1 : 1;

	int wykladnik = 0;
	for (int i = 1; i <= 11; i++) {
		if (bin[i] == '1') {
			wykladnik += pow(2, 11 - i);
		}
	}
	wykladnik -= 1023; 

	double mantysa = 1.0; 
	double waga = 0.5; 
	for (int i = 12; i < 64; i++) {
		if (bin[i] == '1') {
			mantysa += waga;
		}
		waga /= 2.0;
	}

	double wynik = znak * mantysa * pow(2, wykladnik);
	return wynik;
}

void BinNaDoubleTest()
{
	string test1 = "0011111111110110111010010111100011010100111111011111001110110110";
	string test2 = "1100000000010010000110011001100110011001100110011001100110011010";
	string test3 = "010000001011000011100011011011101011101100101010111101011110001";

	cout << "\n\n\nLiczba binarna " << test1 <<" w postaci dziesietnej to " << BinNaDouble(test1) << "\n\n";
	cout << "Liczba binarna " << test2 << " w postaci dziesietnej to " << BinNaDouble(test2) << "\n\n";
	cout << "Liczba binarna " << test3 << " w postaci dziesietnej to " << BinNaDouble(test3) << "\n\n";
}

int popyt1(double losowa) {
	if (losowa <= 0.3) return 100;
	if (losowa > 0.3 && losowa <= 0.6) return 150;
	if (losowa > 0.6 && losowa <= 0.8) return 200;
	if (losowa > 0.8 && losowa <= 0.95) return 250;
	return 300;
}

void Symulacja() {
	double najlepszyZysk = -100; 
	int najlepszeI = 0; 

	for (int i = 100; i <= 300; i += 5) { 
		double sumaZysku = 0;

		for (int j = 1; j <= 100; j++) { 
			double losowa = (double)rand() / RAND_MAX;
			int popyt = popyt1(losowa);
			double zysk = 0;

			if (popyt <= i) { 
				zysk = 10 * popyt - (i - popyt) * 8;
			}
			else { 
				zysk = 10 * i;
			}

			sumaZysku += zysk;
		}

		double sredniZysk = sumaZysku / 100.0; 

		if (sredniZysk > najlepszyZysk) { 
			najlepszyZysk = sredniZysk;
			najlepszeI = i;
		}

		cout << "\nLiczba zamowionych kalendarzy: " << i << ", Sredni zysk: " << sredniZysk << "\n";
	}

	cout << "\nNajlepszy wynik: Zamowionych kalendarzy: " << najlepszeI
		<< ", Najwyzszy sredni zysk: " << najlepszyZysk << "\n\n";
}

