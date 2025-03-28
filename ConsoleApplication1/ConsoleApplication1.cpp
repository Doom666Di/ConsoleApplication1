/*
* 
Исходный
контейнер list, копируем в
vector
*/
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <unordered_set>
#include <algorithm>

struct Depos_val
{
	std::string name;
	int value;
	std::string type;
	double rate;
};

class Depos {
	std::string name;
	int value;
	std::string type;
	double rate;
public:
	Depos() : name(""), value(0), type(""), rate(0) {}
	Depos(std::string name_, int value_, std::string type_, double rate_) : name(name_), value(value_), type(type_), rate(rate_) {}
	Depos(const Depos& p) : name(p.name), value(p.value), type(p.type), rate(p.rate) {}
	Depos(Depos&& p) : name(p.name), value(p.value), type(p.type), rate(p.rate) {}

	Depos& operator=(const Depos& p) {
		if (this != &p) {
			name = p.name;
			value = p.value;
			type = p.type;
			rate = p.rate;
		}
		return *this;
	}
	Depos& operator=(Depos&& p) {
		if (this != &p) {
			name = std::move(p.name);
			value = p.value;
			type = std::move(p.type);
			rate = p.rate;
		}
		return *this;
	}
	Depos_val get() const {
		const Depos_val _ = { name, value, type, rate };
		return _;
	}
	bool operator<(const Depos& p) const { return value < p.value; }
	bool operator>(const Depos& p) const { return value > p.value; }
	bool operator==(const Depos& p) const { 
		return value == p.value &&
			name == p.name &&
			type == p.type &&
			rate == p.rate; }
	friend std::ostream& operator<<(std::ostream& out, const Depos& ob);
};

std::ostream& operator<<(std::ostream& out, const Depos& ob)
{
	out << ob.name << " " << ob.value << " " << ob.type << " " << ob.rate << std::endl;
	return out;
}

struct Depos_hasher
{
	std::hash<std::string> hname;
	std::hash<int> hvalue;
	std::hash <std::string> htype;
	std::hash<double> hrate;
	size_t operator()(const Depos& _) const {
		const size_t coef = 2'946'901;
		Depos_val obj = _.get();
		return (coef * coef * coef * hname(obj.name) +
				coef * coef * hvalue(obj.value) +
				coef * htype(obj.type) +
				hrate(obj.rate));
	}
};

int main() {
	std::unordered_set<Depos, Depos_hasher> dep;
	std::set<Depos> c_dep;
	std::ifstream in("input.txt");
	for (int i = 0; i < 3; i++) {
		std::string name, type;
		int value; double rate;
		in >> name >> value >> type >> rate;
		dep.insert(Depos(name, value, type, rate));
	}
	in.close();
	for (auto i : dep) {
		c_dep.insert(i);
	}
	std::ofstream out("output.txt");
	for (auto i : c_dep) {
		out << i;
	}
	return 1;
}