#ifndef PRINT_UNIT_H
#define PRINT_UNIT_H

#include <memory>
#include <string>

using Flag = unsigned int;

class PrintUnit
{
public:
	virtual ~PrintUnit() = default;
	virtual void add(const std::shared_ptr<PrintUnit>& printUnit, const Flag& flag) = 0;
	virtual std::string compile(const Flag& flag) = 0;
	virtual std::string generateShift(const Flag& flag) = 0;
};

#endif // PRINT_UNIT_H