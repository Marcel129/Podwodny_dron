#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include "int_rysowania.hh"
#include "Dr3D_gnuplot_api.hh"

#define MIN_ROZ_WYS 0.5 //wyskosc nierownosci powierzchni

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::vector;

class powierzchnia : public int_rysowania
{
public:
    powierzchnia(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api) { api = wskazane_api;ID=-20; };
    void draw(double wysokosc, std::string kolor = "grey");
};

#endif