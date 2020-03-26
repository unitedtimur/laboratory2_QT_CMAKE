#ifndef CLASS_UNIT_H
#define CLASS_UNIT_H

#include "include/Unit.h"

class ClassUnit : public Unit
{
public:
	explicit ClassUnit(QString name);

	virtual void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags) override		= 0;
	virtual QString compile(const Configuration::UI& level) const override								= 0;

protected:
	virtual QString generateShift(const Configuration::UI& level) const override;

	QString							_name;
	QVector<Configuration::Fields>	_fields;
};

#endif // CLASS_UNIT_H