#pragma once
#include <iostream>
class Token
{
  public:
	enum Types
	{
		VAR,
		AND,
		OR,
		EQUAL,
		NOT,
		IMPLICATION,
		BOPEN,
		BCLOSE,
		NUM,
		XOR,
	};
	Token(Types Type, char Value, int Pos)
	{
		m_Type = Type;
		m_Value = Value;
		m_Pos = Pos;
	}
	Token() {}
	Types getType()
	{
		return m_Type;
	}
	char getValue()
	{
		return m_Value;
	}
	int getPos()
	{
		return m_Pos;
	}

  private:
	Types m_Type;
	char m_Value;
	int m_Pos;
};
