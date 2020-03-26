#include "include/CPP/CPP_ClassUnit.h"


CPP_ClassUnit::CPP_ClassUnit(const QString& name) :
	ClassUnit(name)
{
	_fields.resize(0x03);
}

void CPP_ClassUnit::add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags)
{
	quint32 accMod = Configuration::AccessModifier::PRIVATE;

	if (flags < 0x03)
		accMod = flags;

	_fields[accMod].push_back(unit);
}

QString CPP_ClassUnit::compile(const Configuration::UI& level) const
{
	QString result = generateShift(level) + "class " + _name + " {\n";

	for (qint32 i = 0x0; i < 0x03; ++i)
	{
		if (_fields[i].isEmpty())
			continue;

		result += Configuration::ACCESS_MODIFIERS[i] + ":\n";

		for (const auto& field : _fields[i])
			result += field->compile(level + 1);

		result += '\n';
	}

	result += generateShift(level) + "};\n";

	return result;
}