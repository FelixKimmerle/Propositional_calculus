#include "Possibilities.h"
namespace Possibilities
{
	void combi(std::string &data, const std::string &characters, int pos, std::vector<std::string> &liste)
	{
		if (pos == data.size())
		{
			liste.push_back(data);
		}
		else
		{
			for (int i = 0; i < characters.size(); ++i)
			{
				data[pos] = characters[i];
				combi(data, characters, pos + 1, liste);
			}
		}
	}

	std::vector<std::string> calc(const std::string &table, size_t length)
	{
		std::vector<std::string> liste;
		std::string t(length, table[0]);
		combi(t, table, 0, liste);
		return liste;
	}

	void combibool(std::string &data, int pos, std::vector<std::string> &liste)
	{
		if (pos == data.size())
		{
			liste.push_back(data);
		}
		else
		{
			for (int i = 0; i < 2; ++i)
			{
				data[pos] = i;
				combibool(data, pos + 1, liste);
			}
		}
	}

	std::vector<std::string> calcboolean(size_t length)
	{
		std::vector<std::string> liste;
		std::string t(length,' ');
		combibool(t, 0, liste);
		return liste;
	}
}
