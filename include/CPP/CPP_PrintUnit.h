#ifndef CPP_PRINT_UNIT_H
#define CPP_PRINT_UNIT_H

#include "include/PrintUnit.h"

class CPP_PrintUnit : PrintUnit
{
public:
	explicit CPP_PrintUnit(QString text);
	~CPP_PrintUnit() override = default;
	QString compile(const Configuration::UI& level = 0) const override;

protected:
	QString generateShift(const Configuration::UI& level) const override;

	private:
	QString _text;
};

#endif // CPP_PRINT_UNIT_H
