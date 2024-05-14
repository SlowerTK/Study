//Приблежение сплайнами
//Для выполнения практической работы необходимо реализовать в программе интерполяцию табличной функции линейными, кубическими и параболическими сплайнами.
//Формат входного файла: 
//k – порядок сплайна(1 – линейный, 2 – параболический, 3 – кубический);
//n – количество сплайнов;
//x0…xn – узлы сетки;
//y0…yn – значения функции в узлах сетки;
//i Ai – граничные условия(для k = 2);
//B0 Bn – граничные условия(для k = 3);
//m – количество интервалов в результирующей сетке(т.е.количество узлов – m + 1, что сделано для унификации с узлами исходной сетки);
//x0…xm – узлы результирующей сетки.
// t – любой символ или строка, сообщающая, известно или нет аналитическое выражение для функции f(x);
// f(x) – аналитическое выражение для функции (если оно известно).
//Формат выходного файла:
//a0 b0 c0 d0 – коэффициенты сплайнов (естественно, что коэффициенты c указываются только для k = 2 и k = 3, коэффициенты d – только для k = 3);
//a1 b1 c1 d1
//...
//an - 1 bn - 1 cn - 1 dn - 1 
//x0 S(x0) – значение сплайна в узлах результирующей сетки;
//x1 S(x1)
//...
//xm S(xm)
//eps - СКО (если аналитическое выражение для функции известно).

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "PolStr.h"

struct SplineData {
	int splineOrder;
	int numSplines;
	std::vector<double> xValues;
	std::vector<double> yValues;
	std::vector<double> boundaryConditions;
	int numIntervals;
	std::vector<double> resultGridNodes;
	std::string analyticalSimbol;
	std::string function;
};

SplineData readInputFile(const std::string& filename) {
	std::ifstream inputFile(filename);
	SplineData data;

	if(inputFile.is_open()) {
		inputFile >> data.splineOrder >> data.numSplines;
		data.xValues.resize(data.numSplines + 1);
		data.yValues.resize(data.numSplines + 1);

		for(int i = 0; i <= data.numSplines; ++i) {
			inputFile >> data.xValues[i];
		}

		for(int i = 0; i <= data.numSplines; ++i) {
			inputFile >> data.yValues[i];
		}

		if(data.splineOrder == 2 || data.splineOrder == 3) {
			data.boundaryConditions.resize(2);
			for(int i = 0; i < 2; ++i) {
				inputFile >> data.boundaryConditions[i];
			}
		}

		inputFile >> data.numIntervals;
		data.resultGridNodes.resize(data.numIntervals + 1);
		for(int i = 0; i <= data.numIntervals; ++i) {
			inputFile >> data.resultGridNodes[i];
		}

		inputFile >> data.analyticalSimbol;
		if(data.analyticalSimbol != "n") {
			inputFile >> data.function;
		}

		inputFile.close();
	}
	else {
		std::cerr << "Unable to open file " << filename << std::endl;
	}

	return data;
}

void linearSplineInterpolation(const SplineData& data, const std::string& outputFile) {
	std::ofstream outFile(outputFile);
	if(!outFile.is_open()) {
		std::cout << "Unable to open file.";
		return;
	}

	//выполнение интерполяции линейными сплайнами
	std::vector<double> a(data.numSplines), b(data.numSplines);
	for(int i = 0; i < data.numSplines; ++i) {
		a[i] = data.yValues[i];
		b[i] = (data.yValues[i + 1] - data.yValues[i]) / (data.xValues[i + 1] - data.xValues[i]);
	}

	//запись коэффициентов в выходной файл
	outFile << "a b" << std::endl;
	for(int i = 0; i < data.numSplines; ++i) {
		outFile << a[i] << " " << b[i] << std::endl;
	}

	//запись значений сплайна в узлах результирующей сетки
	outFile << "x S(x)" << std::endl;
	for(int i = 0; i < data.numIntervals; ++i) {
		outFile << data.resultGridNodes[i] << " " << (a[i] + b[i] * data.resultGridNodes[i]) << std::endl;
	}

	//если аналитическое выражение для функции известно, то посчитать СКО
	if(data.analyticalSimbol != "n") {
		char* polStr = new char[data.function.size() + 1];
		strcpy_s(polStr, data.function.size() + 1, data.function.c_str());
		char* Str = CreatePolStr(polStr, 0);
		double sum = 0.0;
		for(int i = 0; i < data.numIntervals; ++i) {
			double Sx = a[i] + b[i] * data.resultGridNodes[i];
			sum += (Sx - EvalPolStr(Str, data.resultGridNodes[i])) * (Sx - EvalPolStr(Str, data.resultGridNodes[i]));
		}
		outFile << "eps = " << sqrt(sum / data.numIntervals) << std::endl;
	}

	outFile.close();
}

void parabolaSplainInterpolation(const SplineData& data, const std::string& outputFilename) {
	std::ofstream outputFile(outputFilename);

	if(!outputFile.is_open()) {
		std::cerr << "Unable to open file " << outputFilename << std::endl;
		return;
	}

	//выполнение интерполяции параболическими сплайнами
	std::vector<double> a(data.numSplines), b(data.numSplines), c(data.numSplines);
	for(int i = 0; i < data.numSplines - 1; ++i) {
		a[i] = data.yValues[i];
		b[i] = (data.yValues[i + 1] - data.yValues[i]) / (data.xValues[i + 1] - data.xValues[i]);
		c[i] = (b[i + 1] - b[i]) / (data.xValues[i + 2] - data.xValues[i]);
	}

	//запись коэффициентов в выходной файл
	outputFile << "a b c" << std::endl;
	for(int i = 0; i < data.numSplines; ++i) {
		outputFile << a[i] << " " << b[i] << " " << c[i] << std::endl;
	}

	//запись значений сплайна в узлах результирующей сетки
	outputFile << "x S(x)" << std::endl;
	for(int i = 0; i < data.numIntervals; ++i) {
		outputFile << data.resultGridNodes[i] << " " << (a[i] + b[i] * data.resultGridNodes[i] + c[i] * data.resultGridNodes[i] * data.resultGridNodes[i]) << std::endl;
	}
	//если аналитическое выражение для функции известно, то посчитать СКО
	if(data.analyticalSimbol != "n") {
		char* polStr = new char[data.function.size() + 1];
		strcpy_s(polStr, data.function.size() + 1, data.function.c_str());
		char* Str = CreatePolStr(polStr, 0);
		double sum = 0.0;
		for(int i = 0; i < data.numIntervals; ++i) {
			double Sx = a[i] + b[i] * data.resultGridNodes[i] + c[i] * data.resultGridNodes[i] * data.resultGridNodes[i];
			sum += (Sx - EvalPolStr(Str, data.resultGridNodes[i])) * (Sx - EvalPolStr(Str, data.resultGridNodes[i]));
		}
		outputFile << "eps = " << sqrt(sum / data.numIntervals) << std::endl;
	}

	outputFile.close();
}

void cubicSplineInterpolation(const SplineData& data, const std::string& outputFilename) {
	std::ofstream outputFile(outputFilename);

	if(!outputFile.is_open()) {
		std::cerr << "Unable to open file" << outputFilename << std::endl;
		return;
	}

	// Выполнение интерполяции кубическими сплайнами
	std::vector<double> h(data.numIntervals);
	std::vector<double> alpha(data.numIntervals);
	std::vector<double> l(data.numIntervals + 1, 1.0);
	std::vector<double> mu(data.numIntervals + 1, 0.0);
	std::vector<double> z(data.numIntervals + 1, 0.0);
	std::vector<double> a(data.numIntervals), b(data.numIntervals), c(data.numIntervals), d(data.numIntervals);

	// Вычисление разностей между узлами
	for(int i = 0; i < data.numIntervals; ++i) {
		h[i] = data.xValues[i + 1] - data.xValues[i];
	}

	// Вычисление коэффициентов для метода прогонки
	for(int i = 1; i < data.numIntervals; ++i) {
		alpha[i] = (3.0 / h[i]) * (data.yValues[i + 1] - data.yValues[i]) - (3.0 / h[i - 1]) * (data.yValues[i] - data.yValues[i - 1]);
	}

	// Решение системы линейных уравнений для нахождения вторых производных
	for(int i = 1; i < data.numIntervals; ++i) {
		l[i] = 2.0 * (data.xValues[i + 1] - data.xValues[i - 1]) - h[i - 1] * mu[i - 1];
		mu[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}

	// Обратный ход метода прогонки
	for(int j = data.numIntervals-2; j > 0; --j) {
		c[j] = z[j] - mu[j] * c[j + 1];
		b[j] = (data.yValues[j + 1] - data.yValues[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
		d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
		a[j] = data.yValues[j];
	}


	// Запись коэффициентов в выходной файл
	outputFile << "a b c d" << std::endl;
	for(int i = 0; i < data.numIntervals; ++i) {
		outputFile << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << std::endl;
	}

	// Запись значений сплайна в узлах результирующей сетки
	outputFile << "x S(x)" << std::endl;
	for(int i = 0; i < data.numIntervals; ++i) {
		double t = 0.1;
		double x = data.xValues[i] + t * h[i];
		double Sx = a[i] + b[i] * t + c[i] * t * t + d[i] * t * t * t;
		outputFile << x << " " << Sx << std::endl;
	}
	//если аналитическое выражение для функции известно, то посчитать СКО
	if(data.analyticalSimbol != "n") {
		char* polStr = new char[data.function.size() + 1];
		strcpy_s(polStr, data.function.size() + 1, data.function.c_str());
		char* Str = CreatePolStr(polStr, 0);
		double sum = 0.0;
		for(int i = 0; i < data.numIntervals; ++i) {
			double t = 0.1;
			double x = data.xValues[i] + t * h[i];
			double Sx = a[i] + b[i] * t + c[i] * t * t + d[i] * t * t * t;
			sum += (Sx - EvalPolStr(Str, x)) * (Sx - EvalPolStr(Str, x));
		}
		outputFile << "eps = " << sqrt(sum / data.numIntervals) << std::endl;
	}

	outputFile.close();
}


int main() {
	std::string filename = "input.txt";
	SplineData data = readInputFile(filename);
	std::string outputFile = "output.txt";

	switch(data.splineOrder) {
	case 1:
		linearSplineInterpolation(data, outputFile);
		break;
	case 2:
		parabolaSplainInterpolation(data, outputFile);
		break;
	case 3:
		cubicSplineInterpolation(data, outputFile);
		break;
	default:
		break;
	}


	return 0;
}
