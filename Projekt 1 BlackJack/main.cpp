//POP_2020_12_06_projekt_1_Nowogrodzki_Adrian_AIR_1_184332
//CodeBlocks 20.03


#include <iostream>
#include <time.h>
#include <windows.h>
#include <iomanip>

using namespace std;

int losuj(int a){                       //losowanie liczby
    return rand()%a;
}
const int kolorow=4, wartosc = 13;

void losowanie(int kolorow, int wartosc_max[], int karta[4][13], int sterta[4][13], int &nr_koloru, int &nr_znaku){ //losowanie indeksu karty

    int kolor, wartosc[kolorow];
    kolor=losuj(kolorow);

    int w_m_tym = wartosc_max[kolor]+1;
    wartosc[kolor]=losuj(w_m_tym);
    sterta[kolor][wartosc[kolor]]++;

    nr_koloru=kolor;                                                    //zapisywane indeksy
    nr_znaku=karta[kolor][wartosc[kolor]];                              //

    if(sterta[kolor][wartosc[kolor]]==3){
        sterta[kolor][wartosc[kolor]]=sterta[kolor][wartosc_max[kolor]];
        karta[kolor][wartosc[kolor]]=karta[kolor][wartosc_max[kolor]];
        wartosc_max[kolor]--;
    }
}

void rysuj_kolor(int nr_koloru){                                        //rysuje kolory(serc, pik itp.)
    char x = static_cast<char>(nr_koloru+3);
    if(nr_koloru==1){
        cout <<
        "|     " << x << "     |" << endl <<
        "|    "  << x << x << x << "    |" << endl <<
        "|   "  << x << x << x << x << x << "   |" << endl <<
        "|    "  << x << x << x << "    |" << endl <<
        "|     " << x << "     |" << endl;
    }
    if(nr_koloru==0){
        cout <<
        "|    " << x << " "<< x << "    |" << endl <<
        "|   " << x << x << x << x << x << "   |" << endl <<
        "|    " << x << x << x << "    |" << endl <<
        "|     " << x << "     |" << endl <<
        "|" << setw(12) << "|" << endl;
    }
   if(nr_koloru==2){
        cout <<
        "|     "  << x << "     |" << endl <<
        "|   " << x << x << x << x << x << "   |" << endl <<
        "|     " << x << "     |" << endl <<
        "|     " << x << "     |" << endl <<
        "|" << setw(12) << "|" << endl;
    }
   if(nr_koloru==3){
        cout <<
        "|     "  << x << "     |" << endl <<
        "|    " << x << x << x << "    |" << endl <<
        "|   " << x << x << x << x << x << "   |" << endl <<
        "|     " << x << "     |" << endl <<
        "|" << setw(12) << "|" << endl;
    }
}

void animacja(int nr_znaku, int nr_koloru){                                          //rysuje calosc karty
    char char_wartosc[wartosc]= {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'W', 'D', 'K', 'A' };
    char char_kolor[kolorow]= {'S', 'K', 'T', 'P'};

    if(nr_znaku!=8){
        cout << " -----------" << endl;
        cout << "|" << char_wartosc[nr_znaku] << setw(11) << "|" << endl;
        rysuj_kolor(nr_koloru);
        cout << "|"<< setw(11) << char_wartosc[nr_znaku] << "|" << endl;
        cout << " -----------" << endl;
    }
    else{
        cout << " -----------" << endl;
        cout << "|" << "10" << setw(10) << "|" << endl;
        rysuj_kolor(nr_koloru);
        cout << "|"<< setw(11) << "10" << "|" << endl;
        cout << " -----------" << endl;
    }
}

int obstaw_zetony(int &zetony, int &graj_zetony){           //obstawia zetony, odejmuje je od puli
    if(zetony>0){
        cout << "podaj liczbe zetonow: ";
        do{
            cin >> graj_zetony;
        }while(graj_zetony>zetony || graj_zetony<=0);
        zetony = zetony - graj_zetony;
    }
    else
        return 0;
}
void suma_punktow(int nr_znaku, int &suma, int &suma_A){        //podstawia warosci za nr. kart i sumuje je
    int wartosc, wartosc_A;
    if(nr_znaku<=7){
        wartosc=nr_znaku+2;
        wartosc_A=nr_znaku+2;
    }
    else if(nr_znaku>=8 && nr_znaku<=11){
        wartosc=10;
        wartosc_A=10;
    }
    else if(nr_znaku==12){
        wartosc=1;
        wartosc_A=11;           //specjalnie dla asa=11
    }

    if((suma_A+wartosc_A)>21){
        suma_A=suma_A+wartosc;
    }
    else
        suma_A=suma_A+wartosc_A;

    suma=suma+wartosc;
}

void hit(int kolorow, int wartosc_max[], int karta[4][13], int sterta[4][13], int &nr_koloru, int &nr_znaku, int &suma, int &suma_A){  //pobieranie karty, animowanie jej i sumowanie jej z reszta
    losowanie(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku);
    animacja(nr_znaku, nr_koloru);
    suma_punktow(nr_znaku, suma, suma_A);
}

void animacja_rewersu(){                //tyl karty dla krupiera
    cout << " -----------" << endl;
    for(int i=0; i<7; i++)
    cout << "|" << setw(12) << "|" << endl;
    cout << " -----------" << endl;
}

void hit_bez_animacji(int kolorow, int wartosc_max[], int karta[4][13], int sterta[4][13], int &nr_koloru, int &nr_znaku, int &suma, int &suma_A){ //pobieranie karty i sumowanie jej, bez pokazyania jej
    losowanie(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku);
    animacja_rewersu();
    suma_punktow(nr_znaku, suma, suma_A);
}

void stand(){   //nic nie rob

}
void double_down(int kolorow, int wartosc_max[], int karta[4][13], int sterta[4][13], int &nr_koloru, int &nr_znaku, int &suma, int &suma_A, int &zetony, int &graj_zetony){    //podwojenie stawki i dobranie jednej karty
    if(zetony>=graj_zetony){
        zetony=zetony-graj_zetony;
        graj_zetony=graj_zetony*2;
        hit(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A);
    }
    else
        cout << "Brak zetonow. " << endl;
}

int split(int &nr_znaku1, int &zetony, int &graj_zetony){   //nadaje nr_znaku1 wartosc unikalna, zeby mozna bylo wejsc w odpowienie funkcje w main

        if(zetony<graj_zetony){
            cout << "Brak zetonow.";
            return 0;
        }
        else{
            zetony=zetony-graj_zetony;
            nr_znaku1=99;
        }
}
                                                                                        //wybor akcji w grze
void wybor_akcji(int akcja, int kolorow, int wartosc_max[], int karta[4][13], int sterta[4][13], int &nr_koloru, int &nr_znaku, int &suma, int &suma_A, int &zetony, int &graj_zetony, int &nr_znaku1, int &nr_znaku2){
     switch(akcja){
        case 1: stand(); break;
        case 2: hit(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A); break;
        case 3: double_down(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A, zetony, graj_zetony); break;
        case 4: split(nr_znaku1, zetony, graj_zetony); break;
        default: cout << "Podaj poprawne dane."; break;
    }
}

int stan_gry(int suma, int suma_A, int suma_kru, int suma_A_kru, int &suma_ostateczna, int &suma_ostateczna_kru, int &win, int &zetony, int &graj_zetony){ //sprawdza kto wygral, przegral, zremisowal

    if(suma==21 || suma_A==21){                 //suma kart gracza lub stan gry
        cout << "Wygrana." << endl;
        win=1;
        zetony=zetony+2*graj_zetony;
        return 0;                               //returny sa w miejscach ktore jednoznacznie definiuja stan gry
    }
    else if(suma<21 && suma_A<21){
        if(suma>suma_A)
            suma_ostateczna=suma;
        else
            suma_ostateczna=suma_A;
    }
    else if(suma>21 && suma_A>21){
        cout << "Przegrana." << endl;
        win=0;
        return 0;
    }
    else if(suma>21 && suma_A<21){
        suma_ostateczna=suma_A;
    }
    else if(suma<21 && suma_A>21){
        suma_ostateczna=suma;
    }
///////////////////////////////////////////

    if(suma_kru<=21 && suma_A_kru<=21){         //suma kart krupiera lub stan gry
        if(suma_kru>suma_A_kru)
            suma_ostateczna_kru=suma_kru;
        else
            suma_ostateczna_kru=suma_A_kru;
    }
    else if(suma_kru>21 && suma_A_kru>21){
        cout << "Wygrana." << endl;
        win=1;
        zetony=zetony+2*graj_zetony;
        return 0;
    }
    else if(suma_kru>21 && suma_A_kru<21){
        suma_ostateczna_kru=suma_A_kru;
    }
    else if(suma_kru<21 && suma_A_kru>21){
        suma_ostateczna_kru=suma_kru;
    }

///////////////////////////////////////////

    if(suma_ostateczna==21)                     //porownywanie i ustalanie stanu gry
        win=1;
    else if(suma_ostateczna>suma_ostateczna_kru)
        win=1;
    else if(suma_ostateczna<suma_ostateczna_kru)
        win=0;
    else{   //Remis
        cout << "Remis!" << endl;
        zetony=zetony+graj_zetony;
        win=1;
        return 0;
    }

    if(win==0){
        cout << "Przegrales!" << endl;
    }
    else if(win==1){
        cout << "Wygrales" << endl;
        zetony=zetony+2*graj_zetony;
    }
}

int czy_21(int &win, int suma, int suma_A, int &zetony, int &graj_zetony){                     //sprawdza czy gracz wylosowal sume=21 lub wieksza
    if(suma==21 || suma_A==21){                                                                // 1-wygrana;  0-przegrana;  -1-gra w trakcie
        cout << "Wygrana." << endl;
        win=1;
        zetony=zetony+2*graj_zetony;
    }
    else if(suma>21 && suma_A>21){
        cout << "Przegrana." << endl;
        win=0;
    }
    else
        win=-1;
}

int main()
{
    srand(time(NULL));

    int wartosc_max[kolorow]={12,12,12,12};
    int karta[kolorow][wartosc];
    int sterta[kolorow][wartosc];     //sterta przechowue ilosc kart wylosowanych z talii
    int nr_koloru, nr_znaku;        // indeksy karty
    int zetony=100;
    int graj_zetony;            //wartosc obstawiana
    int akcja;
    int nr_znaku1, nr_znaku2;    //indeksy 2 pierwszych kart
    int suma_ostateczna, suma_ostateczna_kru;       //do ostatecznego rozstrzygniecia gry (funckja stan_gry)
    int win;    //stan gry
    int wyjscie=1;
    int n;
    int suma_4, suma_A_4, suma_tym, suma_A_tym, ktory_obieg; //dane dla akcji==4 czyli dla splitu


////////////////////////////GRA/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
while(zetony>0 && wyjscie!=0){

    int wartosc_max[kolorow]={12,12,12,12}; //
                                            //przywracanie kart do talii
    for(int i=0; i<kolorow; i++){           //
        for(int j=0; j<wartosc; j++){
            karta[i][j]=j;
            sterta[i][j]=0;
        }
    }

    int suma_kru=0, suma_A_kru=0, nr_znaku_kru, nr_koloru_kru;  //zerowanie wartosci dla kazdej rundy
    int suma=0, suma_A=0;                                       //

    cout << "Twoje zetony: " << zetony << endl;                 //obstawianie zetonow
        obstaw_zetony(zetony, graj_zetony);

    cout << "Karty krupiera: " << endl;                         //losowanie kart krupiera
        hit(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku_kru, suma_kru, suma_A_kru);
        hit_bez_animacji(kolorow, wartosc_max, karta, sterta, nr_koloru_kru, nr_znaku_kru, suma_kru, suma_A_kru);
//        cout << "suma_kru: " <<suma_kru << endl;
//        cout << "suma_A_kru: " <<suma_A_kru << endl;

    cout << "Twoje karty: " << endl;                            //losowanie kart gracza
        hit(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A);
        nr_znaku1=nr_znaku;
        hit(kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A);
        nr_znaku2=nr_znaku;
//        cout << "suma: " <<suma << endl;
//        cout << "suma_A: " <<suma_A << endl;

    czy_21(win, suma, suma_A, zetony, graj_zetony);
    if(win!=1){
        if(nr_znaku1==nr_znaku2){               //sprawdzanie czy karty maja takie same wartosci (np. dama==dama)
            cout << "stand-press(1) hit-press(2) double_down-press(3) split-press(4) :";    //jesli karty sa rowne co do wartosci to mamy 4 akcje
            do{
                cin >> akcja;
            }while (akcja>4 || akcja<1);
            wybor_akcji(akcja, kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A, zetony, graj_zetony, nr_znaku1, nr_znaku2);
        }
        else{
            cout << "stand-press(1) hit-press(2) double_down-press(3): ";           //jesli karty sa rowne co do wartosci to mamy 3 akcje
            do{
                cin >> akcja;
            }while (akcja>3 || akcja<1);
            wybor_akcji(akcja, kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A, zetony, graj_zetony, nr_znaku1, nr_znaku2);
            czy_21(win, suma, suma_A, zetony, graj_zetony);
        }
        if(nr_znaku1==99){      //nr_znaku1==99 tylko gdy wczesniej wybrano akcje nr 4(split)
            n=2;
            suma_4=suma/2;      //poniewaz wybrano split - rozdzielenie kart
            suma_A_4=suma/2;    //
            if(nr_znaku2==12)
                suma_A_4=11;
        }
        else if(akcja==3){      //gdy wybrano double- zeby ominac czesc funckji main
            n=0;
        }
        else{
            n=1;
        }
        for(int i=0; i<n; i++){
            if(n==2){
                suma=suma_4;
                suma_A=suma_A_4;
                win=-1;
                ktory_obieg=i;      //numerowanie obiegu petli
                akcja=2;
                cout << "dobierasz do " << i+1 << " karty" << endl;
            }

            if(win==-1){
                czy_21(win, suma, suma_A, zetony, graj_zetony);
                while((suma<21 || suma_A<21) && akcja!=1){
                    cout << "stand-press(1) hit-press(2): ";
                    do{
                        cin >> akcja;
                    }while (akcja>2 || akcja<1);
                    wybor_akcji(akcja, kolorow, wartosc_max, karta, sterta, nr_koloru, nr_znaku, suma, suma_A, zetony, graj_zetony, nr_znaku1, nr_znaku2);
                }
//                cout << "suma: " <<suma << endl;
//                cout << "suma_A: " <<suma_A << endl;
                if(n!=2)
                czy_21(win, suma, suma_A, zetony, graj_zetony);

                if(n==2 && ktory_obieg==0){
                    suma_tym=suma;          //sumy tymczasowe dla dobierania do pierwszej karty ze splitu
                    suma_A_tym=suma_A;      //
                }
            }
        }
                if(n==2){
                    ktory_obieg=0;
                    win=-1;
                }
                if(win==-1){                //odsloniecie kart krupiera i nadanie ostatecznego stanu grze
                    cout << "Zaslonieta karta krupiera: " << endl;
                    animacja(nr_znaku_kru, nr_koloru);

                    while(suma_kru<=16 && suma_A_kru<=16){
                        cout << "Krupier dobiera karte" << endl;
                        hit(kolorow, wartosc_max, karta, sterta, nr_koloru_kru, nr_znaku_kru, suma_kru, suma_A_kru);
                    }
 //                   cout << "suma_kru: " <<suma_kru << endl;
 //                   cout << "suma_A_kru: " <<suma_A_kru << endl;

                    if(n==2 && ktory_obieg==0){
                        cout << "wynik z pierwszej karty: ";
                        stan_gry(suma_tym, suma_A_tym, suma_kru, suma_A_kru, suma_ostateczna, suma_ostateczna_kru, win, zetony, graj_zetony);
                        cout << "wynik z drugiej karty: ";
                        stan_gry(suma, suma_A, suma_kru, suma_A_kru, suma_ostateczna, suma_ostateczna_kru, win, zetony, graj_zetony);
                    }
                    else
                        stan_gry(suma, suma_A, suma_kru, suma_A_kru, suma_ostateczna, suma_ostateczna_kru, win, zetony, graj_zetony);
                }


    }
    cout << "zetony: " << zetony << endl;
    if(zetony>0){                                                       //warunek dalszej gry
        cout << endl << "wyjscie-press(0) graj_dalej-press(any_integer): ";
        cin >> wyjscie;
    }
    else
        return 0;
}

    return 0;
}
