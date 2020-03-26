#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QVector>

class Unit;

namespace Configuration
{
	using Flags		= unsigned int;
	using UI		= unsigned int;
	using Fields	= QVector<std::shared_ptr<Unit>>;

	enum AccessModifier : quint32
	{
		PUBLIC,
		PROTECTED,
		PRIVATE
	};

	enum Modifier : quint32
	{
		STATIC	= 0x01,
		CONST	= 0x02,
		VIRTUAL	= 0x04
	};

	static const QVector<QString> ACCESS_MODIFIERS = {
		"public",
		"protected",
		"private"
	};


}

#endif // CONFIGURATION_H