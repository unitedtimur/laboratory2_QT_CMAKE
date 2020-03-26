#ifndef METHOD_UNIT_H
#define METHOD_UNIT_H

#include <memory>
#include <string>

using Flag = unsigned int;

class MethodUnit
{
public:
	virtual ~MethodUnit() = default;
	virtual void add(const std::shared_ptr<MethodUnit>& printUnit, const Flag& flag) = 0;
	virtual std::string compile(const Flag& flag) = 0;
	virtual std::string generateShift(const Flag& flag) = 0;
};

#endif // METHOD_UNIT_H