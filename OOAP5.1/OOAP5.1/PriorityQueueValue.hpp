#ifndef PRIORITYQUEUEVALUE_HPP
#define PRIORITYQUEUEVALUE_HPP

template <typename T>
class PriorityQueueValue
{
private:
	T v;
	double p;

protected:
	void setValue(T val){
		this->v = val;
	}

public:
	PriorityQueueValue(T val, double prt){
		this->setValue(val);
		this->setPriority(prt);
	}

	PriorityQueueValue(const PriorityQueueValue<T>& rhs){
		this->setValue(rhs->getValue());
		this->setPriority(rhs->getPriority());
	}

	void setPriority(double prt){
		this->p = prt;
	}

	T getValue(){
		return this->v;
	}

	double getPriority(){
		return this->p;
	}

	operator double(){
		return this->getPriority();
	}

	operator T(){
		return this->getValue();
	}
};

#endif