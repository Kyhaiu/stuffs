#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Aresta.h"
#include "TLista.h"

using namespace std;

//--------------------------------------------------
//Classe Vertice - Prot�tipo
//--------------------------------------------------
class Vertice{
   int id;
   string name;
   float x;
   float y;
   bool visited;
   TLista<Aresta>* LArestas;
public:
   Vertice();
   int getid();
   string getname();
   float getX();
   float getY();
   bool isVisited();
   void setid(int _id);
   void setname(string _name);
   void setX(float _x);
   void setY(float _y);
   void setVisited(bool isVisited);
   TLista<Aresta>* getLArestas();
   void Add_Aresta(int _destino, string _name, double _peso);
   bool Rem_Aresta (int _id);
};

//--------------------------------------------------
//Classe Aresta - Implementa��o
//--------------------------------------------------
Vertice::Vertice(){
   LArestas = new TLista<Aresta>();
}

int Vertice::getid(){
   return id;
}

string Vertice::getname(){
   return name;
}

float Vertice::getX(){
    return x;
}

float Vertice::getY(){
    return y;
}

bool Vertice::isVisited(){
    if(visited){
        return true;
    }
    return false;
}

void Vertice::setid(int _id){
   id = _id;
}

void Vertice::setname(string _name){
   name = _name;
}

void Vertice::setX(float _x){
    x = _x;
}

void Vertice::setY(float _y){
    y = _y;
}

void Vertice::setVisited(bool isVisisted){
    visited = isVisisted;
}

TLista<Aresta>* Vertice::getLArestas(){
   return LArestas;
}

void Vertice::Add_Aresta(int _destino, string _name, double _peso){
   Aresta *A;

   A = new Aresta(_destino, _name, _peso);
   LArestas->ins_fim(*A);
   free(A);
}

bool Vertice::Rem_Aresta (int _id){
   TNo<Aresta> *p = LArestas->getprim();
   int i = 0;
   bool achou = false;

   while ((p != nullptr) && (!achou)){
      if (p->getinfo().getid_dest() == _id) achou = true;
      else {
         p = p->getprox();
         ++i;
      }
   }

   if (achou) LArestas->rem(i);
   return(achou);
}

#endif // VERTICE_H_INCLUDED
