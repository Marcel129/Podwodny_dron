#include <iostream>
using namespace std;

struct t_osoba
{
    float stan_konta;
    char imie[20];
    char nazwisko[20];
};

void podaj_osobe(t_osoba &kliencisko)
{
    cout << "Podaj imie: ";
    cin >> kliencisko.imie;
    cout << "Podaj nazwisko: ";
    cin >> kliencisko.nazwisko;
    cout << "Podaj stan konta biedaku: ";
    cin >> kliencisko.stan_konta;
}

/*
t_osoba podaj_osobe(){
    t_osoba kliencisko;
    cout<<"Podaj imie: ";
    cin>>kliencisko.imie;
    cout<<"Podaj nazwisko: ";
    cin>>kliencisko.nazwisko;
    cout<<"Podaj stan konta biedaku: ";
    cin>>kliencisko.stan_konta;
    return kliencisko;
}
*/

void wypisz_osobe(t_osoba klient)
{
    cout << "Imie klienta: " << klient.imie << endl;
    cout << "Nazwisko klienta: " << klient.nazwisko << endl;
    cout << "Stan konta klienta: " << klient.stan_konta << endl;
}

void wczytaj_grupe(t_osoba grupa_klientow[], int rozmiar)
{
    for (int i = 0; i < rozmiar; ++i)
        podaj_osobe(grupa_klientow[i]);
}

float sredni_stan(t_osoba grupa_klientow[], int rozmiar)
{
    float srednia = 0;
    for (int i = 0; i < rozmiar; ++i)
        srednia += grupa_klientow[i].stan_konta; //alternatywanie  srednia = srednia grupa_klientow[i].stan_konta;
    return srednia / rozmiar;
}

//tu jest referencja         a tu wskaźnik
void mini_max(t_osoba grupa_klientow[], int rozmiar, t_osoba &najwiekszy_biedak, t_osoba *najwieszy_burzuj)
{
    for (int i = 0; i < rozmiar; ++i)
    {cout << "poczatek " << grupa_klientow[i].stan_konta << endl;
        if (i > 0)
        { //pomijamy 1 element, bo nie ma go z czym porównać
            if (grupa_klientow[i].stan_konta < grupa_klientow[i - 1].stan_konta){
                najwiekszy_biedak = grupa_klientow[i];cout << "w petli 11 " << najwieszy_burzuj->stan_konta << endl;}

            if (grupa_klientow[i].stan_konta > grupa_klientow[i - 1].stan_konta)
            {
                najwieszy_burzuj = &grupa_klientow[i];
                cout << "w petli " << najwieszy_burzuj->stan_konta << endl;
            }
        }
        else
        {
            najwiekszy_biedak = grupa_klientow[i];
            najwieszy_burzuj = grupa_klientow ;
        }
    }
}

int main()
{
    t_osoba klient;
    t_osoba bank[50]; //rozmiar roboczy
    t_osoba najwiekszy_biedak, najwieszy_burzuj;
    float nasza_srednia;
    //podaj_osobe(klient);
    /*  klient = podaj_osobe();  <--- wersja dla funkcji z return */
    //wypisz_osobe(klient);
    wczytaj_grupe(bank, 3);
    wypisz_osobe(bank[0]);
    wypisz_osobe(bank[1]);
    nasza_srednia = sredni_stan(bank, 3);
    cout << "Srednia to: " << nasza_srednia << endl;
    mini_max(bank, 2, najwiekszy_biedak, &najwieszy_burzuj);
    cout << "MIN: " << najwiekszy_biedak.stan_konta << "    MAX: " << najwieszy_burzuj.stan_konta << endl;
}