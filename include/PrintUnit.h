#pragma once

#include <utility>
#include "include/Unit.h"

// Абстрактный класс ВыводЮнит ( не интерфейс! )
class PrintUnit : public Unit
{
public:
	explicit PrintUnit(std::string text);

	void add(const Configuration::Ptr&, const Configuration::Flags& flags) override {}
	std::string compile(const Configuration::UI& level) const override = 0;

protected:
	std::string _text;
};

inline PrintUnit::PrintUnit(std::string text) :
	_text(std::move(text))
{
}