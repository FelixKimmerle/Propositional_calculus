#pragma once
#include "Token.h"
#include <algorithm>
#include <map>
#include <vector>
namespace Lexer
{
	struct LexerResult
	{
		std::vector<Token> Tokens;
		std::vector<char> Variables;
	};
	LexerResult Tokenize(std::string text);
};
