//ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ ФУНКЦИЙ
//реализовать четыре обязательных метода численного интегрирования функций – левосторонних и правосторонних прямоугольников, трапеций и Симпсона и, по желанию, один из двух дополнительных – Чебышева или Гаусса.
//Формат входного файла: 
//m – формула интегрирования(в порядке их перечисления), при m = 5 используется дополнительный метод;
//g  – любой символ или строка, задающие тип сетки: равномерная, неравномерная, динамическая(при m != 5);
//n  – количество интервалов интегрирования(если используется формула Симпсона, то кратно двум);
//a b – границы отрезка(если сетка не является неравномерной или m = 5);
//x0…xn – узлы сетки(если она неравномерная);
//s – любой символ или строка, определяющие способ задания функции, если сетка не динамическая и m != 5 (табличная, аналитическая);
//y0…yn – значения функции в узлах сетки(если она задана таблично);
//f(x) – аналитическое выражение для функции(если сетка динамическая или m = 5);
//ε – точность вычисления интеграла на динамической сетке.
//
//Формат выходного файла: 
//I – значение интеграла;
//k – количество итераций(для динамической сетки);
//ε*  – достигнутая точность(для динамической сетки);
//ti – абсциссы точек интегрирования(при m = 5);
//Ai – коэффициенты Ai для формулы Гаусса.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "PolStr.h"


void out2File(double result, int k, double eps) {
	std::ofstream out("output.txt");
	if(!out.is_open()) {
		return;
	}
	out << "I: " << result;
	if(k != 0) {
		out << std::endl << "k: " << k << std::endl << "eps*: " << eps;
	}
	out.close();
}
void LeftRectangleMethod(double& a, double& b, int& n, std::string& g, std::vector<double>& y, std::vector<double>& x, char*& str, double eps) {
	double sum = 0;
	int k = 0;
	double eps1 = 0;
	if(g == "r") {
		for(int i = 0; i < n; i++) {
			sum += y[i];
		}
		sum *= (b - a) / 2;
	}
	else if(g == "n") {
		for(int i = 0; i < n; i++) {
			sum += y[i] * (x[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1] - x[i]);
		}
	}
	else if(g == "d") {
		do {
			k++;
			double h = (b - a) / n;
			double sum1 = 0;
			for(int i = 0; i < n; i++) {
				sum1 += EvalPolStr(str, a + i * h) * h;
			}
			if(abs(sum1 - sum) < eps) {
				eps1 = abs(sum1 - sum);
				break;
			}
			sum = sum1;
			n *= 2;
		} while(true);
	}
	out2File(sum, k, eps1);
}
void RightRectangleMethod(double& a, double& b, int& n, std::string& g, std::vector<double>& y, std::vector<double>& x, char*& str, double eps) {
	double sum = 0;
	int k = 0;
	double eps1 = 0;
	if(g == "r") {
		for(int i = 1; i <= n; i++) {
			sum += y[i];
		}
		sum *= (b - a) / 2;
	}
	else if(g == "n") {
		for(int i = 0; i < n; i++) {
			sum += y[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1] * (x[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1] - x[i]);
		}
	}
	else if(g == "d") {
		do {
			k++;
			double h = (b - a) / n;
			double sum1 = 0;
			for(int i = 0; i < n; i++) {
				sum1 += EvalPolStr(str, a + (i + 1) * h) * h;
			}
			if(abs(sum1 - sum) < eps) {
				eps1 = abs(sum1 - sum);
				break;
			}
			sum = sum1;
			n *= 2;
		} while(true);
	}
	out2File(sum, k, eps1);
}
void TrapezoidMethod(double& a, double& b, int& n, std::string& g, std::vector<double>& y, std::vector<double>& x, char*& str, double eps) {
	double sum = 0;
	int k = 0;
	double eps1 = 0;
	if(g == "r") {
		for(int i = 1; i < n; i++) {
			sum += y[i];
		}
		sum = (sum + (y[0] + y[n]) / 2) * (b - a) / n;
	}
	else if(g == "n") {
		for(int i = 0; i < n; i++) {
			sum += (y[i] + y[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1]) * (x[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1] - x[i]) / 2;
		}
	}
	else if(g == "d") {
		do {
			k++;
			double h = (b - a) / n;
			double sum1 = 0;
			for(int i = 0; i < n; i++) {
				sum1 += (EvalPolStr(str, a + i * h) + EvalPolStr(str, a + (i + 1) * h)) * h / 2;
			}
			if(abs(sum1 - sum) < eps) {
				eps1 = abs(sum1 - sum);
				break;
			}
			sum = sum1;
			n *= 2;
		} while(true);
	}
	out2File(sum, k, eps1);
}
void SimpsonMethod(double& a, double& b, int& n, std::string& g, std::vector<double>& y, std::vector<double>& x, char*& str, double eps) {
	double sum = 0;
	int k = 0;
	double eps1 = 0;
	if(g == "r") {
		for(int i = 1; i < n; i++) {
			if(i % 2 == 0) {
				sum += 2 * y[i];
			}
			else {
				sum += 4 * y[i];
			}
		}
		sum = (sum + y[0] + y[n]) * (b - a) / (3 * n);
	}
	else if(g == "n") {
		for(int i = 0; i < n; i++) {
			if(i % 2 == 0) {
				sum += 2 * (y[i] + y[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1]);
			}
			else {
				sum += 4 * (y[i] + y[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1]);
			}
		}
		sum = sum * (x[static_cast<std::vector<double, std::allocator<double>>::size_type>(n)] - x[0]) / (3 * n);
	}
	else if(g == "d") {
		do {
			k++;
			double h = (b - a) / n;
			double sum1 = 0;
			for(int i = 0; i < n; i++) {
				sum1 += (EvalPolStr(str, a + i * h) + 4 * EvalPolStr(str, a + (i + 0.5) * h) + EvalPolStr(str, a + (i + 1) * h)) * h / 6;
			}
			if(abs(sum1 - sum) < eps) {
				eps1 = abs(sum1 - sum);
				break;
			}
			sum = sum1;
			n *= 2;
		} while(true);
	}
	out2File(sum, k, eps1);
}
void ChebyshevMethod(double& a, double& b, int& n, char*& str) {
	double sum = 0;
	double* ti = new double[n];

	//Как в интернете, но c погрешностью
	//for(int i = 0; i <= n; i++) {
	//	sum += EvalPolStr(str, (a + b) / 2 + (b - a) / 2 * cos((2 * i + 1) * acos(-1) / (2 * n + 2)));
	//}
	//sum *= (b - a) / (n+1);


	//Как в методичке, но работает с большой погрешностью
	std::vector<double> nodes;
	for(int i = 0; i <= n; ++i) {
		double xi_prime = (1 + std::pow(-1, i)) / (2.0 * (i + 1));
		double xi = (a + b) / 2.0 + (b - a) / 2.0 * xi_prime;
		nodes.push_back(xi);
	}
	for(int i = 0; i <= n; i++)
		sum += EvalPolStr(str, nodes[i]);
	sum *= (b - a) / n;


	std::ofstream out("output.txt");
	if(!out.is_open()) {
		return;
	}
	out << "I: " << sum << std::endl;
	out << "ti: ";
	//for(int i = 0; i < n; i++) {
	//	ti[i] = (a + b) / 2 + (b - a) / 2 * cos((2 * i + 1) * acos(-1) / (2 * n + 2));
	//	out << ti[i] << " ";
	//}
	for(int i = 0; i <= n; i++) {
		out << nodes[i] << " ";
	}
	out.close();
	delete[] ti;
}

int main() {
	std::ifstream in("input.txt");
	if(!in.is_open()) {
		return -1;
	}
	int m = 0, n = 0;
	double a = 0, b = 0, e = 0;
	std::string g, s;
	char* str = new char[256];
	in >> m >> g >> n;
	std::cout << "m = " << m << "\ng = " << g << "\nn = " << n << std::endl;
	if(m == 5 || g != "n") {
		in >> a >> b;
		std::cout << "a = " << a << " b = " << b << std::endl;
	}
	std::vector<double> x(n + 1), y(n + 1);
	if(g == "n") {
		for(int i = 0; i <= n; ++i) {
			in >> x[i];
			std::cout << "x[" << i << "] = " << x[i] << std::endl;
		}
	}
	in >> s;
	std::cout << "s = " << s << std::endl;
	if(g != "d" && m != 5) {
		if(s == "t") {
			for(int i = 0; i <= n; ++i) {
				in >> y[i];
				std::cout << "y[" << i << "] = " << y[i] << std::endl;
			}
		}
	}
	if(g == "d" || m == 5) {
		if(s == "a") {
			std::string f;
			in >> f;
			const char* temp = { f.c_str() };
			str = CreatePolStr(temp, 0);
			std::cout << "f(x) = " << f << std::endl;
		}
		if(s == "t"){
			return -1; //несоответствие условию задачи
		}
		if(m != 5) {
			in >> e;
			std::cout << "E = " << e << std::endl;
		}
	}
	in.close();

	std::ofstream out("output.txt");
	if(!out.is_open()) {
		return -1;
	}
	switch(m) {
	case 1:
		LeftRectangleMethod(a, b, n, g, y, x, str, e);
		break;
	case 2:
		RightRectangleMethod(a, b, n, g, y, x, str, e);
		break;
	case 3:
		TrapezoidMethod(a, b, n, g, y, x, str, e);
		break;
	case 4:
		SimpsonMethod(a, b, n, g, y, x, str, e);
		break;
	case 5:
		ChebyshevMethod(a, b, n, str);
		break;
	default:
		break;
	}

	return 0;
}