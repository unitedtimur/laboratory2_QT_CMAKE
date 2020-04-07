#pragma once

#include "include/Configuration.h"

class Unit
{
public:
	virtual ~Unit() noexcept = default;
	virtual void add(const Configuration::Ptr& unit, const Configuration::Flags& flags = 0)	= 0;
	virtual std::string compile(const Configuration::UI& level = 0) const						= 0;

protected:
	virtual std::string generateShift(const Configuration::UI& level) const;
};

inline std::string Unit::generateShift(const Configuration::UI& level) const
{
	std::string result;

	for (Configuration::UI i = 0; i < level; ++i)
		result += '\t';

	return result;
}
