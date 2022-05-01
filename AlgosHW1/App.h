#pragma once
#include <string>
#include "PrintService.h"

class App
{

private:

	PrintService m_printService;

	template<typename T>
	bool readInputFromFile(const std::string& path, Queue<T>& queue) {

		std::ifstream file;
		file.open(path);

		if (file.is_open())
		{
			for (std::string s; file >> s;)
			{
				queue.enqueue(s);
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	bool isValidInput(std::string input) {

		for (const char c : input)
		{
			if (!isalnum(c))
			{
				return false;
			}
		}

		return true;
	}

public:

	App(PrintService printService) {
		m_printService = printService;
	}

	void RunApp() {

		std::string filePath = "homework1-1.txt"; // place input file in the same directory as this file.

		Queue<std::string> queueFromFile = Queue<std::string>(50);
		bool readSuccess = readInputFromFile(filePath, queueFromFile);

		std::vector<std::string> menuItems = {
			"to add an element",
			"to delete an element",
			"to check whether a queue is empty",
			"to check whether a queue is full",
			"to print a queue",
			"to clear a queue",
			"to output the size of a queue"
		};

		m_printService.PrintMenu(menuItems);

		std::string userInput;
		std::string queueElementInput;
		int choice = 0;
		bool exitProgram = false;

		do
		{
			std::cout << "Choose operation (1 - 7) or 'E' to exit: ";
			std::cin >> userInput;

			if (!isValidInput(userInput))
			{
				std::cout << "invalid input" << std::endl;
				continue;
			}

			try
			{
				choice = stoi(userInput);

				switch (choice)
				{
				case 1:
					std::cout << "Enter a number: ";
					std::cin >> queueElementInput;
					queueFromFile.enqueue(queueElementInput);
					break;
				case 2:
					queueFromFile.dequeue();
					break;
				case 3:
					std::cout << "Queue is " << (queueFromFile.isEmpty() ? "empty!" : "not empty!") <<std::endl;
					break;
				case 4:
					std::cout << "Queue is " << (queueFromFile.isFull() ? "full!" : "not full!") <<std::endl;
					break;
				case 5:
					std::cout << "Queue contains: " <<std::endl;
					queueFromFile.display();
					std::cout <<std::endl;
					break;
				case 6:
					queueFromFile.clear();
					std::cout << "Queue is empty now: " <<std::endl;
					break;
				case 7:
					std::cout << "Queue size is: " << queueFromFile.size() <<std::endl;
					break;
				default:
					std::cout << "invalid input" <<std::endl;
					break;
				}
			}
			catch (const std::exception&)
			{
				if (userInput == "e" || userInput == "E")
				{
					exitProgram = true;
				}
			}

		} while (exitProgram == false);

		std::cout << "Exit app" <<std::endl;
		m_printService.PrintLine(30);
	}
};
