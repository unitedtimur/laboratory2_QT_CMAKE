#ifndef CPP_ABSTRACT_FACTORY_H
#define CPP_ABSTRACT_FACTORY_H

#include "include/AbstractFactory.h"

class CPP_AbstractFactory final : public AbstractFactory
{
public:
	ClassUnit* createClassUnit(QString name, Configuration::Flags flags) const override;
	MethodUnit* CreateMethodUnit(const std::string& name, const std::string& returnType, Configuration::Flags flags) const override;
	PrintUnit* CreatePrintOperatorUnit(const std::string& text) const override;
	~CPP_AbstractFactory() override = default;
};

#endif // CPP_ABSTRACT_FACTORY_H
