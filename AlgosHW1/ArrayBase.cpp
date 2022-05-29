#include "ArrayBase.h"
#include <stdexcept>
#include <string>
//
//template<typename T>
//void ArrayBase<T>::resetSize() {
//	m_currentCount = 0;
//}
//
//template<typename T>
//void ArrayBase<T>::incCount() {
//
//	if (isFull())
//	{
//		throw std::out_of_range("Array is already full");
//	}
//
//	m_currentCount++;
//}
//
//template<typename T>
//void ArrayBase<T>::decCount() {
//
//	if (m_currentCount == 0)
//	{
//		throw std::out_of_range("Array is already empty");
//	}
//
//	m_currentCount--;
//}
//
//template<typename T>
//int ArrayBase<T>::add(T obj) {
//
//	if (!isFull())
//	{
//		storeArray[m_currentCount++] = obj;
//		return  m_currentCount;
//	}
//
//	return -1;
//}
//
//template<typename T>
//void ArrayBase<T>::removeAt(int index) {
//
//	if (index < 0 || index > m_currentCount - 1)
//	{
//		throw std::invalid_argument("Imposible to remove");
//	}
//
//	for (size_t i = index; i < m_currentCount - 1; i++)
//	{
//		storeArray[i] = storeArray[i + 1];
//	}
//
//	m_currentCount--;
//}
//
//template<typename T>
//T& ArrayBase<T>::operator[](int index) {
//
//	if (index < 0 || index > m_capacity - 1)
//	{
//		throw std::invalid_argument("Index is outside of range");
//	}
//
//	return storeArray[index];
//}
//
//template<typename T>
//ArrayBase<T>::ArrayBase(int arraySize) {
//	m_capacity = arraySize <= m_defaultSize ? m_defaultSize : arraySize;
//	storeArray = new T[m_capacity];
//}
//
//template<typename T>
//bool ArrayBase<T>::isEmpty() const {
//	return m_currentCount == 0;
//}
//
//template<typename T>
//int ArrayBase<T>::size() {
//	return m_currentCount;
//}
//
//template<typename T>
//int ArrayBase<T>::capacity() {
//	return m_capacity;
//}
//
//template<typename T>
//bool ArrayBase<T>::isFull() {
//	return m_currentCount == m_capacity;
//}
//
//template<typename T>
//T ArrayBase<T>::elementAt(int index) {
//
//	if (index < 0 || index > m_currentCount - 1)
//	{
//		throw std::invalid_argument("Index is outside of range");
//	}
//
//	return storeArray[index];
//}
//
//template class ArrayBase<int>;
//template class ArrayBase<double>;
//template class ArrayBase<char>;
//template class ArrayBase<std::string>;
//
