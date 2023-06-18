#pragma once

#include <iostream>
#include <vector>

// Observer
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "ConcreteObserver received message: " << message << std::endl;
    }
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        for (auto it = observers.begin(); it != observers.end(); it++) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};