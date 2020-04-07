#pragma once

#include "include/AbstractFactory.h"
#include "include/JAVA/JAVA_ClassUnit.h"
#include "include/JAVA/JAVA_MethodUnit.h"
#include "include/JAVA/JAVA_PrintUnit.h"

class JAVA_AbstractFactory : public AbstractFactory
{
public:
	std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags, const Configuration::Flags& modFlags = 0) const override;
	std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const override;
	std::shared_ptr<PrintUnit> CreatePrintOperatorUnit(const std::string& text) const override;
	~JAVA_AbstractFactory() override = default;
};

inline std::shared_ptr<ClassUnit> JAVA_AbstractFactory::CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags, const Configuration::Flags& /*modFlags*/) const
{
	return std::make_shared<JAVA_ClassUnit>(name, accFlags);
}

inline std::shared_ptr<MethodUnit> JAVA_AbstractFactory::CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const
{
	return std::make_shared<JAVA_MethodUnit>(name, returnType, flags);
}

inline std::shared_ptr<PrintUnit> JAVA_AbstractFactory::CreatePrintOperatorUnit(const std::string& text) const
{
	return std::make_shared<JAVA_PrintUnit>(text);
}
