#pragma once
#include "Token.h"
#include <map>
#include <vector>
#include "Possibilities.h"
#include "Lexer.h"
class Parser
{
  public:
	struct PResult
	{
		std::map<std::string, bool> Results;
		std::vector<char> depend;
		std::vector<char> notdepend;
		bool tautology;
		bool contradiction;
	};

	Parser();
	bool Calc(std::map<char, bool> pVarTable = {});
	void Load(std::string text);
	PResult CalcAll(std::string text);
	std::vector<char> getVariables();

  private:
	bool Level0();
	bool Level1();
	void getNextToken();

	int m_Pos;
	std::map<char, bool> VarTable;
	Token currentToken;
	Lexer::LexerResult m_LResult;
};
