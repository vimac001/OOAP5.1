#ifndef QUEUEEXCEPTION_HPP
#define QUEUEEXCEPTION_HPP

class QueueException
{
private:
	char* msg;
	int nr;

public:
	QueueException(int nr, char* msg){
		this->msg = msg;
		this->nr = nr;
	}

	char* getMessage(){
		return this->msg;
	}

	int getNumber(){
		return this->nr;
	}
};

#endif