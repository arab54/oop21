#pragma once

#include <string>
#include <cassert>
#include "Container.h"

class Object {
public:
	Object() {
		sm_objectNum++;
	}

	virtual ~Object() {
		sm_objectNum--;
	}

	virtual std::string toString() = 0;

	static int getObjectNum() {
		return sm_objectNum;
	}

private:
	static int sm_objectNum;
};


class Task : public virtual Object {
public:
	Task() : m_result("<not_executed>") {}

	virtual void execute() = 0;

	std::string toString() {
		return m_result;
	}
protected:
	std::string m_result;
};


class Named : public virtual Object {
public:
	Named(std::string name) : m_name(name) {}

	std::string toString() {
		return "my name is " + m_name;
	}

protected:
	std::string m_name;
};


class Arithmetic : public virtual Task, public virtual Named {
public:
	enum class Op { Add, Sub, Mul, Div };

	Arithmetic(Op op, int arg1, int arg2, std::string name) :
		Task(), Named(name), m_op(op), m_arg1(arg1), m_arg2(arg2) {}

	void execute() {
		switch (m_op) {
		case Op::Add:
			m_result = std::to_string(m_arg1) + " + " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 + m_arg2);
			break;
		case Op::Sub:
			m_result = std::to_string(m_arg1) + " - " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 - m_arg2);
			break;
		case Op::Mul:
			m_result = std::to_string(m_arg1) + " * " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 * m_arg2);
			break;
		case Op::Div:
			m_result = std::to_string(m_arg1) + " / " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 / m_arg2);
			break;
		default:
			throw std::logic_error("Unknown binary arithmeric operation ");
		}
	}

	std::string toString() {
		return Named::toString() + ": " + Task::toString();
	}

private:
	Op m_op;
	int m_arg1;
	int m_arg2;
};

class Adder : public virtual Task {
public:
	Adder(Container<Task*>* container, Task* task) :
		m_container(container),
		m_task(task) {}

	~Adder() {
		m_container->resetIterator();
		while (m_container->hasNext()) {
			Object* obj = m_container->getNext();
			delete obj;
		}
		delete m_container;
	}

	void execute() {
		m_container->addLast(m_task);
		m_result = "added";
	}

private:
	Container<Task*>* m_container;
	Task* m_task;
};

class Counter : public virtual Task {
public:
	Counter(Container<Object*>* container) :
		m_container(container) {}

	~Counter() {
		m_container->resetIterator();
		while (m_container->hasNext()) {
			Object* obj = m_container->getNext();
			delete obj;
		}
		delete m_container;
	}

	void execute() {
		m_result = "Num of objects in container: " + std::to_string(m_container->getSize());
	}

private:
	Container<Object*>* m_container;
};


class Cleaner : public virtual Task {
public:
	Cleaner(Container<Object*>* container) :
		m_container(container) {}
	
	~Cleaner() {
		assert(m_container->isEmpty());
		delete m_container;
	}

	void execute() {
		m_container->resetIterator();
		while (m_container->hasNext()) {
			Object* obj = m_container->getNext();
			delete obj;
		}
		m_container->clear();
		m_result = "cleaned";
	}

private:
	Container<Object*>* m_container;
};


class ObjectCountGetter : public virtual Task {
public:
	~ObjectCountGetter() {}

	void execute() {
		m_result = "Object count: " + std::to_string(Object::getObjectNum());
	}
};
