#ifndef CPP_METHOD_UNIT_H
#define CPP_METHOD_UNIT_H

#include "include/MethodUnit.h"

class CPP_MethodUnit final : public MethodUnit
{
public:
	explicit CPP_MethodUnit(QString name, QString returnType, const Configuration::Flags& flags);
	~CPP_MethodUnit() override = default;

	void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags) override;
	QString compile(const Configuration::UI& level) const override;

protected:
	QString generateShift(const Configuration::UI& level) const override;

private:
	QString					_name;
	QString					_returnType;
	Configuration::Flags	_flags;
	Configuration::Fields	_body;
};

#endif // CPP_METHOD_UNIT_H