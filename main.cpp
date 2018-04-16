#include <iostream>
#include <vector>
#include "Possibilities.h"
#include "Lexer.h"
#include "Parser.h"
#include <string>
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <input>" << std::endl;
	}
	else
	{
		std::string input = argv[1];
		if (input == "-h" || input == "--help")
		{
			std::cout << "Usage: " << argv[0] << " <input>" << std::endl;
			std::cout << "Surround your input with: ' or \" if you use | or &" << std::endl;
			std::cout << "Logical operators are: " << std::endl;
			std::cout << "| =	or" << std::endl;
			std::cout << "& =	and" << std::endl;
			std::cout << "^ =	xor" << std::endl;
			std::cout << "! =	not" << std::endl;
			std::cout << "(...) =	encapsulation" << std::endl;
			std::cout << "1 =	true" << std::endl;
			std::cout << "0 =	false" << std::endl;
		}
		else
		{
			Parser parser;
			auto results = parser.CalcAll(input);

			if (results.error)
			{
				std::cout << "Syntax error" << std::endl;
			}
			else
			{

				std::vector<char> Variables = parser.getVariables();
				std::cout << "expression: " << input << ((Variables.size() == 0) ? " " : "\n");

				if (Variables.size() > 0)
				{
					for (int z = 0; z < Variables.size(); z++)
					{
						std::cout << Variables[z] << " ";
					}
					std::cout << std::endl;
				}
				for (auto i = results.Results.begin(); i != results.Results.end(); i++)
				{
					for (int l = 0; l < i->first.size(); l++)
					{
						std::cout << i->first[l] << " ";
					}
					std::cout << "= " << i->second << std::endl;
				}
				if (results.tautology)
				{
					std::cout << "It's a tautology" << std::endl;
				}
				if (results.contradiction)
				{
					std::cout << "It's a contradiction" << std::endl;
				}
				if (results.depend.size() > 0)
				{
					for (int i = 0; i < results.depend.size(); i++)
					{
						std::cout << results.depend[i] << ((i < results.depend.size() - 1) ? "," : "");
					}

					std::cout << ((results.depend.size() == 1) ? " is" : " are") << " equal to the input" << std::endl;
				}
				if (results.notdepend.size() > 0)
				{
					for (int i = 0; i < results.notdepend.size(); i++)
					{
						std::cout << "!" << results.notdepend[i] << ((i < results.notdepend.size() - 1) ? "," : "");
					}
					std::cout << ((results.notdepend.size() == 1) ? " is" : " are") << " equal to the input" << std::endl;
				}
			}
		}
	}
	return 0;
}
