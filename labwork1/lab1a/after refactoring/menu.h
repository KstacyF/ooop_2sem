#pragma once

#include "polynom.h"

class Storage {
	std::vector<Polynom> storage;

public:
	std::size_t size;

	Storage() {
		this->storage = {};
		size = 0;
	}

	void add(Polynom to_add) {
		for (auto i : this->storage) {
			if (i == to_add) {
				std::cout << "\nPolynomial is already in the storage!\n";
				return;
			}
		}
		storage.push_back(to_add);
		size++;
	}

	void print() {
		std::size_t s = 1;
		for (auto i : this->storage) {
			std::cout << s << ". ";
			i.print();
			std::cout << "\n";
			s++;
		}
	}

	Polynom get(std::size_t pos) {
		return this->storage[pos];
	}
};

void mod(std::string& str) {
	std::size_t i = 0, s = str.size();
	std::string res = "";
	while (i < s) {
		while (str[i] == ' ' && i < s)
			i++;
		if ((str[i] == '+' || str[i] == '-') && i < s) {
			res += str[i];
			i++;
		}
		while (str[i] == ' ' && i < s)
			i++;
		if (!isdigit(str[i]) && i < s) {
			res += "1";
		}
		while (isdigit(str[i]) && i < s) {
			res += str[i];
			i++;
		}
		while (str[i] == ' ' && i < s)
			i++;
		if (str[i] == '*' && i < s)
			i++;
		while (str[i] == ' ' && i < s)
			i++;
		if (str[i] != 'x' && i <= s) {
			res += "x^0";
			str = res;
			continue;
		}
		else {
			res += str[i];
			i++;
		}
		while ((str[i] != '^' && str[i] != '+' && str[i] != '-') && i < s)
			i++;
		if (str[i] == '^') {
			res += str[i];
			i++;
		}
		else {
			res += "^1";
			continue;
		}
		while (!isdigit(str[i]) && i < s)
			i++;
		while (isdigit(str[i]) && i < s) {
			res += str[i];
			i++;
		}
	}
	str = res;
	return;
}

void demo() {
	Storage st;
	Polynom p1("1x^2+3x^1+5x^0");
	Polynom p2("1x^4+4x^2+3x^0");
	Polynom p3("1x^1+1x^0");
	Polynom p4("1x^4+1x^3-3x^1+7x^0");
	Polynom p5("1x^2-4x^0");
	st.add(p1);
	st.add(p2);
	st.add(p3);
	st.add(p4);
	st.add(p5);
	Polynom p6 = p1 + p2;
	Polynom p7 = p3 * p3;
	std::pair<Polynom, Polynom> d = p4 / p5;
	Polynom quo = d.first;
	Polynom rem = d.second;
	std::cout << "This program allows you to perform some operations with polynomials, such as addition, multiplication or division.\nOur polynomials:\n";
	st.print();
	std::cout << "\nAddition: ";
	p1.print();
	std::cout << " + ";
	p2.print();
	std::cout << " = ";
	p6.print();
	std::cout << "\n\nMultiplication: ";
	p3.print();
	std::cout << " * ";
	p3.print();
	std::cout << " = ";
	p7.print();
	std::cout << "\n\nDivision: ";
	p4.print();
	std::cout << " / ";
	p5.print();
	std::cout << " = ";
	quo.print();
	std::cout << ", remainder = ";
	rem.print();
	std::cout << "\nThe end of demonstration\n\n";
}

void inter() {
	Storage st;
	st.add(Polynom("1x^1"));
	Polynom p1, p2, p3;
	std::pair<Polynom, Polynom> d;
	std::string pol, pol1, pol2;
	int choice;
	int c1, c2;
	do {
		std::cout << "Enter new polynomial (1), print polynomials from storage (2), perform addition (3), multiplication (4) or division (5). For exit print (0): ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "\nEnter polynomial: ";
			std::cin >> pol;
			mod(pol);
			st.add(Polynom(pol));
			break;
		case 2:
			std::cout << "\nStorage:\n";
			st.print();
			break;
		case 3:
			std::cout << "\nStorage:\n";
			st.print();
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the first polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "First polynomial: ";
					std::cin >> pol1;
					mod(pol1);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol1));
					p1 = Polynom(pol1);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p1 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the second polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "Second polynomial: ";
					std::cin >> pol2;
					mod(pol2);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol2));
					p2 = Polynom(pol2);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p2 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			std::cout << "Addition result: ";
			p3 = p1 + p2;
			p3.print();
			std::cout << "\nResult added to storage";
			st.add(p3);
			std::cout << "\n";
			break;
		case 4:
			std::cout << "\nStorage:\n";
			st.print();
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the first polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "First polynomial: ";
					std::cin >> pol1;
					mod(pol1);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol1));
					p1 = Polynom(pol1);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p1 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the second polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "Second polynomial: ";
					std::cin >> pol2;
					mod(pol2);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol2));
					p2 = Polynom(pol2);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p2 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			std::cout << "Multiplication result: ";
			p3 = p1 * p2;
			p3.print();
			std::cout << "\nResult added to storage";
			st.add(p3);
			std::cout << "\n";
			break;
		case 5:
			std::cout << "\nStorage:\n";
			st.print();
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the first polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "First polynomial: ";
					std::cin >> pol1;
					mod(pol1);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol1));
					p1 = Polynom(pol1);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p1 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			do {
				std::cout << "\nDo you want to enter (1) or choose (2) the second polynomial? ";
				std::cin >> c1;
				switch (c1) {
				case 1:
					std::cout << "Second polynomial: ";
					std::cin >> pol2;
					mod(pol2);
					std::cout << "Polynomial is added to the storage\n";
					st.add(Polynom(pol2));
					p2 = Polynom(pol2);
					break;
				case 2:
					do {
						std::cout << "Enter the number of polynomial from the storage: ";
						std::cin >> c2;
						if (c2 < st.size) {
							p2 = st.get(c2 - 1);
						}
					} while (c2 > st.size);
				}
			} while (c1 != 1 && c1 != 2);
			std::cout << "Division result: ";
			d = p1 / p2;
			d.first.print();
			std::cout << ", remainder = ";
			d.second.print();
			std::cout << "\nQuotient and remainder added to storage";
			st.add(d.first);
			st.add(d.second);
			std::cout << "\n";
			break;
		case 0:
			break;
		}
	} while (choice);
}

void menu() {
	int choice;
	do {
		std::cout << "Choose demo version (1), interactive mode (2) or Exit (0): ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			demo();
			break;
		case 2:
			inter();
			break;
		case 0:
			std::cout << "Exiting... ";
		}
	} while (choice);
	std::cout << "Done!";
}