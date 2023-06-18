#pragma once

#include <iostream>
#include <string>
#include <vector>

class Book {
public:
    virtual std::string getTitle() = 0;
    virtual std::string getAuthor() = 0;
    virtual double getPrice() = 0;
};

class FictionBook : public Book {
private:
private:
    std::string title;
    std::string author;
    double price = 0.00;

public:
    FictionBook(const std::string& title, const std::string& author, const double& price) : title(title), author(author), price(price) {}

    std::string getTitle() override {
        return title;
    }

    std::string getAuthor() override {
        return author;
    }

    double getPrice() override {
        return price;
    }
};

class NonFictionBook : public Book {
private:
    std::string title;
    std::string author;
    double price = 0.00;

public:
    NonFictionBook(const std::string& title, const std::string& author, const double& price) : title(title), author(author), price(price) {}

    std::string getTitle() override {
        return title;
    }

    std::string getAuthor() override {
        return author;
    }

    double getPrice() override {
        return price;
    }
};

// Factory
class BookFactory {
public:
    enum class BookType {
        Fiction,
        NonFiction
    };

    static Book* createBook(BookType type, const std::string& title, const std::string& author, const double& price) {
        switch (type) {
        case BookType::Fiction:
            return new FictionBook(title, author, price);
        case BookType::NonFiction:
            return new NonFictionBook(title, author, price);
        default:
            return nullptr;
        }
    }
};

// Strategy
class DiscountStrategy {
public:
    virtual double applyDiscount(double price) const = 0;
};

class NoDiscountStrategy : public DiscountStrategy {
public:
    double applyDiscount(double price) const override {
        return price;
    }
};

class HalfPriceDiscountStrategy : public DiscountStrategy {
public:
    double applyDiscount(double price) const override {
        return price * 0.5;
    }
};

class BookShop {
private:
    std::vector<Book*> books;
    DiscountStrategy* discountStrategy;

public:
    void setDiscountStrategy(DiscountStrategy* strategy) {
        discountStrategy = strategy;
    }

    void addBook(Book* book) {
        books.push_back(book);
    }

    void displayBooks() const {
        for (auto book : books) {
            std::cout << "Title: " << book->getTitle() << std::endl;
            std::cout << "Author: " << book->getAuthor() << std::endl;
            std::cout << "Price: " << discountStrategy->applyDiscount(book->getPrice()) << std::endl;
            std::cout << "---------------------" << std::endl;
        }
    }
};