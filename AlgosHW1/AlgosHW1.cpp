// AlgosHW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

template<typename T>
class ArrayBase {

private:

	static const int m_defaultSize = 5;
	T* storeArray;	
	int m_capacity;
	int m_currentCount = 0;

public:

	ArrayBase<T>(int arraySize = m_defaultSize) {
		m_capacity = arraySize <= m_defaultSize ? m_defaultSize : arraySize;
		storeArray = new T[m_capacity];
	}

	int count() {
		return m_currentCount;
	}

	int capacity() {
		return m_capacity;
	}

	int add(T obj) {

		if (m_currentCount < m_capacity)
		{
			storeArray[m_currentCount++] = obj;
			return  m_currentCount;
		}
		
		return -1;
	}

	void removeAt(int index) {

		if (index >= 0 && index <= m_currentCount)
		{
			for (size_t i = index; i < m_currentCount - 1; i++)
			{
				storeArray[i] = storeArray[i + 1];
			}

			m_currentCount--;
		}
	}

	T elementAt(int index) {
		return storeArray[index];
	}
};

template<typename T>
class Stack : ArrayBase<T> {

private:


public:

	Stack<T>() {}

	Stack<T>(int stackSize) : ArrayBase<T>(stackSize) {

	}

	void Push(T arg) {

		ArrayBase<T>::add(arg);
	}

	T Peek() {
		return ArrayBase<T>::elementAt(0);
	}
};


int main()
{

	Stack<string> stack = Stack<string>(5);
	stack.Push("33dd");

	std::cout << stack.Peek() << std::endl;


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
