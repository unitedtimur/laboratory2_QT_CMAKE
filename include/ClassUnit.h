#ifndef CLASS_UNIT_H
#define CLASS_UNIT_H

#include "include/Unit.h"

class ClassUnit : public Unit
{
public:
	explicit ClassUnit(QString name);

	virtual void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags) override;
	virtual QString compile(const Configuration::UI& level) const override = 0;

protected:
	QString							_name;
	QVector<Configuration::Fields>	_fields;
};

#endif // CLASS_UNIT_H