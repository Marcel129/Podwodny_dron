#include "dron.hh"

dron::dron(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double d, double s, double w, double x, double y, double z)
{
    prostopadloscian pi(wskazane_api, d, s, w, x, y, z);
    korpus = pi;
    Wirnik Wir(wskazane_api, D_WIRNIKA, S_WIRNIKA, W_WIRNIKA, 0, 0, 0);
    Wir_lewy = Wir;
    Wir_prawy = Wir;
    Wektor3D WL(x, y, z);                                                                   //wektory inicjalizacyjne dla wirnikow
    Wektor3D OD_L((S_DRONA + S_WIRNIKA) / 2, 0, 0), OD_P(-(S_DRONA + S_WIRNIKA) / 2, 0, 0); //wektory inicjalizacyjne dla wirnikow
    Wir_prawy.set_od(OD_L);
    Wir_lewy.set_od(OD_P);
    Wir_lewy.przesun(WL);
    Wir_prawy.przesun(WL);
}

void dron::draw()
{  
    Wir_prawy.draw();
    Wir_lewy.draw();
    korpus.draw();
}

void dron::move(const Wektor3D &W)
{
    int ilosc_krokow = W.dlugosc() / MIN_DYST;
    Wektor3D krok = W / ilosc_krokow;                        //oblicz wektor cząstkowy
    Wektor3D zapamietaj_przesuniecie_k = korpus.get_przes(); //zapamietaj aktualne polozenie
    Wektor3D zapamietaj_przesuniecie_wp = Wir_prawy.get_przes();
    Wektor3D zapamietaj_przesuniecie_wl = Wir_lewy.get_przes();

    for (int i = 0; i < ilosc_krokow + 1; ++i) //animuj ruch
    {
        Wir_lewy.set_own_angle('y', 30 * (i % 3));
        Wir_prawy.set_own_angle('y', 30 * (i % 3));
        przesun(krok);
        draw();
    }
    korpus.set_przes(zapamietaj_przesuniecie_k); //unikam bledu numerycznego powstałego przy animacji wykonujac pojedyncze przesuniecie
    Wir_prawy.set_przes(zapamietaj_przesuniecie_wp);
    Wir_lewy.set_przes(zapamietaj_przesuniecie_wl);
    przesun(W); //przesuwam dron
}

void dron::rotate(char os, double kat)
{
    double zapamietaj_orientacje_k = korpus.get_angle(os);
    double zapamietaj_orientacje_wl = Wir_lewy.get_angle(os);
    double zapamietaj_orientacje_wp = Wir_prawy.get_angle(os);
    int k = 0;
    for (double i = 0; i < (kat / MIN_KAT) + MIN_KAT; ++k, i += MIN_KAT) //animuj obrot
    {
        Wir_lewy.set_own_angle('y', 30 * (k % 3));
        Wir_prawy.set_own_angle('y', 30 * (k % 3));
        obroc(os, MIN_KAT);
        draw();
    }
    korpus.set_angle(os, zapamietaj_orientacje_k);
    Wir_prawy.set_angle(os, zapamietaj_orientacje_wp);
    Wir_lewy.set_angle(os, zapamietaj_orientacje_wl);
    obroc(os, kat);
}

//operacje cząstkowe
void dron::przesun(const Wektor3D &W)
{
    korpus.przesun(W);
    Wir_prawy.przesun(W);
    Wir_lewy.przesun(W);
}

void dron::obroc(char os, double kat)
{
    korpus.obroc(os, kat);
    Wir_prawy.obroc(os, kat);
    Wir_lewy.obroc(os, kat);
}