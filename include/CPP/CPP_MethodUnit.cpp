#include "include/CPP/CPP_MethodUnit.h"

CPP_MethodUnit::CPP_MethodUnit(QString name, QString returnType, const Configuration::Flags& flags) :
	_name(name),
	_returnType(returnType),
	_flags(flags)
{
}

void CPP_MethodUnit::add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags)
{
	_body.push_back(unit);
}

QString CPP_MethodUnit::compile(const Configuration::UI& level) const
{
	QString result = this->generateShift(level);

	if (_flags & Configuration::Modifier::STATIC)
		result += "static ";
	else if (_flags & Configuration::Modifier::VIRTUAL)
		result += "virtual ";

	result += _returnType + " " + _name + "()";

	if (_flags & Configuration::Modifier::CONST)
		result += " const";

	result += " {\n";

	for (const auto& it : _body)
		result += it->compile(level + 1);

	result += this->generateShift(level) + "}\n";

	return result;
}

QString CPP_MethodUnit::generateShift(const Configuration::UI& level) const
{
	QString result;

	for (Configuration::UI i = 0; i < level; ++i)
		result += '\t';

	return result;
}
