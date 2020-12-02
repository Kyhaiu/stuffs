#include <bits/stdc++.h>

///Função que converte um numero decimal inteiro para binário, e retorna uma string
std::string decimal_to_binary(int n){ 
    int binary_number[5]; //vetor que armazenara o numero binário
  
    int i = 0; 
    while (n > 0) { 
  
        binary_number[i] = n % 2; //armazena o resto no vetor inteiro
        n = n / 2; 
        i++; 
    }

    std::string number;

    for (int i = 0; i < 5; i++)
        number.push_back(binary_number[i] + '0'); //realiza a conversão de inteiro para char e armazena na string que sera retornanda

    return number;
}

void get_parity_bits_from_original(int *_array_parity_bits, std::string word){
    /*
        c1  = d1 d2 d4 d5 d7 d9 d11 d12 d14 d16 
        c2  = d1 d3 d4 d6 d7 d10 d11 d13 d14
        c4  = d2 d3 d4 d8 d9 d10 d11 d15 d16
        c8  = d5 d6 d7 d8 d9 d10 d11 
        c16 = d12 d13 d14 d15 d16

        indice do vetor começa em 0, e o do hamming começa em 1. Pois o 0 no hamming significa que não tem que alterar nenhum indice.
        +5   : nos indices pois é revertido para ficar mais legivel, e os bits de partidade estão nas 5 ultimas posições.
        - '0': É para realizar a converção de char para inteiro
    */
    std::reverse(word.begin(), word.end());
    _array_parity_bits[0] = (word[0+5] - '0') ^ (word[1+5] - '0') ^ (word[3+5] - '0') ^ (word[4+5] - '0') ^ (word[6+5] - '0') ^ (word[8+5] - '0') ^ (word[10+5] - '0') ^ (word[11+5] - '0') ^ (word[13+5] - '0') ^ (word[15+5] - '0');
    _array_parity_bits[1] = (word[0+5] - '0') ^ (word[2+5] - '0') ^ (word[3+5] - '0') ^ (word[5+5] - '0') ^ (word[6+5] - '0') ^ (word[9+5] - '0') ^ (word[10+5] - '0') ^ (word[12+5] - '0') ^ (word[13+5] - '0');
    _array_parity_bits[2] = (word[1+5] - '0') ^ (word[2+5] - '0') ^ (word[3+5] - '0') ^ (word[7+5] - '0') ^ (word[8+5] - '0') ^ (word[9+5] - '0') ^ (word[10+5] - '0') ^ (word[14+5] - '0') ^ (word[15+5] - '0');
    _array_parity_bits[3] = (word[4+5] - '0') ^ (word[5+5] - '0') ^ (word[6+5] - '0') ^ (word[7+5] - '0') ^ (word[8+5] - '0') ^ (word[9+5] - '0') ^ (word[10+5] - '0');
    _array_parity_bits[4] = (word[11+5] - '0') ^ (word[12+5] - '0') ^ (word[13+5] - '0') ^ (word[14+5] - '0') ^ (word[15+5] - '0');
}

void get_parity_bits_from_recived(int *_array_parity_bits, std::string word){
    std::reverse(word.begin(), word.end());
    _array_parity_bits[0] = word[0] - '0';
    _array_parity_bits[1] = word[1] - '0';
    _array_parity_bits[2] = word[2] - '0';
    _array_parity_bits[3] = word[3] - '0';
    _array_parity_bits[4] = word[4] - '0';
}

int get_inverted_bit_index(int *parity_original, int *parity_recived){
    std::string index_inverted_bit;
    for(int i = 0; i < 5; i++){
        index_inverted_bit.push_back((parity_original[i] ^ parity_recived[i]) + '0');
    }

    for(int i = 0; i < 5; i++){
        std::cout << index_inverted_bit[i];
    }

    return (std::stoi(index_inverted_bit));
}

void inverted_bit_correction(std::string word, int index_inverted_bit){
    
}

int main (){
    int n = 0;
    int parity_original[5]; //paridades dos bits recebidos
    int parity_recived[5]; //paridades dos bits recebidos
    std::string word;
    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::cin >> word;
        get_parity_bits_from_original(parity_original, word);
        get_parity_bits_from_recived(parity_recived, word);
        inverted_bit_correction(word, get_inverted_bit_index(parity_original, parity_recived));
        ///std::cout << decimal_to_binary(std::stoi(word)) << std::endl;
    }
    
    return 0;
}