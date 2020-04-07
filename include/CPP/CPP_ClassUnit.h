#pragma once

#include "include/ClassUnit.h"

class CPP_ClassUnit : public ClassUnit
{
public:
	explicit CPP_ClassUnit(const std::string& name);
	void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
	std::string compile(const Configuration::UI& level) const override;
};

inline CPP_ClassUnit::CPP_ClassUnit(const std::string& name) :
	ClassUnit(name)
{
	_fields.resize(0x03);
}

inline void CPP_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
	unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

	if (flags < 0x03)
		accessModifier = flags;

	_fields[accessModifier].push_back(unit);
}

inline std::string CPP_ClassUnit::compile(const Configuration::UI& level) const
{
	std::string result = generateShift(level) + "class " + _name + " {\n";

	for (size_t i = 0; i < _fields.size(); ++i)
	{
		if (_fields[i].empty())
			continue;

		result += Configuration::ACCESS_MODIFIERS[i] + ":\n";

		for (const auto& it : _fields[i])
		{
			result += it->compile(level + 1);
		}

		result += '\n';
	}

	result += generateShift(level) + "};\n";

	return result;
}
