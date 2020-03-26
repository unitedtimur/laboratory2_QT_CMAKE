#include "include/CPP/CPP_PrintUnit.h"

CPP_PrintUnit::CPP_PrintUnit(QString text) :
	_text(text)
{
}

QString CPP_PrintUnit::compile(const Configuration::UI& level) const
{
	return this->generateShift(level) + "printf( \"" + _text + "\" );\n";
}

QString CPP_PrintUnit::generateShift(const Configuration::UI& level) const
{
	QString result;

	for (Configuration::UI i = 0; i < level; ++i)
		result += '\t';

	return result;
}
