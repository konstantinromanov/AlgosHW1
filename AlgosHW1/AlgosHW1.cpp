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
//#include <windows.h>
#include <fstream>
//#include "ArrayBase.h"
//#include "Stack.h"
//#include "Queue.h"
//#include "PrintService.h"
//#include "ConversionService.h"
//#include "App.h"
//#include "Tests.h"
#include <cmath>
#include <algorithm>

using namespace std;

// ------------------------------------------- ArrayBase -----------------------------------------------

template<typename T>
class ArrayBase {

private:

	static const int m_defaultSize = 5;
	T* storeArray;
	int m_capacity;
	int m_currentCount = 0;

protected:

	void resetSize();
	void incCount();
	void decCount();
	int add(T);
	void removeAt(int);
	T& operator[](int);

public:

	ArrayBase(int arraySize = m_defaultSize);
	bool isEmpty() const;
	int size();
	int capacity();
	bool isFull();
	T virtual elementAt(int);
	virtual void clear() = 0;
};

//typedef ArrayBase<int>;
//typedef ArrayBase<double>;
//typedef ArrayBase<char>;
//typedef ArrayBase<std::string>;

// ------------------------------------------- End of ArrayBase Header -----------------------------------------------

template<typename T>
void ArrayBase<T>::resetSize() {
	m_currentCount = 0;
}

template<typename T>
void ArrayBase<T>::incCount() {

	if (isFull())
	{
		throw std::out_of_range("Array is already full");
	}

	m_currentCount++;
}

template<typename T>
void ArrayBase<T>::decCount() {

	if (m_currentCount == 0)
	{
		throw std::out_of_range("Array is already empty");
	}

	m_currentCount--;
}

template<typename T>
int ArrayBase<T>::add(T obj) {

	if (!isFull())
	{
		storeArray[m_currentCount++] = obj;
		return  m_currentCount;
	}

	return -1;
}

template<typename T>
void ArrayBase<T>::removeAt(int index) {

	if (index < 0 || index > m_currentCount - 1)
	{
		throw std::invalid_argument("Imposible to remove");
	}

	for (size_t i = index; i < m_currentCount - 1; i++)
	{
		storeArray[i] = storeArray[i + 1];
	}

	m_currentCount--;
}

template<typename T>
T& ArrayBase<T>::operator[](int index) {

	if (index < 0 || index > m_capacity - 1)
	{
		throw std::invalid_argument("Index is outside of range");
	}

	return storeArray[index];
}

template<typename T>
ArrayBase<T>::ArrayBase(int arraySize) {
	m_capacity = arraySize <= m_defaultSize ? m_defaultSize : arraySize;
	storeArray = new T[m_capacity];
}

template<typename T>
bool ArrayBase<T>::isEmpty() const {
	return m_currentCount == 0;
}

template<typename T>
int ArrayBase<T>::size() {
	return m_currentCount;
}

template<typename T>
int ArrayBase<T>::capacity() {
	return m_capacity;
}

template<typename T>
bool ArrayBase<T>::isFull() {
	return m_currentCount == m_capacity;
}

template<typename T>
T ArrayBase<T>::elementAt(int index) {

	if (index < 0 || index > m_currentCount - 1)
	{
		throw std::invalid_argument("Index is outside of range");
	}

	return storeArray[index];
}

template class ArrayBase<int>;
template class ArrayBase<double>;
template class ArrayBase<char>;
template class ArrayBase<std::string>;

// ------------------------------------------- End of ArrayBase -----------------------------------------------

// ------------------------------------------- Queue -----------------------------------------------

template<typename T>
class Queue : public ArrayBase<T> {

private:

	int m_first = 0;
	int m_last = -1;

public:

	Queue(int);
	Queue();
	bool enqueue(T);
	T dequeue();
	void display();
	void clear();
	T elementAt(int) override;
};

//typedef Queue<int>;
//typedef Queue<double>;
//typedef Queue<char>;
//typedef Queue<std::string>;

// ------------------------------------------- End of Queue Header -----------------------------------------------

template<typename T>
Queue<T>::Queue(int queueSize) : ArrayBase<T>(queueSize) {

}

template<typename T>
Queue<T>::Queue() : ArrayBase<T>()
{

}

template<typename T>
bool Queue<T>::enqueue(T next) {

	ArrayBase<T>::incCount();
	m_last = (m_last + 1) % ArrayBase<T>::capacity();
	ArrayBase<T>::operator[](m_last) = next;

	return true;
}

template<typename T>
T Queue<T>::dequeue() {
	int dequeuIndex = m_first;
	ArrayBase<T>::decCount();
	m_first = (m_first + 1) % ArrayBase<T>::capacity();

	return ArrayBase<T>::operator[](dequeuIndex);
}

template<typename T>
void Queue<T>::display() {

	for (int i = 0; i < ArrayBase<T>::size(); i++)
	{
		T el = ArrayBase<T>::operator[]((m_first + i) % ArrayBase<T>::capacity());
		std::cout << el << ' ';
	}
}

template<typename T>
void Queue<T>::clear() {
	m_first = 0;
	m_last = -1;
	ArrayBase<T>::resetSize();
}

template<typename T>
T Queue<T>::elementAt(int index) {

	if (index < 0 || index > ArrayBase<T>::size() - 1)
	{
		throw std::invalid_argument("Index is outside of range");
	}

	return ArrayBase<T>::operator[]((m_first + index) % ArrayBase<T>::capacity());
}

template class Queue<int>;
template class Queue<double>;
template class Queue<char>;
template class Queue<std::string>;

// ------------------------------------------- End of Queue -----------------------------------------------


// ------------------------------------------- Stack -----------------------------------------------

template<typename T>
class Stack : public ArrayBase<T> {

public:

	Stack(int);
	Stack();
	void push(T);
	T pop();
	T peek();
	void display();
	void clear();
};

//typedef Stack<int>;
//typedef Stack<double>;
//typedef Stack<char>;
//typedef Stack<std::string>;

// ------------------------------------------- End of Stack Header -----------------------------------------------

template<typename T>
Stack<T>::Stack(int stackSize) : ArrayBase<T>(stackSize)
{

}

template<typename T>
Stack<T>::Stack() : ArrayBase<T>()
{

}

template<typename T>
void Stack<T>::push(T arg) {

	if (ArrayBase<T>::isFull())
	{
		throw std::out_of_range("Stack is already full");
	}

	ArrayBase<T>::add(arg);
}

template<typename T>
T Stack<T>::pop() {

	if (ArrayBase<T>::size() == 0)
	{
		throw std::out_of_range("Stack is empty");
	}

	T arg = ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
	ArrayBase<T>::decCount();

	return arg;
}

template<typename T>
T Stack<T>::peek() {

	if (ArrayBase<T>::size() == 0)
	{
		throw std::out_of_range("Stack is empty");
	}

	return ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
}

template<typename T>
void Stack<T>::display() {

	for (int i = 0; i < ArrayBase<T>::size(); i++)
	{
		T el = ArrayBase<T>::elementAt(i);
		std::cout << el << ' ';
	}
}

template<typename T>
void Stack<T>::clear() {
	ArrayBase<T>::resetSize();
}

template class Stack<int>;
template class Stack<double>;
template class Stack<char>;
template class Stack<std::string>;

// ------------------------------------------- End of Stack -----------------------------------------------


// ------------------------------------------- Print Service -----------------------------------------------

class PrintService
{

private:

	template<typename T>
	std::string toString(T val)
	{
		std::stringstream ss("");
		ss << val;
		return ss.str();
	};

public:

	PrintService()
	{

	};

	void PrintTestResult(int testNumber, bool testResult) {
		std::cout
			<< std::left << std::setw(5) << "Test "
			<< std::right << std::setw(2) << testNumber << ": "
			<< std::setw(5) << (testResult == true ? "passed" : "not passed") << std::endl;
	};

	void PrintLine(int lenght)
	{
		std::cout << std::string(lenght, '-') << std::endl;
	}

	template<typename T>
	void PrintIntermidiateResults(Stack<T> stack, std::string resultExpression, std::string currentStr = "", int iteration = -1)
	{
		std::string stackStr;
		int lenght = 75;
		std::map<std::string, int> colWidth{
			std::pair<std::string, int>("element", 10),
			std::pair<std::string, int>("stack", 25),
			std::pair<std::string, int>("result", 50)
		};

		for (size_t i = 0; i < stack.size(); i++)
		{
			stackStr += toString(stack.elementAt(i)) + ' ';
		}

		if (iteration == 0)
		{
			PrintLine(lenght);
			std::cout
				<< std::left << std::setw(colWidth.at("element")) << "Element"
				<< std::setw(colWidth.at("stack")) << "Stack"
				<< std::left << std::setw(colWidth.at("result")) << "Result" << std::endl;
			PrintLine(lenght);
		}

		std::cout
			<< std::left << std::setw(colWidth.at("element")) << "  " + currentStr
			<< std::setw(colWidth.at("stack")) << stackStr
			<< std::left << std::setw(colWidth.at("result")) << resultExpression << std::endl;
	};

	void PrintMenu(std::vector<std::string>& menuItems)
	{
		PrintLine(30);
		std::cout << std::setw(10) << "Menu" << std::endl;

		for (size_t i = 0; i < menuItems.size(); i++)
		{
			std::cout << i + 1 << ' ' << menuItems[i] << std::endl;
		}
	};
};

// ------------------------------------------- End of Print Service -----------------------------------------------


// ------------------------------------------- Conversion Service -----------------------------------------------

class ConversionService
{

private:

	PrintService m_printService;
	bool isNumber(const std::string&);

public:

	ConversionService(PrintService);
	ConversionService();
	std::string ConvertInfixToPostfix(std::string);
	double EvaluatePostfix(std::string);
};

// ------------------------------------------- End of Conversion Service Header -----------------------------------------------

bool ConversionService::isNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}

	return true;
}


ConversionService::ConversionService(PrintService printService)
{
	m_printService = printService;
}

ConversionService::ConversionService()
{

}

std::string ConversionService::ConvertInfixToPostfix(std::string expression) {

	expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

	Stack<char> stack = Stack<char>(expression.size());
	std::string resultExpression;
	std::map<char, int> opPrecedence{
		std::pair<char, int>('^', 4),
		std::pair<char, int>('/', 3),
		std::pair<char, int>('*', 3),
		std::pair<char, int>('%', 3),
		std::pair<char, int>('+', 2),
		std::pair<char, int>('-', 2)
	};

	bool prevCharIsOperand = false;

	for (size_t i = 0; i < expression.size(); i++)
	{
		char currentChar = expression[i];

		if (isalpha(currentChar) || isdigit(currentChar) || currentChar == '.' || currentChar == ',')
		{
			if (!prevCharIsOperand && resultExpression.size() != 0)
			{
				resultExpression.push_back(' ');
			}

			resultExpression.push_back(currentChar);
			prevCharIsOperand = true;
		}
		else if (currentChar == ')')
		{
			prevCharIsOperand = false;

			while (stack.peek() != '(')
			{
				resultExpression.push_back(' ');
				resultExpression.push_back(stack.pop());
			}

			stack.pop();
		}
		else if (currentChar == '(')
		{
			prevCharIsOperand = false;
			stack.push(currentChar);
		}
		else
		{
			prevCharIsOperand = false;

			while (!stack.isEmpty()
				&& stack.peek() != '('
				&& !(currentChar == '^' && stack.peek() == '^')
				&& opPrecedence.at(currentChar) <= opPrecedence.at(stack.peek()))
			{
				resultExpression.push_back(' ');
				resultExpression.push_back(stack.pop());
			}

			stack.push(currentChar);
		}

		m_printService.PrintIntermidiateResults(stack, resultExpression, std::string(1, currentChar), i);
	}

	while (!stack.isEmpty())
	{
		resultExpression.push_back(' ');
		resultExpression.push_back(stack.pop());

		m_printService.PrintIntermidiateResults(stack, resultExpression);
	}

	return resultExpression;
}

double ConversionService::EvaluatePostfix(std::string expression) {

	std::stringstream ss(expression);
	std::vector<std::string> words{};
	std::string word;

	while (getline(ss, word, ' '))
	{
		if (word == "")
		{
			continue;
		}

		words.push_back(word.c_str());
	}

	Stack<double> stack = Stack<double>(expression.size());

	for (size_t i = 0; i < words.size(); i++)
	{
		word = words[i];

		if (isNumber(word))
		{
			stack.push(stod(word));
		}
		else
		{
			double secondOperand = double(stack.pop());
			double firstOperand = double(stack.pop());

			double operationResult = 0.0;

			switch (word.at(0))
			{
			case '+':
				operationResult = firstOperand + secondOperand;
				break;
			case '-':
				operationResult = firstOperand - secondOperand;
				break;
			case '*':
				operationResult = firstOperand * secondOperand;
				break;
			case '/':
				operationResult = firstOperand / secondOperand;
				break;
			case '^':
				operationResult = pow(firstOperand, secondOperand);
				break;
			default:
				break;
			}

			stack.push(operationResult);
		}

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << stack.peek();
		m_printService.PrintIntermidiateResults(stack, stream.str(), word, i);
	}

	return stack.pop();
}

// ------------------------------------------- End of Conversion Service -----------------------------------------------


// ------------------------------------------- Tests -----------------------------------------------

class Tests
{

private:

	ConversionService m_conversionService;
	PrintService m_printService;

public:

	Tests(PrintService printService, ConversionService conversionService);
	void RunTests();
};

// ------------------------------------------- End of Tests Header -----------------------------------------------

Tests::Tests(PrintService printService, ConversionService conversionService)
{
	m_conversionService = conversionService;
	m_printService = printService;
}

void Tests::RunTests() {

	int queueLength = 6;
	Queue<int> queue = Queue<int>(queueLength);

	// ---------------------------------- Test 1 ----------------------------------

	for (int i = 0; i < queueLength; i++)
	{
		queue.enqueue(i + 1);
	}

	bool test1 = queue.size() == queueLength;

	m_printService.PrintTestResult(1, test1);

	// ---------------------------------- Test 2 ----------------------------------

	bool test2 = false;

	try
	{
		queue.enqueue(7);
		test2 = false;
	}
	catch (const std::out_of_range&)
	{
		test2 = true;
	}

	m_printService.PrintTestResult(2, test2);

	// ---------------------------------- Test 3 ----------------------------------

	int queueSize = queue.size();

	for (int i = 0; i < 2; i++)
	{
		queue.dequeue();
	}

	queue.enqueue(7);
	queue.enqueue(8);

	for (int i = 0; i < queueSize; i++)
	{
		queue.dequeue();
	}

	bool test3 = queue.size() == 0;

	m_printService.PrintTestResult(3, test3);

	// ---------------------------------- Test 4 ----------------------------------

	bool test4;

	try
	{
		queue.dequeue();
		test4 = false;
	}
	catch (const std::out_of_range&)
	{
		test4 = true;
	}

	m_printService.PrintTestResult(4, test4);

	// ---------------------------------- Test 5 ----------------------------------

	for (size_t i = 0; i < 3; i++)
	{
		queue.enqueue(i + 1);
	}

	queue.clear();

	bool test5 = queue.size() == 0;

	m_printService.PrintTestResult(5, test5);

	// ---------------------------------- Test 6 ----------------------------------

	bool test6 = queue.isEmpty();

	m_printService.PrintTestResult(6, test6);

	// ---------------------------------- Test 7 ----------------------------------

	bool test7 = !queue.isFull();

	m_printService.PrintTestResult(7, test7);

	// ---------------------------------- Test 8 ----------------------------------

	for (size_t i = 0; i < queueLength; i++)
	{
		queue.enqueue(i + 1);
	}

	bool test8 = queue.isFull();

	m_printService.PrintTestResult(8, test8);

	// ---------------------------------- Test 9 ----------------------------------

	bool test9 = "a b c d ^ e - f g h * + ^ * + i -" == m_conversionService.ConvertInfixToPostfix("a + b * (c^d-e)^(f+g*h)-i");

	m_printService.PrintTestResult(9, test9);

	// ---------------------------------- Test 10 ----------------------------------

	bool test10 = "12.3 4 + 15 * 16 -" == m_conversionService.ConvertInfixToPostfix("(12.3+4)*15-16");

	m_printService.PrintTestResult(10, test10);

	// ---------------------------------- Test 11 ----------------------------------

	bool test11 = "A B + C * D -" == m_conversionService.ConvertInfixToPostfix("(A+B)*C-D");

	m_printService.PrintTestResult(11, test11);

	// ---------------------------------- Test 12 ----------------------------------

	bool test12 = "18 3 2 ^ / 9 - 4 6 * +" == m_conversionService.ConvertInfixToPostfix("18/3^2-9+4*6");

	m_printService.PrintTestResult(12, test12);

	// ---------------------------------- Test 13 ----------------------------------

	bool test13 = "A B * C D / +" == m_conversionService.ConvertInfixToPostfix("A*B+C/D");

	m_printService.PrintTestResult(13, test13);

	// ---------------------------------- Test 14 ----------------------------------

	bool test14 = "A B C * E F - / +" == m_conversionService.ConvertInfixToPostfix("A+B*C/(E-F)");

	m_printService.PrintTestResult(14, test14);

	// ---------------------------------- Test 15 ----------------------------------

	bool test15 = "a b + c d - ^ m n + *" == m_conversionService.ConvertInfixToPostfix("(a + b) ^(c - d) * (m + n)");

	m_printService.PrintTestResult(15, test15);

	// ---------------------------------- Test 16 ----------------------------------

	bool test16 = "a b + d c ^ -" == m_conversionService.ConvertInfixToPostfix("a+b-d^c");

	m_printService.PrintTestResult(16, test16);

	// ---------------------------------- Test 17 ----------------------------------

	bool test17 = "10 3 * 15 5 / +" == m_conversionService.ConvertInfixToPostfix("10*3+15/5");

	m_printService.PrintTestResult(17, test17);

	// ---------------------------------- Test 18 ----------------------------------

	bool test18 = "5 10 + 12 9 - * 3 /" == m_conversionService.ConvertInfixToPostfix("(5+10)*(12-9)/3");

	m_printService.PrintTestResult(18, test18);

	// ---------------------------------- Test 19 ----------------------------------

	bool test19 = "a b * c + d ^ a b - c d + / +" == m_conversionService.ConvertInfixToPostfix("(a*b + c)^d+(a-b)/(c+d)");

	m_printService.PrintTestResult(19, test19);

	// ---------------------------------- Test 20 ----------------------------------

	bool test20 = 7 == m_conversionService.EvaluatePostfix("3 2 2 * +");

	m_printService.PrintTestResult(20, test20);

	// ---------------------------------- Test 21 ----------------------------------

	bool test21 = 2 == m_conversionService.EvaluatePostfix("4 2 /");

	m_printService.PrintTestResult(21, test21);

	// ---------------------------------- Test 22 ----------------------------------

	bool test22 = -50.899999999999999 == m_conversionService.EvaluatePostfix("3 30 / 6 3 11 18 36 / + - * + ");

	m_printService.PrintTestResult(22, test22);

	// ---------------------------------- Test 23 ----------------------------------

	bool test23 = -15 == m_conversionService.EvaluatePostfix("3 9 12 - / 10 5 + *");

	m_printService.PrintTestResult(23, test23);

	// ---------------------------------- Test 24 ----------------------------------

	bool test24 = -128 == m_conversionService.EvaluatePostfix("6 7 - 2 3 4 + ^ *");

	m_printService.PrintTestResult(24, test24);

	// ---------------------------------- Test 25 ----------------------------------

	bool test25 = -0.21875 == m_conversionService.EvaluatePostfix("2 25 100 / - 40 6 8 * - /");

	m_printService.PrintTestResult(25, test25);

	// ---------------------------------- Test 26 ----------------------------------

	bool test26 = -0.11111111111111110 == m_conversionService.EvaluatePostfix("1 23 11 17 + - 85 100 - / + 4 64 80 - + /");

	m_printService.PrintTestResult(26, test26);

	// ---------------------------------- Test 27 ----------------------------------

	bool test27 = 0.32122905027932963 == m_conversionService.EvaluatePostfix("4 16 / 6 - 3 30 / 18 - /");

	m_printService.PrintTestResult(27, test27);

	// ---------------------------------- Test 28 ----------------------------------

	bool test28 = "b c * a - a b * c * +" == m_conversionService.ConvertInfixToPostfix("b*c-a+a*b*c");

	m_printService.PrintTestResult(28, test28);

	// ---------------------------------- Test 29 ----------------------------------

	bool test29 = "a b c * a + b * +" == m_conversionService.ConvertInfixToPostfix("a+(b*c+a)*b");

	m_printService.PrintTestResult(29, test29);

	// ---------------------------------- Test 30 ----------------------------------	

	bool test30 = "a b c * + d - l m * n / k ^ *" == m_conversionService.ConvertInfixToPostfix("(a+b*c-d)*((l*m)/n)^k");

	m_printService.PrintTestResult(30, test30);

	// ---------------------------------- Test 31 ----------------------------------

	bool test31 = 30.333333333333332 == m_conversionService.EvaluatePostfix("5 15 / 3 10 * +");

	m_printService.PrintTestResult(31, test31);

	// ---------------------------------- Test 32 ----------------------------------

	bool test32 = -55.333333333333336 == m_conversionService.EvaluatePostfix("12 7 11 * - 1 4 12 / - 9 + +");

	m_printService.PrintTestResult(32, test32);
}

// ------------------------------------------- End of Tests -----------------------------------------------


// ------------------------------------------- App -----------------------------------------------

class App
{

private:

	PrintService m_printService;
	bool readInputFromFile(const std::string&, Queue<std::string>&);
	bool isValidInput(std::string);

public:

	App(PrintService);
	void RunApp();
};

bool App::readInputFromFile(const std::string& path, Queue<std::string>& queue) {

	queue = Queue<std::string>(20);
	std::ifstream file;
	file.open(path);

	if (file.is_open())
	{
		for (std::string s; file >> s;)
		{
			if (!isValidInput(s))
			{
				return false;
			}

			try
			{
				queue.enqueue(s);
			}
			catch (const std::exception&)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool App::isValidInput(std::string input) {

	for (const char c : input)
	{
		if (!isalnum(c))
		{
			return false;
		}
	}

	return true;
}

App::App(PrintService printService) {
	m_printService = printService;
}

void App::RunApp() {

	std::string filePath = "homework1-1.txt"; // place input file in the same directory as this file or provide path with file with '/'s.

	Queue<std::string> queueFromFile;
	bool readSuccess = readInputFromFile(filePath, queueFromFile);

	if (!readSuccess)
	{
		std::cout << "Error while reading file, alphanumeric characters allowed, separated by space." << std::endl;
		std::cout << "You can still enter data manually by adding it to the queue!" << std::endl;
		std::cout << "Queue size is " << queueFromFile.size() << std::endl;
	}

	std::vector<std::string> menuItems = {
		"to add an element",
		"to delete an element",
		"to check whether a queue is empty",
		"to check whether a queue is full",
		"to print a queue",
		"to clear a queue",
		"to output the size of a queue"
	};

	m_printService.PrintMenu(menuItems);

	std::string userInput;
	std::string queueElementInput;
	int choice = 0;
	bool exitProgram = false;

	do
	{
		std::cout << "Choose operation (1 - 7) or 'E' to exit: ";
		std::cin >> userInput;

		if (!isValidInput(userInput))
		{
			std::cout << "invalid input" << std::endl;
			continue;
		}

		try
		{
			choice = stoi(userInput);

			switch (choice)
			{
			case 1:
				std::cout << "Enter a number: ";
				std::cin >> queueElementInput;
				if (queueFromFile.isFull())
				{
					std::cout << "Queue is already full" << std::endl;
				}
				else
				{
					queueFromFile.enqueue(queueElementInput);
					std::cout << "Added " << queueElementInput << " to the end of the queue!" << std::endl;
				}
				break;
			case 2:
				if (queueFromFile.isEmpty())
				{
					std::cout << "Queue is already empty" << std::endl;
				}
				else
				{
					std::cout << "Removed " << queueFromFile.dequeue() << " from the beginning of the queue!" << std::endl;
				}
				break;
			case 3:
				std::cout << "Queue is " << (queueFromFile.isEmpty() ? "empty!" : "not empty!") << std::endl;
				break;
			case 4:
				std::cout << "Queue is " << (queueFromFile.isFull() ? "full!" : "not full!") << std::endl;
				break;
			case 5:
				std::cout << "Queue contains: " << std::endl;
				queueFromFile.display();
				std::cout << std::endl;
				break;
			case 6:
				queueFromFile.clear();
				std::cout << "Queue is empty now: " << std::endl;
				break;
			case 7:
				std::cout << "Queue size is: " << queueFromFile.size() << std::endl;
				break;
			default:
				std::cout << "invalid input" << std::endl;
				break;
			}
		}
		catch (const std::exception&)
		{
			if (userInput == "e" || userInput == "E")
			{
				exitProgram = true;
			}
		}

	} while (exitProgram == false);

	std::cout << "Exit app" << std::endl;
	m_printService.PrintLine(30);
}

// ---------------------------------------- End of App -----------------------------------------------

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
