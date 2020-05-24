#include "Wektor.cpp"
#include "Macierz.cpp"
#include "rozmiar.h"

template class Wektor<double, ROZ>;
template class Macierz<double, ROZ>;
//template class UkladRownanLiniowych<double, ROZ>;
template std::istream &operator>>(std::istream &strWej, Wektor<double, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Wektor<double, ROZ> &W);
template std::istream &operator>>(std::istream &strWej, Macierz<double, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Macierz<double, ROZ> &W);/*
template std::istream &operator>>(std::istream &Strm, UkladRownanLiniowych<double, ROZ> &UklRown);
template std::ostream &operator<<(std::ostream &Strm, const UkladRownanLiniowych<double, ROZ> &UklRown);

template class Wektor<LZespolona, ROZ>;
template class Macierz<LZespolona, ROZ>;
template class UkladRownanLiniowych<LZespolona, ROZ>;
template std::istream &operator>>(std::istream &strWej, Macierz<LZespolona, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Macierz<LZespolona, ROZ> &W);
template std::istream &operator>>(std::istream &strWej, Wektor<LZespolona, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Wektor<LZespolona, ROZ> &W);
template std::istream &operator>>(std::istream &Strm, UkladRownanLiniowych<LZespolona, ROZ> &UklRown);
template std::ostream &operator<<(std::ostream &Strm, const UkladRownanLiniowych<LZespolona, ROZ> &UklRown);
*/
/*  SPECJALIZACJE  */
template<>
double Wektor<double,ROZ>::dlugosc()const
{
    double dl = 0;
    for (int a = 0; a < ROZ; ++a)
        dl += tablica[a] * tablica[a];
    dl = sqrt(dl);
    return dl;
}
/*
template<>
double Wektor<LZespolona,ROZ>::dlugosc()const
{
    double dl = 0;
    for (int a = 0; a < ROZ; ++a)
        dl += sqrt(pow(tablica[a].get_re(),2) + pow(tablica[a].get_im(),2));
    dl = sqrt(dl);
    return dl;
}*/