#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

template<typename T>
void wyswietlTablice(T tab[] ,int wielkosc){
    for(int i = 0; i < wielkosc ; i++){
        cout<<tab[i]<<"  ";
        if(i!=0 && i%15==0)
        cout<<endl;
    }
    cout<<endl;
}

template<typename T>
void wypelnijTablice(T tab[], int wielkosc){
    srand(time(NULL));
    for(int i = 0; i < wielkosc ; i++)
    {
       tab[i] = rand() % 10000;
    }

}

template<typename T>
void sprawdzKolejnosc(T tablica[], int wielkosc){
    for(int i = 1; i < wielkosc ; i++){
       if(tablica[i-1] > tablica[i]){
            cout<<"Tablica nieposortowana!"<<endl;
            break;
       }
    }
}

template<typename T>
void scal(T tablica[], int poczatek, int srodek, int koniec){
    int i, j, k;
    T tab_pom[koniec];
    for(i = poczatek; i <= koniec; i++)
        tab_pom[i] = tablica[i];

    i = poczatek;
    j = srodek+1;
    k = poczatek;

    while(i <= srodek && j <= koniec){
        if(tab_pom[i] < tab_pom[j])
            tablica[k++] = tab_pom[i++];
        else
            tablica[k++] = tab_pom[j++];
    }

    while(i <= srodek)
        tablica[k++] = tab_pom[i++];
}

template<typename T>
void sortowanieScalcanie(T tab[], int poczatek, int koniec){
    if(koniec <= poczatek)
        return;

    int srodek = (poczatek + koniec)/2;
    sortowanieScalcanie<T>(tab, poczatek, srodek);
    sortowanieScalcanie<T>(tab, srodek + 1, koniec);
    scal(tab, poczatek, srodek, koniec);
}

template<typename T>
void szybkieSortowanie(T tablica[], int poczatek , int koniec){
    
    int i = poczatek, j = koniec;
    int tmp;

    int pivot = tablica[(poczatek+koniec)/2];            

      while (i <= j){
            while (tablica[i] < pivot)
                  i++;

            while (tablica[j] > pivot)
                  j--;

            if (i <= j){
                  tmp = tablica[i];
                  tablica[i] = tablica[j];
                  tablica[j] = tmp;
                  i++;
                  j--;
            }

      };

      if (poczatek < j)
            szybkieSortowanie<T>(tablica, poczatek, j);
      if (i < koniec)
            szybkieSortowanie<T>(tablica, i, koniec);

}

template<typename T>
void babelkoweSortowanie(T tablica[], int rozmiar){
    int tmp;
    for(int i=0; i<rozmiar; i++){
        for(int j=1; j<rozmiar-i; j++){
            if (tablica[j-1]>tablica[j]){
                tmp = tablica[j-1];
                tablica[j-1] = tablica[j];
                tablica[j] = tmp;
            }
        }
    }
}

int main(){

double czas_1;
double czas_2;
double czas_3;
int a;


    cout<<endl<<"Szybkie"<<endl;
    for(int d=10; d<=100000; d=d*10){
        for(a=1; a<=10; a++){
            int *tablica = new int[d];
            wypelnijTablice(tablica, d);

            auto start = Clock::now();
            szybkieSortowanie(tablica, 0, d);
            auto stop = Clock::now();

            sprawdzKolejnosc(tablica, d);
            czas_1 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
        }
        cout<<"Sortowanie tablicy "<<d<<" elementowej trwało średnio "<<czas_1/(1000000*a)<<" ms"<<endl;
    }
    cout<<endl<<"Scalanie:"<<endl;
        for(int d=10; d<=100000; d=d*10){
        for(a=1; a<=10; a++){
            int *tablica = new int[d];
            wypelnijTablice(tablica, d);

            auto start = Clock::now();
            sortowanieScalcanie(tablica, 0, d-1);
            auto stop = Clock::now();

            sprawdzKolejnosc(tablica, d);
            czas_2 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
        }
        cout<<"Sortowanie tablicy "<<d<<" elementowej trwało średnio "<<czas_2/(1000000*a)<<" ms"<<endl;
    }

    cout<<endl<<"Babelkowe:"<<endl;
        for(int d=10; d<=10000; d=d*10){
        for(a=1; a<=10; a++){
            int *tablica = new int[d];
            wypelnijTablice(tablica, d);

            auto start = Clock::now();
            babelkoweSortowanie(tablica, d);
            auto stop = Clock::now();
            
            sprawdzKolejnosc(tablica, d);
            czas_3 = (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
        }
        cout<<"Sortowanie tablicy "<<d<<" elementowej trwało średnio "<<czas_3/(1000000)<<" ms"<<endl;
    }

}