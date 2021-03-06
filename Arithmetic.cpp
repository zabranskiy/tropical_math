#include "Semifield.h"
#include <math.h>
#include <iostream>
#include <stdlib.h> 

/*
  ����� ����������� ����������
  ������� ����������, 2015 �.
*/

#define EPSILON    0.0001

extern Semifield sf;

const TropicDouble operator +(TropicDouble const & left,
	TropicDouble const & right) {
	// ��������������� ��������
	if (left == right) {
		return left;
	}
	switch (sf.getAdditionType()) {
	case MAX: {
			return left > right ? left : right;
		}
	case MIN: {
			return left < right ? left : right;
		}
	default: {
			break;
		}
	}

	return TropicDouble(left.value + right.value);
}

const TropicDouble operator * (TropicDouble const & left,
	TropicDouble const & right) {

	switch (sf.getMultiplicationType()) {
	case ADDITION: {
			return TropicDouble(left.value + right.value);
		}
	case MULTIPLICATION: {
			return TropicDouble(left.value * right.value);
		}
	default: {
			break;
		}
	}

	return TropicDouble(left.value * right.value);
}

TropicDouble* TropicDouble:: operator += (TropicDouble const & td) {
	switch (sf.getAdditionType()) {
	case MAX: {
			if (td.value > value) {
				value = td.value;
			}
			break;
		}
	case MIN: {
			if (td.value < value) {
				value = td.value;
			}
			break;
		}
	default: {
			break;
		}
	}
	return this;
}

bool operator == (TropicDouble const & left, TropicDouble const & right) {
	return fabs(left.value - right.value) < EPSILON;
}

bool operator > (TropicDouble const & left, TropicDouble const & right) {
	return left.value > right.value;
}

bool operator < (TropicDouble const & left, TropicDouble const & right) {
	return left.value < right.value;
}

double TropicDouble::toDouble() const {
	return value;
}

// ���������� ������������ ����� � �������
TropicDouble TropicDouble::pow(double degree) {
	double res = 0.0;
	switch (sf.getMultiplicationType()) {
	case ADDITION: {
			if (degree == -1) {
				res = -value;
			}
			else {
				res = value + degree;
			}
			break;
		}
	case MULTIPLICATION: {
			if (degree == -1) {
				if (value < EPSILON) {
					return TropicDouble(res);
				}
				res = 1 / value;
			}
			else {
				res = powl(value, degree);
			}
			break;
		}
	default: {
			break;
		}
	}
	return TropicDouble(res);
}

TropicMatrix::TropicMatrix(std::size_t size) : mRows(size), mCols(size),
	mData(size * size) {
	// Identity Matrix
	std::fill(mData.begin(), mData.end(), sf.getAdditionNeutralElement());
	for (std::size_t i = 0; i < size; i++) {
		mData[i * size + i] = sf.getMultiplicationNeutralElement();
	}
}

TropicMatrix::TropicMatrix(std::size_t rows, std::size_t cols) : mRows(rows), mCols(cols),
	mData(rows * cols) {
	std::fill(mData.begin(), mData.end(), sf.getAdditionNeutralElement());
}

TropicMatrix::TropicMatrix(std::size_t rows, std::size_t cols, std::string str)
	: mRows(rows), mCols(cols), mData(rows * cols) {
	std::size_t j = 0, idx = 0;
	std::size_t i = 0, k = 0;
	bool fl = false;
	while (i <= str.size()) {
		if (str[i] == ' ' || str[i] == 0) {
			if (fl) {
				std::string sl1 = str.substr(k, idx - k);
				char * ptrEnd;
				double num1 = strtod(sl1.c_str(), &ptrEnd);
				std::string sl2 = str.substr(idx + 1, i - idx - 1);
				double num2 = strtod(sl2.c_str(), &ptrEnd);
				mData[j++] = num1 / num2;
				fl = false;
			}
			else {
				std::string sl = str.substr(k, i - k);
				char * ptrEnd;
				double num = strtod(sl.c_str(), &ptrEnd);
				mData[j++] = TropicDouble(num);
			}
			k = i + 1;
		}
		else if (str[i] == '/') {
			idx = i;
			fl = true;
		}
		i++;
	}
}

TropicMatrix::~TropicMatrix() {
	std::vector<TropicDouble>().swap(mData); // swap trick to deallocate the vector's memory
}

const std::size_t TropicMatrix::getRows() {
	return mRows;
}

const std::size_t TropicMatrix::getCols() {
	return mCols;
}

// ����� ������� �� �������
void TropicMatrix::print() {
	for (std::size_t i = 0; i < mRows * mCols; i++) {
		std::cout << mData[i].toDouble() << ' ';
		if ((i + 1) % mCols == 0) {
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}

TropicDouble& TropicMatrix:: operator[](std::size_t idx) {
	return mData[idx];
}

const TropicDouble& TropicMatrix:: operator[](std::size_t idx) const {
	return mData[idx];
}

TropicMatrix operator *(TropicDouble const & left, TropicMatrix const & right) {
	TropicMatrix product(right.mRows, right.mCols);

	for (std::size_t row = 0; row < product.mRows; row++) {
		for (std::size_t col = 0; col < product.mCols; col++) {
			std::size_t idx = row * product.mCols + col;
			product[idx] = left * right[idx];
		}
	}
	return product;
}

TropicMatrix operator * (TropicMatrix const & left, TropicMatrix const & right)
{
	if (left.mCols == right.mRows) {
		TropicMatrix product(left.mRows, right.mCols);

		for (std::size_t row = 0; row < product.mRows; row++) {
			for (std::size_t col = 0; col < product.mCols; col++) {
				std::size_t i1 = row * product.mCols + col;
				for (std::size_t inner = 0; inner < left.mCols; inner++) {
					std::size_t i2 = row * left.mCols + inner;
					std::size_t i3 = inner * right.mCols + col;
					product[i1] += left[i2] * right[i3];
				}
			}
		}
		return product;
	}

	return left;
}

TropicMatrix operator +(TropicMatrix const & left, TropicMatrix const & right) {
	if (left.mRows == right.mRows && left.mCols == right.mCols) {
		TropicMatrix sum(left.mRows, left.mCols);

		for (std::size_t row = 0; row < sum.mRows; row++) {
			for (std::size_t col = 0; col < sum.mCols; col++) {
				std::size_t idx = row * sum.mCols + col;
				sum[idx] = left[idx] + right[idx];
			}
		}
		return sum;
	}

	return left;
}

// ������ ����� �������
TropicDouble TropicMatrix::getTrace() {
	TropicDouble res(0);
	for (std::size_t i = 0; i < mRows; i++) {
		res += mData[i * mRows + i];
	}
	return res;
}

// ���������� ����������������-����������� �������
TropicMatrix TropicMatrix::getMultiplicativeConjugateMatrix() {
	TropicMatrix res(mCols, mRows);

	for (std::size_t i = 0; i < mRows; i++) {
		for (std::size_t j = 0; j < mCols; j++) {
			std::size_t idx1 = i * mCols + j;
			std::size_t idx2 = j * res.mCols + i;
			if (mData[idx2] == 0) {
				res[idx1] = 0;
			}
			else {
				res[idx1] = mData[idx2].pow(-1);
			}
		}
	}
	return res;
}

// ���������� ������� � �������
TropicMatrix TropicMatrix::pow(std::size_t degree) {
	TropicMatrix res = *this;
	for (std::size_t i = 1; i < degree; i++) {
		res = res * (*this);
	}
	// res.print();
	return res;
}

// ����� ������������� ������� �������
TropicDouble TropicMatrix::getSpectralRadius() {
	TropicDouble res(0);
	for (std::size_t m = 1; m <= mRows; m++) {
		double t = 1 / (double)m;
		res += this->pow(m).getTrace().pow(t);
	}
	return res;
}

// ����� ������ �����
TropicMatrix TropicMatrix::getKleeneStar() {
	TropicMatrix res(mRows); // Identity Matrix

	TropicMatrix tM = this->getSpectralRadius().pow(-1) * (*this);
	for (std::size_t i = 1; i <= mRows - 1; i++) {
		res = res + tM.pow(i);
	}
	return res;
}

TropicMatrix TropicMatrix::getColumnByIndex(std::size_t idx) {
	TropicMatrix res(mRows, 1);

	for (std::size_t i = 0; i < mRows; i++) {
		res[i] = mData[i * mCols + idx];
	}

	return res;
}

TropicMatrix TropicMatrix::excludeColumnByIndex(std::size_t idx) {
	if (mCols == 1) {
		return *this;
	}
	TropicMatrix res(mRows, mCols - 1);

	if (idx > (mCols - 1)) {
		// Error
		return *this;
	}

	for (std::size_t i = 0; i < mRows; i++) {
		for (std::size_t j = 0; j < mCols; j++) {
			std::size_t idx1 = i * mCols + j;
			std::size_t idx2 = i * res.mCols + j;
			if (j != idx) {
				if (j > idx) {
					idx2--;
				}
				res[idx2] = mData[idx1];
			}
		}
	}

	return res;
}

TropicDouble Delta(TropicMatrix & A, TropicMatrix & b) {
	TropicMatrix t1 = b.getMultiplicativeConjugateMatrix() * A;
	TropicMatrix t2 = A * t1.getMultiplicativeConjugateMatrix();
	TropicMatrix t3 = t2.getMultiplicativeConjugateMatrix() * b;
	return t3[0];
}

// ������������� �������
TropicMatrix TropicMatrix::reduce() {
	TropicMatrix temp = *this;
	for (std::size_t i = 0; i < temp.getCols(); i++) {
		TropicMatrix Ai = temp.excludeColumnByIndex(i);
		TropicMatrix ai = temp.getColumnByIndex(i);
		if (Delta(Ai, ai) == sf.getMultiplicationNeutralElement()) {
			if (Ai.getCols() == 1) {
				return Ai;
			}
			temp = Ai.reduce();
			break;
		}
	}
	return temp;
}

void TropicMatrix::insert(std::size_t idx, double val) {
	mData[idx] = val;
}

// ������������ ������� ������� ����
TropicMatrix TropicMatrix::normalize() {
	TropicMatrix res = *this;
	if (res.mCols == 1) {
		double sum = 0.0;
		for (std::size_t i = 0; i < mRows; i++) {
			sum += mData[i].toDouble();
		}
		for (std::size_t i = 0; i < mRows; i++) {
			res.insert(i, mData[i].toDouble() / sum);
		}
	}
	return res;
}

// ������������ ������� ������� ����
TropicMatrix TropicMatrix::normalize2() {
	TropicMatrix res = *this;
	if (res.mCols == 1) {
		double t = 1 / mData[0].toDouble();
		res.insert(0, 1.0);
		for (std::size_t i = 1; i < mRows; i++) {
			res.insert(i, mData[i].toDouble() * t);
		}
	}
	return res;
}

TropicMatrix TropicMatrix::getX() {
	TropicMatrix x = *this;
	TropicMatrix _x = x.getMultiplicativeConjugateMatrix();
	return x * _x;
}

// ������� ��������
double TropicMatrix::getChebyshevDistance(TropicMatrix & A) {
	TropicMatrix B = *this;
	double max = 0.0;
	for (std::size_t row = 0; row < A.mRows; row++) {
		for (std::size_t col = 0; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			double dif = fabs(B[idx].toDouble() - A[idx].toDouble());
			if (dif > max) {
				max = dif;
			}
		}
	}
	return max;
}

// ��������� ����������
double TropicMatrix::getEuclideanDistance(TropicMatrix & A) {
	TropicMatrix B = *this;
	double sum = 0.0;
	for (std::size_t row = 0; row < A.mRows; row++) {
		for (std::size_t col = 0; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			sum += powl((A[idx].toDouble() - B[idx].toDouble()), 2);
		}
	}
	return sqrt(sum);
}

void TropicMatrix::checkDistances() {
	TropicMatrix A = *this;
	A.print();
	TropicMatrix A_star = A.getKleeneStar().reduce();
	A_star.print();
	double radius = A.getSpectralRadius().toDouble();
	std::cout << "   Spectral radius: " << radius << "\n" << std::endl;
	double min_val = radius * 10;
	std::size_t min_idx = 0;
	for (std::size_t i = 0; i < A_star.mCols; i++) {
		TropicMatrix M(A_star.mCols, 1);
		M.insert(i, 1.0);
		M.print();
		TropicMatrix vector_x = A_star * M;
		vector_x.normalize().print();
		TropicMatrix X = vector_x.getX();
		X.print();
		double num1 = A.getEuclideanDistance(X);
		double num2 = A.getChebyshevDistance(X);
		double num3 = getDistance(A, X);
		std::cout << "Euclidean distance: " << num1 << "\n";
		std::cout << "Chebyshev distance: " << num2 << "\n";
		std::cout << "          Distance: " << num3 << "\n" << std::endl;
		if (min_val > num1) {
			min_val = num1;
			min_idx = i;
		}
	}
	TropicMatrix M(A_star.mCols, 1);
	M.insert(min_idx, 1.0);
	M.print();
	TropicMatrix vector_x = A_star * M;
	TropicMatrix X = vector_x.getX();
	std::cout << "Solution\n" << std::endl;
	X.print();
	double num1 = A.getEuclideanDistance(X);
	double num2 = A.getChebyshevDistance(X);
	double num3 = getDistance(A, X);
	std::cout << "Euclidean distance: " << num1 << "\n";
	std::cout << "Chebyshev distance: " << num2 << "\n";
	std::cout << "          Distance: " << num3 << "\n" << std::endl;
}

// �����-����������� �������
double getDistance(TropicMatrix & A, TropicMatrix & B) {
	return ((A.getMultiplicativeConjugateMatrix() * B).getTrace() +
		(B.getMultiplicativeConjugateMatrix() * A).getTrace()).toDouble();
}

// �������� �������� �� ������� �������-�������������� 
bool TropicMatrix::isSymmetricallyReciprocal() {
	TropicMatrix A = *this;
	bool fl = true;
	for (std::size_t row = 0; row < A.mRows; row++) {
		for (std::size_t col = row; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			if (row == col) {
				if (fabs(mData[idx].toDouble() - 1) >= EPSILON) {
					fl = false;
					break;
				}
			}
			else {
				std::size_t idx2 = col * A.mCols + row;
				TropicDouble product = mData[idx] * mData[idx2];
				if (!(product == sf.getMultiplicationNeutralElement())) {
					fl = false;
					break;
				}
			}
		}
	}
	if (!fl) {
		std::cout << "Matrix is not symmetrically reciprocal\n" << std::endl;
	}
	else {
		std::cout << "Matrix is symmetrically reciprocal\n" << std::endl;
	}
	return fl;
}

// �������� ������� �� ������ ��������������
bool TropicMatrix::isTransitive() {
	TropicMatrix A = *this;
	bool fl = true;
	for (std::size_t row = 0; row < A.mRows; row++) {
		for (std::size_t col = row; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			if (row == col) {
				if (fabs(mData[idx].toDouble() - 1) >= EPSILON) {
					fl = false;
					break;
				}
			}
			else {
				for (std::size_t j = 0; j < A.mCols; j++) {
					std::size_t idx2 = col * A.mCols + j;
					std::size_t idx3 = row * A.mCols + j;
					if (col != j && !(mData[idx] * mData[idx2] == mData[idx3]))
					{
						fl = false;
						break;
					}
				}
			}
		}
	}
	if (!fl) {
		std::cout << "Matrix is not transitive\n" << std::endl;
	}
	else {
		std::cout << "Matrix is transitive\n" << std::endl;
	}
	return fl;
}

// ����� ���������� ������� � ������� ������ ��������� ��� ������������ ������
void TropicMatrix::generalSolution() {
	TropicMatrix A = *this;
	A.print();
	TropicMatrix A_ = A.getMultiplicativeConjugateMatrix();
	A_.print();
	TropicMatrix B = A_ + A;
	B.checkDistances();
}

void multicriterialApproximation(std::vector<TropicMatrix>matrices) {
	if (!matrices.empty()) {
		TropicMatrix sum(matrices[0].getRows(), matrices[0].getCols());
		for (std::vector<TropicMatrix>::iterator it = matrices.begin();
		it != matrices.end(); ++it) {
			TropicMatrix A = (*it);
			sum = sum + A.getMultiplicativeConjugateMatrix() + A;
		}
		sum.generalSolution();
	}
}

// ������� ������������ ������� ������ ������� ��������
void tropicAHP(TropicMatrix & A, std::vector<TropicMatrix>Ai) {
	TropicMatrix A_ = A.getMultiplicativeConjugateMatrix();
	TropicMatrix B = A_ + A;
	TropicMatrix B_star = B.getKleeneStar().reduce();
	TropicMatrix weight_vector(B_star.getRows(), 1);
	if (B_star.getCols() != 1) {
		double min_val = B.getSpectralRadius().toDouble() * 10;
		std::size_t min_idx = 0;
		for (std::size_t i = 0; i < B_star.getCols(); i++) {
			TropicMatrix M(B_star.getCols(), 1);
			M.insert(i, 1.0);
			TropicMatrix vector_x = B_star * M;
			TropicMatrix X = vector_x.getX();
			double num = B.getEuclideanDistance(X);
			if (min_val > num) {
				min_val = num;
				min_idx = i;
			}
		}
		TropicMatrix M(B_star.getCols(), 1);
		M.insert(min_idx, 1.0);
		weight_vector = B_star * M;
	}
	else {
		weight_vector = B_star;
	}
	std::cout << "Weight vector:\n" << std::endl;
	weight_vector.print();

	if (!Ai.empty() && weight_vector.getRows() == Ai.size()) {
		TropicMatrix Sum(Ai[0].getRows(), Ai[0].getCols());
		for (std::size_t i = 0; i < Ai.size(); i++) {
			TropicMatrix T = Ai[i].getMultiplicativeConjugateMatrix() + Ai[i];
			TropicMatrix Bi = weight_vector[i] * T;
			Sum = Sum + Bi;
		}
		std::cout << "Sum matrix:\n" << std::endl;
		Sum.print();
		double radius = Sum.getSpectralRadius().toDouble();
		std::cout << "   Spectral radius: " << radius << "\n" << std::endl;
		TropicMatrix Sum_star = Sum.getKleeneStar().reduce();
		Sum_star.print();
		TropicMatrix Res(Sum_star.getRows(), 1);
		if (Sum_star.getCols() != 1) {
			double min_val = radius * 10;
			std::size_t min_idx = 0;
			for (std::size_t i = 0; i < Sum_star.getCols(); i++) {
				TropicMatrix M(Sum_star.getCols(), 1);
				M.insert(i, 1.0);
				TropicMatrix vector_x = Sum_star * M;
				vector_x.print();
				TropicMatrix X = vector_x.getX();
				X.print();
				double num = Sum.getEuclideanDistance(X);
				std::cout << num << "\n" << std::endl;
				if (min_val > num) {
					min_val = num;
					min_idx = i;
				}
			}
			TropicMatrix M(Sum_star.getCols(), 1);
			M.insert(min_idx, 1.0);
			Res = Sum_star * M;
		}
		else {
			Res = Sum_star;
		}
		std::cout << "Result vector:\n" << std::endl;
		Res.normalize().print();
	}
}

double TropicMatrix::getElementwiseNorm(unsigned int p) {
	TropicMatrix A = *this;
	double sum = 0.0;
	for (std::size_t row = 0; row < A.mRows; row++) {
		for (std::size_t col = 0; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			sum += powl(fabs(mData[idx].toDouble()), p);
		}
	}
	return powl(sum, 1 / p);
}

double TropicMatrix::getlNorm() {
	TropicMatrix A = *this;
	double max = 0.0;
	for (std::size_t row = 0; row < A.mRows; row++) {
		double sum = 0.0;
		for (std::size_t col = 0; col < A.mCols; col++) {
			std::size_t idx = row * A.mCols + col;
			sum += fabs(mData[idx].toDouble());
		}
		if (max < sum) {
			max = sum;
		}
	}
	return max;
}

double TropicMatrix::getmNorm() {
	TropicMatrix A = *this;
	double max = 0.0;
	for (std::size_t col = 0; col < A.mCols; col++) {
		double sum = 0.0;
		for (std::size_t row = 0; row < A.mRows; row++) {
			std::size_t idx = row * A.mCols + col;
			sum += fabs(mData[idx].toDouble());
		}
		if (max < sum) {
			max = sum;
		}
	}
	return max;
}
