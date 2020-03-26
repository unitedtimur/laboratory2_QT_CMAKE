#include <utility>
#include "include/MethodUnit.h"

MethodUnit::MethodUnit(QString name, QString returnType, const Configuration::Flags& flags) :
	_name(std::move(name)),
	_returnType(std::move(returnType)),
	_flags(flags)
{
}

void MethodUnit::add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& /*flags*/)
{
	_body.push_back(unit);
}
