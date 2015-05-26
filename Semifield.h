#ifndef SEMIFIELD_H
#define SEMIFIELD_H

#include "Arithmetic.h"

enum AdditionType {
	MAX, MIN, ADD
};

enum MultiplicationType {
	ADDITION, MULTIPLICATION
};

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
