#pragma once

#include "include/MethodUnit.h"

class CSHARP_MethodUnit : public MethodUnit
{

public:
	explicit CSHARP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
	void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
	std::string compile(const Configuration::UI& level) const override;
};

inline CSHARP_MethodUnit::CSHARP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
	MethodUnit(name, returnType, flags)
{
}

inline void CSHARP_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
	_body.push_back(unit);
}

inline std::string CSHARP_MethodUnit::compile(const Configuration::UI& level) const
{
	std::string result;

	if (_flags & Configuration::Modifier::ABSTRACT && !(_flags & Configuration::Modifier::ASYNC))
		result += "abstract ";

	if (_flags & Configuration::Modifier::SEALED)
		result += "sealed ";

	if (_flags & Configuration::Modifier::ASYNC)
		result += "async ";

	if (_flags & Configuration::Modifier::UNSAFE)
		result += "unsafe ";

	if (_flags & Configuration::Modifier::VIRTUAL)
		result += "virtual ";

	if (_flags & Configuration::Modifier::STATIC)
		result += "static ";

	result += _returnType + ' ' + _name + "()" + " {\n";

	for (const auto& it : _body)
		result += it->compile(level + 1);

	result += generateShift(level) + "}\n";

	return result;
}
