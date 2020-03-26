#include <utility>
#include "include/ClassUnit.h"

ClassUnit::ClassUnit(QString name) :
	_name(std::move(name))
{
	_fields.resize(Configuration::ACCESS_MODIFIERS.size());
}

void ClassUnit::add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags)
{
	quint32 accMod = Configuration::AccessModifier::PRIVATE;

	if (flags < quint32(Configuration::ACCESS_MODIFIERS.size()))
		accMod = flags;

	_fields[accMod].push_back(unit);
}
