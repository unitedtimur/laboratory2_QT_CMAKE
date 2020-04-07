#pragma once

#include "include/Configuration.h"
#include "include/ClassUnit.h"
#include "include/MethodUnit.h"
#include "include/PrintUnit.h"

// Абстрактная фабрика с дефолтным конструктором и методами, возвращающие smart pointers ( shared_ptr ) на Класс / Метод / ВыводЮнит
class AbstractFactory
{
public:
	virtual std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags = 0, const Configuration::Flags& modFlags = 0) const = 0;
	virtual std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const = 0;
	virtual std::shared_ptr<PrintUnit> CreatePrintOperatorUnit(const std::string& text) const = 0;
	virtual ~AbstractFactory() = default;
};
