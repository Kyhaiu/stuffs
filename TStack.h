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
        int Size();
        TLista<T>* getList();
        ~TStack();
};

template <typename T> TStack<T>::TStack(){
    L = new TLista<T>();
}

template <typename T> void TStack<T>::push(T _info){
    L->ins_ini(_info);
}

template <typename T> void TStack<T>::pop(){
    L->rem_ini();
}

template <typename T> T TStack<T>::top(){
    TNo<T> *aux = L->getprim();
    return aux->getinfo();
}

template <typename T> TStack<T>::~TStack(){
    delete L;
}

template <typename T> int TStack<T>::Size(){
    return L->size();
}

template <typename T> TLista<T>* TStack<T>::getList(){
    return L;
}

#endif // TSTACK_H_INCLUDED
