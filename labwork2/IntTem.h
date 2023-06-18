#pragma once

// Приклад використання паттернів Interpreter та Template Method у міні-програмі,
// яка інтерпретує рядок у вираз і обчислює його значення

#include <iostream>
#include <string>
#include <stack>

// Абстрактний базовий клас для виразу
class Expression {
public:
    virtual int interpret() = 0;
};

// Клас виразу для числа
class NumberExpression : public Expression {
private:
    int number;

public:
    NumberExpression(int number) : number(number) {}

    int interpret() override {
        return number;
    }
};

// Клас виразу для додавання
class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

// Клас виразу для віднімання
class SubtractExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    SubtractExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret() override {
        return left->interpret() - right->interpret();
    }
};

// Клас контексту, що інтерпретує вираз
class InterpreterContext {
private:
    std::stack<Expression*> expressions;

public:
    void pushExpression(Expression* expression) {
        expressions.push(expression);
    }

    Expression* popExpression() {
        if (!expressions.empty()) {
            Expression* expression = expressions.top();
            expressions.pop();
            return expression;
        }
        return nullptr;
    }
};

// Функція для побудови виразу із рядка
Expression* buildExpression(const std::string& input) {
    InterpreterContext context;

    std::size_t s = input.size();
    std::size_t i = 0;

    while (i < s) {
        char op = '!';
        if (input[i] == '+') {
            op = '+';
            i++;
        }
        else if (input[i] == '-') {
            op = '-';
            i++;
        }

        int number = input[i] - '0';
        if (i < s) {
            i++;
        }
        
        while (isdigit(input[i]) && i < s && s > 1) {
            number *= 10;
            number += (input[i] - '0');
            i++;
        }

        Expression* expression = new NumberExpression(number);
        context.pushExpression(expression);

        if (op == '+') {
            Expression* right = context.popExpression();
            Expression* left = context.popExpression();
            Expression* expression1 = new AddExpression(left, right);
            context.pushExpression(expression1);
        }
        else if (op == '-') {
            Expression* right = context.popExpression();
            Expression* left = context.popExpression();
            Expression* expression1 = new SubtractExpression(left, right);
            context.pushExpression(expression1);
        }
    }

    return context.popExpression();
}