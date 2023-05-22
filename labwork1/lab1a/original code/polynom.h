#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Term {
    int deg;
    double coef;

    Term(int deg = 0, double coef = 0.00) {
        this->deg = deg;
        this->coef = coef;
    }

    void print() {
        if (deg == 0) {
            std::cout << coef;
            return;
        }
        if (coef != 1 && coef != -1) { std::cout << coef; }
        if (coef == -1) { std::cout << "-"; }
        std::cout << "x";
        if (deg > 1) { std::cout << "^" << deg; }
    }

    bool operator!=(const Term& other) {
        if (this->coef != other.coef || this->deg != other.deg) {
            return true;
        }
        return false;
    }
};

struct Polynom {
    Term term;
    Polynom* next;
    Polynom* prev;

    Polynom(Term term = { 0, 0.00 }, Polynom* next = nullptr, Polynom* prev = nullptr) {
        this->term = term;
        this->next = next;
        this->prev = prev;
    }

    Polynom(std::string pol) { // x^3 + 2x^1 - 3x^0
        this->next = nullptr;
        this->prev = nullptr;
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

    Polynom* lead = nullptr;

    void add(Term term) {
        if (term.coef == 0) { return; }
        Polynom* new_term = new Polynom;
        new_term->term = term;
        if (!lead) {
            new_term->next = nullptr;
            new_term->prev = nullptr;
            lead = new_term;
            return;
        }
        Polynom* curr = lead;
        while (curr->term.deg > term.deg && curr->next) {
            curr = curr->next;
        }
        if (curr == lead) {
            if (curr->term.deg > term.deg) {
                new_term->prev = lead;
                lead->next = new_term;
                new_term->next = nullptr;
                return;
            }
            if (curr->term.deg < term.deg) {
                new_term->prev = nullptr;
                new_term->next = lead;
                lead->prev = new_term;
                lead = new_term;
                return;
            }
            lead->term.coef += new_term->term.coef;
            if (lead->term.coef == 0) { lead = nullptr; }
            return;
        }
        if (curr->term.coef + new_term->term.coef == 0) {
            curr->prev->next = curr->next;
            if (curr->next) { curr->next->prev = curr->prev; }
            return;
        }
        if (curr->term.deg == new_term->term.deg) {
            curr->term.coef += new_term->term.coef;
            return;
        }
        if (curr->next) {
            curr->next->prev = new_term;
            new_term->next = curr->next;
        }
        else { new_term->next = nullptr; }
        curr->next = new_term;
        new_term->prev = curr;
    }

    void print() {
        if (!lead) {
            std::cout << "No terms\n\n";
            return;
        }
        Polynom* curr = lead;
        while (curr) {
            if (curr->prev && curr->term.coef > 0) { std::cout << "+"; }
            curr->term.print();
            curr = curr->next;
        }
    }

    bool operator==(const Polynom& other) {
        Polynom* one = this->lead;
        Polynom* two = other.lead;
        while (one && two) {
            if (one->term != two->term) {
                return false;
            }
            one = one->next;
            two = two->next;
        }
        if (one || two) {
            return false;
        }
        return true;
    }
};

Polynom sum(Polynom* one, Polynom* two) {
    Polynom three;
    Term to_add;
    while (one || two) {
        if (!one) {
            three.add(two->term);
            two = two->next;
            continue;
        }
        if (!two) {
            three.add(one->term);
            one = one->next;
            continue;
        }
        if (one->term.deg < two->term.deg) {
            three.add(two->term);
            two = two->next;
            continue;
        }
        if (one->term.deg > two->term.deg) {
            three.add(one->term);
            one = one->next;
            continue;
        }
        to_add.coef = one->term.coef + two->term.coef;
        to_add.deg = one->term.deg;
        three.add(to_add);
        one = one->next;
        two = two->next;
    }
    return three;
}

void minus(Term& term) {
    term.coef *= -1;
}

void minus(Polynom*& pol) {
    Polynom* curr = pol;
    while (curr) {
        minus(curr->term);
        curr = curr->next;
    }
}

Term multi_term(Term one, Term two) {
    Term three;
    three.coef = one.coef * two.coef;
    three.deg = one.deg + two.deg;
    return three;
}

Polynom multi(Polynom* one, Polynom* two) {
    Polynom three;
    Term to_add;
    Polynom* curr;
    while (one) {
        curr = two;
        while (curr) {
            to_add = multi_term(one->term, curr->term);
            three.add(to_add);
            curr = curr->next;
        }
        one = one->next;
    }
    return three;
}

Polynom multi(Polynom* one, Term two) {
    Polynom three;
    Term to_add;
    while (one) {
        to_add = multi_term(one->term, two);
        three.add(to_add);
        one = one->next;
    }
    return three;
}

struct Division {
    Polynom quotient;
    Polynom remainder;

    Division(Polynom quotient = { {0, 0.00}, nullptr, nullptr }, Polynom remainder = { {0, 0.00}, nullptr, nullptr }) {
        this->quotient = quotient;
        this->remainder = remainder;
    }

    void print() {
        std::cout << "quotient = ";
        if (!quotient.lead) { std::cout << 0; }
        else { quotient.print(); }
        std::cout << " ,  remainder = ";
        if (!remainder.lead) { std::cout << 0; }
        else { remainder.print(); }
    }
};

Polynom part(Polynom* one, Polynom* two) {
    Polynom pol, pol1, pol2;
    Term to_add;
    Polynom* one_l = one;
    while (one_l) {
        to_add.coef = one_l->term.coef / two->term.coef;
        to_add.deg = one_l->term.deg - two->term.deg;
        pol.add(to_add);
        if (to_add.deg == 0) {
            return pol;
        }
        pol1 = multi(two, to_add);
        minus(pol1.lead);
        pol2 = sum(one_l, pol1.lead);
        one_l = pol2.lead;
    }
    return pol;
}

Division div(Polynom one, Polynom two) {
    Division three;
    Polynom* one_lead = one.lead;
    Polynom* two_lead = two.lead;
    Polynom pol;
    Term to_add;
    if (one_lead->term.deg < two_lead->term.deg) {
        three.quotient.term = { 0, 0.00 };
        three.quotient.next = nullptr;
        three.quotient.prev = nullptr;
        three.remainder = one;
        return three;
    }
    three.quotient = part(one_lead, two_lead);
    pol = multi(three.quotient.lead, two_lead);
    minus(pol.lead);
    three.remainder = sum(one_lead, pol.lead);
    return three;
}