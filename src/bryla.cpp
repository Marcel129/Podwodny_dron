#include "bryla.hh"

prostopadloscian::prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI> w_api, double d, double s, double w, double x, double y, double z)
{
    ID = -20;
    kat_x = 0;
    kat_y = 0;
    kat_z = 0;
    wlasny_kat_x = 0, wlasny_kat_y = 0, wlasny_kat_z = 0;
    api = w_api;
    dlugosc = d;
    szerokosc = s;
    wysokosc = w;
    Wektor3D WT(x, y, z), wz;
    przesuniecie = wz;
    Wektor3D W(szerokosc, dlugosc, wysokosc);
    W = W * 0.5;
    wierzcholki[0][0] = srodek[0] + W[0];
    wierzcholki[0][1] = srodek[1] - W[1];
    wierzcholki[0][2] = srodek[2] - W[2];
    wierzcholki[1][0] = srodek[0] + W[0];
    wierzcholki[1][1] = srodek[1] + W[1];
    wierzcholki[1][2] = srodek[2] - W[2];
    wierzcholki[2][0] = srodek[0] - W[0];
    wierzcholki[2][1] = srodek[1] + W[1];
    wierzcholki[2][2] = srodek[2] - W[2];
    wierzcholki[3][0] = srodek[0] - W[0];
    wierzcholki[3][1] = srodek[1] - W[1];
    wierzcholki[3][2] = srodek[2] - W[2];
    wierzcholki[4][0] = srodek[0] + W[0];
    wierzcholki[4][1] = srodek[1] - W[1];
    wierzcholki[4][2] = srodek[2] + W[2];
    wierzcholki[5][0] = srodek[0] + W[0];
    wierzcholki[5][1] = srodek[1] + W[1];
    wierzcholki[5][2] = srodek[2] + W[2];
    wierzcholki[6][0] = srodek[0] - W[0];
    wierzcholki[6][1] = srodek[1] + W[1];
    wierzcholki[6][2] = srodek[2] + W[2];
    wierzcholki[7][0] = srodek[0] - W[0];
    wierzcholki[7][1] = srodek[1] - W[1];
    wierzcholki[7][2] = srodek[2] + W[2];
    przesun(WT);
    cout << "Zainicjowano prostopadloscian w punkcie: " << srodek << endl;
}

double prostopadloscian::get_angle(char os)
{
    if (os == 'x')
        return kat_x;
    else if (os == 'y')
        return kat_y;
    else if (os == 'z')
        return kat_z;
    else
        cerr << "Nie ma takiej osi" << endl;
}

void prostopadloscian::set_angle(char os, double kat)
{
    if (os == 'x')
        kat_x = kat;
    else if (os == 'y')
        kat_y = kat;
    else if (os == 'z')
        kat_z = kat;
}
double prostopadloscian::get_own_angle(char os)
{
    if (os == 'x')
        return wlasny_kat_x;
    else if (os == 'y')
        return wlasny_kat_y;
    else if (os == 'z')
        return wlasny_kat_z;
    else
        cerr << "Nie ma takiej osi" << endl;
}
void prostopadloscian::set_own_angle(char os, double kat)
{
    if (os == 'x')
        wlasny_kat_x = kat;
    else if (os == 'y')
        wlasny_kat_y = kat;
    else if (os == 'z')
        wlasny_kat_z = kat;
}

void prostopadloscian::draw(std::string zadany_kolor)
{
    kolor = zadany_kolor;
    usun(); //usunięcie poprzedniego widoku drona
    //rysowanie drona o zadanych wymiarach
    ID = api->draw_polyhedron(vector<vector<Point3D>>{{drawNS::Point3D(wierzcholki[0][0], wierzcholki[0][1], wierzcholki[0][2]),
                                                       drawNS::Point3D(wierzcholki[1][0], wierzcholki[1][1], wierzcholki[1][2]),
                                                       drawNS::Point3D(wierzcholki[2][0], wierzcholki[2][1], wierzcholki[2][2]),
                                                       drawNS::Point3D(wierzcholki[3][0], wierzcholki[3][1], wierzcholki[3][2]),
                                                       drawNS::Point3D(wierzcholki[0][0], wierzcholki[0][1], wierzcholki[0][2])},
                                                      {drawNS::Point3D(wierzcholki[4][0], wierzcholki[4][1], wierzcholki[4][2]),
                                                       drawNS::Point3D(wierzcholki[5][0], wierzcholki[5][1], wierzcholki[5][2]),
                                                       drawNS::Point3D(wierzcholki[6][0], wierzcholki[6][1], wierzcholki[6][2]),
                                                       drawNS::Point3D(wierzcholki[7][0], wierzcholki[7][1], wierzcholki[7][2]),
                                                       drawNS::Point3D(wierzcholki[4][0], wierzcholki[4][1], wierzcholki[4][2])}},
                              kolor);
    api->redraw();
}

void prostopadloscian::aktualizuj_wierzcholki(const Wektor3D &W2, char os, double kat) //domyslnie nie obracaj wokol zadnej osi i nie przesuwaj
{
    if (os == 'x')
    {
        kat_x += kat;
    }
    else if (os == 'y')
    {
        kat_y += kat;
    }
    else if (os == 'z')
    {
        kat_z += kat;
    }
    Macierz_Obrotu W_OX('x', wlasny_kat_x), W_OY('y', wlasny_kat_y), W_OZ('z', wlasny_kat_z), wlasna_orientacja;
    Macierz_Obrotu OX('x', kat_x), OY('y', kat_y), OZ('z', kat_z), orientacja_drona;
    wlasna_orientacja = W_OX * W_OY * W_OZ;
    orientacja_drona = OX * OY * OZ;
    przesuniecie = W2 + przesuniecie;
    Wektor3D W(szerokosc, dlugosc, wysokosc);
    W = W * 0.5;
    wierzcholki[0][0] = srodek[0] + W[0];
    wierzcholki[0][1] = srodek[1] - W[1];
    wierzcholki[0][2] = srodek[2] - W[2];
    wierzcholki[1][0] = srodek[0] + W[0];
    wierzcholki[1][1] = srodek[1] + W[1];
    wierzcholki[1][2] = srodek[2] - W[2];
    wierzcholki[2][0] = srodek[0] - W[0];
    wierzcholki[2][1] = srodek[1] + W[1];
    wierzcholki[2][2] = srodek[2] - W[2];
    wierzcholki[3][0] = srodek[0] - W[0];
    wierzcholki[3][1] = srodek[1] - W[1];
    wierzcholki[3][2] = srodek[2] - W[2];
    wierzcholki[4][0] = srodek[0] + W[0];
    wierzcholki[4][1] = srodek[1] - W[1];
    wierzcholki[4][2] = srodek[2] + W[2];
    wierzcholki[5][0] = srodek[0] + W[0];
    wierzcholki[5][1] = srodek[1] + W[1];
    wierzcholki[5][2] = srodek[2] + W[2];
    wierzcholki[6][0] = srodek[0] - W[0];
    wierzcholki[6][1] = srodek[1] + W[1];
    wierzcholki[6][2] = srodek[2] + W[2];
    wierzcholki[7][0] = srodek[0] - W[0];
    wierzcholki[7][1] = srodek[1] - W[1];
    wierzcholki[7][2] = srodek[2] + W[2];

    for (int i = 0; i < 8; ++i)
        wierzcholki[i] = orientacja_drona * (wlasna_orientacja * wierzcholki[i] + get_od()) + przesuniecie;
}
