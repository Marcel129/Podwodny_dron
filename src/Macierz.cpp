#include "Macierz.hh"
template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strWej, Macierz<TYP, ROZMIAR> &M)
{
    for (int i = 0; i < ROZMIAR; i++)
        strWej >> M[i];
    return strWej;
}

template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strWyj, const Macierz<TYP, ROZMIAR> &M)
{
    for (int i = 0; i < ROZMIAR; i++)
        std::cout << M[i];
    std::cout << std::endl;

    return strWyj;
}
template <typename TYP, int ROZMIAR>
Macierz<TYP, ROZMIAR>::Macierz()
{
    int i = 0;
    for (Wektor<TYP, ROZMIAR> &tab : tablica)
    {
        tab = 0.0;
        ++i;
    }
}

template <typename TYP, int ROZMIAR>
void Macierz<TYP, ROZMIAR>::transponuj_macierz()
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = i; j < ROZMIAR; j++)
            std::swap(tablica[i][j], tablica[j][i]);
    }
}

template <typename TYP, int ROZMIAR>
const Wektor<TYP, ROZMIAR> &Macierz<TYP, ROZMIAR>::operator[](int ind) const //get
{
    if (ind < 0 || ind > ROZMIAR)
    {
        std::cout << ind << std::endl;
        std::cerr << "Przekroczenie zakresu" << std::endl;
        exit(1);
    }
    return tablica[ind];
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> &Macierz<TYP, ROZMIAR>::operator[](int ind) //set
{
    if (ind < 0 || ind > ROZMIAR)
    {
        std::cout << ind << std::endl;
        std::cerr << "Przekroczenie zakresu" << std::endl;
        exit(1);
    }
    return tablica[ind];
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Macierz<TYP, ROZMIAR>::operator*(const Wektor<TYP, ROZMIAR> W) const //mnożenie macierzy przez wektor
{
    Wektor<TYP, ROZMIAR> Wynik;
    for (int k = 0; k < ROZMIAR; ++k)
    {
        TYP iloczyn;
        iloczyn = iloczyn * 0; //zainicjowanie iloczynu zerem
        for (int i = 0; i < ROZMIAR; ++i)
        {
            iloczyn = iloczyn + tablica[k][i] * W[i];
        }
        Wynik[k] = iloczyn;
    }
    return Wynik;
}

template <typename TYP, int ROZMIAR>
Macierz<TYP, ROZMIAR> Macierz<TYP, ROZMIAR>::operator*(const Macierz<TYP, ROZMIAR> M) const //mnożenie macierzy przez macierz
{
    Macierz<TYP, ROZMIAR> Wynik;
    for (int j = 0; j < ROZMIAR; ++j)
    {
        for (int k = 0; k < ROZMIAR; ++k)
        {
            TYP iloczyn;
            iloczyn = iloczyn * 0; //zainicjowanie iloczynu zerem
            for (int i = 0; i < ROZMIAR; ++i)
            {
                iloczyn = iloczyn + tablica[j][i] * M[i][k];
            }
            Wynik[j][k] = iloczyn;
        }
    }
    return Wynik;
}

template <typename TYP, int ROZMIAR>
TYP Macierz<TYP, ROZMIAR>::wyz_gauss()
{
    /*
    Implementacja obliczania wyznacznika macierzy metodą Gaussa.
    Odejmuje od kolejnych wierszy macierzy jej pierwszy wiersz pomnożony przez iloraz pierwszego elementu w danym wierszu i pierwszego elementu macierzy 
    (elementu o indeksie[1][1]). Po zakończeniu operacji jest ona powtarzana, tym razem zaczynając od wiersza drugiego pomnożonego przez iloraz 
    pierwszego niezerowego elementu tego wiersza i elementu macierzy o indeksach [2][2]. Operacje powtarzamy dla wszystkich wierszy, za każdym razem
    przesuwając się o wiersz w dół, a dzielnikiem stają się kolejne elementy stojące na głównej przekątnej.
    Przeprowadzanie tych operacji ma na celu przekształcenie macierzy do postaci górnotrójkątnej (wyzerowanie elementów znajdujących się pod główną przekątną).
    Wyznacznik powstałej macierzy obliczamy mnożąc przez siebie wszystkie elementy znajdujące się na głównej przekątnej.
    */
    Macierz<TYP, ROZMIAR> M = tablica;
    TYP wyznacznik(1.0);
    int znak = 1;

    for (int k = 0; k < ROZMIAR - 1; ++k)
    {
        for (int i = 1 + k; i < ROZMIAR; ++i)
        {
            if (M[k][k] != 0)
                M[i] = M[i] - M[k] * (M[i][k] / M[k][k]);
            else
            {
                std::cout << "Wykryto zerowy element macierzy. Obliczenie niemożliwe." << std::endl;
                exit(1);
            }
        }
    }
    for (int i = 0; i < ROZMIAR; ++i)
        wyznacznik = M[i][i] * wyznacznik;

    return wyznacznik * znak;
}

Macierz_Obrotu::Macierz_Obrotu()
{
    Wektor3D W(0, 0, 0);
    for (int i = 0; i < ROZ; ++i)
        tablica[i] = W;
    
    for (int i = 0; i < ROZ; ++i)
        tablica[i][i] = 1; //inicjalizuje macierz jednostkową
    
}

Macierz_Obrotu::Macierz_Obrotu(char os, double kat)
{ 
    Wektor3D W(0, 0, 0);
    kat = (M_PI / 180) * kat;//radiany na stopnie
    for (int i = 0; i < ROZ; ++i)
        tablica[i] = W;

    if (os == 'z')
    {
        tablica[0][0] = cos(kat);
        tablica[0][1] = -sin(kat);
        tablica[1][0] = sin(kat);
        tablica[1][1] = cos(kat);
        tablica[2][2] = 1;
    }
    else if (os == 'y')
    {
        tablica[0][0] = cos(kat);
        tablica[0][2] = sin(kat);
        tablica[2][0] = -sin(kat);
        tablica[2][2] = cos(kat);
        tablica[1][1] = 1;
    }
    else if (os == 'x')
    {
        tablica[1][1] = cos(kat);
        tablica[1][2] = -sin(kat);
        tablica[2][1] = sin(kat);
        tablica[2][2] = cos(kat);
        tablica[0][0] = 1;
    }
    else{
        cout<<"Nie ma takiej osi"<<endl;
        Wektor3D W(0, 0, 0);
    for (int i = 0; i < ROZ; ++i)
        tablica[i] = W;
    
    for (int i = 0; i < ROZ; ++i)
        tablica[i][i] = 1; //wykonuje obrót dla macierzy jednostkowej, czyli nie wykonuje
    }
}
