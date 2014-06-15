#ifndef PRIORITYQUEUEENTRY_HPP
#define PRIORITYQUEUEENTRY_HPP

#include "PriorityQueueValue.hpp"

template <typename T>
class PriorityQueueEntry
{
private:
	PriorityQueueEntry<T> *p_parent;
	PriorityQueueEntry<T> *p_left;
	PriorityQueueEntry<T> *p_right;
	PriorityQueueEntry<T> *p_twin;

	PriorityQueueValue<T> *p_value;

protected:
	void setValue(PriorityQueueValue<T> *p_value){
		this->p_value = p_value;
	}

public:
	PriorityQueueEntry(PriorityQueueValue<T> *p_value){
		this->setValue(p_value);
		this->p_parent = nullptr;
		this->p_left = nullptr;
		this->p_right = nullptr;
		this->p_twin = nullptr;
	}

	void setParent(PriorityQueueEntry<T> *p_parent){
		this->p_parent = p_parent;
	}

	void setLeft(PriorityQueueEntry<T> *p_left){
		this->p_left = p_left;
	}

	void setRight(PriorityQueueEntry<T> *p_right){
		this->p_right = p_right;
	}

	void setTwin(PriorityQueueEntry<T> *p_twin){
		this->p_twin = p_twin;
	}

	PriorityQueueEntry<T> *getParent(){
		return this->p_parent;
	}

	PriorityQueueEntry<T> *getLeft(){
		return this->p_left;
	}

	PriorityQueueEntry<T> *getRight(){
		return this->p_right;
	}

	PriorityQueueEntry<T> *getTwin(){
		return this->p_twin;
	}

	PriorityQueueValue<T> *getValue(){
		return this->p_value;
	}

	bool isRoot(){
		return this->getParent() == nullptr;
	}

	bool hasLeft(){
		return this->getLeft() != nullptr;
	}

	bool hasRight(){
		return this->getRight() != nullptr;
	}

	bool isLeft(){
		if(this->isRoot()) return false;
		return this->getParent()->getLeft() == this;
	}

	bool isRight(){
		if(this->isRoot() == nullptr) return false;
		return this->getParent()->getRight() == this;
	}

	template <typename C>
	void append(PriorityQueueEntry<T> *e){
		if((C)*e->getValue() < (C)*this->getValue()){
			if(this->hasLeft()) return this->getLeft()->append<C>(e);
			else this->setLeft(e);
		}else{
			if(this->hasRight()) return this->getRight()->append<C>(e);
			else this->setRight(e);
		}

		e->setParent(this);
	}

	PriorityQueueEntry<T> *findEntry(T value){
		if(this->getValue()->getValue() > value){
			if(this->hasLeft()){
				return this->getLeft()->findEntry(value);
			}
		}else if(this->getValue()->getValue() < value){
			if(this->hasRight()){
				return this->getRight()->findEntry(value);
			}
		}else{
			return this;
		}

		return nullptr;
	}

	///<summary>
	///Entfernt den aktuellen Eintrag mit dessen Value und verkettet die Liste neu.
	///<param name="**p_root">Referenz auf den root Pointer.</param>
	///</summary>
	PriorityQueueValue<T> *remove(PriorityQueueEntry<T> **p_root){
		if(this->hasRight()){
			if(this->hasLeft()){
				PriorityQueueEntry<T> *tmp = this->getRight()->getMostLeft();
				tmp->setLeft(this->getLeft());
				this->getLeft()->setParent(tmp);
			}
		}else{
			if(this->hasLeft()){
				this->setRight(this->getLeft()); //Using right as an temp var for dynamic append
			}
		}

		//Dynamic append of left|right on parent
		if(this->hasRight()){
			this->getRight()->setParent(this->getParent());
		}

		if(this->isRoot()){
			*p_root = this->getRight();
		}else if(this->isLeft()){
			this->getParent()->setLeft(this->getRight());
		}else{
			this->getParent()->setRight(this->getRight());
		}

		if(this->getTwin() != nullptr){
			this->getTwin()->setTwin(nullptr);
			this->getTwin()->setValue(nullptr);
		}

		PriorityQueueValue<T> *rv = this->getValue();

		this->setLeft(nullptr);
		this->setRight(nullptr);
		delete this;

		return rv;
	}

	PriorityQueueEntry<T> *getMostLeft(){
		if(this->hasLeft()) return this->getLeft()->getMostLeft();
		return this;
	}

	~PriorityQueueEntry(){
		if(this->hasLeft()) delete this->getLeft();
		if(this->hasRight()) delete this->getRight();
	}
};


#endif