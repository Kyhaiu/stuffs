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
    ///pesquisa pra ver se já tem cadastrado o vertice, caso não tenha o 1° parametro retorna -1
    tuple<int, long, long> verI = grafo->getVerticePerXY(xi, yi);
    tuple<int, long, long> verF = grafo->getVerticePerXY(xf, yf);
    string name;
    double dist = 0; ///distancia = peso(no caso)
    if(get<0>(verI) == -1 && get<0>(verF) == -1){ ///caso não tenha nenhum vertice cadastrado
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xi, yi);
        id++;
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xf, yf);
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){///caso as duas impedancias forem diferentes de -1 significa que é sentido duplo
            name = "Aresta " + to_string(id-2) + "<->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-2, id-1, name, dist, true);
        } else if(imp_positiva == -1){/// se a impedancia positiva for  = -1 entao tem sentido inicio fim
            name = "Aresta " + to_string(id-2) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-2, id-1, name, dist, false);
        } else if(imp_negativa == -1){ /// se a impedancia negatica for = -1 entao tem sentido fim inicio
            name = "Aresta " + to_string(id-2) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, id-2, name, dist, false);
        }
    } else if(get<0>(verI) == -1){
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xi, yi);
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){
            name = "Aresta " + to_string(id-1) + "<->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verF), id-1, name, dist, true);
        } else if(imp_positiva == -1){
            name = "Aresta " + to_string(id-1) + "->" + to_string(get<0>(verF));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verF), id-1, name, dist, false);
        } else if(imp_negativa == -1){
            name = "Aresta " + to_string(get<0>(verF)) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verF), name, dist, false);
        }
    } else if(get<0>(verF) == -1){
        name = "Vertice " + to_string(id);
        grafo->AddVertice(name, xf, yf);
        id++;
        if(imp_positiva != -1 && imp_negativa != -1){
            name = "Aresta " + to_string(get<0>(verI)) + "<->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, true);
        } else if(imp_positiva == -1){
            name = "Aresta " + to_string(get<0>(verI)) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, false);
        } else if(imp_negativa == -1){
            name = "Aresta " + to_string(id-1) + "->" + to_string(get<0>(verI));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verI), name, dist, false);
        }
    }else{
        if(imp_positiva != -1 && imp_negativa != -1){
            name = "Aresta " + to_string(get<0>(verI)) + "<->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, true);
        } else if(imp_positiva == -1){
            name = "Aresta " + to_string(get<0>(verI)) + "->" + to_string(id-1);
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(get<0>(verI), id-1, name, dist, false);
        } else if(imp_negativa == -1){
            name = "Aresta " + to_string(id-1) + "->" + to_string(get<0>(verI));
            dist = sqrt(pow(xf-xi, 2) + pow(yf-yi, 2));
            grafo->AddAresta(id-1, get<0>(verI), name, dist, false);
        }
    }
}

TGrafo* lerArquivo(string nomeArquivo){
    TGrafo* grafo = new TGrafo();
    FILE * arquivo =  fopen(nomeArquivo.data(), "r");
    int id = 0, trash = 0;
    float  imp_positiva, imp_negativa, xi, yi, xf, yf, t;
    /// ele le por blocos( o separador de blocos é END
    //fseek(arquivo, 4, SEEK_SET);
    if (arquivo != nullptr){
        while (fscanf(arquivo, "%d %f %f %f\n", &trash, &imp_positiva, &imp_negativa, &t) != EOF){
            fscanf(arquivo, "%f %f\n", &xi, &yi);
            fscanf(arquivo, "%f %f\n", &xf, &yf);
            fscanf(arquivo, "END\n");
            montarGrafo(grafo, id, imp_positiva, imp_negativa, xi, yi, xf, yf);
        }
        fclose(arquivo);
    } else{
        cout << "Nao foi possivel abrir o arquivo" << endl;
    }
    return grafo;
}

void menu(){
    int i = 0;
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
            cout << "Informe o nome do arquivo+extenção(.txt), que contenha o nome os dados do grafo: " << endl;
            cin >> arquivo;
            lido = true;
            g = lerArquivo(arquivo);
            g->Print();
            system("PAUSE");
        } else if(i == 2 && lido){

        } else if(i == 3 && lido){

        } else if(i == 4 && lido){
            g->dijkstra(1.5,7.5,6,6);
        } else if(i == 5){
            cout << "\t\t\t\t\tTrabalho 02(Grafos) - ED" << endl;
            cout << "\tEste programa foi desenvolvido como solicitado pelo professor Adair Costa,\n"
                 << "\tpara a obtencao de nota na disciplina de Estrutura de Dados(2° ano) - Unioeste Cascavel - PR.\n" << endl;
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
