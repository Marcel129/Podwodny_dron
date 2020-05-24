#include <iostream>
#include <unistd.h>
#include "Macierz.hh"
#include "Dr3D_gnuplot_api.hh"
#include "dron.hh"
#include "powierzchnia.hh"
#include "parametry_drona.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{

  Wektor3D WT,W0; //zmienna na przechowanie parametrów translacji wprowadzonych przez użytkownika
  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-SZEROKOSC_BASENU, DLUGOSC_BASENU, -WYSOKOSC_BASENU, SZEROKOSC_BASENU, -DLUGOSC_BASENU, WYSOKOSC_BASENU, -1));
  //włacza gnuplota, pojawia się scena, odswiezanie po każdym pojawieniu sie nowego konturu
  int x = 0; //zmienna pomocnicza do sterowania switchem
  powierzchnia dno(api),lustro_wody(api);
  dno.draw(-9.5);
  lustro_wody.draw(8.5, "blue");
  
  
  cout << endl
       << endl
       << "Podaj współrzędne startowe: ";
  cin >> WT;
  dron dronisko(api, D_DRONA, S_DRONA, W_DRONA, WT[0],WT[1],WT[2]);
  dronisko.draw();
  do
  {
    if (cin.fail() == false)
    {
      cout << "Co chcesz zrobić z dronem?\n1-Przesuń\n2-Obróć\n";
      cin >> x;
      switch (x)
      {
      case 1:
        cout << "Podaj wektor przesuniecia: " << endl;
        cin >> WT;
        dronisko.move(WT);
        dronisko.draw();
        cout<<"Aktualne polozenie drona: "<<dronisko.get_przes()<<endl;
        break;
      case 2:
        cout << "Podaj os i kat obrotu:  " << endl;
        double kat;
        char os;
        cin >> os >> kat;
        dronisko.rotate(os,kat);
        dronisko.draw();
        break;
      case 12:
        cout << "Zakończono pracę." << endl;
        exit(1);
        break;
      default:
        cout << "Nie ma takiej opcji." << endl;
        break;
      }
    }
  } while (cin.fail() == false);
}
