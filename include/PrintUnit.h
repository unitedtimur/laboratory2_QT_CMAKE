#ifndef PRINT_UNIT_H
#define PRINT_UNIT_H

#include "include/Unit.h"

class PrintUnit : public Unit
{
public:
	explicit PrintUnit(QString text);

	virtual QString compile(const Configuration::UI& level = 0) const override = 0;

protected:
	QString _text;
};

#endif // PRINT_UNIT_H