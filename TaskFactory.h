#pragma once

#include "Container.h"
#include "Objects.h"

class TaskFactory {
public:
    Arithmetic* createArithmetic() {
        Arithmetic::Op op = Arithmetic::Op(getRandomInt() % 4);
        int arg1 = getRandomInt();
        int arg2 = getRandomInt();
        std::string name = "a" + std::to_string(getRandomInt());
        return new Arithmetic(op, arg1, arg2, name);
    }

    Adder* createAdder() {
        Container<Task*>* container = createAndFillTaskContainer();
        Task* task = createArithmetic();
        return new Adder(container, task);
    }

    Counter* createCounter() {
        Container<Object*>* container = createAndFillObjectContainer();
        return new Counter(container);
    }

    Cleaner* createCleaner() {
        Container<Object*>* container = createAndFillObjectContainer();
        return new Cleaner(container);
    }

    ObjectCountGetter* createObjectCountGetter() {
        return new ObjectCountGetter();
    }

    Task* createRandomTask() {
        switch (std::rand() % 5) {
        case 0: return createArithmetic();
        case 1: return createAdder();
        case 2: return createCounter();
        case 3: return createCleaner();
        case 4: return createObjectCountGetter();
        default: return nullptr;
        }
    }

private:
    Container<Task*>* createAndFillTaskContainer() {
        Container<Task*>* container = new Container<Task*>;
        for (int i = 0; i < getRandomInt(); i++) {
            container->addLast(createArithmetic());
        }
        return container;
    }

    Container<Object*>* createAndFillObjectContainer() {
        Container<Object*>* container = new Container<Object*>;
        for (int i = 0; i < getRandomInt(); i++) {
            container->addLast(createArithmetic());
        }
        return container;
    }

    int getRandomInt() {
        return std::rand() % 100;
    }
};
