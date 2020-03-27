#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include "include/Configuration.h"

/*
 * Forward declarations
 */
class ClassUnit;
class MethodUnit;
class PrintUnit;

class AbstractFactory
{
public:
	virtual ~AbstractFactory() = default;
	virtual ClassUnit* createClassUnit(QString name, Configuration::Flags flags = 0) const = 0;
    virtual MethodUnit* CreateMethodUnit(const std::string& name, const std::string& returnType, Configuration::Flags flags) const = 0;
    virtual PrintUnit* CreatePrintOperatorUnit(const std::string& text) const = 0;
};

#endif // ABSTRACT_FACTORY_H