// AlgosHW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
using namespace std;

template<typename T>
class ArrayBase {

private:

	static const int m_defaultSize = 5;
	T* storeArray;
	int m_capacity;
	int m_currentCount = 0;

public:

	ArrayBase(int arraySize = m_defaultSize) {
		m_capacity = arraySize <= m_defaultSize ? m_defaultSize : arraySize;
		storeArray = new T[m_capacity];
	}

	T& operator[](int index) {
		return storeArray[index];
	}

	bool isEmpty() const {
		return m_currentCount == 0;
	}

	int size() {
		return m_currentCount;
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

	int capacity() {
		return m_capacity;
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

	bool isFull() {
		return m_currentCount == m_capacity;
	}

	virtual void clear() = 0;

	void resetSize() {
		m_currentCount = 0;
	}
};

template<typename T>
class Stack : public ArrayBase<T> {

public:

	Stack() {

	}

	Stack(int stackSize) : ArrayBase<T>(stackSize) {

	}

	void Push(T arg) {

		if (ArrayBase<T>::isFull())
		{
			throw out_of_range("Stack is already full");
		}

		ArrayBase<T>::add(arg);
	}

	T Pop() {

		if (ArrayBase<T>::size() == 0)
		{
			throw out_of_range("Stack is empty");
		}

		T arg = ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
		ArrayBase<T>::decCount();

		return arg;
	}

	T Peek() {

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

	void Test() {
		cout << "test" << endl;
	}
};

void runTests() {

	Queue<int> queue = Queue<int>(6);

	for (size_t i = 0; i < 6; i++)
	{
		queue.enqueue(i + 1);
	}
	
	bool test1 = queue.size() == 6;
	cout << "Test 1 " << boolalpha << test1 << endl;

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
	
	cout << "Test 2 " << boolalpha << test2 << endl;

	int queueSize = queue.size();

	for (int i = 0; i < queueSize; i++)
	{
		queue.dequeue();
	}
		
	bool test3 = queue.size() == 0;

	cout << "Test 3 " << boolalpha << test3 << endl;

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
	
	cout << "Test 4 " << boolalpha << test3 << endl;

	for (size_t i = 0; i < 3; i++)
	{
		queue.enqueue(i + 1);
	}

	queue.clear();

	bool test5 = queue.size() == 0;

	cout << "Test 5 " << boolalpha << test5 << endl;

	bool test6 = queue.isEmpty();

	cout << "Test 6 " << boolalpha << test6 << endl;

	bool test7 = !queue.isFull();

	cout << "Test 7 " << boolalpha << test7 << endl;

	for (size_t i = 0; i < 6; i++)
	{
		queue.enqueue(i + 1);
	}

	bool test8 = queue.isFull();

	cout << "Test 8 " << boolalpha << test8 << endl;
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
