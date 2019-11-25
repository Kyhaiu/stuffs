#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include <cmath>
#include <string>

using namespace std;

//--------------------------------------------------
//Classe Aresta - Prot�tipo
//--------------------------------------------------
class Aresta{
   int id_dest;
   string name;
   double peso;

public:
   Aresta():id_dest(-1), name(""), peso(0){};
   Aresta(int _id_dest, string _name, double _peso):id_dest(_id_dest), name(_name), peso(_peso){};
   int getid_dest();
   string getname();
   double getpeso();
   void setid_dest(int _dest);
   void setname(string _name);
   void setpeso(double _peso);
};

//--------------------------------------------------
//Classe Aresta - Implementa��o
//--------------------------------------------------
int Aresta::getid_dest(){
   return id_dest;
}

string Aresta::getname(){
   return name;
}

double Aresta::getpeso(){
   return peso;
}

void Aresta::setid_dest(int _dest){
   id_dest = _dest;
}

void Aresta::setname(string _name){
   name = _name;
}

void Aresta::setpeso(double _peso){
   peso = _peso;
}

#endif // ARESTA_H_INCLUDED
