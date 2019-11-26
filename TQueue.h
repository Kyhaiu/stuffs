#ifndef TQUEUE_H_INCLUDED
#define TQUEUE_H_INCLUDED
#include "TLista.h"

template<typename T> class TQueue{
    private:
        TLista<T> *Q;
    public:
        TQueue<T>();
        void enqueue(T _info);
        T dequeue();
        TLista<T>* getList();
};

template<typename T>TQueue<T>::TQueue(){
    Q = new TLista<T>();
}

template<typename T> void TQueue<T>::enqueue(T _info){
    Q->ins_fim(_info);
}

template<typename T> T TQueue<T>::dequeue(){
    T aux = Q->getprim()->getinfo();
    Q->rem_ini();
    return aux;
}

template<typename T>TLista<T>* TQueue<T>::getList(){
    return Q;
}

#endif // TQUEUE_H_INCLUDED
