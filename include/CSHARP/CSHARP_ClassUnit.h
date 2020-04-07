#pragma once

#include "include/ClassUnit.h"

class CSHARP_ClassUnit : public ClassUnit
{
public:
	explicit CSHARP_ClassUnit(const std::string& name, const Configuration::Flags& flags = Configuration::AccessModifier::PRIVATE);
	void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
	std::string compile(const Configuration::UI& level) const override;

private:
	Configuration::Flags _accMod;
};

inline CSHARP_ClassUnit::CSHARP_ClassUnit(const std::string& name, const Configuration::Flags& flags) :
	ClassUnit(name),
	_accMod(flags)
{
	_fields.resize(0x06);
}

inline void CSHARP_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
	unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

	if (flags < 0x06)
		accessModifier = flags;

	_fields[accessModifier].push_back(unit);
;}

inline std::string CSHARP_ClassUnit::compile(const Configuration::UI& level) const
{
	std::string result = generateShift(level) + Configuration::ACCESS_MODIFIERS[_accMod] + " class " + _name + " {\n";

	for (size_t i = 0; i < _fields.size(); ++i)
	{
		if (_fields[i].empty())
			continue;

		for (const auto& field : _fields[i])
			result += generateShift(level + 1) + Configuration::ACCESS_MODIFIERS[i] + ' ' + field->compile(level + 1);

		result += '\n';
	}

	result += generateShift(level) + "};\n";

	return result;
}