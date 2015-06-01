#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <vector>

class TropicDouble {
private:
	double value;

public:
	TropicDouble() {
	}

	TropicDouble(double num) : value(num) {
	}

	friend const TropicDouble operator +(TropicDouble const & left,
		TropicDouble const & right);

	friend const TropicDouble operator * (TropicDouble const & left,
		TropicDouble const & right);

	TropicDouble* operator += (TropicDouble const & td);

	friend bool operator == (TropicDouble const & left,
		TropicDouble const & right);

	friend bool operator > (TropicDouble const & left,
		TropicDouble const & right);

	friend bool operator < (TropicDouble const & left,
		TropicDouble const & right);

	double toDouble() const ;
	TropicDouble pow(double);
};

class TropicMatrix {
private:
	size_t mCols, mRows;

	std::vector<TropicDouble>mData;

public:
	TropicMatrix(size_t size); // Identity Matrix
	TropicMatrix(size_t rows, size_t cols);
	TropicMatrix(size_t rows, size_t cols, std::string str);

	const size_t getRows();
	const size_t getCols();
	void print();
	void insert(size_t, double);
	double getChebyshevDistance(TropicMatrix & A);
	double getEuclideanDistance(TropicMatrix & A);
	double getElementwiseNorm(unsigned int p);
	double getmNorm(); // p = 1
	double getlNorm(); // p = Infinity
	void checkDistances();
	void generalSolution();
	bool isSymmetricallyReciprocal();
	bool isTransitive();

	TropicDouble& operator[](size_t idx);
	const TropicDouble& operator[](size_t idx) const ;

	friend TropicMatrix operator *(TropicDouble const & left,
		TropicMatrix const & right);

	friend TropicMatrix operator * (TropicMatrix const & left,
		TropicMatrix const & right);

	friend TropicMatrix operator +(TropicMatrix const & left,
		TropicMatrix const & right);

	TropicMatrix getColumnByIndex(size_t);
	TropicMatrix excludeColumnByIndex(size_t);
	TropicDouble getTrace();
	TropicDouble getSpectralRadius();
	TropicMatrix getMultiplicativeConjugateMatrix();
	TropicMatrix pow(size_t);
	TropicMatrix getKleeneStar();
	TropicMatrix reduce();
	TropicMatrix normalize();
	TropicMatrix normalize2();
	TropicMatrix getX();
};

TropicDouble Delta(TropicMatrix & A, TropicMatrix & b);
double getDistance(TropicMatrix & A, TropicMatrix & B);
void multicriterialApproximation(std::vector<TropicMatrix>matrices);
void tropicAHP(TropicMatrix & A, std::vector<TropicMatrix>Ai);

#endif /* ARITHMETIC_H */
