#include "ConversionService.h"
//
//bool ConversionService::isNumber(const std::string& str)
//{
//	for (char const& c : str) {
//		if (std::isdigit(c) == 0) return false;
//	}
//
//	return true;
//}
//
//
//ConversionService::ConversionService(PrintService printService)
//{
//	m_printService = printService;
//}
//
//ConversionService::ConversionService()
//{
//
//}
//
//std::string ConversionService::ConvertInfixToPostfix(std::string expression) {
//
//	expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
//
//	Stack<char> stack = Stack<char>(expression.size());
//	std::string resultExpression;
//	std::map<char, int> opPrecedence{
//		std::pair<char, int>('^', 4),
//		std::pair<char, int>('/', 3),
//		std::pair<char, int>('*', 3),
//		std::pair<char, int>('%', 3),
//		std::pair<char, int>('+', 2),
//		std::pair<char, int>('-', 2)
//	};
//
//	bool prevCharIsOperand = false;
//
//	for (size_t i = 0; i < expression.size(); i++)
//	{
//		char currentChar = expression[i];
//
//		if (isalpha(currentChar) || isdigit(currentChar) || currentChar == '.' || currentChar == ',')
//		{
//			if (!prevCharIsOperand && resultExpression.size() != 0)
//			{
//				resultExpression.push_back(' ');
//			}
//
//			resultExpression.push_back(currentChar);
//			prevCharIsOperand = true;
//		}
//		else if (currentChar == ')')
//		{
//			prevCharIsOperand = false;
//
//			while (stack.peek() != '(')
//			{
//				resultExpression.push_back(' ');
//				resultExpression.push_back(stack.pop());
//			}
//
//			stack.pop();
//		}
//		else if (currentChar == '(')
//		{
//			prevCharIsOperand = false;
//			stack.push(currentChar);
//		}
//		else
//		{
//			prevCharIsOperand = false;
//
//			while (!stack.isEmpty()
//				&& stack.peek() != '('
//				&& !(currentChar == '^' && stack.peek() == '^')
//				&& opPrecedence.at(currentChar) <= opPrecedence.at(stack.peek()))
//			{
//				resultExpression.push_back(' ');
//				resultExpression.push_back(stack.pop());
//			}
//
//			stack.push(currentChar);
//		}
//
//		m_printService.PrintIntermidiateResults(stack, resultExpression, std::string(1, currentChar), i);
//	}
//
//	while (!stack.isEmpty())
//	{
//		resultExpression.push_back(' ');
//		resultExpression.push_back(stack.pop());
//
//		m_printService.PrintIntermidiateResults(stack, resultExpression);
//	}
//
//	return resultExpression;
//}
//
//double ConversionService::EvaluatePostfix(std::string expression) {
//
//	std::stringstream ss(expression);
//	std::vector<std::string> words{};
//	std::string word;
//
//	while (getline(ss, word, ' '))
//	{
//		if (word == "")
//		{
//			continue;
//		}
//
//		words.push_back(word.c_str());
//	}
//
//	Stack<double> stack = Stack<double>(expression.size());
//
//	for (size_t i = 0; i < words.size(); i++)
//	{
//		word = words[i];
//
//		if (isNumber(word))
//		{
//			stack.push(stod(word));
//		}
//		else
//		{
//			double secondOperand = double(stack.pop());
//			double firstOperand = double(stack.pop());
//
//			double operationResult = 0.0;
//
//			switch (word.at(0))
//			{
//			case '+':
//				operationResult = firstOperand + secondOperand;
//				break;
//			case '-':
//				operationResult = firstOperand - secondOperand;
//				break;
//			case '*':
//				operationResult = firstOperand * secondOperand;
//				break;
//			case '/':
//				operationResult = firstOperand / secondOperand;
//				break;
//			case '^':
//				operationResult = pow(firstOperand, secondOperand);
//				break;
//			default:
//				break;
//			}
//
//			stack.push(operationResult);
//		}
//
//		std::stringstream stream;
//		stream << std::fixed << std::setprecision(2) << stack.peek();
//		m_printService.PrintIntermidiateResults(stack, stream.str(), word, i);
//	}
//
//	return stack.pop();
//}
