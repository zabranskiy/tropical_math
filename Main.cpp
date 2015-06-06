#include "Semifield.h"
#include <iostream>

/*
  Дмитрий Забранский, 2015 г.
*/

using namespace std;

Semifield sf; // полуполе, с которым работаем, задаётся по умолчанию

int main(int argc, const char* argv[]) {
	// простой пример использования тропических чисел
	TropicDouble n1 = 10.5;
	TropicDouble n2(5.5);
	double res = (n1 * n2).toDouble();
	cout.precision(4);
	cout << fixed << res << endl;

	// Поиск оценочного вектора разных матриц
	TropicMatrix tM3(4, 4, "1 2 0.5 0.5 0.5 1 2 0.5 2 0.5 1 0.5 2 2 2 1");
	tM3.generalSolution();

	TropicMatrix ex1(4, 4, "1 5 6 7 0.2 1 4 6 0 0.25 1 4 0 0 0.25 1");
	ex1.insert(8, (double)1 / 6);
	ex1.insert(12, (double)1 / 7);
	ex1.insert(13, (double)1 / 6);
	ex1.generalSolution();

	TropicMatrix ex2(4, 4, "1 4 6 7 0.25 1 3 4 0 0 1 2 0 0.25 0.5 1");
	ex2.insert(8, (double)1 / 6);
	ex2.insert(9, (double)1 / 3);
	ex2.insert(12, (double)1 / 7);
	ex2.generalSolution();

	TropicMatrix ex3(7, 7,
		"1 4 9 6 6 5 5 0.25 1 7 5 5 3 4 0.11 0.14 1 0.2 0.2 0.14 0.2 0.17 0.2 5 1 1 0.33 0.33 0.17 0.2 5 1 1 0.33 0.33 0.2 0.33 7 3 3 1 2 0.2 0.25 5 3 3 0.5 1");
	ex3.print();
	ex3.generalSolution();

	TropicMatrix ex4(4, 4, "1 4 6 7 2 1 3 4 1.5 2 1 2 0.1 0.3 3 1");
	ex4.generalSolution();

	TropicMatrix ex5(4, 4, "1 0.2 3 3 5 1 5 3 0 0.2 1 0.2 0 0 5 1");
	ex5.insert(8, (double)1 / 3);
	ex5.insert(12, (double)1 / 3);
	ex5.insert(13, (double)1 / 3);
	ex5.generalSolution();

	TropicMatrix ex6(4, 4, "1 0 0 0.625 0.9 1 0.8 0.75 1.5 1.25 1 0 1.6 0 0 1");
	ex6.insert(1, (double)10 / 9);
	ex6.insert(2, (double)2 / 3);
	ex6.insert(11, (double)15 / 16);
	ex6.insert(13, (double)4 / 3);
	ex6.insert(14, (double)16 / 15);
	ex6.generalSolution();

	TropicMatrix ex7(5, 5,
		"1 0 0 0.125 5 6 1 2 1 8 3 0.5 1 0.5 5 8 1 2 1 5 0.2 0.125 0.2 0.2 1");
	ex7.insert(1, (double)1 / 6);
	ex7.insert(2, (double)1 / 3);
	ex7.generalSolution();

	// Пример вычисления итогового вектора тропического аналога МАИ
	std::vector<TropicMatrix>matrices;
	// Матрица сравнения критериев
	TropicMatrix ex8(5, 5,
		"1 0.2 0.2 1 1/3 5 1 0.2 0.2 1 5 5 1 0.2 1 1 5 5 1 5 3 1 1 0.2 1");
	ex8.print();

	
	// Матрицы сравнения альтернатив относительно разных критериев
	TropicMatrix A1(4, 4, "1 3 7 9 1/3 1 6 7 1/7 1/6 1 3 1/9 1/7 1/3 1");
	TropicMatrix A2(4, 4, "1 1/5 1/6 1/4 5 1 2 4 6 1/2 1 6 4 1/4 1/6 1");
	TropicMatrix A3(4, 4, "1 7 7 1/2 1/7 1 1 1/7 1/7 1 1 1/7 2 7 7 1");
	TropicMatrix A4(4, 4, "1 4 1/4 1/3 1/4 1 1/2 3 4 2 1 3 3 1/3 1/3 1");
	TropicMatrix A5(4, 4, "1 1 7 4 1 1 6 3 1/7 1/6 1 1/4 1/4 1/3 4 1");

	matrices.push_back(A1);
	matrices.push_back(A2);
	matrices.push_back(A3);
	matrices.push_back(A4);
	matrices.push_back(A5);
	tropicAHP(ex8, matrices); // само вычисление

	cout << "To continue press Enter\n";
	cin.get();
	return 0;
}
