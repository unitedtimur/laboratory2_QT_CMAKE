#pragma once

#include "include/ClassUnit.h"

class JAVA_ClassUnit : public ClassUnit
{
public:
	explicit JAVA_ClassUnit(const std::string& name, const Configuration::Flags& flags = Configuration::AccessModifier::PUBLIC, const Configuration::Flags& accMod = 0);
	void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
	std::string compile(const Configuration::UI& level) const override;

private:
	Configuration::Flags _accMod;
	Configuration::Flags _classMod;
};

inline JAVA_ClassUnit::JAVA_ClassUnit(const std::string& name, const Configuration::Flags& flags, const Configuration::Flags& accMod) :
	ClassUnit(name),
	_accMod(flags),
	_classMod(0x00)
{
	_fields.resize(0x03);

	if (_accMod & Configuration::Modifier::FINAL)
		_classMod |= Configuration::Modifier::FINAL;
	else if (_accMod & Configuration::Modifier::ABSTRACT)
		_classMod |= Configuration::Modifier::ABSTRACT;
}

inline void JAVA_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
	unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

	if (flags < 0x03)
		accessModifier = flags;

	_fields[accessModifier].push_back(unit);
;}

inline std::string JAVA_ClassUnit::compile(const Configuration::UI& level) const
{
	std::string accMod = Configuration::ACCESS_MODIFIERS[_accMod] + ' ';
	std::string classMod;

	if (_classMod & Configuration::Modifier::FINAL)
		classMod = "final ";
	else if (_classMod & Configuration::Modifier::ABSTRACT)
		classMod = "abstract ";

	std::string result = generateShift(level) + accMod + classMod + "class " + _name + " {\n";

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