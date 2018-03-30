#include "Parser.h"

Parser::Parser()
{
}
bool Parser::Calc(std::map<char, bool> pVarTable)
{
    VarTable = pVarTable;
    m_Pos = 0;
    currentToken = m_LResult.Tokens[m_Pos];
    return Level0();
}
void Parser::Load(std::string text)
{
    m_LResult = Lexer::Tokenize(text);
}
Parser::PResult Parser::CalcAll(std::string text)
{
    PResult result;
    m_LResult = Lexer::Tokenize(text);
    if (m_LResult.Variables.size() > 0)
    {
        std::map<char, bool> depend;
        std::map<char, bool> notdepend;
        result.tautology = true;
        result.contradiction = true;

        for (int i = 0; i < m_LResult.Variables.size(); i++)
        {
            depend.insert(std::make_pair(m_LResult.Variables[i], true));
            notdepend.insert(std::make_pair(m_LResult.Variables[i], true));
        }

        std::map<char, bool> val;
        auto list = Possibilities::calc("01", m_LResult.Variables.size());
        for (int i = 0; i < list.size(); i++)
        {
            val.clear();
            for (int z = 0; z < m_LResult.Variables.size(); z++)
            {
                bool v = false;
                if (list[i][z] == '1')
                {
                    v = true;
                }
                val.insert(std::make_pair(m_LResult.Variables[z], v));
            }
            bool line = Calc(val);
            for (auto d = m_LResult.Variables.begin(); d != m_LResult.Variables.end(); d++)
            {
                if (depend[*d] && (val[*d] != line))
                {
                    depend[*d] = false;
                }
                if (notdepend[*d] && (val[*d] == line))
                {
                    notdepend[*d] = false;
                }
            }
            if (result.contradiction && line)
            {
                result.contradiction = false;
            }
            if (result.tautology && !line)
            {
                result.tautology = false;
            }
            result.Results.insert(std::make_pair(list[i], line));
        }
        for (auto d = m_LResult.Variables.begin(); d != m_LResult.Variables.end(); d++)
        {
            if (depend[*d])
            {
                result.depend.push_back(*d);
            }
            if (notdepend[*d])
            {
                result.notdepend.push_back(*d);
            }
        }
    }
    else
    {
        result.tautology = false;
        result.contradiction = false;
        result.Results.insert(std::make_pair("", Calc()));
    }
    return result;
}
std::vector<char> Parser::getVariables()
{
    return Parser::m_LResult.Variables;
}

bool Parser::Level0()
{
    bool result = Level1();
    while (currentToken.getType() == Token::Types::AND ||
           currentToken.getType() == Token::Types::OR ||
           currentToken.getType() == Token::Types::EQUAL ||
           currentToken.getType() == Token::Types::NOT ||
           currentToken.getType() == Token::Types::IMPLICATION ||
           currentToken.getType() == Token::Types::XOR)
    {
        switch (currentToken.getType())
        {
        case Token::Types::AND:
            getNextToken();
            result = Level1() && result;
            break;
        case Token::Types::OR:
            getNextToken();
            result = Level1() || result;
            break;
        case Token::Types::EQUAL:
            getNextToken();
            result = result == Level1();
            break;
        case Token::Types::NOT:
            getNextToken();
            if (currentToken.getType() == Token::Types::EQUAL)
            {
                result = result != Level1();
            }
            break;
        case Token::Types::IMPLICATION:
            getNextToken();
            result = !(!Level1() && result);
            break;
        case Token::Types::XOR:
            getNextToken();
            result = Level1() ^ result;
            break;
        }
    }
    return result;
}
bool Parser::Level1()
{
    bool bnot = false;
    bool res = false;
    if (currentToken.getType() == Token::Types::NOT)
    {
        bnot = true;
        getNextToken();
    }
    if (currentToken.getType() == Token::Types::BOPEN)
    {
        getNextToken();
        res = Level0();
        getNextToken();
    }

    if (currentToken.getType() == Token::Types::VAR)
    {
        res = VarTable[currentToken.getValue()];
        getNextToken();
    }
    if (currentToken.getType() == Token::Types::NUM)
    {
        if (currentToken.getValue() == '1')
        {
            res = true;
        }
        else
        {
            res = false;
        }
        getNextToken();
    }
    if (bnot)
    {
        return !res;
    }
    return res;
}
void Parser::getNextToken()
{
    if (m_LResult.Tokens.size() > m_Pos + 1)
    {
        currentToken = m_LResult.Tokens[++m_Pos];
    }
}