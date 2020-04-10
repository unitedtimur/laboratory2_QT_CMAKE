#include <iostream>

#include "include/CPP/CPP_AbstractFactory.h"
#include "include/CSHARP/CSHARP_AbstractFactory.h"
#include "include/JAVA/JAVA_AbstractFactory.h"

std::string generate();

int main(int argc, char* argv[])
{
	// Для проверки на утечку памяти
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Пример утечки, раскомментируйте, чтобы посмотреть что выведет консоль ( она укажет на не очищенную область в ОП )
	//int* a = new int;

	std::cout << generate() << std::endl;

	// Нажмите 'enter'
	return getchar();
}

std::string generate()
{
	std::string result;

	for (int i = 0; i < 3; ++i)
	{
		std::shared_ptr<AbstractFactory> factory;

		switch (i)
		{
			// создаём фабрику языка c++
		case 0:
			factory = std::make_shared<CPP_AbstractFactorty>();
			break;

			// создаём фабрику языка c#
		case 1:
			factory = std::make_shared<CSHARP_AbstractFactory>();
			break;

			// создаём фабрику языка java
		case 2:
			factory = std::make_shared<JAVA_AbstractFactory>();
			break;

			// невозможная ситуация для данного цикла, но в случае если попадём сюда, то ничего критичного не случится
			// этот аттрибут используются в основном для case`ов сообщающий компилятору, что break не обязателен
		default: [[__fallthrough]];
		}

		// smart ptr класса (инициализируем)
		std::shared_ptr<ClassUnit> myClass(factory->CreateClassUnit("MyClass"));
		// smart ptr метода (инициализируем)
		std::shared_ptr<Unit> method(factory->CreateMethodUnit("testFunc4", "void", Configuration::Modifier::STATIC));

		// добавляем в класс юниты (функции)
		myClass->add(factory->CreateMethodUnit("testFunc1", "void", 0), Configuration::AccessModifier::PUBLIC);
		myClass->add(factory->CreateMethodUnit("testFunc2", "void", Configuration::Modifier::STATIC), Configuration::AccessModifier::PRIVATE);
		myClass->add(factory->CreateMethodUnit("testFunc3", "void", Configuration::Modifier::VIRTUAL | Configuration::Modifier::CONST), Configuration::AccessModifier::PUBLIC);

		// производим дополнение в методе как добавление вывода текста
		method->add(factory->CreatePrintOperatorUnit("Hello, UnitedTimur! ;)"));

		// добавляем этот метод в класс
		myClass->add(method, Configuration::AccessModifier::PROTECTED);

		// производим генерацию
		result += myClass->compile() + '\n';
	}

	// возвращаем результат
	return result;
}