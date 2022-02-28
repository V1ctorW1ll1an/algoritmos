#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>

class Individual {
   private:
    std::string classe;
    double a, b, c, d;

   public:
    Individual(double a, double b, double c, double d, std::string classe) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->classe = classe;
    }

    std::string getClasse() {
        return classe;
    }
    double getA() {
        return a;
    }
    double getB() {
        return b;
    }
    double getC() {
        return c;
    }
    double getD() {
        return d;
    }
};

double getEuclideanDistance(Individual ind1, Individual ind2) {
    double sum = pow((ind1.getA() - ind2.getA()), 2) +
                 pow((ind1.getB() - ind2.getB()), 2) +
                 pow((ind1.getC() - ind2.getC()), 2) +
                 pow((ind1.getD() - ind2.getD()), 2);

    return sqrt(sum);
}

std::string sortSample(std::vector<Individual>& individuals, Individual new_example, int k) {
    // se o k for par, decrementa

    if (k % 2 == 0) {
        k--;
        if (k <= 0) k = 1;
    }

    int tam_vet = individuals.size();

    
    std::set<std::pair<double, int>> individuals_dist;


    for (int i = 0; i < tam_vet; i++)
    {
        double dist = getEuclideanDistance(individuals[i], new_example);
        individuals_dist.insert(std::make_pair(dist, i));
    }

    std::set<std::pair<double, int>>::iterator it;

    std::vector<int> contClasses(3);
    int contK = 0;

    for ( it = individuals_dist.begin(); it != individuals_dist.end(); it++)
    {
        std::string classe = individuals[it->second].getClasse();

        if(classe == "Iris-setosa")
            contClasses[0]++;
        else if(classe == "Iris-versicolor")
            contClasses[1]++;
        else
            contClasses[2]++;

        if (contK > k) break;

        contK++;
    }

    std::string classeClassificacao;

    if(contClasses[0] >= contClasses[1] && contClasses[0] >= contClasses[2])
        classeClassificacao = "Iris-setosa";

    else if(contClasses[1] >= contClasses[0] && contClasses[1] >= contClasses[2])
        classeClassificacao = "Iris-versicolor";
    else
        classeClassificacao = "Iris-virginica";

    return classeClassificacao;
}

int main(int argc, char const* argv[]) {
    std::vector<Individual> individuals;

    int k = 3;

    int tamTreinamento = 105;

    for(int i= 0; i < tamTreinamento; i++){
        std::string classe;
        double a, b, c, d;

        std::cin >> a >> b >> c >> d >> classe;

        individuals.push_back(Individual(a, b, c, d, classe));
    }

    int acertos = 0;
    int tamTestes = 150 - tamTreinamento;

    for (int i = 0; i < tamTestes; i++)
    {
        std::string classe;
        double a, b, c, d;

        std::cin >> a >> b >> c >> d >> classe;

        Individual ind(a, b, c, d, classe);

        std::string classeObtida = sortSample(individuals, ind, k);

        std::cout << "Classe esperada : " << classe << "\n";
        std::cout << "Classe obtida: " << classeObtida << "\n\n";

        if(classe == classeObtida)
            acertos++;
    }

    std::cout << acertos << " Acertos de um total de " << tamTestes << " testes \n\n";

    return 0;
}
