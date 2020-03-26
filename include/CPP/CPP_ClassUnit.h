#ifndef CPP_CLASS_UNIT_H
#define CPP_CLASS_UNIT_H

#include "include/ClassUnit.h"

class CPP_ClassUnit final : public ClassUnit
{
public:
	explicit CPP_ClassUnit(const QString& name);
	~CPP_ClassUnit() override = default;
	
	void add(const std::shared_ptr<Unit>& unit, const Configuration::Flags& flags) override;
	QString compile(const Configuration::UI& level = 0) const override;

protected:
	QString							_name;
	QVector<Configuration::Fields>	_fields;
};

#endif // CPP_CLASS_UNIT_H