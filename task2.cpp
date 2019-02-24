#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

struct Entity
{
	std::string Query;
	float Frequency;
	bool equal(std::string s) const {
		if (Query == s) return true;
		else return false;
	}
};
using Dict = std::multimap<std::string, Entity>;

std::multimap<std::string, Entity> load(const std::string& filename) {
	std::ifstream file(filename);
	std::multimap<std::string, Entity> mulmap;
	if (file.is_open()) {
		while (file) {
			std::string line;
			std::getline(file, line);
			std::istringstream stream(line);
			std::vector<std::string> data((std::istream_iterator<std::string>(stream)), std::istream_iterator<std::string>());
			if (data.size() == 3) {
				mulmap.emplace(data[0], Entity{ data[1],std::stof(data[2]) });
			}
		}
	}
	return mulmap;
}

std::vector<Entity> suggest(const Dict& m, const std::string& currentWord) {
	std::vector<Entity> res;
	for (auto it = m.begin(); it != m.end(); ++it) {
		std::pair<std::string, Entity> a = *it;
		if (a.first == currentWord) {
			res.push_back(it->second);
		}
	}
	std::sort(res.begin(), res.end(), [](Entity b, Entity c) {return b.Frequency > c.Frequency; });
	return res;
}

int main() {
	setlocale(LC_ALL, "RUS");
	auto dict = load("input.txt");
	for (auto& p : dict) {
		std::cout << p.first << " " << p.second.Query << " " << p.second.Frequency << '\n';
	}
	std::cout << '\n';
	auto result = suggest(dict, "добрый");
	for (auto& a : result) {
		std::cout << a.Query << " " << a.Frequency << '\n';
	}
	return 0;
}
