#include "App.h"

bool App::readInputFromFile(const std::string& path, Queue<std::string>& queue) {

	queue = Queue<std::string>(20);
	std::ifstream file;
	file.open(path);

	if (file.is_open())
	{
		for (std::string s; file >> s;)
		{
			if (!isValidInput(s))
			{
				return false;
			}

			try
			{
				queue.enqueue(s);
			}
			catch (const std::exception&)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool App::isValidInput(std::string input) {

	for (const char c : input)
	{
		if (!isalnum(c))
		{
			return false;
		}
	}

	return true;
}

App::App(PrintService printService) {
	m_printService = printService;
}

void App::RunApp() {

	std::string filePath = "homework1-1.txt"; // place input file in the same directory as this file or provide path with file with '/'s.

	Queue<std::string> queueFromFile;
	bool readSuccess = readInputFromFile(filePath, queueFromFile);

	if (!readSuccess)
	{
		std::cout << "Error while reading file, alphanumeric characters allowed, separated by space." << std::endl;
		std::cout << "You can still enter data manually by adding it to the queue!" << std::endl;
		std::cout << "Queue size is " << queueFromFile.size() << std::endl;
	}

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
				if (queueFromFile.isFull())
				{
					std::cout << "Queue is already full" << std::endl;
				}
				else
				{
					queueFromFile.enqueue(queueElementInput);
					std::cout << "Added " << queueElementInput << " to the end of the queue!" << std::endl;
				}
				break;
			case 2:
				if (queueFromFile.isEmpty())
				{
					std::cout << "Queue is already empty" << std::endl;
				}
				else
				{					
					std::cout << "Removed " << queueFromFile.dequeue() << " from the beginning of the queue!" << std::endl;
				}				
				break;
			case 3:
				std::cout << "Queue is " << (queueFromFile.isEmpty() ? "empty!" : "not empty!") << std::endl;
				break;
			case 4:
				std::cout << "Queue is " << (queueFromFile.isFull() ? "full!" : "not full!") << std::endl;
				break;
			case 5:
				std::cout << "Queue contains: " << std::endl;
				queueFromFile.display();
				std::cout << std::endl;
				break;
			case 6:
				queueFromFile.clear();
				std::cout << "Queue is empty now: " << std::endl;
				break;
			case 7:
				std::cout << "Queue size is: " << queueFromFile.size() << std::endl;
				break;
			default:
				std::cout << "invalid input" << std::endl;
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

	std::cout << "Exit app" << std::endl;
	m_printService.PrintLine(30);
}