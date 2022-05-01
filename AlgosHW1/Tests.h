#pragma once
#include "ConversionService.h"

class Tests
{

private:

	ConversionService m_conversionService;
	PrintService m_printService;

public:
		
	Tests(PrintService printService, ConversionService conversionService);
	void RunTests();
};

