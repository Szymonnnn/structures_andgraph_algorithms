#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 10

template <typename X>
class queue{
	X *wsk;
	int objetosc;
	int pierwszy;
	int ostatni;
	int wielkosc;

public:
	queue(int size = SIZE);		// konstruktor

	void dequeue();
	void enqueue(X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};

// konstruktor do inicjalizacji kolejki
template <class X>
queue<X>::queue(int size)
{
	wsk = new X[size];
	objetosc = size;
	pierwszy = 0;
	ostatni = -1;
	wielkosc = 0;
}

// Funkcja zdejmujaca pierwszy element z kolejki
template <class X>
void queue<X>::dequeue(){
	if (isEmpty()){
		cout << "Kolejka jest pusta\n";
	}else{
		cout << "Zdejmuje: " << wsk[pierwszy] << '\n';
		pierwszy = (pierwszy + 1) % objetosc;
		wielkosc--;
	}
}

// Funkcja dodająca element x do kolejki
template <class X>
void queue<X>::enqueue(X x){
	if (isFull()) 
	{
		cout << "Kolejka przepełniona\n";
	}else{

	cout << "Dodaje: " << x <<endl;

	ostatni = (ostatni + 1) % objetosc;
	wsk[ostatni] = x;
	wielkosc++;
	}
}

// Funkcja wyswietlajaca pierwszy element z kolejki
template <class X>
X queue<X>::peek()
{
	if (isEmpty()) 
	{
		cout << "Kolejka jest pusta\n";
	}else{
	return wsk[pierwszy];
	}
}

// Funkcja zwracająca rozmiar kolejki
template <class X>
int queue<X>::size()
{
	return wielkosc;
}

template <class X>
bool queue<X>::isEmpty()
{
	return (size() == 0);
}

template <class X>
bool queue<X>::isFull()
{
	return (size() == objetosc);
}

int main(){
	int zmienna=0;
	int wielkosc_kolejki;
	char dod;

	cout<<"Podaj wielkosc kolejki jaka chcesz utworzyc: ";
	cin>>wielkosc_kolejki;
	queue<char> kol(wielkosc_kolejki);
	cout<<endl<<" 1 - DODAJ DO KOLEJKI\n 2 - WYPUSC Z KOLEJKI\n 3 - POKAZ WIELKOSC KOLEJKI\n 4 - PIERWSZY W KOLEJCE\n 5 - WYJSCIE\n"<<endl;

	while(zmienna!=5){
		cin>>zmienna;
		switch(zmienna){
			case 1:		cin>>dod;							kol.enqueue(dod); 	break;
			case 2:											kol.dequeue();		break;
			case 3: 	cout <<"Wielkosc kolejki: "		  <<kol.size()<<endl;	break;
			case 4: 	cout <<"Pierwszy w kolejce: "	  <<kol.peek()<<endl;	break;
			case 5: 	cout <<"Wyjscie\n"; 									break;
			default:	cout <<"Podaj cyfre z przedzialu 1-5\n";				break;
			case 6:		cout <<"Wszystkie elementy:\n";
			for(int i=kol.size(); i>=1; i--){
				kol.dequeue();
			} 																	break;
		}
	}
	return 0;
}