#pragma once
#include "ConversionService.h"

class Tests
{

private:

	ConversionService m_conversionService;
	PrintService m_printService;

public:
		
	Tests(PrintService printService, ConversionService conversionService)
	{
		m_conversionService = conversionService;
		m_printService = printService;
	}

	void RunTests() {

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
};

