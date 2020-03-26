#include <utility>
#include "include/ClassUnit.h"

ClassUnit::ClassUnit(QString name) :
	_name(std::move(name))
{
	_fields.resize(Configuration::ACCESS_MODIFIERS.size());
}

QString ClassUnit::generateShift(const Configuration::UI& level) const
{
	QString result;

	for (Configuration::UI i = 0; i < level; ++i)
		result += '\t';

	return result;
}

