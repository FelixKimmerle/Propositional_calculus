#pragma once
#include "Token.h"
#include <algorithm>
#include <map>
namespace Lexer
{
struct LexerResult
{
	std::vector<Token> Tokens;
	std::vector<char> Variables;
};
std::map<char, Token::Types> m_Definitions = {
	{'&', Token::Types::AND},
	{'|', Token::Types::OR},
	{'=', Token::Types::EQUAL},
	{'!', Token::Types::NOT},
	{'(', Token::Types::BOPEN},
	{')', Token::Types::BCLOSE},
	{'-', Token::Types::IMPLICATION},
	{'^', Token::Types::XOR},
};

const std::string m_Ignore = ">";

LexerResult Tokenize(std::string text)
{
	LexerResult LResult;
	for (int i = 0; i < text.size(); i++)
	{
		if (m_Ignore.find(text[i]) != std::string::npos)
		{
			continue;
		}
		if (m_Definitions.count(text[i]))
		{
			LResult.Tokens.push_back(Token(m_Definitions[text[i]], text[i], i));
		}
		else
		{
			if (text[i] == '0' || text[i] == '1')
			{
				LResult.Tokens.push_back(Token(Token::Types::NUM, text[i], i));
			}
			else
			{
				LResult.Tokens.push_back(Token(Token::Types::VAR, text[i], i));
				auto it = std::find(LResult.Variables.begin(), LResult.Variables.end(), text[i]);
				if (it == LResult.Variables.end())
				{
					LResult.Variables.push_back(text[i]);
				}
			}
		}
	}
	return LResult;
}
};
