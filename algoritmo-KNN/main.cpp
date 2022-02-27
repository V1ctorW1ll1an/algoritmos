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
}

int main(int argc, char const* argv[]) {
    return 0;
}
