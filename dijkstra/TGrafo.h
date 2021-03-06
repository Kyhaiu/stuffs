#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <string>
#include <tuple>
#include "TLista.h"
#include "Vertice.h"
#include "TStack.h"
#include "TQueue.h"
#include <vector>

#define inf 2147483647;

using namespace std;

//--------------------------------------------------
//Classe Grafo - Prot�tipo
//--------------------------------------------------
class TGrafo{
   bool tipo; ///False = Grafo; True = D�grafo, Orientado ou Dirigido
   int autoid;
   int ordem;
   int dimensao;
   TLista<Vertice>* LVertices;
public:
   TGrafo();
   TGrafo(int _ordem, int _dimensao, bool _tipo);
   bool gettipo();
   void settipo(bool _tipo);
   int getordem();
   int getdimensao();
   TLista<Vertice>* getLVertices();
   tuple<int, float, float> getVerticePerXY(float _x, float _y);
   tuple<int, float, float> getVerticePerId(int _id);
   TNo<Vertice>* getVertice(float _x, float _y);
   TNo<Vertice>* getVerticeId(int _id);
   int AddVertice(string _name, float _x, float _y);
   void RemVertice(int _id);
   bool AddAresta(int _origem, int _destino, string _name, double _peso, bool _bidir);
   void RemAresta(int _origem, int _destino, bool _bidir);
   TLista<Vertice>* buscaAmplitude(float _x, float _y);
   TLista<Vertice>* buscaProfundiade(float _x, float _y);
   tuple<TLista<Vertice>*, double> dijkstra(float xi, float yi, float xf, float yf);
   void Print();
   ~TGrafo();
};

//--------------------------------------------------
//Classe Grafo - Implementa��o
//--------------------------------------------------
TGrafo::TGrafo(){
   tipo = false;
   ordem = 0;
   autoid = 0;
   dimensao = 0;
   LVertices = new TLista<Vertice>();
}

TGrafo::TGrafo(int _ordem, int _dimensao, bool _tipo = false){
   ordem = _ordem;
   dimensao = _dimensao;
   tipo = _tipo;
   autoid = 0;
   LVertices = new TLista<Vertice>();
}

bool TGrafo::gettipo(){
   return tipo;
}

void TGrafo::settipo(bool _tipo){
   tipo = _tipo;
}

int TGrafo::getordem(){
   return ordem;
}

int TGrafo::getdimensao(){
   return dimensao;
}

TLista<Vertice>* TGrafo::getLVertices(){
   return LVertices;
}

tuple<int, float, float> TGrafo::getVerticePerXY(float _x, float _y){
    tuple<int, float, float> ver;
    TNo<Vertice>* no = getLVertices()->getprim();
    float a, b;
    while(no != nullptr){
        a = no->getinfo().getX();
        b = no->getinfo().getY();
        if(_x == a && _y == b){
            get<0>(ver) = no->getinfo().getid();
            get<1>(ver) = no->getinfo().getX();
            get<2>(ver) = no->getinfo().getY();
            return ver;
        }
        no = no->getprox();
    }
    get<0>(ver) = -1;
    get<1>(ver) = 0;
    get<2>(ver) = 0;
    return ver;
}

tuple<int, float, float> TGrafo::getVerticePerId(int _id){
    tuple<int, float, float> ver;
    TNo<Vertice>* no = getLVertices()->getprim();
    int a;
    while(no != nullptr){
        a = no->getinfo().getid();
        if(_id == a){
            get<0>(ver) = no->getinfo().getid();
            get<1>(ver) = no->getinfo().getX();
            get<2>(ver) = no->getinfo().getY();
            return ver;
        }
        no = no->getprox();
    }
    get<0>(ver) = -1;
    get<1>(ver) = 0;
    get<2>(ver) = 0;
    return ver;
}

TNo<Vertice>* TGrafo::getVertice(float _x, float _y){
    TNo<Vertice>* no = getLVertices()->getprim();
    while(no != nullptr){
        if(no->getinfo().getX() == _x && no->getinfo().getY() == _y){
            break;
        }
        no = no->getprox();
    }
    return no;
}

TNo<Vertice>* TGrafo::getVerticeId(int _id){
    TNo<Vertice>* no = getLVertices()->getprim();
    while(no != nullptr){
        if(no->getinfo().getid() == _id){
            break;
        }
        no = no->getprox();
    }
    return no;
}

int TGrafo::AddVertice(string _name, float _x, float _y){
   Vertice *V = new Vertice();

   V->setid(autoid);
   ++autoid;
   V->setname(_name);
   V->setX(_x);
   V->setY(_y);
   LVertices->ins_fim(*V);
   ++ordem;
   free(V);
   return(autoid - 1);
}

void TGrafo::RemVertice(int _id){
   int i, j;
   TNo<Vertice> *v1 = LVertices->getprim();
   TNo<Vertice> *v2 = LVertices->getprim();
   bool achou = false;

   i = 0;
   while ((v1 != nullptr) and (!achou)){
      if (v1->getinfo().getid() == _id) achou = true;
      else{
         ++i;
         v1 = v1->getprox();
      }
   }

   if (v1 != nullptr){
      for (j = 0; j < ordem; ++j){
         if (v1 == v2) continue;
         while(v2->getinfo().Rem_Aresta(_id)) --dimensao;
         v2 = v2->getprox();
      }
      dimensao -= v1->getinfo().getLArestas()->size();
      LVertices->rem(i);
      --ordem;
   }
}

bool TGrafo::AddAresta(int _origem, int _destino, string _name, double _peso, bool _bidir){
   TNo<Vertice> *v = LVertices->getprim();
   TNo<Vertice> *vOrig, *vDest;

   vOrig = nullptr;
   vDest = nullptr;

   while((v != nullptr) || ((vOrig == nullptr) && (vDest == nullptr))){
      if(v->getinfo().getid() == _origem) vOrig = v;
      if(v->getinfo().getid() == _destino) vDest = v;
      v = v->getprox();
   }

   if(vOrig == nullptr){
      cout << "Vertice de origem nao encontrado. Aresta nao pode ser inserida!" << endl;
      return(false);
   }

   if(vDest == nullptr){
      cout << "Vertice de destino nao encontrado. Aresta nao pode ser inserida!" << endl;
      return(false);
   }

   vOrig->getinfo().Add_Aresta(_destino, _name, _peso);
   dimensao++;

   if (_bidir){
      vDest->getinfo().Add_Aresta(_origem, _name, _peso);
      dimensao++;
   }
   return(true);
}

void TGrafo::RemAresta(int _origem, int _destino, bool _bidir){
   TNo<Vertice> *v = LVertices->getprim();
   TNo<Vertice> *vOrig, *vDest;

   vOrig = nullptr;
   vDest = nullptr;

   while((v != nullptr) || ((vOrig == nullptr) && (vDest == nullptr))){
      if(v->getinfo().getid() == _origem) vOrig = v;
      if(v->getinfo().getid() == _destino) vDest = v;
      v = v->getprox();
   }

   if((vOrig == nullptr) || (vDest == nullptr)){
      cout << "Aresta nao encontrada!" << endl;
      exit(1);
   }

   while(vOrig->getinfo().Rem_Aresta(_destino)) --dimensao;
   if (_bidir){
      while(vDest->getinfo().Rem_Aresta(_origem)) --dimensao;
   }
}

void TGrafo::Print(){
   TNo<Vertice> *NoV;
   TNo<Aresta> *NoA;
   Vertice V;
   Aresta A;

   cout << endl << "----------------------------------------------------" << endl;
   cout << "Lista de vertices: " << endl;
   NoV = getLVertices()->getprim();
   tuple<int, float, float> t;
   while (NoV != nullptr){
      V = NoV->getinfo();
      cout << V.getname() << endl;
      cout << "Este vertice possui " << V.getLArestas()->size() << " arestas." << endl;
      cout << "Coordenadas do vertice: " << V.getX() << "-" << V.getY() << endl;
      NoA = V.getLArestas()->getprim();

      while (NoA != nullptr){
         A = NoA->getinfo();
         t = getVerticePerId(A.getid_dest());
         cout << "Origem: " << V.getid() << " - Destino: " << A.getid_dest() << " - Nome: " << A.getname() << endl;
         NoA = NoA->getprox();
      }
      cout << "----------------------------------------------------" << endl;
      NoV = NoV->getprox();
   }

   cout << "----------------------------------------------------" << endl;
   cout << "O grafo possui ordem = " << getordem() << endl;
   cout << "            dimensao = " << getdimensao() << endl;
   cout << "                tipo = " << gettipo() << endl;
   cout << "----------------------------------------------------" << endl << endl;
}

TLista<Vertice>* TGrafo::buscaAmplitude(float _x, float _y){
    TQueue<Vertice>* q = new TQueue<Vertice>();
    if(get<0>(getVerticePerXY(_x, _y)) == -1){
        cout << "Erro vertice inexistente!" << endl;
        return q->getList();
    }
    TNo<Vertice>* noV = getVertice(_x, _y); ///ponteiro que contem a referencia para o n� do vertice inicial
    TNo<Aresta>*  noA; ///no que contem a referencia para a lista de Adjacencia de cada vertice
    vector<Vertice> vect; /// vetor de Vertices j� percorridos
    bool jaVisitado = false; ///flag para indicar se o vertice est� no vetor de vertices percorridos

    vect.push_back(noV->getinfo()); ///insere o vertice inicial no vetor
    q->enqueue(noV->getinfo()); ///coloca na fila
    TLista<Vertice>* l = new TLista<Vertice>();
    l->ins_fim(noV->getinfo());
    while(q->Size() > 0){
        noA = q->dequeue().getLArestas()->getprim();
        while(noA != nullptr){
            for(int i = 0; i < (int)vect.size(); i++){
                if(vect[i].getid() == noA->getinfo().getid_dest()){
                    jaVisitado = true;
                    break;
                } else{
                    jaVisitado = false;
                }
            }
            if(!jaVisitado){
                l->ins_fim(getVerticeId(noA->getinfo().getid_dest())->getinfo());
                vect.push_back(getVerticeId(noA->getinfo().getid_dest())->getinfo());
                q->enqueue(getVerticeId(noA->getinfo().getid_dest())->getinfo());
            }
            noA = noA->getprox();
        }
    }
    if((int)l->size() == getordem()){ /// verifica se o tamanho da lista � = a ordem do grafo
        cout << "\nFoi possivel percorer todos os vertices a partir do ponto P(" << _x << ", " << _y << ").\n" << endl;
    } else{
        cout << "\nNao foi possivel percorer todos os vertices a partir do ponto P(" << _x << ", " << _y << ").\n" << endl;
    }
    return l;
}

TLista<Vertice>* TGrafo::buscaProfundiade(float _x, float _y){
    TStack<Vertice>* stck = new TStack<Vertice>();
    TStack<Vertice>* stcka = new TStack<Vertice>();
    if(get<0>(getVerticePerXY(_x, _y)) == -1){
        cout << "Erro vertice inexistente!" << endl;
        return stck->getList();
    }
    TNo<Vertice>* noV = getVertice(_x, _y);
    TNo<Aresta>*  noA;
    vector<Vertice> vect;
    bool seen = false;

    stck->push(noV->getinfo()); ///coloca na fila
    TLista<Vertice>* l = new TLista<Vertice>();
    l->ins_fim(stck->top());
    while(stck->Size() > 0){
        for(int i = 0; i < (int)vect.size(); i++){
                if(vect[i].getid() != stck->top().getid()){
                    seen = true;
                } else{
                    seen = false;
                    break;
                }
            }
        if(seen){
            l->ins_fim(stck->top());
        }
        vect.push_back(stck->top());
        noA = stck->top().getLArestas()->getprim();
        stck->pop();
        while(noA != nullptr){
            for(int i = 0; i < (int)vect.size(); i++){
                if(vect[i].getid() != noA->getinfo().getid_dest()){
                    seen = true;
                } else{
                    seen = false;
                    break;
                }
            }
            if(seen){
                stcka->push(getVerticeId(noA->getinfo().getid_dest())->getinfo());
            }
            noA = noA->getprox();
        }
        while(stcka->Size() > 0){
            stck->push(stcka->top());
            stcka->pop();
        }
    }
    if((int)l->size() == getordem()){ /// verifica se o tamanho da lista � = a ordem do grafo
        cout << "\n Foi possivel percorer todos os vertices a partir do ponto P(" << _x << ", " << _y << ").\n" << endl;
    } else{
        cout << "\n\n Nao foi possivel percorer todos os vertices a partir do ponto P(" << _x << ", " << _y << ").\n" << endl;
    }
    return l;
}

tuple<TLista<Vertice>*, double> TGrafo::dijkstra(float xi, float yi, float xf, float yf){
    int _origem = get<0>(getVerticePerXY(xi, yi));
    int _destino = get<0>(getVerticePerXY(xf, yf));
    tuple<TLista<Vertice>*, double> ret;
    get<0>(ret) = nullptr;
    get<1>(ret) = -1;
    if(_origem == -1 && _destino == -1){
        cout << "Origem e Destino nao encontrados" << endl;
        system("PAUSE");
        return ret;
    } else if(_origem == -1){
        cout << "Origem nao encontrada" << endl;
        system("PAUSE");
        return ret;
    } else if(_destino == -1){
        cout << "Destino nao encontrado" << endl;
        system("PAUSE");
    }
    double mat[getordem()][4];
    int i = 0;
    TNo<Vertice>* v = LVertices->getprim();
    int  aux;
    while(v != nullptr){
        aux = v->getinfo().getid();
        if(aux == _origem){
            mat[i][0] = aux;
            mat[i][1] = 0;
            mat[i][2] = 0;
            mat[i][3] = -1;
        } else{
            mat[i][0] = aux;
            mat[i][1] = 0;
            mat[i][2] = inf;
            mat[i][3] = -1;
        }
        i++;
        v = v->getprox();
    }
    TNo<Vertice>* noV = getVerticeId(get<0>(getVerticePerXY(xi, yi)));
    TNo<Aresta>* noA;

    i = _origem;
    int j, menor;
    double k;

    while(!mat[i][1] || i == _origem){
        mat[i][1] = 1;
        noA = noV->getinfo().getLArestas()->getprim();
        while(noA != nullptr){
            j = noA->getinfo().getid_dest();
            if(mat[j][1] == 0){
                k = mat[i][2] + noA->getinfo().getpeso();
                if(mat[j][2] > k){
                    mat[j][2] = k;
                    mat[j][3] = mat[i][0];
                }
            }
            noA = noA->getprox();
        }
        j = 0;
        while(mat[j][1] == 1){
            j++;
        }
        menor = j;
        j = 0;
        while(j < (int)getordem()){
            if(mat[menor][2] > mat[j][2] && mat[j][2] != 0 && mat[j][1] == 0){
                menor = mat[j][0];
            }
            j++;
        }
        noV = getVerticeId(menor);
        i = menor;
    }

    i = 0;
    while(mat[i][1]){
        i++;
    }
    mat[i][1] = 1;

    TLista<Vertice>* l = new TLista<Vertice>();
    i = _destino;
    if(mat[i][3] == -1){
        cout << "Nao existe rota que ligue direta/indiramente os vertices: "
             << mat[_origem][0] << "(" << getVerticeId(_origem)->getinfo().getX()
             << ", " << getVerticeId(_origem)->getinfo().getY() << ") e"
             << mat[_destino][0] << "(" << getVerticeId(_destino)->getinfo().getX()
             << ", " << getVerticeId(_destino)->getinfo().getY() << ")." << endl;
             return ret;
    }
    cout << "Caminho Minimo utilizando Dijkstra" << endl;
    cout << "Custo total para ir do V(" << xi << ", " << yi << ") ao V("
         << xf << ", " << yf << "). eh de " << mat[_destino][2] << " unidades de distancia" << endl;
    cout << "Vertices percorridos: " << endl << endl << "Inicio ";
    while(mat[i][2] != 0){
        l->ins_ini(getVerticeId(i)->getinfo());
        i = mat[i][3];
    }
    l->ins_ini(getVerticeId(i)->getinfo());
    noV = l->getprim();
    while(noV != nullptr){
        cout << noV->getinfo().getid() << "(" << noV->getinfo().getX()
             << ", " << noV->getinfo().getY() << ") -> ";
        noV = noV->getprox();
    }
    cout << "Fim" << endl;
    system("PAUSE");

    get<0>(ret) = l;
    get<1>(ret) = mat[_destino][2];
    return ret;
}

TGrafo::~TGrafo(){
   TNo<Vertice> *V = LVertices->getprim();

   while (V != nullptr){
      delete(V->getinfo().getLArestas());
      V = V->getprox();
   }
   delete(LVertices);
}

#endif // GRAFO_H_INCLUDED
