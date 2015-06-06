#include "Semifield.h"
#include <limits>
/*
  ����� �������������� ��������
  ������� ����������, 2015 �.
*/
using namespace std;

Semifield::Semifield() {
	a_type = MAX;
	m_type = MULTIPLICATION;
}

Semifield::Semifield(AdditionType t1, MultiplicationType t2) {
	a_type = t1;
	m_type = t2;
}

void Semifield::setAdditionType(AdditionType _type) {
	a_type = _type;
}

void Semifield::setMultiplicationType(MultiplicationType _type) {
	m_type = _type;
}

AdditionType Semifield::getAdditionType() {
	return a_type;
}

MultiplicationType Semifield::getMultiplicationType() {
	return m_type;
}

// ��������� ������������ �������� �� ��������
TropicDouble Semifield::getAdditionNeutralElement() {
	double res = 0;
	switch (a_type) {
	case MAX: {
			if (m_type == MULTIPLICATION) {
				// R+
				res = 0;
			}
			else {
				// R union -Infinity
				if (numeric_limits<double>::is_iec559) {
					res = -numeric_limits<double>::infinity();
				}
				else {
					res = numeric_limits<double>::min();
				}
			}
			break;
		}
	case MIN: {
			if (numeric_limits<double>::is_iec559) {
				res = numeric_limits<double>::infinity();
			}
			else {
				res = numeric_limits<double>::max();
			}
			break;
		}
	default: {
			res = 0;
			break;
		}
	}
	TropicDouble neutral(res);
	return neutral;
}

// ��������� ������������ �������� �� ���������
TropicDouble Semifield::getMultiplicationNeutralElement() {
	double res = 0;
	switch (m_type) {
	case ADDITION: {
			res = 0;
			break;
		}
	case MULTIPLICATION: {
			res = 1;
			break;
		}
	default: {
			break;
		}
	}
	TropicDouble neutral(res);
	return neutral;
}
