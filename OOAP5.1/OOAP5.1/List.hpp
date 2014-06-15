#ifndef LIST_HPP
#define LIST_HPP

using namespace std;

template <typename T>
class List
{
	private:
		T *_values;			//Wert der List an einer beliebigen Stelle
		int _last, _size;	//Letzte Stekke und Länge der List
		bool isFull();		//Private Funktion ob List Voll ist
		int find(T val);	//Finden funktion für getValue at position
		void increase();	//verdoppeln der List vom Speicherplatz her , wird nur bei append benötigt wenn Wert hinzugefügt wird
		void decrease();	//halbieren der List vom Speicherplatz her, wird nur bei erase benötigt wenn Wert gelöscht wird

	public:
		List();
		List(int size);		//Konsturktor
		List(List<T>& old);//Kopierkonstruktor
		~List();				//hier Manchmal Fehler warum?
		void append (T val);	//Methode anhängen
		T getValueAt(int pos);	//Methode zurückgeben des Wertes an Stelle pos
		void erase(T val);		//Löschen des Wertes
		void toScreen();		//Ausgabe der Kompletten List

		unsigned int size(void);//´Gibt die Anzahl der in der List vorhandenen Elemente zurück
};

template <typename T>
List<T>::List() //Konstukror -> Werte initialiesieren und Speicherreservierung
{
	_size = 8;			//initialisierung von size
	_last = 0;				//initialisierung von last
	_values = new T[_size];	// Speicherreservierung mit size Plätzen des Types T
}

template <typename T>
List<T>::List(int size) //Konstukror -> Werte initialiesieren und Speicherreservierung
{
	_size = size;			//initialisierung von size
	_last = 0;				//initialisierung von last
	_values = new T[size];	// Speicherreservierung mit size Plätzen des Types T
}

template <typename T>		//Vorlesungstechnisch nachschauen - Kopierkonsturktor
List<T>::List(List<T>& old)
{
	_size = old.size();
	_last = 0;
	_values = new T[_size];

	for(unsigned int i = 0; i < old.size(); i++){
		this->append(old.getValueAt(i));
	}
}

template <typename T>
List<T>::~List()
{
	delete[] _values; //Löschen des reservierten Speichers
}

template <typename T>
void List<T>::append(T val)
{
	if (isFull())	// List Voll? Wenn ja Speicher vergößern
	{
		increase();
	}

	_values[_last] = val;
	_last += 1;
}

template <typename T>
bool List<T>::isFull()
{
	return (_size == _last);
}

template <typename T>
void List<T>::increase()
{
	_size *= 2;
	T *temp = new T[_size];		

	for (int i = 0; i < _size/2; i++)
	{
		temp[i] = _values[i];
	}

	delete[] _values;
	_values = temp;		//Adressübergabe
}

template <typename T>
void List<T>::decrease()
{
		int i;
		_size /= 2;
		T *temp = new T[_size];

		for (i = 0; i < _size; i++)
		{
			temp[i] = _values[i];
		}
		delete [] _values;
		_values = temp;

}

template <typename T>
int List<T>::find(T val)
{
	int pos;

	for (pos = 0; pos < _last; pos++)
	{
		if(_values[pos] == val)
		{
			return pos;
		}
	}
	return -1;
}

template <typename T>
T List<T>::getValueAt(int pos)
{
	return _values[pos];
}

template <typename T>
void List<T>::erase(T val)
{
	int pos = find(val);

	/*if (pos == -1)
	{
		throw "Wert nicht gefunden";  Hier richtige Fehlerbehebung rein!!
	}*/ 

	for(; pos < _last-1; pos++)
	{
		_values[pos] = _values[pos+1];
	}
	_last -= 1;

	if (_last < _size  / 4)
		decrease();
}

template <typename T>
void List<T>::toScreen()
{
	int i;

	for (i = 0; i < _last; i++)
	{
		cout << i << ": " <<_values[i] << endl;
	}


}

template <typename T>
unsigned int List<T>::size(){
	return _last;
}

#endif
