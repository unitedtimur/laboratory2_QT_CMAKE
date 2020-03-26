#ifndef METHOD_UNIT_H
#define METHOD_UNIT_H

#include "include/Unit.h"

class MethodUnit : public Unit
{
public:
	explicit MethodUnit(QString name, QString returnType, const Configuration::Flags& flags);

	virtual void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& /*flags*/ = 0) override;
	virtual QString compile(const Configuration::UI& level) const override = 0;

private:
	QString					_name;
	QString					_returnType;
	Configuration::Flags	_flags;
	Configuration::Fields	_body;
};

#endif // METHOD_UNIT_H