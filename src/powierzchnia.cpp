#include "powierzchnia.hh"

void powierzchnia::draw(double wysokosc, std::string kolor)
{
    ID = api->draw_surface(vector<vector<Point3D>>{
                               {drawNS::Point3D(-10, -10, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(-10, -5, wysokosc), drawNS::Point3D(-10, 0, wysokosc+MIN_ROZ_WYS)},
                               {drawNS::Point3D(-5, -10, wysokosc), drawNS::Point3D(-5, -5, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(-5, 0, wysokosc)},
                               {drawNS::Point3D(0, -10, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(0, -5, wysokosc), drawNS::Point3D(0, 0, wysokosc+MIN_ROZ_WYS)},
                               {drawNS::Point3D(5, -10, wysokosc), drawNS::Point3D(5, -5, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(5, 0, wysokosc)},
                               {drawNS::Point3D(10, -10, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(10, -5, wysokosc), drawNS::Point3D(10, 0, wysokosc+MIN_ROZ_WYS)},
                               {drawNS::Point3D(10, 0, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(10, 5, wysokosc), drawNS::Point3D(10, 10, wysokosc+MIN_ROZ_WYS)},
                               {drawNS::Point3D(5, 0, wysokosc), drawNS::Point3D(5, 5, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(5, 10, wysokosc)},
                               {drawNS::Point3D(0, 0, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(0, 5, wysokosc), drawNS::Point3D(0, 10, wysokosc+MIN_ROZ_WYS)},
                               {drawNS::Point3D(-5, 0, wysokosc), drawNS::Point3D(-5, 5, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(-5, 10, wysokosc)},
                               {drawNS::Point3D(-10, 0, wysokosc+MIN_ROZ_WYS), drawNS::Point3D(-10, 5, wysokosc), drawNS::Point3D(-10, 10, wysokosc+MIN_ROZ_WYS)},
                           },
                           kolor); //rysuje powierzchnie
                            api->redraw();
}