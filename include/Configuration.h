#pragma once

#include <memory>
#include <vector>
#include <string>

class Unit;

// Конфигурационный "файл" для упрощения работы с фабрикой
namespace Configuration
{
	typedef std::shared_ptr<Unit> Ptr;
	using Flags		= unsigned int;
	using UI		= unsigned int;
	using Fields	= std::vector<std::vector<std::shared_ptr<Unit>>>;
	using Body		= std::vector<std::shared_ptr<Unit>>;

	enum AccessModifier : unsigned
	{
		PUBLIC = 0x00,
		PROTECTED,
		PRIVATE,
		INTERNAL,
		PROTECTED_INTERNAL,
		PRIVATE_PROTECTED
	};

	enum Modifier : unsigned
	{
		STATIC			= 0x01,
		CONST			= 0x02,
		VIRTUAL			= 0x04,
		ABSTRACT		= 0x08,
		ASYNC			= 0x10,
		UNSAFE			= 0x20,
		SEALED			= 0x40,
		FINAL			= SEALED,
		SYNCHRONIZED	= 0x80
	};

	static const std::vector<std::string> ACCESS_MODIFIERS = {
		"public",
		"protected",
		"private",
		"internal",
		"protected internal",
		"private protected"
	};
}