#include <iostream>
#include <string>
#include "BazaTestu.hh"

using namespace std;




int main(int argc, char **argv)
{

  if (argc < 2) {
    cout << endl;
    cout << " Brak opcji okreslajacej rodzaj testu." << endl;
    cout << " Dopuszczalne nazwy to:  latwy, trudny." << endl;
    cout << endl;
    return 1;
  }


  BazaTestu   BazaT = { nullptr, 0, 0 };

  if (InicjalizujTest(&BazaT,argv[1]) == false) {
    cerr << " Inicjalizacja testu nie powiodla sie." << endl;
    return 1;
  }


  
  cout << endl;
  cout << " Start testu arytmetyki zespolonej: " << argv[1] << endl;
  cout << endl;

  int i;
  WyrazenieZesp   WyrZ_PytanieTestowe;
  LZespolona      Odpowiedz;    
  LZespolona      Wynik;
  Statystyka      StatOdp;
  StatOdp = Wyzeruj(StatOdp);
  
  while (PobierzNastpnePytanie(&BazaT,&WyrZ_PytanieTestowe)) {
    cout << "Podaj wynik operacji: " << WyrZ_PytanieTestowe << " = " << endl;
    cout << endl << "Twoja odpowiedz:  " << endl;
    cin >> Odpowiedz;
    if(cin.fail()){
      for(i=0;i<2;i++){
        cin.clear();
        cin.ignore(256, '\n');
        cout << endl;
        cout << "Blad zapisu liczby zespolonej. Sprobuj jeszcze raz." << endl;
        cout << endl << "Twoja odpowiedz:  " << endl;
        cin >> Odpowiedz;
        if(!cin.fail()){
          break;
        }    
      }
      if(cin.fail()){
        cout << "Przekroczono liczbę błędów zapisu liczby zespolonej." << endl;
      }
      cin.clear();
      cin.ignore(256, '\n');
    }
    cout << endl;
    Wynik = Oblicz(WyrZ_PytanieTestowe);
    if(Odpowiedz == Wynik){
      cout << " :) Odpowiedz poprawna! " << endl << endl;
      StatOdp = Poprawnie(StatOdp);
    } else {
      cout << " :( Odpowiedz niepoprawna, prawidlowy wynik: " << Wynik << endl << endl; 
      StatOdp = Niepoprawnie(StatOdp);
    }
  }

  
  cout << endl;
  cout << " Koniec testu" << endl;
  cout << endl;
  cout << "Ilosc dobrych odpowiedzi: " << StatOdp.poprawne << endl;
  cout << "Ilosc blednych odpowiedzi: " << StatOdp.wszystkie - StatOdp.poprawne << endl;
  cout << "Wynik procentowy poprawnych odpowiedzi: " << 100 * StatOdp.poprawne / StatOdp.wszystkie << "%" << endl;

}
