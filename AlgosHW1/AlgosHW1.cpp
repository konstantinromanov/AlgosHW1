// AlgosHW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <map>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
class ArrayBase {

private:

	static const int m_defaultSize = 5;
	T* storeArray;
	int m_capacity;
	int m_currentCount = 0;

protected:

	void resetSize() {
		m_currentCount = 0;
	}

	void incCount() {

		if (isFull())
		{
			throw out_of_range("Array is already full");
		}

		m_currentCount++;
	}

	void decCount() {

		if (m_currentCount == 0)
		{
			throw out_of_range("Array is already empty");
		}

		m_currentCount--;
	}

	int add(T obj) {

		if (!isFull())
		{
			storeArray[m_currentCount++] = obj;
			return  m_currentCount;
		}

		return -1;
	}

	void removeAt(int index) {

		if (index < 0 || index > m_currentCount - 1)
		{
			throw invalid_argument("Imposible to remove");
		}

		for (size_t i = index; i < m_currentCount - 1; i++)
		{
			storeArray[i] = storeArray[i + 1];
		}

		m_currentCount--;
	}

	T elementAt(int index) {
		return storeArray[index];
	}

	T& operator[](int index) {
		return storeArray[index];
	}

public:

	ArrayBase(int arraySize = m_defaultSize) {
		m_capacity = arraySize <= m_defaultSize ? m_defaultSize : arraySize;
		storeArray = new T[m_capacity];
	}

	bool isEmpty() const {
		return m_currentCount == 0;
	}

	int size() {
		return m_currentCount;
	}

	int capacity() {
		return m_capacity;
	}

	bool isFull() {
		return m_currentCount == m_capacity;
	}

	virtual void clear() = 0;
};

template<typename T>
class Stack : public ArrayBase<T> {

public:

	Stack(int stackSize) : ArrayBase<T>(stackSize) {

	}

	void push(T arg) {

		if (ArrayBase<T>::isFull())
		{
			throw out_of_range("Stack is already full");
		}

		ArrayBase<T>::add(arg);
	}

	T pop() {

		if (ArrayBase<T>::size() == 0)
		{
			throw out_of_range("Stack is empty");
		}

		T arg = ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
		ArrayBase<T>::decCount();

		return arg;
	}

	T peek() {

		if (ArrayBase<T>::size() == 0)
		{
			throw std::out_of_range("Stack is empty");
		}

		return ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
	}

	void clear() {
		ArrayBase<T>::resetSize();
	}
};

template<typename T>
class Queue : public ArrayBase<T> {

private:

	int m_first = 0;
	int m_last = 0;

public:

	Queue() {

	}

	Queue(int queueSize) : ArrayBase<T>(queueSize) {

	}

	bool enqueue(T next) {

		ArrayBase<T>::incCount();
		m_last = (m_first + ArrayBase<T>::size() - 1) % ArrayBase<T>::capacity();
		ArrayBase<T>::operator[](m_last) = next;

		return true;
	}

	T dequeue() {
		int dequeuIndex = m_first;
		ArrayBase<T>::decCount();
		m_first = (m_first + 1) % ArrayBase<T>::capacity();

		return ArrayBase<T>::elementAt(dequeuIndex);
	}

	void display() {

		for (int i = 0; i < ArrayBase<T>::size(); i++)
		{
			T el = ArrayBase<T>::elementAt((m_first + i) % ArrayBase<T>::capacity());
			cout << el << endl;
		}
	}

	void clear() {
		m_first = 0;
		m_last = 0;
		ArrayBase<T>::resetSize();
	}
};

void printTestResult(int testNumber, bool testResult) {
	cout << "Test " << testNumber << ": " << boolalpha << testResult << endl;
}

string convertInfixToPostfix(string expression) {

	expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

	Stack<char> stack = Stack<char>(expression.size());
	string resultExpression;
	map<char, int> opPrecedence{
		pair<char, int>('^', 4),
		pair<char, int>('/', 3),
		pair<char, int>('*', 3),
		pair<char, int>('%', 3),
		pair<char, int>('+', 2),
		pair<char, int>('-', 2)
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
	}

	while (!stack.isEmpty())
	{
		resultExpression.push_back(' ');
		resultExpression.push_back(stack.pop());
	}

	return resultExpression;
}

bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

double evaluatePostfix(string expression) {

	stringstream ss(expression);
	vector<string> words{};
	string word;

	while (getline(ss, word, ' '))
	{
		if (word == "")
		{
			continue;
		}

		words.push_back(word.c_str());
	}

	double resultExpression;
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
			double firstOperand = double(stack.pop());
			double secondOperand = double(stack.pop());
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
	}

	return stack.pop();
}

void runTests() {

	int queueLength = 6;
	Queue<int> queue = Queue<int>(queueLength);

	// ---------------------------------- Test 1 ----------------------------------

	for (int i = 0; i < queueLength; i++)
	{
		queue.enqueue(i + 1);
	}

	bool test1 = queue.size() == queueLength;

	printTestResult(1, test1);

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

	printTestResult(2, test2);

	// ---------------------------------- Test 3 ----------------------------------

	int queueSize = queue.size();

	for (int i = 0; i < queueSize; i++)
	{
		queue.dequeue();
	}

	bool test3 = queue.size() == 0;

	printTestResult(3, test3);

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

	printTestResult(4, test4);

	// ---------------------------------- Test 5 ----------------------------------

	for (size_t i = 0; i < 3; i++)
	{
		queue.enqueue(i + 1);
	}

	queue.clear();

	bool test5 = queue.size() == 0;

	printTestResult(5, test5);

	// ---------------------------------- Test 6 ----------------------------------

	bool test6 = queue.isEmpty();

	printTestResult(6, test6);

	// ---------------------------------- Test 7 ----------------------------------

	bool test7 = !queue.isFull();

	printTestResult(7, test7);

	// ---------------------------------- Test 8 ----------------------------------

	for (size_t i = 0; i < queueLength; i++)
	{
		queue.enqueue(i + 1);
	}

	bool test8 = queue.isFull();

	printTestResult(8, test8);

	// ---------------------------------- Test 9 ----------------------------------

	bool test9 = "a b c d ^ e - f g h * + ^ * + i -" == convertInfixToPostfix("a + b * (c^d-e)^(f+g*h)-i");

	printTestResult(9, test9);

	// ---------------------------------- Test 10 ----------------------------------

	string test = convertInfixToPostfix("(12.3+4)*15-16");
	bool test10 = "12.3 4 + 15 * 16 -" == convertInfixToPostfix("(12.3+4)*15-16");

	printTestResult(10, test10);

	// ---------------------------------- Test 11 ----------------------------------

	bool test11 = "A B + C * D -" == convertInfixToPostfix("(A+B)*C-D");

	printTestResult(11, test11);

	// ---------------------------------- Test 12 ----------------------------------

	bool test12 = "18 3 2 ^ / 9 - 4 6 * +" == convertInfixToPostfix("18/3^2-9+4*6");

	printTestResult(12, test12);

	// ---------------------------------- Test 13 ----------------------------------

	bool test13 = "A B * C D / +" == convertInfixToPostfix("A*B+C/D");

	printTestResult(13, test13);

	// ---------------------------------- Test 14 ----------------------------------

	bool test14 = "A B C * E F - / +" == convertInfixToPostfix("A+B*C/(E-F)");

	printTestResult(14, test14);

	// ---------------------------------- Test 15 ----------------------------------

	bool test15 = "a b + c d - ^ m n + *" == convertInfixToPostfix("(a + b) ^(c - d) * (m + n)");

	printTestResult(15, test15);

	// ---------------------------------- Test 16 ----------------------------------

	bool test16 = "a b + d c ^ -" == convertInfixToPostfix("a+b-d^c");

	printTestResult(16, test16);

	// ---------------------------------- Test 17 ----------------------------------

	bool test17 = "10 3 * 15 5 / +" == convertInfixToPostfix("10*3+15/5");

	printTestResult(17, test17);

	// ---------------------------------- Test 18 ----------------------------------

	bool test18 = "5 10 + 12 9 - * 3 /" == convertInfixToPostfix("(5+10)*(12-9)/3");

	printTestResult(18, test18);

	// ---------------------------------- Test 19 ----------------------------------

	bool test19 = "a b * c + d ^ a b - c d + / +" == convertInfixToPostfix("(a*b + c)^d+(a-b)/(c+d)");

	printTestResult(19, test19);

	// ---------------------------------- Test 20 ----------------------------------

	bool test20 = 7 == evaluatePostfix("3 2 2 * +");

	printTestResult(20, test20);

	// ---------------------------------- Test 21 ----------------------------------

	bool test21 = 7 == evaluatePostfix("3 2 2 * +");

	printTestResult(21, test21);

	// ---------------------------------- Test 22 ----------------------------------

	bool test22 = 70 == evaluatePostfix("3 30 / 6 3 11 18 36 / + - * + ");

	printTestResult(22, test22);

	// ---------------------------------- Test 23 ----------------------------------

	bool test23 = 15 == evaluatePostfix("3 9 12 - / 10 5 + *");

	printTestResult(23, test23);

	// ---------------------------------- Test 24 ----------------------------------

	bool test24 = 49 == evaluatePostfix("6 7 - 2 3 4 + ^ *");

	printTestResult(24, test24);

	// ---------------------------------- Test 25 ----------------------------------

	bool test25 = 4 == evaluatePostfix("2 25 100 / - 40 6 8 * - /");

	printTestResult(25, test25);

	// ---------------------------------- Test 26 ----------------------------------

	bool test26 = 5 == evaluatePostfix("1 23 11 17 + - 85 100 - / + 4 64 80 - + /");

	printTestResult(26, test26);

	// ---------------------------------- Test 27 ----------------------------------

	bool test27 = 4 == evaluatePostfix("4 16 / 6 - 3 30 / 18 - /");

	printTestResult(27, test27);
}


int main()
{
	runTests();
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
