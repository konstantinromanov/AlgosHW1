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

		if (m_currentCount < 0)
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

		if (ArrayBase<T>::count() == 0)
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

		T* obj = ArrayBase<T>::elementAt(m_first);
		ArrayBase<T>::decCount();
		m_first = (m_first + 1) % ArrayBase<T>::capacity();

		return obj;
	}

	void display() {

		for (int i = 0; i < ArrayBase<T>::size(); i++)
		{
			T el = ArrayBase<T>::elementAt((m_first + i) % ArrayBase<T>::capacity());
			cout << el << endl;
		}
	}

	void clear() {

	}

	void Test() {
		cout << "test" << endl;
	}
};


int main()
{
	//ArrayBase<int> arr = ArrayBase<int>(3);
	//std::cout << "capacity" << arr.capacity() << std::endl;
	//std::cout << "count" << arr.count() << std::endl;
	//int ind0 = arr.add(1);
	//int ind1 = arr[1] = 33;
	//std::cout << "value0" << arr[0] << std::endl;
	//std::cout << "value1" << arr[1] << std::endl;
	Queue<int> queue = Queue<int>(6);
	bool isEmpty = queue.isEmpty();
	bool isFull = queue.isFull();
	int size = queue.size();
	//Queue<int> queue = Queue<int>(6);
	//queue.Test();
	//bool empty = queue.isEmpty();
	//queue.enqueue(1);
	//queue.display();


	//queue.enqueue(2);
	//queue.display();

	//queue.enqueue(3);
	//queue.enqueue(4);
	//queue.enqueue(5);
	//queue.enqueue(6);
	////queue.enqueue(7);
	//queue.display();

	//int el1 = queue.dequeue();
	//int el2 = queue.dequeue();
	//int el3 = queue.dequeue();
	//int el4 = queue.dequeue();

	//queue.display();

	//queue.enqueue(44);
	//queue.enqueue(54);
	//queue.enqueue(64);

	//queue.display();

	//int el5 = queue.dequeue();
	//int el6 = queue.dequeue();
	//int el7 = queue.dequeue();

	//queue.display();


	//Stack<string> stack = Stack<string>(6);
	//stack.Push("33dd");
	//std::cout << stack.Peek() << std::endl;

	//stack.Push("sdfassdfafd");
	//std::cout << stack.Peek() << std::endl;

	//stack.Push("sdfassdfafd");
	//stack.Push("ddddd");
	//stack.Push("ccccc");
	//stack.Push("gggggggg");
	//std::cout << stack.Peek() << std::endl;

	//string pop1 = stack.Pop();
	//std::cout << stack.Peek() << std::endl;



	//ArrayBase<int> arr = ArrayBase<int>(3);
	//std::cout << "capacity" << arr.capacity() << std::endl;
	//std::cout << "count" << arr.count() << std::endl;
	//int ind0 = arr.add(1);
	//int ind1 = arr.add(2);
	//int ind2 = arr.add(3);
	//int ind3 = arr.add(4);
	//int ind5 = arr.add(5);
	//int ind6 = arr.add(6);
	//int ind7 = arr.add(7);
	//std::cout << "capacity" << arr.capacity() << std::endl;
	//std::cout << "count" << arr.count() << std::endl;
	//arr.removeAt(2);
	////std::cout << "success" << std::endl;
	//
	//for (size_t i = 0; i < arr.count(); i++)
	//{
	//	std::cout << arr.elementAt(i) << std::endl;
	//}

	//std::cout << "capacity" << arr.capacity() << std::endl;
	//std::cout << "count" << arr.count() << std::endl;
	////std::stack<char> st;

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
