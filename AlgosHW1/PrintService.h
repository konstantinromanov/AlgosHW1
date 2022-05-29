#pragma once
#include<iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <fstream>
#include <iomanip> 
#include <utility>
#include <vector>
#include <map>
//
//class PrintService
//{
//
//private:
//
//	template<typename T>
//	std::string toString(T val)
//	{
//		std::stringstream ss("");
//		ss << val;
//		return ss.str();
//	};
//
//public:
//
//	PrintService()
//	{
//
//	};
//
//	void PrintTestResult(int testNumber, bool testResult) {
//		std::cout
//			<< std::left << std::setw(5) << "Test "
//			<< std::right << std::setw(2) << testNumber << ": "
//			<< std::setw(5) << (testResult == true ? "passed" : "not passed") << std::endl;
//	};
//
//	void PrintLine(int lenght) 
//	{
//		std::cout << std::string(lenght, '-') << std::endl;
//	}
//
//	template<typename T>
//	void PrintIntermidiateResults(Stack<T> stack, std::string resultExpression, std::string currentStr = "", int iteration = -1)
//	{
//		std::string stackStr;
//		int lenght = 75;
//		std::map<std::string, int> colWidth{
//			std::pair<std::string, int>("element", 10),
//			std::pair<std::string, int>("stack", 25),
//			std::pair<std::string, int>("result", 50)
//		};
//
//		for (size_t i = 0; i < stack.size(); i++)
//		{
//			stackStr += toString(stack.elementAt(i)) + ' ';
//		}
//
//		if (iteration == 0)
//		{
//			PrintLine(lenght);
//			std::cout
//				<< std::left << std::setw(colWidth.at("element")) << "Element"
//				<< std::setw(colWidth.at("stack")) << "Stack"
//				<< std::left << std::setw(colWidth.at("result")) << "Result" << std::endl;
//			PrintLine(lenght);
//		}
//
//		std::cout
//			<< std::left << std::setw(colWidth.at("element")) << "  " + currentStr
//			<< std::setw(colWidth.at("stack")) << stackStr
//			<< std::left << std::setw(colWidth.at("result")) << resultExpression << std::endl;
//	};
//
//	void PrintMenu(std::vector<std::string>& menuItems)
//	{
//		PrintLine(30);
//		std::cout << std::setw(10) << "Menu" << std::endl;
//
//		for (size_t i = 0; i < menuItems.size(); i++)
//		{
//			std::cout << i + 1 << ' ' << menuItems[i] << std::endl;
//		}
//	};
//};

