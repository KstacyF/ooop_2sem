#pragma once

#include <iostream>
#include <vector>

class Term {
	int deg;
	double coef;
    friend class Polynom;
public:
	Term(int deg = 0, double coef = 0.00);
	void print();
	bool operator==(const Term& other);
    Term operator*(const Term& other);
};

Term::Term(int deg, double coef) {
	this->deg = deg;
	this->coef = coef;
}

void Term::print() {
	if (deg == 0) {
		std::cout << coef;
		return;
	}
	if (coef != 1 && coef != -1) { std::cout << coef; }
	if (coef == -1) { std::cout << "-"; }
	std::cout << "x";
	if (deg > 1) { std::cout << "^" << deg; }
}

bool Term::operator==(const Term& other) {
	if (this->coef != other.coef || this->deg != other.deg) {
		return true;
	}
	return false;
}

Term Term::operator*(const Term& other) {
    Term result;
    result.coef = this->coef * other.coef;
    result.deg = this->deg + other.deg;
    return result;
}

class Polynom {
	std::vector<Term> polynom;
public:
    Polynom();
    Polynom(std::vector<Term> pol);
    Polynom(std::string pol);
	void add(Term to_add);
	void print();
    Polynom minus();
    bool operator==(const Polynom& other);
    Polynom operator+(const Polynom& other);
    Polynom operator-(Polynom& other);
    Polynom operator*(const Polynom& other);
    Polynom quotient(Polynom other);
    std::pair<Polynom, Polynom> operator/(const Polynom& other);
};

Polynom::Polynom() {
    this->polynom = {};
}

Polynom::Polynom(std::vector<Term> pol) {
    this->polynom = pol;
}

Polynom::Polynom(std::string pol) {
    std::size_t i = 0;
    double coef = 0.00;
    int deg = 0;
    while (i < pol.size()) {
        coef = 0;
        deg = 0;
        int p = 0;
        int k = 1;
        if (pol[i] == '+') i++;
        if (pol[i] == '-') {
            k = -1;
            i++;
        }
        while (pol[i] != 'x') {
            int c = pol[i] - '0';
            coef *= std::pow(10, p);
            coef += c;
            i++; p++;
        }
        coef *= k;
        i += 2;
        p = 0;
        while (isdigit(pol[i])) {
            int d = pol[i] - '0';
            deg *= std::pow(10, p);
            deg += d;
            i++; p++;
        }
        this->add({ deg, coef });
    }
}

void Polynom::add(Term to_add) {
    if (to_add.coef == 0)
        return;
    if (this->polynom.empty()) {
        this->polynom.push_back(to_add);
        return;
    }
    std::vector<Term>::iterator it = this->polynom.begin();
    while (it != this->polynom.end()) {
        if (it->deg > to_add.deg)
            it++;
        else
            break;
    }
    if (it == this->polynom.end()) {
        this->polynom.push_back(to_add);
        return;
    }
    if (it->deg == to_add.deg) {
        if (it->coef + to_add.coef == 0) {
            this->polynom.erase(it);
            return;
        }
        it->coef += to_add.coef;
        return;
    }
    this->polynom.insert(it, to_add);
}

void Polynom::print() {
    if (this->polynom.empty()) {
        std::cout << "Empty\n";
    }
    std::vector<Term>::iterator it = this->polynom.begin();
    for (it; it != this->polynom.end(); it++) {
        if (it != this->polynom.begin() && it->coef > 0)
            std::cout << "+";
        it->print();
    }
}

Polynom Polynom::minus() {
    Polynom minus;
    Term to_add;
    auto it = this->polynom.begin();
    while (it != this->polynom.end()) {
        to_add.deg = it->deg;
        to_add.coef = -1 * it->coef;
        minus.add(to_add);
        it++;
    }
    return minus;
}

bool Polynom::operator==(const Polynom& other) {
    auto it1 = this->polynom.begin();
    auto it2 = other.polynom.begin();
    while (it1 != this->polynom.end() && it2 != other.polynom.end()) {
        if (it1->coef != it2->coef || it1->deg != it2->deg)
            return false;
        it1++;
        it2++;
    }
    if (it1 != this->polynom.end() || it2 != other.polynom.end()) {
        return false;
    }
    return true;
}

Polynom Polynom::operator+(const Polynom& other) {
    Polynom result;
    Term to_add;
    auto it1 = this->polynom.begin();
    auto it2 = other.polynom.begin();
    while (it1 != this->polynom.end() || it2 != other.polynom.end()) {
        if (it1 != this->polynom.end()) {
            to_add.coef = it1->coef;
            to_add.deg = it1->deg;
            result.add(to_add);
            it1++;
        }
        if (it2 != other.polynom.end()) {
            to_add.coef = it2->coef;
            to_add.deg = it2->deg;
            result.add(to_add);
            it2++;
        }
    }
    return result;
}

Polynom Polynom::operator-(Polynom& other) {
    Polynom result = this->polynom;
    Polynom other_min = other.minus();
    result = result + other_min;
    return result;
}

Polynom Polynom::operator*(const Polynom& other) {
    Polynom result;
    Term to_add;
    auto it1 = this->polynom.begin();
    while (it1 != this->polynom.end()) {
        auto it2 = other.polynom.begin();
        Term one(it1->deg, it1->coef);
        while (it2 != other.polynom.end()) {
            Term two(it2->deg, it2->coef);
            to_add = one * two;
            result.add(to_add);
            it2++;
        }
        it1++;
    }
    return result;
}

Polynom Polynom::quotient(Polynom other) {
    Polynom result, p1, p2;
    Polynom tp = this->polynom;
    Term to_add;
    auto it1 = this->polynom.begin();
    auto it2 = other.polynom.begin();
    do {
        to_add.coef = it1->coef / it2->coef;
        to_add.deg = it1->deg - it2->deg;
        result.add(to_add);
        if (to_add.deg <= 0)
            return result;
        Polynom p3;
        p3.add(to_add);
        p1 = other * p3;
        p2 = tp - p1;
        tp = p2;
        it1 = p2.polynom.begin();
    } while (!p2.polynom.empty());
    return result;
}

std::pair<Polynom, Polynom> Polynom::operator/(const Polynom& other) {
    std::pair<Polynom, Polynom> result;
    if (this->polynom.empty() || other.polynom.empty()) {
        return result;
    }
    Polynom pol, tp = this->polynom;
    auto it1 = this->polynom.begin();
    auto it2 = other.polynom.begin();
    if (it1->deg < it2->deg) {
        result.second = other;
        return result;
    }
    result.first = this->quotient(other);
    pol = result.first* other;
    result.second = tp - pol;
    return result;
}