#include <iostream>
#include <string>
#include <vector>

class Person {
public:
    std::string name;
    int age;
    std::string address;

    void printInfo() const {
        std::cout << "Name: " << name << "\nAge: " << age << "\nAddress: " << address << "\n\n";
    }
};

// Builder
class PersonBuilder {
public:
    virtual void setName(const std::string& name) = 0;
    virtual void setAge(int age) = 0;
    virtual void setAddress(const std::string& address) = 0;
    virtual Person build() const = 0;
};

class ConcretePersonBuilder : public PersonBuilder {
private:
    Person person;

public:
    void setName(const std::string& name) override {
        person.name = name;
    }

    void setAge(int age) override {
        person.age = age;
    }

    void setAddress(const std::string& address) override {
        person.address = address;
    }

    Person build() const override {
        return person;
    }
};

// Iterator
class PersonIterator {
private:
    std::vector<Person> persons;
    int currentIndex;

public:
    PersonIterator(const std::vector<Person>& persons) : persons(persons), currentIndex(0) {}

    bool hasNext() const {
        return currentIndex < persons.size();
    }

    Person next() {
        return persons[currentIndex++];
    }
};

// Decorator
class PersonDecorator {
private:
    Person person;

public:
    PersonDecorator(const Person& person) : person(person) {}

    void printInfo() const {
        std::cout << "Name: " << person.name << "\nAge: " << person.age << "\nAddress: " << person.address << std::endl;
        std::cout << "This person is awesome!\n\n";
    }
};