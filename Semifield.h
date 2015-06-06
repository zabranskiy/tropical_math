#pragma once
#ifndef SEMIFIELD_H
#define SEMIFIELD_H

#include "Arithmetic.h"

/*
  Дмитрий Забранский, 2015 г.
*/

// Тип операции сложения
enum AdditionType {
	MAX, MIN, ADD
};

// Тип операции умножения
enum MultiplicationType {
	ADDITION, MULTIPLICATION
};

// Класс идемпотентного полуполя
class Semifield {
private:
	AdditionType a_type;
	MultiplicationType m_type;

public:
	Semifield();
	Semifield(AdditionType t1, MultiplicationType t2);

	void setAdditionType(AdditionType _type);
	void setMultiplicationType(MultiplicationType _type);
	AdditionType getAdditionType();
	MultiplicationType getMultiplicationType();
	TropicDouble getAdditionNeutralElement();
	TropicDouble getMultiplicationNeutralElement();
};

#endif /* SEMIFIELD_H */
