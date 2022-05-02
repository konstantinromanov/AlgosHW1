// AlgosHW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip> 
#include <utility>
#include <windows.h>
#include <fstream>
#include "ArrayBase.h"
#include "Stack.h"
#include "Queue.h"
#include "PrintService.h"
#include "ConversionService.h"
#include "App.h"
#include "Tests.h"

using namespace std;

int main()
{	
	PrintService printService = PrintService();
	ConversionService conversionService = ConversionService(printService);
	App app = App(printService);
	Tests tests = Tests(printService, conversionService);

	app.RunApp(); // App implements task 3 of the Homework.
	tests.RunTests(); // Homework task 1 is printed as Test 12 to console, task 2 - as Test 22.
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
