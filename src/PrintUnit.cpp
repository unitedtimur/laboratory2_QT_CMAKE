#include "include/PrintUnit.h"

PrintUnit::PrintUnit(QString text) :
	_text(std::move(text))
{
}