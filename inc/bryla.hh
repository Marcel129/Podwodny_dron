#ifndef BRYLA_HH
#define BRYLA_HH

#include "Macierz.hh"
#include "Wektor.hh"
#include "Dr3D_gnuplot_api.hh"
#include "int_rysowania.hh"
#include "parametry_drona.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::vector;

class bryla : public int_rysowania
{
protected:
    Wektor3D srodek, przesuniecie;
    double kat_x, kat_y, kat_z;
    Wektor3D odsuniecie;
    double wlasny_kat_x, wlasny_kat_y, wlasny_kat_z;

public:
    bryla(){};
    const Wektor3D &get_s() { return srodek; }
    void move(const Wektor3D &W);
};

class prostopadloscian : public bryla
{
protected:
    Wektor3D wierzcholki[8];
    double dlugosc, szerokosc, wysokosc;
    

public:
    prostopadloscian(){};
    prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI>, double d, double s, double w, double x, double y, double z);

    void draw(std::string zadany_kolor = "green"); //można zmienić kolor, ale nie ma obowiązku, żeby go podać
    void aktualizuj_wierzcholki(const Wektor3D &W2, char os = 'z', double kat = 0);
    void przesun(const Wektor3D &W2) { aktualizuj_wierzcholki(W2); }
    void obroc(char os, double kat)
    {
        Wektor3D wektor_zerowy;
        aktualizuj_wierzcholki(wektor_zerowy, os, kat);
    }
    void set_od(const Wektor3D &W) { odsuniecie = W; }
    const Wektor3D &get_od() { return odsuniecie; }
    void set_przes(const Wektor3D &W) { przesuniecie = W; }
    const Wektor3D &get_przes() { return przesuniecie; }
    double get_angle(char os);
    void set_angle(char os, double kat);
    double get_own_angle(char os);
    void set_own_angle(char os, double kat);
};

#endif
