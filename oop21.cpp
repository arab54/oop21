#include <iostream>
#include "Container.h"
#include "Objects.h"
#include "TaskFactory.h"


int Object::sm_objectNum = 0;


int main() {
	srand(unsigned(time(0)));

	Container<Task*> tasks;
	
	TaskFactory factory;
	for (int i = 0; i < 10; i++) {
		tasks.addLast(factory.createRandomTask());
	}

	Container<std::string> results;

	std::cout << Object::getObjectNum() << std::endl;

	tasks.resetIterator();
	while (tasks.hasNext()) {
		Task* task = tasks.getNext();
		task->execute();
		std::string result = task->toString();
		results.addLast(result);
	}
	
	results.resetIterator();
	while (results.hasNext()) {
		std::string result = results.getNext();
		std::cout << result << std::endl;
	}

	while (!tasks.isEmpty()) {
		Task* task = tasks.getFirst();
		tasks.removeFirst();
		delete task;
	}

	std::cout << Object::getObjectNum() << std::endl;
}


