#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int tamGenes = 500;
int tamPopulacao = 10000;
int tamTorneio = 20;
int quantGeracoes = 5000;
double probMutacoes = 0.1;
double probCruzamentos = 0.7;

vector<vector<int>> populacao;


void inicializaPopulacao(){

    for (int i = 0; i < tamPopulacao; i++)
    {
        vector<int> individuo;

        for (int j = 0; j < tamGenes; j++)
        {
            int num = rand() % 2; // 0 ou 1
            individuo.push_back(num);
        }

        populacao.push_back(individuo);
    }
}

void mostrarPopulacao(){
    for (int i = 0; i < tamPopulacao; i++)
    {
        for (int j = 0; j < tamGenes; j++)
        {
            cout << populacao[i][j] << " ";
        }
        cout << endl;
    }
}

int obterPontuacao(vector<int> individuo){
    int soma = 0;

    for (int i = 0; i < tamGenes; i++)
    {
        soma += individuo[i];
    }

    return soma;
}

void mutacao(vector<int>& individuo){
    // [0, tamGenes - 1]
    int gene = rand() % tamGenes;

    if(individuo[gene] == 0)
        individuo[gene] = 1;
    else
        individuo[gene] = 0;
}

void cruzamento(int indicePai1, int indicePai2, vector<int>& filho){
    int ponto = rand() % tamGenes;

    for (int i = 0; i <= ponto; i++)
    {
        filho.push_back(populacao[indicePai1][i]);
    }
    for (int i = ponto + 1; i < tamGenes; i++)
    {
        filho.push_back(populacao[indicePai2][i]);
    }
}

int obterMelhorIndividuo(){
    int indiceMelhor = 0;
    int scoreMelhor = obterPontuacao(populacao[0]);

    for (int i = 0; i < tamPopulacao; i++)
    {
        int score = obterPontuacao(populacao[i]);

        if (score > scoreMelhor){
            indiceMelhor = i;
            scoreMelhor = score;
        }
    }

    return indiceMelhor;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    inicializaPopulacao();

    for (int i = 0; i < quantGeracoes; i++)
    {
        for (int j = 0; j < tamTorneio; j++)
        {
            // calcula probabilidade do cruzamento
            // gerar um numero entre 0 e 1 e comparar com a probabilidade de cruzamento;
            double prob = ((double)rand() / ((double)RAND_MAX + 1));

            if(prob < probCruzamentos){
                // escolher os dois pais
                int indicePai1 = rand() % tamPopulacao;
                int indicePai2;

                do{
                    indicePai2 = rand() % tamPopulacao;
                } while (indicePai1 == indicePai2);

                vector<int> filho;

                cruzamento(indicePai1, indicePai2, filho);
                prob = ((double)rand() / ((double)RAND_MAX + 1));

                if(prob < probMutacoes){
                    mutacao(filho);
                }

                int scorePai1 = obterPontuacao(populacao[indicePai1]);
                int scorePai2 = obterPontuacao(populacao[indicePai2]);
                int scoreFilho = obterPontuacao(filho);


                // if(scoreFilho > scorePai1){
                //     for (int k = 0; k < tamGenes; k++)
                //     {
                //         populacao[indicePai1][k] = filho[k];
                //     }
                // }

                if((scoreFilho > scorePai1) && (scorePai2 > scorePai1)){
                    for (int k = 0; k < tamGenes; k++)
                    {
                        populacao[indicePai1][k] = filho[k];
                    }
                }
                else if((scoreFilho > scorePai2) && (scorePai1 > scorePai2)){
                   
                    for (int k = 0; k < tamGenes; k++)
                    {
                        populacao[indicePai2][k] = filho[k];
                    }
                }
            }
        }

        cout << "Geracao " << i + 1 << endl;
        cout << "Melhor: ";
        int indiceMelhor = obterMelhorIndividuo();
        int scoreMelhor = obterPontuacao(populacao[indiceMelhor]);

        for (int j = 0; j < tamGenes; j++)
        {
            cout << populacao[indiceMelhor][j] << " ";
        }
        cout << "\nPontuacao: " << scoreMelhor << "\n\n";

        if(scoreMelhor == tamGenes)
            break;
    }

    return 0;
}
