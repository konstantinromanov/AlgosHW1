// AlgosHW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <map>
#include <iterator>
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
	
	/*auto evalOp = [](char op, map<char, int> mp) {
		return (mp.find(op) == mp.end()) ? -1 : mp.at(op);
	};*/

	for (size_t i = 0; i < expression.size(); i++)
	{
		char currentChar = expression[i];

		if (isalpha(currentChar) || isdigit(currentChar) || currentChar == '.' || currentChar == ',')
		{
			resultExpression.push_back(currentChar);
		}
		else if (currentChar == ')')
		{
			while (stack.peek() != '(')
			{
				resultExpression.push_back(stack.pop());
			}

			stack.pop();
		}
		else if (currentChar == '(')
		{
			stack.push(currentChar);
		}
		else
		{
			while (!stack.isEmpty()
				&& stack.peek() != '('
				&& !(currentChar == '^' && stack.peek() == '^')
				&& opPrecedence.at(currentChar) <= opPrecedence.at(stack.peek()))
			{
				resultExpression.push_back(stack.pop());
			}

			stack.push(currentChar);
		}
	}

	while (!stack.isEmpty())
	{
		resultExpression.push_back(stack.pop());
	}

	return resultExpression;
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

	bool test2;

	try
	{
		queue.enqueue(7);
		bool test2 = false;
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

	bool test9 = "abcd^e-fgh*+^*+i-" == convertInfixToPostfix("a+b*(c^d-e)^(f+g*h)-i");

	printTestResult(9, test9);

	// ---------------------------------- Test 10 ----------------------------------

	bool test10 = "12.34+15*16-" == convertInfixToPostfix("(12.3+4)*15-16");

	printTestResult(10, test10);

	// ---------------------------------- Test 11 ----------------------------------

	bool test11 = "AB+C*D-" == convertInfixToPostfix("(A+B)*C-D");

	printTestResult(11, test11);

	// ---------------------------------- Test 12 ----------------------------------

	bool test12 = "1832^/9-46*+" == convertInfixToPostfix("18/3^2-9+4*6");

	printTestResult(12, test12);

	// ---------------------------------- Test 13 ----------------------------------

	bool test13 = "AB*CD/+" == convertInfixToPostfix("A*B+C/D");

	printTestResult(13, test13);

	// ---------------------------------- Test 14 ----------------------------------

	bool test14 = "ABC*EF-/+" == convertInfixToPostfix("A+B*C/(E-F)");

	printTestResult(14, test14);
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
