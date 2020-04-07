#pragma once

#include "include/PrintUnit.h"

class CSHARP_PrintUnit : public PrintUnit
{
public:
	explicit CSHARP_PrintUnit(const std::string& text);
	void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override {}
	std::string compile(const Configuration::UI& level) const override;
};

inline CSHARP_PrintUnit::CSHARP_PrintUnit(const std::string& text) :
	PrintUnit(text)
{
}

inline std::string CSHARP_PrintUnit::compile(const Configuration::UI& level) const
{
	return generateShift(level) + "Console.WriteLine( \"" + _text + "\" );\n";
}
