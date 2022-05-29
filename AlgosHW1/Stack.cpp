#include "Stack.h"
#include<iostream>
//
//template<typename T>
//Stack<T>::Stack(int stackSize) : ArrayBase<T>(stackSize)
//{
//
//}
//
//template<typename T>
//Stack<T>::Stack() : ArrayBase<T>()
//{
//
//}
//
//template<typename T>
//void Stack<T>::push(T arg) {
//
//	if (ArrayBase<T>::isFull())
//	{
//		throw std:: out_of_range("Stack is already full");
//	}
//
//	ArrayBase<T>::add(arg);
//}
//
//template<typename T>
//T Stack<T>::pop() {
//
//	if (ArrayBase<T>::size() == 0)
//	{
//		throw std::out_of_range("Stack is empty");
//	}
//
//	T arg = ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
//	ArrayBase<T>::decCount();
//
//	return arg;
//}
//
//template<typename T>
//T Stack<T>::peek() {
//
//	if (ArrayBase<T>::size() == 0)
//	{
//		throw std::out_of_range("Stack is empty");
//	}
//
//	return ArrayBase<T>::elementAt(ArrayBase<T>::size() - 1);
//}
//
//template<typename T>
//void Stack<T>::display() {
//
//	for (int i = 0; i < ArrayBase<T>::size(); i++)
//	{
//		T el = ArrayBase<T>::elementAt(i);
//		std::cout << el << ' ';
//	}
//}
//
//template<typename T>
//void Stack<T>::clear() {
//	ArrayBase<T>::resetSize();
//}
//
//template class Stack<int>;
//template class Stack<double>;
//template class Stack<char>;
//template class Stack<std::string>;
