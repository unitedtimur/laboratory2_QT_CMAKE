#include "include/CPP/CPP_AbstractFactory.h"

#include "CPP_ClassUnit.h"
#include "CPP_MethodUnit.h"

ClassUnit* CPP_AbstractFactory::createClassUnit(QString name, Configuration::Flags flags) const
{
	return new CPP_ClassUnit(name);
}

MethodUnit* CPP_AbstractFactory::CreateMethodUnit(const std::string& name, const std::string& returnType, Configuration::Flags flags) const
{
	return new CPP_MethodUnit(name, returnType);
}
