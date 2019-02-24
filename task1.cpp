#include <iostream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

struct Student
{
	std::string Name;
	std::string GroupId;
	std::map<std::string, unsigned> Ratings;

	Student(std::string Name, std::map<std::string, unsigned> Ratings) {
		this->Name = Name;
		this->Ratings = Ratings;
	}

	float adv() {
		float summ = 0;
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			summ += (*i).second;
		}
		return summ / Ratings.size();
	}
	bool bad_result() {
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			if ((*i).second <= 2) {
				return true;
			}
		}
		return false;
	}
	bool exams_result() {
		bool result = false;
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			if ((*i).second == 5) result = true;
			else {
				result = false;
				break;
			}
		}
		return result;
	}
	bool good_math() {
		if (this->Ratings["Math"] == 5) {
			return true;
		}
		return false;
	}

	void get_mark()
	{
		Ratings["Politology"] = 5;
	}

};

void print(const Student &s) {
	std::cout << s.Name << '\n';
	for (auto it = s.Ratings.begin(); it != s.Ratings.end(); ++it) {
		std::cout << it->first << ":" << it->second << '\n';
	}
	std::cout << '\n' << '\n';
}


int main() {
	Student v1("Ivanov", { {"Math",3},{"Politology",4},{"English",2} }),
		v2("Sidorov", { {"Math",4},{"Politology",4},{"English",5} }),
		v3("Kozlov", { {"Math",5},{"Politology",5},{"English",5} });
	std::vector<Student> students{ v1,v2,v3 };

	std::cout << "Alphabеt order:" << '\n';
	std::sort(students.begin(), students.end(), [](const Student a, const Student b) {
		return (a.Name.compare(b.Name) < 0);
	});
	std::for_each(students.begin(), students.end(), print);

	std::cout << "Average mark:" << '\n';
	std::sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.adv() > b.adv());
	});
	std::for_each(students.begin(), students.end(), print);

	std::cout << "How many students have '2': " << '\n';
	unsigned long c = 0;
	c = std::count_if(students.begin(), students.end(), [](Student a) {
		return (a.bad_result());
	});
	std::cout << c << '\n';

	std::cout << "How many students have all '5':" << '\n';
	unsigned long a = 0;
	a = std::count_if(students.begin(), students.end(), [](Student a) {
		return (a.exams_result());
	});
	std::cout << a << '\n';

	std::cout << "Students have '5' for Math:" << '\n';
	std::vector<Student> target;
	std::copy_if(students.begin(), students.end(), std::back_inserter(target), [](Student a) {
		return a.good_math();
	});
	std::for_each(target.begin(), target.end(), print);

	std::cout << "Students have '4' for Politology:" << '\n';
	std::transform(students.begin(), students.end(), students.begin(), [](Student a) {
		a.get_mark();
		return a;
	});
	std::for_each(students.begin(), students.end(), print);
	return 0;
}
