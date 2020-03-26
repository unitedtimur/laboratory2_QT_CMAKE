#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include "include/Configuration.h"

class Unit
{
public:
	virtual ~Unit() = default;
	virtual void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags)	= 0;
	virtual QString compile(const Configuration::UI& level = 0) const						= 0;

protected:
	virtual QString generateShift(const Configuration::UI& level) const						= 0;
};

#endif // UNIT_H
