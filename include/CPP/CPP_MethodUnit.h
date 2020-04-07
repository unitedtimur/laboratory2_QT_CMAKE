#pragma once

#include "include/MethodUnit.h"

class CPP_MethodUnit : public MethodUnit
{

public:
	explicit CPP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
	void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
	std::string compile(const Configuration::UI& level) const override;
};

inline CPP_MethodUnit::CPP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
	MethodUnit(name, returnType, flags)
{
}

inline void CPP_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
	_body.push_back(unit);
}

inline std::string CPP_MethodUnit::compile(const Configuration::UI& level) const
{
	std::string result = generateShift(level);

	if (_flags & Configuration::Modifier::STATIC)
		result += "static ";
	else if (_flags & Configuration::Modifier::VIRTUAL)
		result += "virtual ";

	result += _returnType + ' ' + _name + "()";

	if (_flags & Configuration::Modifier::CONST)
		result += " const";

	result += " {\n";

	for (const auto& it : _body)
		result += it->compile(level + 1);

	result += generateShift(level) + "}\n";

	return result;
}
