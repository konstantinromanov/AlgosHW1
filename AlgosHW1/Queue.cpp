#include "Queue.h"
#include<iostream>
//
//template<typename T>
//Queue<T>::Queue(int queueSize) : ArrayBase<T>(queueSize) {
//
//}
//
//template<typename T>
//Queue<T>::Queue() : ArrayBase<T>()
//{
//
//}
//
//template<typename T>
//bool Queue<T>::enqueue(T next) {
//
//	ArrayBase<T>::incCount();
//	m_last = (m_last + 1) % ArrayBase<T>::capacity();
//	ArrayBase<T>::operator[](m_last) = next;
//
//	return true;
//}
//
//template<typename T>
//T Queue<T>::dequeue() {
//	int dequeuIndex = m_first;
//	ArrayBase<T>::decCount();
//	m_first = (m_first + 1) % ArrayBase<T>::capacity();
//
//	return ArrayBase<T>::operator[](dequeuIndex);
//}
//
//template<typename T>
//void Queue<T>::display() {
//
//	for (int i = 0; i < ArrayBase<T>::size(); i++)
//	{
//		T el = ArrayBase<T>::operator[]((m_first + i) % ArrayBase<T>::capacity());
//		std::cout << el << ' ';
//	}
//}
//
//template<typename T>
//void Queue<T>::clear() {
//	m_first = 0;
//	m_last = -1;
//	ArrayBase<T>::resetSize();
//}
//
//template<typename T>
//T Queue<T>::elementAt(int index) {
//
//	if (index < 0 || index > ArrayBase<T>::size() - 1)
//	{
//		throw std::invalid_argument("Index is outside of range");
//	}
//
//	return ArrayBase<T>::operator[]((m_first + index) % ArrayBase<T>::capacity());
//}
//
//template class Queue<int>;
//template class Queue<double>;
//template class Queue<char>;
//template class Queue<std::string>;
