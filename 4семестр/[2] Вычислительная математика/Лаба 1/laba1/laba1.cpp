//Формат входного файла :
//n – номер метода(в порядке их перечисления в
//	п. 2.1.1, т.е. 1 – дихотомии, 2 – хорд и т.д.);
//f(x) – исследуемая функция в аналитическом виде;
//a b – границы отрезка;
//eps – требуемая точность решения

//Формат выходного файла :
//x* – решение уравнения;
//f(x*) – значение функции в найденной точке x*;
//eps* – погрешность полученного решения.

//Решение должно быть найдено с абсолютной погрешностью по аргументу eps и / или абсолютной погрешностью по значению функции δ, т.е
//| ξ – x*| < ε и / или | f(x*) | < δ
//где ξ – точное значение корня уравнения
//а x* - приблеженное.	
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "PolStr.h"
#define LEN 100
using namespace std;
#define EPS(x) EvalPolStr(i.str, x)
#define EPS_1(x) EvalPolStr(i.str, x, 1)
#define EPS_2(x) EvalPolStr(i.str, x, 2)

struct Input {
	int n;
	double a;
	double b;
	char* str;
	double eps;
};

struct Output {
	double x;
	double f;
	double eps;
};

void Dihotomii(Input i, Output* o) {
	while(abs(i.b - i.a) > i.eps) {
		o->x = (i.a + i.b) / 2;
		if(EPS(i.a) * EPS(o->x) > 0) {
			i.a = o->x;
		}
		else {
			i.b = o->x;
		}
	}
	o->f = EPS(o->x);
	o->eps = i.b - i.a;
}

void Chord(Input i, Output* o) {
	int n = 0;
	do {
		o->x = i.a - ((EPS(i.a) * (i.b - i.a)) / (EPS(i.b) - EPS(i.a)));
		if(EPS(i.a) * EPS(o->x) > 0) {
			i.a = o->x;
		}
		else {
			i.b = o->x;
		}
		n++;
	} while(abs(EPS(o->x)) > i.eps && abs(i.b - i.a) > i.eps);
	o->f = EPS(o->x);
	o->eps = abs(o->x - i.a);
}

void Newton(Input i, Output* o) {
	double x = (i.a + i.b) / 2;
	double x1 = x - EPS(x) / EPS_1(x);
	while(abs(x1 - x) > i.eps) {
		x = x1;
		x1 = x - EPS(x) / EPS_1(x);
	}
	o->x = x1;
	o->f = EPS(o->x);
	o->eps = abs(x1 - x);
}

void Combined(Input i, Output* o) {
	double x = (i.a + i.b) / 2;
	double x1 = x - EPS(x) / EPS_1(x);
	while(abs(x1 - x) > i.eps) {
		x = x1;
		x1 = x - EPS(x) / EPS_1(x);
	}
	o->x = x1;
	o->f = EPS(o->x);
	o->eps = abs(x1 - x);
}

double maxim(Input i) {
	double maxi = i.a;
	for(double j = i.a; j <= i.b; j += i.eps) {
		if(abs(EPS_1(j)) > abs(EPS_1(maxi))) {
			maxi = j;
		}
	}
	return EPS_1(maxi);
}

void Iter(Input i, Output* o) {
	double x0 = i.a;
	double x = 0;
	double iter = 0;
	double niz = maxim(i);
	if(abs(x - EPS(x) / niz )> 1)
		return;
	while(abs(x - x0) > i.eps) {
		x0 = x;
		iter++;
		x = x - EPS(x) / niz;
	}
	o->x = x;
	o->f = EPS(o->x);
	o->eps = abs(x - x0);
}

void GoldenRatio(Input i, Output* o) {
	double k2 = (sqrt(5) - 1) / 2;
	double k1 = 1 - k2;
	double x1 = i.a + k1 * (i.b - i.a);
	double x2 = i.a + k2 * (i.b - i.a);
	double F1 = EPS(x1);
	double F2 = EPS(x2);
	while((i.b - i.a) >= i.eps) {
		if(F1 < F2) {
			i.b = x2;
			x2 = x1;
			F2 = F1;
			x1 = i.a + k1 * (i.b - i.a);
			F1 = EPS(x1);
		}
		else {
			i.a = x1;
			x1 = x2;
			F1 = F2;
			x2 = i.a + k2 * (i.b - i.a);
			F2 = EPS(x2);
		}
	}
	o->x = (i.a + i.b)/2;
	o->f = EPS(o->x);
	o->eps = i.b - i.a;
}

int main() {
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	if(!infile.is_open() || !outfile.is_open())
		return -1;
	Input input = {};
	Output output = {};

	infile >> input.n;
	char* expr = new char[LEN] {};
	while(expr[0] == '\0') {
		infile.getline(expr, LEN, '\n');
	}
	infile >> input.a >> input.b >> input.eps;
	infile.close();

	input.str = CreatePolStr(expr, 0);
	delete[] expr;

	//double eps = input.eps;
	//int i = 0;
	//while(eps < 1) {
	//	eps = eps * 10;
	//	i++;
	//}
	//std::cout.precision(i);

	switch(input.n) {
	case 1:
		Dihotomii(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 2:
		Chord(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 3:
		Newton(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 4:
		Combined(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 5:
		Iter(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 6:
		GoldenRatio(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "x = " << output.x << "\tf(x) = " << output.f << "\teps = " << output.eps;
		break;
	case 0:
		Dihotomii(input, &output);
		outfile << "x = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "Dihot:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		output = {};
		Chord(input, &output);
		outfile << "\nx = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "\nChord:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		output = {};
		Newton(input, &output);
		outfile << "\nx = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "\nNewton:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		output = {};
		Combined(input, &output);
		outfile << "\nx = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "\nCombin:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		output = {};
		Iter(input, &output);
		outfile << "\nx = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "\nIter:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		output = {};
		GoldenRatio(input, &output);
		outfile << "\nx = " << output.x << "\nf(x) = " << output.f << "\neps = " << output.eps;
		std::cout << std::fixed << "\nGRatio:\tx = " << output.x << "\t\tf(x) = " << output.f << "\t\teps = " << output.eps;
		break;
	default:
		outfile << "введите цифру от 0 до 6";
		break;
	}
	outfile.close();
	delete[] input.str;
	return 0;
}