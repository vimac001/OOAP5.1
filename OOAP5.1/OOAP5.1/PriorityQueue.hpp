#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include "PriorityQueueEntry.hpp"
#include "QueueException.hpp"

template <typename T>
class PriorityQueue
{
private:
	unsigned int length;

	PriorityQueueEntry<T> *p_ptree; //Priority Tree
	PriorityQueueEntry<T> *p_vtree; //Value Tree
	PriorityQueueEntry<T> *p_minen; //Entry with highest priority (lowest priority num)

public:
	PriorityQueue(){
		this->length = 0;
		this->p_ptree = nullptr;
		this->p_vtree = nullptr;
		this->p_minen = nullptr;
	}

	unsigned int getLength(){
		return this->length;
	}

	bool isEmpty(){
		return this->getLength() <= 0;
	}

	void insertValue(PriorityQueueValue<T> *v){
		PriorityQueueEntry<T> *pe = new PriorityQueueEntry<T>(v),
							  *ve = new PriorityQueueEntry<T>(v);

		pe->setTwin(ve);
		ve->setTwin(pe);

		if(this->isEmpty()){
			this->p_ptree = pe;
			this->p_vtree = ve;
			this->p_minen = pe;
		}else{
			this->p_ptree->append<double>(pe);
			this->p_vtree->append<T>(ve);

			if((double)*pe->getValue() < (double)*this->p_minen->getValue()){
				this->p_minen = pe;
			}
		}


		this->length++;
	}

	void insert(T value, double priority){
		PriorityQueueValue<T> *v = new PriorityQueueValue<T>(value, priority);
		this->insertValue(v);
	}

	void remove(T value){
		PriorityQueueEntry<T> *e = this->findEntry(value);
		PriorityQueueValue<T> *rv = this->removeEntry(e);
		if(rv != nullptr){
			delete rv;
		}
	}

	PriorityQueueValue<T> *removeEntry(PriorityQueueEntry<T> *e){
		PriorityQueueValue<T> *rv = nullptr;
		if(e != nullptr){
			PriorityQueueEntry<T> *te = e->getTwin();

			if(te->getValue()->getPriority() <= this->p_minen->getValue()->getPriority()){
				if(te->hasRight()){
					this->p_minen = te->getRight()->getMostLeft();
				}else{
					this->p_minen = te->getParent();
				}

			}

			rv = te->remove(&this->p_ptree);
			e->remove(&this->p_vtree); //Value should be nullptr

			this->length--;
		}

		return rv;
	}

	T extractMin(){
		if(this->p_minen != nullptr){
			T tval = this->p_minen->getValue()->getValue();
			this->removeEntry(this->p_minen->getTwin());
			return tval;
		}

		throw new QueueException(2, "Queue list is empty!");
	}

	void decreaseKey(T value, double priority){
		PriorityQueueEntry<T> *e = this->findEntry(value);
		PriorityQueueValue<T> *v = this->removeEntry(e);
		v->setPriority(priority);
		this->insertValue(v);
	}

	PriorityQueueEntry<T> *findEntry(T value){
		PriorityQueueEntry<T> *re = this->p_vtree->findEntry(value);
		if(re == nullptr) throw new QueueException(1, "Value not found!");
		return re;
	}

	~PriorityQueue(){
		if(!this->isEmpty()){
			delete this->p_ptree;
			delete this->p_vtree;
		}
	}
};


#endif