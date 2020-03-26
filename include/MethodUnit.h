#ifndef METHOD_UNIT_H
#define METHOD_UNIT_H

#include "include/Unit.h"

class MethodUnit : public Unit
{
public:
	virtual void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags = 0) override = 0;
	virtual QString compile(const Configuration::UI& level) const override								= 0;
};

#endif // METHOD_UNIT_H