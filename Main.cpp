#include <vcl.h>

#pragma hdrstop
#pragma argsused

#include "Semifield.h"
#include <iostream>
#include <conio.h>

using namespace std;

Semifield sf;

int _tmain(int argc, _TCHAR* argv[]) {
	TropicDouble n1 = 10.5;
	TropicDouble n2(5.5);
	Double res = (n1 * n2).toDouble();
	cout.precision(4);
	cout << fixed << res << endl;
	// TropicMatrix tM(3, 3, "1 25 36.8 4 5 6 7 8 9");
	size_t t = 8;
	// TropicDouble td = tM[t];
	int k = 0;

	TropicMatrix tM1(3, 3, "0 1.5 -1 -1.5 0 1 1 -1 0");
	// TropicMatrix tM2(3, 3, "1 25 36.8 4 5 6 7 8 9");
	TropicMatrix pM = tM1 * tM1;
	pM.print();
	TropicMatrix tM2(3, 3, "0 1.5 3 -0.5 5 1.5 1 -1 0");
	TropicMatrix pM2 = tM2.getMultiplicativeConjugateMatrix();
	// TropicDouble td = pM2.getTrace();
	// tM2.print();
	// pM2.print();

	TropicMatrix tM3(4, 4, "1 2 0.5 0.5 0.5 1 2 0.5 2 0.5 1 0.5 2 2 2 1");
	// TropicMatrix tM4(1, 4, "2 0 0 1");
	// tM3.print();
	// (tM3 * tM4).print();
	// tM3.print();
	// TropicMatrix tM7 = tM3.getKleeneStar();
	// // tM7.print();
	// TropicMatrix tM8 = tM7.reduce();
	// // tM8.print();
	// TropicMatrix tM9(2, 1, "0 1");
	// tM9.print();
	// TropicMatrix tM10 = tM8 * tM9;
	// (tM3 * tM10).print();
	// (tM3.getSpectralRadius() * tM10).print();
	// TropicMatrix tM11 = tM10.getX();
	// tM11.print();
	// tM11.checkDistances();
	// tM11.checkDistances(tM3);
	tM3.generalSolution();
	// TropicMatrix tM12 = tM7 * tM7.getMultiplicativeConjugateMatrix();
	// tM12.checkDistances(tM3);

	TropicMatrix ex1(4, 4, "1 5 6 7 0.2 1 4 6 0 0.25 1 4 0 0 0.25 1");
	ex1.insert(8, (double)1 / 6);
	ex1.insert(12, (double)1 / 7);
	ex1.insert(13, (double)1 / 6);
	ex1.generalSolution();
	// ex1.isCoherence();

	TropicMatrix ex2(4, 4, "1 4 6 7 0.25 1 3 4 0 0 1 2 0 0.25 0.5 1");
	ex2.insert(8, (double)1 / 6);
	ex2.insert(9, (double)1 / 3);
	ex2.insert(12, (double)1 / 7);
	ex2.generalSolution(); // page 39

	// std::vector<TropicMatrix>vec;
	// vec.push_back(ex1);
	// vec.push_back(ex2);
	// multicriterialApproximation(vec);

	TropicMatrix ex3(7, 7,
		"1 4 9 6 6 5 5 0.25 1 7 5 5 3 4 0.11 0.14 1 0.2 0.2 0.14 0.2 0.17 0.2 5 1 1 0.33 0.33 0.17 0.2 5 1 1 0.33 0.33 0.2 0.33 7 3 3 1 2 0.2 0.25 5 3 3 0.5 1");
	ex3.print();
	ex3.generalSolution();
	// TropicMatrix id(7, 7,
	// "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1");
	// id.print();
	// (ex3.getMultiplicativeConjugateMatrix() + ex3).exp2(id, 100);
	// ex3.getKleeneStar().print();
	// id.print();
	// ex3.exp(id).print();

	// TropicMatrix t_ex31 = ex3.getKleeneStar();
	// TropicMatrix t_ex32 = t_ex31.reduce();
	// t_ex32.print();
	// TropicMatrix p1(2, 1, "1 0");
	// p1.print();
	// TropicMatrix p2 = t_ex32 * p1;
	// p2.print(); // page 41
	// (ex3 * p2).print();
	// (ex3.getSpectralRadius() * p2).print();
	// TropicMatrix p3 = p2.getX();
	// // p3.checkDistances(ex3);
	// // p3.isCoherence();
	// TropicMatrix p33 = ex3.getKleeneStar() * ex3.getKleeneStar()
	// .getMultiplicativeConjugateMatrix();
	// p33.print();
	// p33.isSymmetric();
	// p33.isCoherence();
	// p33.checkDistances(ex3);

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

	std::vector<TropicMatrix>matrices;
	TropicMatrix ex8(5, 5,
		"1 0.2 0.2 1 1/3 5 1 0.2 0.2 1 5 5 1 0.2 1 1 5 5 1 5 3 1 1 0.2 1");
	ex8.print();

	TropicMatrix A1(4, 4, "1 3 7 9 1/3 1 6 7 1/7 1/6 1 3 1/9 1/7 1/3 1");
	// A1.print();
	TropicMatrix A2(4, 4, "1 1/5 1/6 1/4 5 1 2 4 6 1/2 1 6 4 1/4 1/6 1");
	// A2.print();
	TropicMatrix A3(4, 4, "1 7 7 1/2 1/7 1 1 1/7 1/7 1 1 1/7 2 7 7 1");
	// A3.print();
	TropicMatrix A4(4, 4, "1 4 1/4 1/3 1/4 1 1/2 3 4 2 1 3 3 1/3 1/3 1");
	// A4.print();
	TropicMatrix A5(4, 4, "1 1 7 4 1 1 6 3 1/7 1/6 1 1/4 1/4 1/3 4 1");
	// A5.print();

	matrices.push_back(A1);
	matrices.push_back(A2);
	matrices.push_back(A3);
	matrices.push_back(A4);
	matrices.push_back(A5);
	// matrices[0].print();
	// matrices[1].print();
	// matrices[2].print();
	// matrices[3].print();
	// matrices[4].print();
	tropicAHP(ex8, matrices);

    TropicMatrix vec(4,1, "0.919 0.745 0.862 0.757");
    vec.normalize().print();
//	standardTropicAHP(ex8, matrices);

	// TropicMatrix id2(4, 4, "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1");
	// ex5.getKleeneStar().print();
	// id2.print();
	// ex5.exp(id2).print();

	// TropicMatrix pM3 = tM2.pow(3);
	// TropicDouble td = tM3.getSpectralRadius();
	// tM3.print();
	// TropicMatrix tM4 = tM3.getSpectralRadius().pow(-1) * tM3;
	// tM4.print();
	// TropicMatrix iM(3, 3);
	// iM.print();

	// tM3.excludeColumnByIndex(6).print();

	// TropicMatrix A(3, 3, "5 3 8 2 4 6 2 6 8");
	// TropicMatrix b(1, 3, "8 6 8");
	// Delta(A, b);
	_getch();
	return 0;
}
