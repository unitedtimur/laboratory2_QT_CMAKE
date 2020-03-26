#ifndef PRINT_UNIT_H
#define PRINT_UNIT_H

#include "include/Unit.h"

class PrintUnit : public Unit
{
public:
	virtual QString compile(const Configuration::UI& level = 0) const override = 0;
};

#endif // PRINT_UNIT_H