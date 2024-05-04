//ВЫЧИСЛЕНИЕ СОБСТВЕННЫХ ЧИСЕЛ И СОБСТВЕННЫХ ВЕКТОРОВ
//Формат входного файла:
//m – тип задачи(1 – поиск собственных чисел, 2 – поиск собственных векторов);
//n – порядок матрицы;
//a11…a1n
//a21…a2n
//……………
//an1…ann – коэффициенты матрицы

//Формат выходного файла:
//P – матрица Фробениуса;
//λi – i - е собственное число;
//| A - λiE | – проверка i - го собственного числа(при m = 1);
//xi – i - й собственный вектор(при m = 2);
//Axi - λixi – проверка i - го собственного вектора(при m = 2);
//ki – кратность i - го собственного числа / вектора;
//... И т.д. для всех i = 1, 2, …, m
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define EXP             const std::vector<std::vector<double>>&
#define CONST           (const unsigned _int64)
#define STEP            0.001
#define EPS             0.001
#define EPS_P           0.01
#define TASK_NUM        1
#define TASK_VECTOR     2

void PrintMatrix(const std::vector<std::vector<double>>& matrix) {
    for(const auto& row : matrix) {
        for(double val : row)
            std::cout << std::fixed << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintMatrix(std::ofstream& file, const std::vector<std::vector<double>>& matrix) {
    for(const auto& row : matrix) {
        for(double val : row)
            file << std::fixed << val << " ";
        file << "\n";
    }
    file << "\n";
}

void PrintVector(const std::vector<double>& vector, bool isVertical) {
    for(double val : vector) {
        std::cout << std::fixed << val << " ";
        if(isVertical)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintVector(std::ofstream& file, const std::vector<double>& vector, bool isVertical) {
    for(double val : vector) {
        file << val << " ";
        if(isVertical)
            file << std::fixed << "\n";
    }
    file << "\n";
    if(!isVertical)
        file << "\n";
}

void MultMatrix(std::vector<std::vector<double>>& left, const std::vector<std::vector<double>>& right) {
    size_t size = left.size();
    std::vector<std::vector<double>> result(size, std::vector<double>(size, 0));
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            for(int k = 0; k < size; ++k) {
                result[i][j] += left[i][k] * right[k][j];
            }
        }
    }
    left = result;
}

double F(const std::vector<double>& pol, double x, int size, int deriv) {
    double result = 0;
    double dLevels;
    for(int i = 0; i < size + 1 - deriv; ++i) {
        dLevels = 1;
        for(int j = 0; j < deriv; ++j)
            dLevels *= size - i - j;
        result += (size - i - deriv < 0 ? 0 : pow(x, size - i - deriv))
            * dLevels * ((i - 1 < 0) ? 1 : -pol[CONST i - 1]);
    }
    return result * pow(-1, size);
}

int main() {
    std::ifstream inputFile;
    inputFile.open("input.txt");
    if(!inputFile.is_open())
        return 1;

    int m = 0;
    int n = 0;
    inputFile >> m >> n;

    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> p(n, std::vector<double>(n));
    std::vector<std::vector<double>> unit(n, std::vector<double>(n, 0));
    std::vector<std::vector<double>> mM(n, std::vector<double>(n));
    std::vector<std::vector<double>> mP(n, std::vector<double>(n));
    std::vector<std::vector<double>> s(n, std::vector<double>(n));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            inputFile >> a[i][j];
            p[i][j] = a[i][j];
        }
        unit[i][i] = 1;
    }
    inputFile.close();
    std::cout.precision(3);
    std::cout << "A:" << std::endl;
    PrintMatrix(a);

    for(int k = n - 2; k >= 0; --k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == k) {
                    mM[i][j] = p[CONST k + 1][j];
                    if(j == k)
                        mP[i][j] = 1 / p[CONST k + 1][j];
                    else
                        mP[i][j] = -p[CONST k + 1][j] / p[CONST k + 1][k];
                }
                else
                    mP[i][j] = mM[i][j] = unit[i][j];
            }
        }
        if(k == n - 2)
            s = mP;
        else
            MultMatrix(s, mP);
        MultMatrix(mM, p);
        std::swap(mM, p);
        MultMatrix(p, mP);
    }

    std::ofstream outputFile;
    outputFile.open("output.txt");
    if(!outputFile.is_open())
        return 2;

    std::cout << "P:" << std::endl;
    PrintMatrix(p);
    outputFile << "P:" << std::endl;
    PrintMatrix(outputFile, p);

    std::vector<double> lambda(n, 0);
    std::vector<int> multiplicity(n, 0);
    int differences = 0;

    int counter = 0;
    std::cout << "All lambda's:" << std::endl;
    for(double iter = 0; counter < n; iter += STEP) {
        if(fabs(F(p[0], iter, n, 0)) < EPS) {
            lambda[differences++] = iter;
            counter++;
            std::cout << std::fixed << "\t" << iter << std::endl;
            for(int j = 1; j < n - counter + 1; j++) {
                if(fabs(F(p[0], iter, n, j)) < EPS_P) {
                    counter++;
                    multiplicity[CONST differences - 1]++;
                    std::cout << std::fixed << "\t" << iter << std::endl;
                }
                else
                    break;
            }
        }
        if(fabs(F(p[0], -iter, n, 0)) < EPS && iter > STEP) {
            lambda[differences++] = -iter;
            counter++;
            std::cout << std::fixed << "\t" << -iter << std::endl;
            for(int j = 1; j < n - counter + 1; j++) {
                if(fabs(F(p[0], -iter, n, j)) < EPS_P) {
                    counter++;
                    multiplicity[CONST differences - 1]++;
                    std::cout << std::fixed << "\t" << -iter << std::endl;
                }
                else
                    break;
            }
        }
    }
    for(int i = 0; i < differences; i++)
        multiplicity[i]++;

    outputFile << "All lambda's:" << std::endl;
    PrintVector(outputFile, lambda, false);

    if(m == TASK_NUM) {
        double dmod;
        for(int i = 0; i < differences; i++) {
            dmod = 0;
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    dmod += pow(a[j][k] - unit[j][k] * lambda[i], 2);
                }
            }
            outputFile << "проверка " << i + 1 << "-го собственного числа: " << sqrt(dmod) << std::endl;
        }
        outputFile << std::endl;
    }

    if(m == TASK_VECTOR) {
        std::vector<std::vector<double>> x(differences, std::vector<double>(n, 0));
        for(int i = 0; i < differences; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    x[i][j] += s[j][k] * pow(lambda[i], n - k - 1);
                }
            }
            std::cout << std::fixed << "X(" << i + 1 << "):" << std::endl;
            PrintVector(x[i], true);
            outputFile << "X(" << i + 1 << "):" << std::endl;
            PrintVector(outputFile, x[i], true);
        }

        double dmod;
        for(int i = 0; i < differences; i++) {
            outputFile << std::fixed << "проверка " << i + 1 << "-го собственного вектора:" << std::endl;
            for(int j = 0; j < n; j++) {
                dmod = 0;
                for(int k = 0; k < n; k++) {
                    dmod += a[j][k] * x[i][k];
                }
                outputFile << "\t" << dmod - lambda[i] * x[i][j] << std::endl;
            }
            outputFile << std::endl;
        }
        outputFile << std::endl;
    }

    for(int i = 0; i < differences; i++)
        outputFile << "кратность " << i+1 << "-го собственного числа / вектора: " << multiplicity[i] << std::endl;
    outputFile << std::endl;

    outputFile.close();
    
    return 0;
}
