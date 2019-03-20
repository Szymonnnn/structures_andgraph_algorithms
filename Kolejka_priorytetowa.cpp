#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 10

template <typename z, typename X>
class priority_queue{
	X *wsk;
	z *priorytet;
	int objetosc;
	int pierwszy;
	int ostatni;
	int wielkosc;

public:
	priority_queue(int size = SIZE);		// konstruktor

	void dequeue();
	void enqueue(z zet, X x);
	X peek();
	int size();
	bool isEmpty();
	bool isFull();
};
// konstruktor do inicjalizacji kolejki
template <class z, class X>
priority_queue<z, X>::priority_queue(int size)
{
	wsk = new X [size];
	priorytet = new int [size];
	objetosc = size;
	pierwszy = 0;
	ostatni = -1;
	wielkosc = 0;
}
// Funkcja zdejmujaca pierwszy element z kolejki
template <class z, class X>
void priority_queue<z, X>::dequeue(){
	if (isEmpty()){
		cout<<"Kolejka jest pusta\n";
	}else{
		cout<<"Zdejmuje: "<<wsk[pierwszy];
		cout<<"     Priorytet: "<<priorytet[pierwszy]<<'\n';
		//cout<<"Pierwszy:  "<<pierwszy<<endl;
		pierwszy=(pierwszy+1)%objetosc;
		wielkosc--;
	}
}
// Funkcja dodająca element x o prior z do kolejki
template <class z, class X>
void priority_queue<z, X>::enqueue(z zet, X x){
	if(isFull()){
		cout<<"Kolejka przepełniona\n";
	}else if(isEmpty()){
		cout<<"kolejka pusta, dodaje pierwszy element"<<endl;
		ostatni = (ostatni +1)%objetosc;
		wsk[ostatni]=x;
		priorytet[ostatni]=zet;
		wielkosc++;
	}else{
		ostatni = (ostatni +1)%objetosc;
		wielkosc++;
		int odl=0;
		for(int k=ostatni-1; zet<priorytet[k]; k--){
			odl=ostatni-k;
		}
		int d=0;
		for(d=ostatni; odl!=0; odl--){
			wsk[d]=wsk[d-1];
			priorytet[d]=priorytet[d-1];
			d--;
		}
		wsk[d]=x;
		priorytet[d]=zet;
	}
}
// Funkcja wyswietlajaca pierwszy element z kolejki
template <class z, class X>
X priority_queue<z, X>::peek(){
	if (isEmpty()){
		cout << "Kolejka jest pusta\n";
	}else{return wsk[pierwszy];
	}
}
// Funkcja zwracająca rozmiar kolejki
template <class z, class X>
int priority_queue<z, X>::size(){
	return wielkosc;
}

template <class z, class X>
bool priority_queue<z, X>::isEmpty(){
	return (size() == 0);
}

template <class z, class X>
bool priority_queue<z, X>::isFull(){
	return (size() == objetosc);
}

int main(){
	int zmienna=0;
	int wielkosc_kolejki;
	int prior; char dod;

	cout<<"Podaj wielkosc kolejki: ";
	cin>>wielkosc_kolejki;
	priority_queue<int, char> kol(wielkosc_kolejki);
	cout<<endl<<" 1 - DODAJ DO KOLEJKI\n 2 - WYPUSC Z KOLEJKI\n 3 - POKAZ WIELKOSC KOLEJKI\n 4 - PIERWSZY W KOLEJCE\n 5 - WYJSCIE\n";

	while(zmienna!=5){
		cout<<endl<<"Wybór:       ";
		cin>>zmienna;
		switch(zmienna){
			case 1:		cout<<"priorytet:   "; 	cin>>prior;
						cout<<"el. kolejki: "; 	cin>>dod; 	kol.enqueue(prior, dod);	break;
			case 2:											kol.dequeue();				break;
			case 3: 	cout <<"Wielkosc kolejki: "		  <<kol.size()<<endl;			break;
			case 4: 	cout <<"Pierwszy w kolejce: "	  <<kol.peek()<<endl;			break;
			case 5: 	cout <<"Wyjscie\n"; 											break;
			default:	cout <<"Podaj cyfre z przedzialu 1-5\n";						break;
			case 6:		cout <<"Wszystkie elementy:\n";
			for(int i=kol.size(); i>=1; i--){
				kol.dequeue();
			} 																			break;
		}
	}
	return 0;
}