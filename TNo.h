#ifndef TNO_H_INCLUDED
#define TNO_H_INCLUDED

using namespace std;

template <typename T> class TNo{
      T info;
      TNo<T> *prox;
   public:
      TNo();
      TNo(const TNo<T> &No);
      void setinfo(T _info);
      T getinfo();
      void setprox(TNo<T> *_prox);
      TNo<T>* getprox();
      TNo<T>& operator=(const TNo<T> &No);
      ~TNo<T>();
};

template<typename T> TNo<T>::TNo(){
   //info = (T)0;
   prox = nullptr;
}

template<typename T> TNo<T>::TNo(const TNo<T> &No){
   info = No.info;
   prox = No.prox;
}

template<typename T> void TNo<T>::setinfo(T _info){
   info = _info;
}

template<typename T> T TNo<T>::getinfo(){
   return info;
}

template<typename T> void TNo<T>::setprox(TNo<T> *_prox){
   prox = _prox;
}

template<typename T> TNo<T>* TNo<T>::getprox(){
   return prox;
}

template<typename T> TNo<T>& TNo<T>::operator=(const TNo<T> &No){
   if (this == &No) return *this;
   else{
      this->info = No.info;
      this->prox = No.prox;
      return(*this);
   }
}

template<typename T> TNo<T>::~TNo(){
   prox = nullptr;
}

#endif // TNO_H_INCLUDED
