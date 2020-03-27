#include "include/CPP/CPP_AbstractFactory.h"
#include "include/CPP/CPP_ClassUnit.h"
#include "include/CPP/CPP_MethodUnit.h"

int main(int argc, char* argv[])
{
	QString result;

	AbstractFactory* abstractFactory = new CPP_AbstractFactory;

	std::shared_ptr<CPP_ClassUnit> myClass(abstractFactory->createClassUnit("MyClass"));
	myClass->add(std::make_shared<CPP_MethodUnit>(abstractFactory->))

}
