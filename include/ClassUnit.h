#ifndef CLASS_UNIT_H
#define CLASS_UNIT_H

#include "include/Unit.h"

class ClassUnit : public Unit
{
public:
	explicit ClassUnit(const QString& name);

private:
	QString							_name;
	QVector<Configuration::Fields>	_fields;
};

#endif // CLASS_UNIT_H