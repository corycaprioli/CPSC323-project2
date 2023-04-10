#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "lexer.h"
#include "par.h" 

int main() {
	std::ifstream inFile;
	std::ofstream outFile("output.txt");
	std::string filename;
	std::string line;

	do {
		std::cout << "Enter a file name .txt (or 'exit' to quit): ";
		std::cin >> filename;

		if (filename != "exit")
		{
			inFile.open(filename.c_str());

			//Make sure file is opened
			if (!inFile.is_open())
			{
				exit(1);
			}
			else
			{
				while (std::getline(inFile, line))
				{
					outFile << line << std::endl;
				}
			}

			outFile << std::endl;

			Par analyze;

			inFile.clear();
			inFile.seekg(0);

			analyze.RAT23S(inFile, outFile);
			inFile.close();

			outFile << std::endl;
		}

	} while (filename != "exit");

	outFile.close();

	return 0;
}
