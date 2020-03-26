#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QVector>

class Unit;

namespace Configuration
{
	using Flags		= unsigned int;
	using UI		= unsigned int;
	using Fields = QVector<std::shared_ptr<Unit>>;

	enum AccessModifier : int
	{
		PUBLIC,
		PROTECTED,
		PRIVATE
	};

	static const QVector<QString> ACCESS_MODIFIERS = {
		"public",
		"protected",
		"private"
	};


}

#endif // CONFIGURATION_H