#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 10

template <typename X>
class stack{
	X *arr;
	int top;
	int pojemnosc;

public:
	stack(int size = SIZE);	// konstruktor

	void push(const X);
	X pop();
	X peek();

	int size();
	bool isEmpty();
	bool isFull();
};

// Konstruktor do inicjalizacji stosu
template <class X>
stack<X>::stack(int size){
	arr = new X[size];
	pojemnosc = size;
	top = -1;
}

// funkcja dodajaca el x do stosu
template <class X>
void stack<X>::push(X x)
{
	if (isFull())
	{
		cout << "Stos jest juz pelny\n";
		//exit(EXIT_FAILURE);
	}else{

	cout << "Dodaje: " << x << endl;
	arr[++top] = x;
	}
}

// funkcja zdejmujaca el ze stosu
template <class X>
X stack<X>::pop()
{
	// sprawdzenie czy stos nie jest pusty
	if (isEmpty())
	{
		cout << "Stos jest juz pusty\n";
	}

	cout << "Zdejmuje " << peek() << endl;

	// decrease stack size by 1 and (optionally) return the popped element
	return arr[top--];
}

// funkcja pokazujaca najwyzszy element
template <class X>
X stack<X>::peek()
{
	if (!isEmpty())
		return arr[top];
	else
		cout<<"Stos jest pusty\n";
}

// Funkcja zwracajaca rozmiar stosu
template <class X>
int stack<X>::size()
{
	return top + 1;
}

// Funkcja sprawdzajaca czy stos nie jest pusty
template <class X>
bool stack<X>::isEmpty()
{
	return top == -1;	// or return size() == 0;
}

// Funkcja sprawdzajaca czy stos nie jest pelny
template <class X>
bool stack<X>::isFull()
{
	return top == pojemnosc - 1;
}

//==================================================================//

int main()
{
	int zmienna=0;
	int wielkosc_stosu;
	char dod;

	cout<<"Podaj wielkosc stosu jaki chcesz utworzyc: ";
	cin>>wielkosc_stosu;
	stack<string> pt(wielkosc_stosu);
	cout<<endl<<" 1 - DODAJ DO STOSU\n 2 - ZDEJMIJ ZE STOSU\n 3 - PODAJ ROZMIAR STOSU\n 4 - WYSWIETL NAJWYZSZY ELEMENT\n 5 - WYJSCIE                         ";

	while(zmienna!=5){
		cin>>zmienna;
		switch(zmienna){
			case 1: 	cin>>dod; 							pt.push(&dod); 		break;
			case 2: 										pt.pop();			break;
			case 3:		cout <<"Wielkosc stosu: " 		  <<pt.size()<<endl;	break;
			case 4:		cout <<"Ostatnio dodany element: "<<pt.peek()<<endl; 	break;
			case 5:		cout <<"Wyjscie"<<endl; 								break;
			default: 	cout <<"Podaj cyfre z przedzialu 1-4\n"; 				break;
			case 6:		cout <<"Wszystkie elementy:\n";
			for(int i=pt.size(); i>=1; i--){
				pt.pop();
			} 
		}
	}
return 0;
}