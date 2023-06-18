#include "IntTem.h"
#include "Patterns.h"
#include "BookShop.h"
#include "Person.h"

void display() {
	std::cout << "Demonstation of patterns using mini-programms as code examples\n\n";
	std::cout << "1-2. Interpreter pattern and Template Method. This programm interprets string as maths expression\n\n";
	std::string input = "13-4+11-5-2";
	Expression* expression = buildExpression(input);
	int result = expression->interpret();
	
	std::cout << "Input: " << input << std::endl;
	std::cout << "Result: " << result << std::endl;
	
	delete expression;

	std::cout << "\n3. Observer pattern\n\n";
	Subject subject;
    ConcreteObserver observer;

    subject.attach(&observer);
    subject.notify("Hello, observers!");

    subject.detach(&observer);

	std::cout << "\n4-5. Factory and Strategy patterns. Example of using this patterns in a program Book Shop\n\n";
	BookShop bookShop;
	
	Book* book1 = BookFactory::createBook(BookFactory::BookType::Fiction, "The Green Mile", "Stephen King", 25.99);
	Book* book2 = BookFactory::createBook(BookFactory::BookType::NonFiction, "Good Omens", "Terry Pratchett & Neil Gaiman", 19.99);

	bookShop.addBook(book1);
	bookShop.addBook(book2);

	NoDiscountStrategy noDiscountStrategy;
	bookShop.setDiscountStrategy(&noDiscountStrategy);

	std::cout << "Books in Book Shop (No Discount):\n" << std::endl;
	bookShop.displayBooks();
	std::cout << std::endl;
	
	HalfPriceDiscountStrategy halfPriceDiscountStrategy;
	bookShop.setDiscountStrategy(&halfPriceDiscountStrategy);
	
	std::cout << "Books in Book Shop (Half Price Discount):\n" << std::endl;
	bookShop.displayBooks();

	std::cout << "\n6-8. Builder, Iterator and Decorator patterns. Personal details\n\n";
	PersonBuilder* builder1 = new ConcretePersonBuilder();
	builder1->setName("John Coffey");
	builder1->setAge(31);
	builder1->setAddress("7 Cold Mountain");
	Person person1 = builder1->build();

	PersonBuilder* builder2 = new ConcretePersonBuilder();
	builder2->setName("A. Z. Fell");
	builder2->setAge(46);
	builder2->setAddress("3 Soho");
	Person person2 = builder2->build();

	std::cout << "Using Iterator for traversing through data:\n\n";
	std::vector<Person> persons = { person1, person2 };
	PersonIterator iterator(persons);
	while (iterator.hasNext()) {
		Person currentPerson = iterator.next();
		currentPerson.printInfo();
	}

	std::cout << "Using Decorator to add new behavior:\n\n";
	PersonDecorator decorator(person2);
	decorator.printInfo();

	delete builder1;
	delete builder2;
}

int main() {
	display();
	return 0;
}