/*****************************

       Algorytm Dijkstry
          bazujacy na
      macierzy sasiedztwa
               i
      liście sąsiedztwa

*****************************/

#include <stdio.h> 
#include <limits.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <time.h>
#include <math.h>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;
   
// liczba wierzcholkow - przykładowo
#define V 1000
const int MAX_N = 1000;
const int INF = 2147483647;

struct Wezel
{
  int numer;
  int waga;
  struct Wezel * nastepny;
};

void sleep(int ms){
  clock_t target = clock() + ms;
  while (clock() < target) ;
}

void stworz_plik(int a, int b){
  int plusplus=0;
  ostringstream ss;
  ss << "Wyp_gr_" << a << "_"<< b << ".txt";
  string str = ss.str();

    string const nazwaPliku(str);
    ofstream mojStrumien(nazwaPliku.c_str());
 
    if(mojStrumien){

      int q;
      int p;
      srand(time(NULL));
      
      

      //Generuję plik z danymi

        mojStrumien << "1" << endl;
        mojStrumien << a*a << endl;
        for(int k=1; k<=a; k++){          
          for(int o=1; o<=a; o++){            
            q = rand() % 100;
            p = rand() % 100;
              if(p<=b){
              mojStrumien << k << " " << o << " " << q << endl;
              plusplus++;
              }
          }
        }
        cout<<"Ilosc lini: "<<plusplus<<endl;
    }else{
        cout << "BŁĄD: nie można pisać do pliku" << endl;
    }
}

//algorytm na liście

void Dijkstry(string nazwa_pliku){

  int i,j,u,n,il_krawedz,x,y,waga_kraw,w_startowy;
  int d[MAX_N+1],p[MAX_N+1];
  bool QS[MAX_N+1];
  struct Wezel *Lista_sasiedztwa[MAX_N+1],*pw;

  for(i = 1; i <= MAX_N; i++){
    d[i]  = INF;
    p[i]  = 0;
    QS[i] = false;
    Lista_sasiedztwa[i]  = NULL;
  }
  n = 0;

  /***********************************/

  ifstream plik(nazwa_pliku);
  int dana;

  if(plik.good()==true){
    while(!plik.eof()){
      plik>>w_startowy;
      plik>>il_krawedz;



  /***********************************/

  //cin >> w_startowy;
  //cin >> il_krawedz;

  for(i = 1; i <= il_krawedz; i++){
    plik >> x >> y >> waga_kraw;
    if(x > n) n = x;
    if(y > n) n = y;
    pw = new Wezel;
    pw->nastepny = Lista_sasiedztwa[x]; pw->numer = y; pw->waga = waga_kraw;
    Lista_sasiedztwa[x] = pw;
  }

    }
    plik.close();
  }



  //cout << endl;
  d[w_startowy] = 0;

    for(i = 1; i <= n; i++){
    u = -1;
    for(j = 1; j <= n; j++)
      if(!QS[j] && ((u == -1) || (d[j] < d[u]))) u = j;

    QS[u] = true;

    pw = Lista_sasiedztwa[u];
    while(pw){
      if(!QS[pw->numer] && (d[pw->numer] > d[u] + pw->waga)){
        d[pw->numer] = d[u] + pw->waga;
        p[pw->numer] = u;
      }
      pw = pw->nastepny;
    }
  }

  int stos[MAX_N],ws;
  
  for(i = 1; i <= n; i++){
    //cout << i << ": ";
    ws = 0; j = i;

    while(j){
      stos[ws++] = j; j = p[j];
    }

    while(ws) /*cout << */stos[--ws]/* << " "*/;

    if(d[i]==INF){
        //cout<<"Brak polaczenia"<<endl;
    }else{
        //cout << "#" << d[i] << endl;  
    }  
  }

}

//funkcja urzyta w alg dikstry dla macierzy, zaimplementowanym poniżej

int minDistance(int dist[], bool sptSet[]){ 
   // Initializuję wartosc minimalną
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) 
         min = dist[v], min_index = v; 
   
   return min_index; 
} 

// Funkcja wypisania tablicy odleglosci dla alg dikstry dla macierzy, zaimplementowanym poniżej
int printSolution(int dist[], int n){ 
   printf("Vertex   Distance from Source\n"); 
   for (int i = 0; i < V; i++) 
      printf("%d tt %d\n", i, dist[i]); 
} 
   
// dijkstra za pomocą macierzy sasiedztwa
void dijkstra(int graph[V][V], int src){ 
     int dist[V];     //tablica przechowywujaca najkótrzą ściezkę
   
     bool sptSet[V]; 
   
     //inicjalizacja
     for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
   
     dist[src] = 0; 
   
     // znajduję najkrótrzą ścieżkę do wszystkich wierzchołków
     for (int count = 0; count < V-1; count++) 
     { 
       // Wybierz minimalny wierzchołek odległości ze zbioru wierzchołków jeszcze nie przetworzonych. u jest zawsze równe src w pierwszej iteracji.
       int u = minDistance(dist, sptSet); 
   
       // Zaznacz wybrany wierzchołek jako przetworzony
       sptSet[u] = true; 
   
       // Zaktualizuj wartość dyst sąsiednich wierzchołków pobranego wierzchołka.
       for (int v = 0; v < V; v++) 
   
         // Aktualizuj dist [v] tylko wtedy, gdy nie ma go w sptSet, istnieje krawędź od u do v, a całkowita waga ścieżki od src do v przez u jest mniejsza niż bieżąca wartość dist [v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  
                                       && dist[u]+graph[u][v] < dist[v]) 
            dist[v] = dist[u] + graph[u][v]; 
     } 
   
     // wypisz tablicę odległości
     //printSolution(dist, V); 
}
   // nie zdążyłem tego napisać ładniej, dlatego wywoływałem tą funkcję ręcznie wiele razy dla rózniej ilosci wierzcholków 
int main(){
   double czasm25=0, czasm50=0, czasm75=0, czasm100=0;
   double czast25=0, czast50=0, czast75=0, czast100=0;

   int graph[V][V];

/////////// graf wypełniony /////////////////////////////////////////////////////////////////////////////////////////

     for(int i=0; i<10; ++i){
     stworz_plik(1000, 100);
     sleep(10000); //aby kolejny stworzony plik róznił się od poprzedniego

      int x, y, waga, il_krawedz, sqrtilkraw, w_startowy, n;
      ifstream plik("Wyp_gr_1000_100.txt");

      int **mojgraf = new int *[MAX_N]; //alokacja pamieci
      for ( int i = 1; i <= MAX_N; ++i ){
          mojgraf[i-1] = new int [MAX_N]; //alokacja pamieci

          for ( int j = 1; j <= MAX_N; ++j) //wpisanie wartosci do tablicy
          mojgraf[i-1][j-1]=0;
          }

   if(plik.good()==true){
    while(!plik.eof()){
      plik>>w_startowy;
      plik>>il_krawedz;
      sqrtilkraw = sqrt(il_krawedz);    

  for(int i = 1; i <= il_krawedz; i++){
    plik >> x >> y >> waga;
    if(x > n) n = x;
    if(y > n) n = y;
    mojgraf[x-1][y-1]=waga;
  }
    }
    plik.close();
  }

  for(int i=0; i<V; i++){
     for(int j=0; j<V; j++){
        graph[i][j]=mojgraf[i][j];
     }
  }

   auto start = Clock::now();
   dijkstra(graph, 0);
   auto stop = Clock::now();
   czasm100 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
   }



    for(int i=0; i<10; ++i){
     stworz_plik(1000, 100);
     sleep(10000);

     auto start = Clock::now();
     Dijkstry("Wyp_gr_1000_100.txt");
     auto stop = Clock::now();
     czast100 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
     }

//// graf wypełnionmy w 75% //////////////////////////////////////////////////////////////////////////////////////////////// 
                     
  for(int i=0; i<10; ++i){
     stworz_plik(1000, 75);
     sleep(10000);

      int x, y, waga, il_krawedz, sqrtilkraw, w_startowy, n;
      ifstream plik("Wyp_gr_1000_75.txt");

      int **mojgraf = new int *[MAX_N]; //alokacja pamieci
      for ( int i = 1; i <= MAX_N; ++i ){
          mojgraf[i-1] = new int [MAX_N]; //alokacja pamieci

          for ( int j = 1; j <= MAX_N; ++j) //wpisanie wartosci do tablicy
          mojgraf[i-1][j-1]=0;
          }

   if(plik.good()==true){
    while(!plik.eof()){
      plik>>w_startowy;
      plik>>il_krawedz;
      sqrtilkraw = sqrt(il_krawedz);      

      //cout<<w_startowy<<endl<<il_krawedz<<endl;
      
  for(int i = 1; i <= il_krawedz; i++){
    plik >> x >> y >> waga;
    //cout<<"x= "<<x<<endl<<"y= "<<y<<endl<<"waga= "<<waga<<endl;
    if(x > n) n = x;
    if(y > n) n = y;
    mojgraf[x-1][y-1]=waga;
  }
    }
    plik.close();
  }

  for(int i=0; i<V; i++){
     for(int j=0; j<V; j++){
        graph[i][j]=mojgraf[i][j];
     }
  }

   auto start = Clock::now();
   dijkstra(graph, 0);
   auto stop = Clock::now();
   czasm75 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
   }



    for(int i=0; i<10; ++i){
     stworz_plik(1000, 75);
     sleep(10000);

     auto start = Clock::now();
     Dijkstry("Wyp_gr_1000_75.txt");
     auto stop = Clock::now();
     czast75 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
     }

//// graf wypełnionmy w 50% ////////////////////////////////////////////////////////////////////////////////////////////////

     for(int i=0; i<10; ++i){
     stworz_plik(1000, 50);
     sleep(10000);

      int x, y, waga, il_krawedz, sqrtilkraw, w_startowy, n;
      ifstream plik("Wyp_gr_1000_50.txt");

      int **mojgraf = new int *[MAX_N]; //alokacja pamieci
      for ( int i = 1; i <= MAX_N; ++i ){
          mojgraf[i-1] = new int [MAX_N]; //alokacja pamieci

          for ( int j = 1; j <= MAX_N; ++j) //wpisanie wartosci do tablicy
          mojgraf[i-1][j-1]=0;
          }

   if(plik.good()==true){
    while(!plik.eof()){
      plik>>w_startowy;
      plik>>il_krawedz;
      sqrtilkraw = sqrt(il_krawedz);      

      //cout<<w_startowy<<endl<<il_krawedz<<endl;
      
  for(int i = 1; i <= il_krawedz; i++){
    plik >> x >> y >> waga;
    //cout<<"x= "<<x<<endl<<"y= "<<y<<endl<<"waga= "<<waga<<endl;
    if(x > n) n = x;
    if(y > n) n = y;
    mojgraf[x-1][y-1]=waga;
  }
    }
    plik.close();
  }

  for(int i=0; i<V; i++){
     for(int j=0; j<V; j++){
        graph[i][j]=mojgraf[i][j];
     }
  }

   auto start = Clock::now();
   dijkstra(graph, 0);
   auto stop = Clock::now();
   czasm50 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
   }



    for(int i=0; i<10; ++i){
     stworz_plik(1000, 50);
     sleep(10000);

     auto start = Clock::now();
     Dijkstry("Wyp_gr_1000_50.txt");
     auto stop = Clock::now();
     czast50 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
     }

//// graf wypełnionmy w 25% ////////////////////////////////////////////////////////////////////////////////////////////////

     for(int i=0; i<10; ++i){
     stworz_plik(1000, 25);
     sleep(10000);

      int x, y, waga, il_krawedz, sqrtilkraw, w_startowy, n;
      ifstream plik("Wyp_gr_1000_25.txt");

      int **mojgraf = new int *[MAX_N]; //alokacja pamieci
      for ( int i = 1; i <= MAX_N; ++i ){
          mojgraf[i-1] = new int [MAX_N]; //alokacja pamieci

          for ( int j = 1; j <= MAX_N; ++j) //wpisanie wartosci do tablicy
          mojgraf[i-1][j-1]=0;
          }

   if(plik.good()==true){
    while(!plik.eof()){
      plik>>w_startowy;
      plik>>il_krawedz;
      sqrtilkraw = sqrt(il_krawedz);      

      //cout<<w_startowy<<endl<<il_krawedz<<endl;
      
  for(int i = 1; i <= il_krawedz; i++){
    plik >> x >> y >> waga;
    //cout<<"x= "<<x<<endl<<"y= "<<y<<endl<<"waga= "<<waga<<endl;
    if(x > n) n = x;
    if(y > n) n = y;
    mojgraf[x-1][y-1]=waga;
  }
    }
    plik.close();
  }

  for(int i=0; i<V; i++){
     for(int j=0; j<V; j++){
        graph[i][j]=mojgraf[i][j];
     }
  }

   auto start = Clock::now();
   dijkstra(graph, 0);
   auto stop = Clock::now();
   czasm25 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
   }



    for(int i=0; i<10; ++i){
     stworz_plik(1000, 25);
     sleep(10000);

     auto start = Clock::now();
     Dijkstry("Wyp_gr_1000_25.txt");
     auto stop = Clock::now();
     czast25 += (chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
     }

////////////////////////////////////////////////////////////////////////////////////////////////////


//wypisanie wynikow
cout<<"dikstra 1000: "<<endl<<"macierz"<<endl;
  cout/*<<"Algorytm Dijkstry macierzy sasiedztwa 100%: "*/<<czasm100/(1000000*10)<<" ms"<<endl;
  cout/*<<"Algorytm Dijkstry macierzy sasiedztwa 75%:  "*/<<czasm75/(1000000*10)<<" ms"<<endl;
  cout/*<<"Algorytm Dijkstry macierzy sasiedztwa 50%:  "*/<<czasm50/(1000000*10)<<" ms"<<endl;
  cout/*<<"Algorytm Dijkstry macierzy sasiedztwa 25%:  "*/<<czasm25/(1000000*10)<<" ms"<<endl<<"lista"<<endl;
  cout/*<<"Algorytm Dijkstry listy sasiedztwa 100%:    "*/<<czast100/(1000000*10)<<" ms"<<endl;  
  cout/*<<"Algorytm Dijkstry listy sasiedztwa 75%:     "*/<<czast75/(1000000*10)<<" ms"<<endl;  
  cout/*<<"Algorytm Dijkstry listy sasiedztwa 50%:     "*/<<czast50/(1000000*10)<<" ms"<<endl;  
  cout/*<<"Algorytm Dijkstry listy sasiedztwa 25%:     "*/<<czast25/(1000000*10)<<" ms"<<endl;
  
   
    return 0; 
}