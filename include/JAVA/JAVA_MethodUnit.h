#pragma once

#include "include/MethodUnit.h"

class JAVA_MethodUnit : public MethodUnit
{

public:
	explicit JAVA_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
	void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
	std::string compile(const Configuration::UI& level) const override;
};

inline JAVA_MethodUnit::JAVA_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
	MethodUnit(name, returnType, flags)
{
}

inline void JAVA_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
	_body.push_back(unit);
}

inline std::string JAVA_MethodUnit::compile(const Configuration::UI& level) const
{
	std::string result;

	if (_flags & Configuration::Modifier::SYNCHRONIZED)
		result += "synchronized ";

	if (_flags & Configuration::Modifier::STATIC)
		result += "static ";

	if (_flags & Configuration::Modifier::ABSTRACT)
		result += "abstract ";
	else if (_flags & Configuration::Modifier::FINAL)
		result += "final ";

	result += _returnType + ' ' + _name + "()" + " {\n";

	for (const auto& it : _body)
		result += it->compile(level + 1);

	result += generateShift(level) + "}\n";

	return result;
}
