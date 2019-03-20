#include <iostream>
#include <string>
#include <sstream>

using namespace std;


template <class T>
class element_listy {
	private:
		T wartosc;
	public:
		element_listy* nastepny;
		element_listy* poprzedni;
		element_listy(T wartosc);
		T getData();
		string toString();
		~element_listy();
};

template <class T>
element_listy<T>::element_listy(T wartosc) {
	this->wartosc = wartosc;
}

template <class T>
T element_listy<T>::getData() {
	return this->wartosc;
}

template <class T>
string element_listy<T>::toString() {
	stringstream s;
	s << this->getData();
	return s.str();
}

template <class T>
element_listy<T>::~element_listy() { }

 
template <class T>
class moja_lista {
	private:
		T* pierwszy;
		T* ostatni;
		int rozm_listy;
	public:
		moja_lista();
		T* getHead();
		T* getTail();
		int size(bool update=false);
		void dodaj_ostatni(T* nowy_el);
		void dodaj_pierwszy(T* nowy_el);
		T* pop();
		T* pop_back();
		T* peek();
		T* peek_back();
		void printList();
		~moja_lista();
};

template <class T>
moja_lista<T>::moja_lista() {
	this->pierwszy = NULL;
	this->ostatni = NULL;
	this->rozm_listy = 0;
}

template <class T>
int moja_lista<T>::size(bool update) {
	if (!update) {
		return this->rozm_listy;
	}
	int size = 0;
	T* temp = this->pierwszy;
	while (temp) {
		size++;
		temp = temp->nastepny;
	}
	this->rozm_listy = size;
	return this->rozm_listy;
}

template <class T>
void moja_lista<T>::dodaj_ostatni(T* nowy_el) {
	nowy_el->nastepny = NULL;
	nowy_el->poprzedni = NULL;
	
	if (this->pierwszy == NULL) {
		this->pierwszy = nowy_el;
		this->ostatni = this->pierwszy;
		this->rozm_listy = this->rozm_listy + 1;
	} else {
		this->ostatni->nastepny = nowy_el;
		nowy_el->poprzedni = this->ostatni;
		this->ostatni = nowy_el;
		this->rozm_listy = this->rozm_listy + 1;
	}
}

template <class T>
void moja_lista<T>::dodaj_pierwszy(T* nowy_el) {
	nowy_el->nastepny = NULL;
	nowy_el->poprzedni = NULL;
	
	if (this->pierwszy == NULL) {
		this->pierwszy = nowy_el;
		this->ostatni = this->pierwszy;
		this->rozm_listy = this->rozm_listy + 1;
	} else {
		this->pierwszy->poprzedni = nowy_el;
		nowy_el->nastepny = this->pierwszy;
		this->pierwszy = nowy_el;
		this->rozm_listy = this->rozm_listy + 1;
	}
}

template <class T>
T* moja_lista<T>::pop(){
	if(this->rozm_listy<=0){
		cout<<"Lista jest pusta\n";
	}else{
		T* temp = this->pierwszy;
		this->pierwszy = this->pierwszy->nastepny;
		this->pierwszy->poprzedni = NULL;
		this->rozm_listy = this->rozm_listy - 1;
		return temp;
	}
}

template <class T>
T* moja_lista<T>::pop_back(){
	if(this->rozm_listy<=0){
		cout<<"Lista jest pusta\n";
	}else{
		T* temp = this->ostatni;
		this->ostatni =this->ostatni->poprzedni;
		this->pierwszy->nastepny = NULL;
		this->rozm_listy = this->rozm_listy -1;
	return temp;
	}
}

template <class T>
T* moja_lista<T>::peek() {
	return this->pierwszy;
}

template <class T>
T* moja_lista<T>::peek_back(){
	return this->ostatni;
}

template <class T>
void moja_lista<T>::printList() {
	T* temp = this->pierwszy;
	while(temp) {
		cout << temp->toString() << " ";
		temp = temp->nastepny;
	}
	cout<<endl;
}

template <class T>
moja_lista<T>::~moja_lista() {
	while (this->pierwszy) {
		T* nastepny = this->pierwszy->nastepny;
		delete this->pierwszy;
		this->rozm_listy = this->rozm_listy - 1;
		this->pierwszy = nastepny;
	}
}

int main(){
	int zmienna=0;
	char dod;

	moja_lista<element_listy<char>> moja_lista;
	int i = 0;
	cout<<" 1 - Dodaj na koniec listy\n 2 - Dodaj na poczatek\n 3 - Zdejmij z poczatku\n 4 - Zdejmij z konca\n 5 - Wyswietl ostatni el. listy\n 6 - Wyswietl pierwszy el. listy\n 7 - Wyswietl rozmiar listy\n 8 - Wyswietl cala liste\n 9 - Wyjscie\n";
	while(zmienna!=9){
		cin>>zmienna;
		cout<<"   ";
		switch(zmienna){
			case 1:		cin>>dod; moja_lista.dodaj_ostatni(new element_listy<char>(dod));					break;
			case 2:		moja_lista.dodaj_pierwszy(new element_listy<char>(dod));							break;
			case 3:		cout << moja_lista.pop()->toString() << endl;					break;
			case 4:		cout << moja_lista.pop_back()->toString() << endl;				break;
			case 5:		cout << moja_lista.peek_back()->toString() <<endl;				break;
			case 6:		cout << moja_lista.peek()->toString() <<endl;					break;
			case 7:		cout << "Rozmiar listy: " << moja_lista.size() << endl;			break;
			case 8:		cout << "Moja lista: "; moja_lista.printList();					break;
			default:	cout<<" 1 - Dodaj na koniec listy\n 2 - Dodaj na poczatek\n 3 - Zdejmij z poczatku\n 4 - Zdejmij z konca\n 5 - Wyswietl pierwszy el. listy\n 6 - Wyswietl ostatni el. listy\n 7 - Wyswietl rozmiar listy\n 8 - Wyswietl cala liste\n 9 - Wyjscie\n";	break;
		}
	}
}
