#ifndef TSTACK_H_INCLUDED
#define TSTACK_H_INCLUDED
#include "TLista.h"

template<typename T> class TStack{
    private:
        TLista<T>* L;
    public:
        TStack<T>();
        T top();
        void push(T info);
        void pop();
        bool isempty();
        ~TStack();
};

template <typename T> TStack<T>::TStack(){
    L = new TLista<T>();
}

template <typename T> void TStack<T>::push(T _info){
    L->setBegin(_info);
}

template <typename T> void TStack<T>::pop(){
    L->removeBegin();
}

template <typename T> T TStack<T>::top(){
    TNo<T> *aux = L->getprim();
    return aux->getInfo();
}

template <typename T> TStack<T>::~TStack(){
    delete L;
}

template <typename T> bool TStack<T>::isempty(){
    return (L->size()==0);
}

#endif // TSTACK_H_INCLUDED
