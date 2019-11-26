#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include "TGrafo.h"

using namespace std;

int nextToken(string linha, int i){
  while(linha[i] != ' ' && linha[i] != '\0') i++;
  return i;
}

void montarGrafo(TGrafo* grafo, int &id, float imp_positiva, float imp_negativa, float xi, float yi, float xf, float yf){
    ///pesquisa pra ver se jс tem cadastrado o vertice, caso nуo tenha o 1А parametro retorna -1
    tuple<int, long, long> verI = grafo->getVerticePerXY(xi, yi);///pesquiza o vertice pelo x e y inicial(caso nao exista retorna -1 no 1° elemento da tupla
    tuple<int, long, long> verF = grafo->getVerticePerXY(xf, yf);
   ///tupla que contem o id do vertice, o x e y do mesmo.
    string name;
    double dist = 0; ///distancia = peso(no caso)
    if(get<0>(verI) == -1 && get<0>(verF) == -1){ ///caso nenhum dos vertices exista ele cria os 2
        name = "Vertice " + to_string(id);///monta o nome do vertice : "Vertice : 'id do vertice'"
        grafo->AddVertice(name, xi, yi); ///adiciona o vertice
        id++;///incrementa o id do vertice
        name = "Vertice " + to_string(id);///monta novamente o id do vertice
        grafo->AddVertice(name, xf, yf);///mesma coisa da funao anteior
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){///caso as duas impedancias forem diferentes de -1 significa que a aresta que liga os dois vertices tem sentido duplo
            name = "Aresta " + to_string(id-2) + "<->" + to_string(id-1); ///monta o nome da aresta como : "Aresta id-2(x,y inicial) <-> e id-1(x,y final)
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));///calcula a distancia euclidiana entre as cordenadas
            grafo->AddAresta(id-2, id-1, name, dist, true);///cria a aresta
        } else if(imp_positiva != -1){/// se a impedancia positiva for  != -1 entao tem sentido inicio=>fim
            name = "Aresta " + to_string(id-2) + "->" + to_string(id-1); ///mesma coisa do trecho acime
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-2, id-1, name, dist, false);
        } else if(imp_negativa != -1){ /// se a impedancia negatica for != -1 entao tem sentido fim inicio
            name = "Aresta " + to_string(id-1) + "->" + to_string(id-2);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, id-2, name, dist, false);
        }
    } else if(get<0>(verI) == -1){///caso o elemento 0 da tupla verI(vertice inicial) for  = a -1 signifiica que o vertice inicial nao esta cadastrado
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xi, yi);
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){///mesma coisa dos enterirores, só que ele pega o valor da tupla verF(Vertice final)
            name = "Aresta " + to_string(id-1) + "<->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verF), name, dist, true);
        } else if(imp_positiva != -1){
            name = "Aresta " + to_string(id-1) + "->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verF), name, dist, false);
        } else if(imp_negativa != -1){
            name = "Aresta " + to_string(get<0>(verF)) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verF), id-1, name, dist, false);
        }
    } else if(get<0>(verF) == -1){ /// caso o 1° elemento da tupla verF(vertice final) for = -1 então o vertice final nao existe
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xf, yf);
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){///mesma condiçao dos anteriores
            name = "Aresta " + to_string(get<0>(verI)) + "<->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, true);
        } else if(imp_positiva != -1){
            name = "Aresta " + to_string(get<0>(verI)) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, false);
        } else if(imp_negativa != -1){
            name = "Aresta " + to_string(id-1) + "->" + to_string(get<0>(verI));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verI), name, dist, false);
        }
    }else{///caso ele esteja fazendo a ligação entre dois vertices já cadastrados

        if(imp_positiva != -1 && imp_negativa != -1){
            name = "Aresta " + to_string(get<0>(verI)) + "<->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), get<0>(verF) , name, dist, true);
        } else if(imp_positiva != -1){
            name = "Aresta " + to_string(get<0>(verI)) + "->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), get<0>(verF), name, dist, false);
        } else if(imp_negativa != -1){
            name = "Aresta " + to_string(get<0>(verF)) + "->" + to_string(get<0>(verI));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verF), get<0>(verI), name, dist, false);
        }
    }
}

TGrafo* lerArquivo(string nomeArquivo){///função responsavel por ler do arquivo .txt e passar pra classe TGrafo
    TGrafo* grafo = new TGrafo();
    FILE * arquivo =  fopen(nomeArquivo.data(), "r");
    int id = 0, trash = 0;
    float  imp_positiva, imp_negativa, xi, yi, xf, yf, t;
    /// ele le por blocos( o separador de blocos щ END
    //fseek(arquivo, 4, SEEK_SET);
    if (arquivo != nullptr){
        while (fscanf(arquivo, "%d %f %f %f\n", &trash, &imp_positiva, &imp_negativa, &t) != EOF){///enquanto nao for final do arquivo ele le o id do vertice, impedancia positiva e negativa e a dependencia(nao usa pra nada)
            fscanf(arquivo, "%f %f\n", &xi, &yi);///le o x e y inicial
            fscanf(arquivo, "%f %f\n", &xf, &yf);///le o x e y final
            fscanf(arquivo, "END\n");///le o END de cada aresta
            montarGrafo(grafo, id, imp_positiva, imp_negativa, xi, yi, xf, yf);///chama a funcao coloca os parametros lidos em cada bloco, dentro da classe TGFAFO
        }
        fclose(arquivo);
    } else{
        cout << "Nao foi possivel abrir o arquivo" << endl;
    }
    return grafo;///retorna o grafo montado
}

void menu(){
    int i = 0;
    float xi, yi, xf, yf;
    bool lido = false;
    TGrafo *g;
    string arquivo;
    do{
        system("cls");
        cout << "1 - Ler grafo do arquivo texto" << endl;
        cout << "2 - Busca em amplitude" << endl;
        cout << "3 - Busca em profundiade" << endl;
        cout << "4 - Caminho minimo" << endl;
        cout << "5 - About" << endl;
        cout << "6 - Sair" << endl;
        cout << "Opcao: ";
        cin >> i;
        if(i == 1){
            cout << "Informe o nome do arquivo+extenчуo(.txt), que contenha o nome os dados do grafo: " << endl;
            cin >> arquivo;
            lido = true;
            g = lerArquivo(arquivo);
            g->Print();
            system("PAUSE");
        } else if(i == 2 && lido){
            cout << "Informe o X: ";
            cin >> xi;
            cout << "Informe o Y: ";
            cin >> yi;
            g->buscaAmplitude(xi,yi);
            system("PAUSE");
        } else if(i == 3 && lido){
            cout << "Informe o X: ";
            cin >> xi;
            cout << "Informe o Y: ";
            cin >> yi;
            g->buscaProfundiade(xi,yi);
            system("PAUSE");
        } else if(i == 4 && lido){
            cout << "Informe o X inicial: ";
            cin >> xi;
            cout << "Informe o Y inicial: ";
            cin >> yi;
            cout << "Informe o X final: ";
            cin >> xf;
            cout << "Informe o Y final: ";
            cin >> yf;
            g->dijkstra(xi, yi, xf, yf);
        } else if(i == 5){
            cout << "\t\t\t\t\tTrabalho 02(Grafos) - ED" << endl;
            cout << "\tEste programa foi desenvolvido como solicitado pelo professor Adair Costa,\n"
                 << "\tpara a obtencao de nota na disciplina de Estrutura de Dados(2А ano) - Unioeste Cascavel - PR.\n" << endl;
            cout << "\tAs funcionalidades desenvolvidas nesse programa foram:\n"
                 << "\t\t * Ler e interpretar as informacoes contidas no arquivo .txt, e com elas montar um grafo\n"
                 << "\t\t * Realizar operacoes de Busca em Amplitude e Profundidade\n"
                 << "\t\t * Executar o algoritmo de Dijkstra buscando encontra o menor caminho entra dois vertices\n"
                 << "\t\t * Determinar se dado um vertice inicial e possivel percorrer todo o grafo\n" << endl;
            cout << "\tTrabalho desenvolvido por Marcos A. Campagnaro, Roberval, Requiao Jnr. e Igor A. Engler\n\n" << endl;
            cout << "Duvidas sobre o funcionamento do programa/codigo, se possivel envie um e-mail para : marcosmuce@gmail.com\n"
                 << "com o assunto 'Duvida Trabalho02'" << endl;

            system("PAUSE");
        } else if(i == 6){
        } else if(!lido && i > 1 && i < 6){
            cout << "Por favor antes de executar qualquer operacao, carregue os valores do grafo utilizando a Op. 1" << endl;
            system("PAUSE");
        }else{
            cout << "Opcao invalida" << endl;
            i = 0;
            system("PAUSE");
        }
    }while(i != 6);
}

int main(){
    menu();
}
