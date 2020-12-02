#include <bits/stdc++.h>
///Código de decodificação do hamming - Marcos Augusto Campagnaro


std::map<std::string, int> bit_position{
                                {"21", 0}, {"20", 1}, {"19", 2}, {"18", 3}, {"17", 4}, {"15", 5},
                                {"14", 6}, {"13", 7}, {"12", 8}, {"11", 9}, {"10", 10}, {"9", 11},
                                {"7", 12}, {"6", 13}, {"5", 14}, {"3", 15}, {"16", 16}, {"8", 17},
                                {"4", 18}, {"2", 19}, {"1", 20}, {"0", -1}
                               }; 


///Função que converte um numero decimal inteiro para binário, e retorna uma string
int binary_to_decimal(std::string n){ 
    int number_decimal;

    for(int i = 0; i < n.length(); i++){
        if((n[i] - '0')){
            number_decimal += pow(2, i);
            
        }
    }
    return number_decimal;
}

void get_parity_bits_from_recived(int *_array_parity_bits, std::string word){
    /*
        P1  = D0 + D1 + D3 + D4 + D6 + D8 + D10 + D11 + D13 + D15
        P2  = D0 + D2 + D3 + D5 + D6 + D9 + D10 + D12 + D13
        P4  = D1 + D2 + D3 + D7 + D8 + D9 + D10 + D14 + D15
        P8  = D4 + D5 + D6 + D7 + D8 + D9 + D10
        P16 = D11 + D12 + D13 + D14 + D15

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

void get_parity_bits_from_original(int *_array_parity_bits, std::string word){
    std::reverse(word.begin(), word.end());
    _array_parity_bits[0] = (word[0] - '0');
    _array_parity_bits[1] = (word[1] - '0');
    _array_parity_bits[2] = (word[2] - '0');
    _array_parity_bits[3] = (word[3] - '0');
    _array_parity_bits[4] = (word[4] - '0');
}

int get_inverted_bit_index(int *parity_original, int *parity_recived){
    std::string index_inverted_bit;
    for(int i = 0; i < 5; i++){
        index_inverted_bit.push_back((parity_original[i] ^ parity_recived[i]) + '0');
        //std::cout << index_inverted_bit[i] << std::endl;
    }
    return bit_position[std::to_string(binary_to_decimal(index_inverted_bit))];
}

std::string inverted_bit_correction(std::string word, int index_inverted_bit){
    std::string fixed_word;
    fixed_word = word;
    fixed_word[index_inverted_bit] = (!(word[index_inverted_bit] - '0') + '0');
    return fixed_word;
}

std::string remove_parity_bits(std::string word){
    std::string word_without_parity_bits;
    for(int i = 0; i < word.length() - 5; i++){
        word_without_parity_bits.push_back(word[i]);
    }
    return word_without_parity_bits;
}

std::string decode(std::string word){
    int parity_original[5]; //paridades dos bits recebidos
    int parity_recived[5]; //paridades dos bits recebidos
    int index_inverted_bit;
    std::string fixed_word;

    get_parity_bits_from_original(parity_original, word);
    get_parity_bits_from_recived(parity_recived, word);

    /*std::cout << "Paridade original: ";
    for(int i = 0; i < 5; i++)
        std::cout << parity_original[i];

    std::cout << "\nParidade recebida: ";
    for(int i = 0; i < 5; i++)
        std::cout << parity_recived[i];*/

    index_inverted_bit = get_inverted_bit_index(parity_original, parity_recived);

    if(index_inverted_bit == - 1){
        fixed_word = word;
    } else{
        fixed_word = inverted_bit_correction(word, index_inverted_bit);
    }
    
    /*std::cout << "Palavra Recebida                : " << word << std::endl;
    std::cout << "Palavra Corrigida               : " << fixed_word << std::endl;
    std::cout << "Index do erro                   : " << index_inverted_bit << std::endl;
    std::cout << "Palavra sem os bits de paridade : " << remove_parity_bits(fixed_word) << std::endl;
    std::cout << "\n\n";*/
    std::string true_word = remove_parity_bits(fixed_word);
    return true_word;
}

int main (){
    int n = 0;
    std::string word;
    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::cin >> word;
        std::cout << decode(word) << std::endl;
    }

    std::system("PAUSE");
    
    return 0;
}