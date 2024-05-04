//В работе необходимо реализовать точный метод:
//Метод Гаусса;
//Дополнительно реализовать еще один итерационный метод – простой итерации
//При помощи данных методов необходимо реализовать решение следующих задач:
//1. Решение СЛАУ.
//2. Поиск определителя матрицы(только для метода Гаусса).
//3. Поиск обратной матрицы.
// 
//Формат входного файла :
//m – тип задачи(в том порядке, в котором они перечислены выше);
//n – порядок матрицы;
//a11…a1n[b1]
//a21…a2n[b2]
//………………………
//an1…ann[bn] – коэффициенты матрицы и вектор свободных коэффициентов(при решешении СЛАУ, т.е.при m = 1).

//Формат выходного файла зависит от метода и типа задачи:
//Если используется метод Гаусса, то в любом случае в выходной файл выводятся матрицы A(1), A(2),…, A(n).
//Если решалась система СЛАУ, то еще и вектора b(1), b(2), …, b(n).
//Если вычислялась обратная матрица – вектора e1(n), e2(n), …, en(n).
//Если вычислялась обратная матрица – матрицы U1, Z1, U2, Z2, …, Un, Zn.
//Для итерационных методов выводятся матрицы α и вектора β(для каждой решаемой СЛАУ).
//При решении СЛАУ в файл выводятся :
//x* – вектор решения;
//ε – вектор невязки;
//|| ε || – норма вектора невязки.
//При поиске определителя – его значение.При вычислении обратной матрицы – следующие величины :
//X – обратная матрица;
//ε – матрица невязки(AX – E);
//|| ε || – норма матрицы невязки.

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct Input {
	int m;
	int n;
	vector<vector<double>> matrix;
	vector<double> freeMembers;
};

static void gauss(Input input, ofstream *output) {
	vector<double> temp = input.freeMembers;
	//прямой ход
	for(int i = 0; i < input.n; i++) {
		for(int j = i + 1; j < input.n; j++) {
			double koef = input.matrix[j][i] / input.matrix[i][i];
			for(int k = i; k < input.n; k++) {
				input.matrix[j][k] -= koef * input.matrix[i][k];
			}
			input.freeMembers[j] -= koef * input.freeMembers[i];
		}
		(*output) << "A(" << i + 1 << "):" << endl;
		for(int j = 0; j < input.n; j++) {
			for(int k = 0; k < input.n; k++) {
				(*output) << input.matrix[j][k] << " ";
			}
			(*output) << endl;
		}
		(*output) << "b(" << i + 1 << "):" << endl;
		for(int j = 0; j < input.n; j++) {
			(*output) << input.freeMembers[j] << " ";
		}
		(*output) << endl;
		(*output) << endl;
	}
	//обратный ход
	for(int i = input.n - 1; i >= 0; i--) {
		for(int j = i - 1; j >= 0; j--) {
			double koef = input.matrix[j][i] / input.matrix[i][i];
			for(int k = i; k >= 0; k--) {
				input.matrix[j][k] -= koef * input.matrix[i][k];
			}
			input.freeMembers[j] -= koef * input.freeMembers[i];
		}
	}
	//вывод вектора решения
	(*output) << "Vector:" << endl;
	vector<double> Vector;
	for(int i = 0; i < input.n; i++) {
		Vector.push_back(input.freeMembers[i] / input.matrix[i][i]);
		(*output) << "x" << i + 1 << " = " << input.freeMembers[i] / input.matrix[i][i] << endl;
	}

	//вывод невязки
	vector<double> residualVector;
	for(int i = 0; i < input.n; i++) {
		double element = 0;
		for(int j = 0; j < input.n; j++) {
			element += input.matrix[i][j] * Vector[j];
		}
		residualVector.push_back(temp[i] - element);
	}
	(*output) << "E:" << endl;
	for(int i = 0; i < input.n; i++) {
		(*output) << residualVector[i] << " ";
	}
	(*output) << endl;

	//вывод нормы невязки
	double norm = 0;
	for(int i = 0; i < input.n; i++) {
		norm += pow(residualVector[i], 2);
	}
	norm = sqrt(norm);
	(*output) << "||E||: " << norm << endl;
}

static void findDeterminant(Input input, ofstream *output) {
	//прямой ход
	for(int i = 0; i < input.n; i++) {
		for(int j = i + 1; j < input.n; j++) {
			if(input.matrix[i][i] == 0) {
				int k = i + 1;
				while(k < input.n && input.matrix[k][i] == 0) {
					k++;
				}
				if(k == input.n) {
					(*output) << "No solution";
					return;
				}
				for(int l = 0; l < input.n; l++) {
					swap(input.matrix[i][l], input.matrix[k][l]);
				}
			}
			double koef = input.matrix[j][i] / input.matrix[i][i];
			for(int k = i; k < input.n; k++) {
				input.matrix[j][k] -= koef * input.matrix[i][k];
			}
		}
		(*output) << "A(" << i + 1 << "):" << endl;
		for(int j = 0; j < input.n; j++) {
			for(int k = 0; k < input.n; k++) {
				(*output) << input.matrix[j][k] << " ";
			}
			(*output) << endl;
		}
		(*output) << endl;
	}
	//вычисление определителя
	double determinant = 1;
	for(int i = 0; i < input.n; i++) {
		determinant *= input.matrix[i][i];
	}
	(*output) << "Determinant: " << determinant << endl;
}

static void findInverseMatrix(Input input, ofstream *output){
	vector<vector<double>> matrix = input.matrix;
	vector<vector<double>> inverseMatrix;
	vector<double> row;
	double element;
	for(int i = 0; i < input.n; i++) {
		row.clear();
		for(int j = 0; j < input.n; j++) {
			element = 0;
			if(i == j) {
				element = 1;
			}
			row.push_back(element);
		}
		inverseMatrix.push_back(row);
	}
	//прямой ход
	for(int i = 0; i < input.n; i++) {
		for(int j = i + 1; j < input.n; j++) {
			double koef = matrix[j][i] / matrix[i][i];
			for(int k = i; k < input.n; k++) {
				matrix[j][k] -= koef * matrix[i][k];
			}
			for(int k = 0; k < input.n; k++) {
				inverseMatrix[j][k] -= koef * inverseMatrix[i][k];
			}
		}
		(*output) << "A(" << i + 1 << "):" << endl;
		for(int j = 0; j < input.n; j++) {
			for(int k = 0; k < input.n; k++) {
				(*output) << matrix[j][k] << " ";
			}
			(*output) << endl;
		}
		(*output) << endl;
	}
	//обратный ход
	for(int i = input.n - 1; i >= 0; i--) {
		for(int j = i - 1; j >= 0; j--) {
			double koef = matrix[j][i] / matrix[i][i];
			for(int k = i; k >= 0; k--) {
				matrix[j][k] -= koef * matrix[i][k];
			}
			for(int k = 0; k < input.n; k++) {
				inverseMatrix[j][k] -= koef * inverseMatrix[i][k];
			}
		}
	}
	//приведение главной диагонали к 1
	for(int i = 0; i < input.n; i++) {
		double koef = 1 / matrix[i][i];
		for(int j = 0; j < input.n; j++) {
			inverseMatrix[i][j] *= koef;
		}
	}
	//вывод обратной матрицы
	(*output) << "Inverse matrix: " << endl;
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++) {
			(*output) << inverseMatrix[i][j] << " ";
		}
		(*output) << endl;
	}
	(*output) << endl;
	//вывод невязки
	(*output) << "E: " << endl;
	vector<vector<double>> E;
	for(int i = 0; i < input.n; i++) {
		row.clear();
		for(int j = 0; j < input.n; j++) {
			element = 0;
			if(i == j) {
				element = 1;
			}
			row.push_back(element);
		}
		E.push_back(row);
	}
	vector<vector<double>> resultMatrix;
	for(int i = 0; i < input.n; i++) {
		row.clear();
		for(int j = 0; j < input.n; j++) {
			element = 0;
			for(int k = 0; k < input.n; k++) {
				element += matrix[i][k] * inverseMatrix[k][j];
			}
			row.push_back(element);
		}
		resultMatrix.push_back(row);
	}
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++) {
			(*output) << resultMatrix[i][j] - E[i][j] << " ";
		}
		(*output) << endl;
	}
	(*output) << endl;
	//вывод нормы невязки
	double norm = 0;
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++) {
			norm += pow(resultMatrix[i][j] - E[i][j], 2);
		}
	}
	norm = sqrt(norm);
	(*output) << "||E||: " << norm << endl;
}


static void SLAUmethodSimpleIteration(Input input, ofstream* output) {
	vector<vector<double>> alpha;
	alpha.resize(input.n);
	for(int i = 0; i < input.n; i++) {
		alpha[i].resize(input.n);
	}
	vector<double> beta;
	beta.resize(input.n);
	vector<double> x;
	x.resize(input.n);
	vector<double> x0;
	x0.resize(input.n);
	vector<double> e;
	e.resize(input.n);
	double temp = 0;
	double _e_ = 0;

	double exitVal = 0;
	for(int i = 0; i < input.n; i++) {
		beta[i] = input.freeMembers[i] / input.matrix[i][i];
		for(int j = 0; j < input.n; j++)
			if(i != j)
				alpha[i][j] = input.matrix[i][j] / -input.matrix[i][i];
	}
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++)
			exitVal += alpha[i][j] * alpha[i][j];
	}
	exitVal = sqrt(exitVal);
	exitVal = (1 - exitVal) * 0.000001 / exitVal;
	//ВЫВОД
	(*output) << "\nAlpha & Beta:" << endl;
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++)
			(*output) << " " << alpha[i][j] << " ";
		(*output) << "\t" << beta[i] << endl;
	}
	(*output) << "\nExit Value:\t" << exitVal << endl;
	//итерационный процесс
	do {
		temp = 0;
		for(int i = 0; i < input.n; i++) {
			x0[i] = x[i];
			x[i] = 0;
			for(int j = 0; j < input.n; j++)
				x[i] += alpha[i][j] * x[j];
			x[i] += beta[i];
			temp += (x[i] - x0[i]) * (x[i] - x0[i]);
		}
	} while(sqrt(temp) >= exitVal);
	//ПОГРЕШНОСТЬ
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++)
			e[i] += input.matrix[i][j] * x[j];
		e[i] -= input.freeMembers[i];
		_e_ += e[i] * e[i];
	}
	_e_ = sqrt(_e_);
	//ВЫВОД
	(*output) << "\n---------------------------------------" << endl;
	(*output) << "\nX:" << endl;
	for(int i = 0; i < input.n; i++)
		(*output) << " " << x[i] << endl;
	(*output) << "\nE:" << endl;
	for(int i = 0; i < input.n; i++)
		(*output) << " " << e[i] << endl;
	(*output) << "\n||E||:\t" << _e_ << endl;
}


int main() {
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");
	if(!inputFile.is_open() || !outputFile.is_open())
		return -1;
	Input input = {};


	inputFile >> input.m;
	inputFile >> input.n;
	vector<double> row;
	double element;
	for(int i = 0; i < input.n; i++) {
		row.clear();
		for(int j = 0; j < input.n; j++) {
			element = 0;
			inputFile >> element;
			row.push_back(element);
		}
			element = 0;
			inputFile >> element;
			input.freeMembers.push_back(element);
		input.matrix.push_back(row);
	}
	inputFile.close();

	outputFile << "A(0):" << endl;
	for(int i = 0; i < input.n; i++) {
		for(int j = 0; j < input.n; j++) {
			outputFile << input.matrix[i][j] << " ";
		}
		outputFile << endl;
	}
	outputFile << endl;

	for(int i = 0; i < input.n; i++) {
		for(int j = 0; i < input.n; i++) {
			if(input.matrix[j][j] == 0) {
				int k = j + 1;
				while(k < input.n && input.matrix[k][j] == 0) {
					k++;
				}
				if(k == input.n) {
					outputFile << "No solution";
					outputFile.close();
					return -1;
				}
				for(int l = 0; l < input.n; l++) {
					swap(input.matrix[j][l], input.matrix[k][l]);
				}
				if(input.m == 1)
					swap(input.freeMembers[j], input.freeMembers[k]);
			}
		}
	}




	switch(input.m) {
	case 1:
		gauss(input, &outputFile);
		break;
	case 2:
		findDeterminant(input, &outputFile);
		break;
	case 3:
		findInverseMatrix(input, &outputFile);
		break;
	case 4:
		SLAUmethodSimpleIteration(input, &outputFile);
		break;
	default:
		break;
	}

	outputFile.close();
	return 0;
}