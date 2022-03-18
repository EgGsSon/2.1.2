#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

void sort_letters(vector <char> &word, vector <int> &powers) {
    char letter;
    int power;

    for (int i = 0; i < word.size() - 1; i++) {
        for (int k = 0; k < word.size() - i - 1; k++) {
            if (word[k] > word[k + 1]) {
                power = powers[k];
                powers[k] = powers[k + 1];
                powers[k + 1] = power;
                letter = word[k];
                word[k] = word[k + 1];
                word[k + 1] = letter;
            }
        }
    }
}

int compare_mono( vector<char> vec_1, vector<char > vec_2) {
    if (vec_1.size() < vec_2.size())
        return 1;

    else if (vec_1.size() > vec_2.size())
        return 0;

    else {
        for (int i = 0; i < vec_1.size(); i++) {
            if (vec_1[i] < vec_2[i])
                return 1;

            else if(vec_1[i] > vec_2[i])
                return 0;
         }
        return -1;
    }
}

class Polynomial {
private:
    int amount_monom = 0;
    vector<int> coefficients;
    vector< vector<char> > variables;
    vector< vector<int> > powers;

public:

    Polynomial() 
    {
    }

    Polynomial(const Polynomial& object) {
        amount_monom = object.amount_monom;
        for (int i = 0; i < amount_monom; i++) {
            coefficients.push_back(object.coefficients[i]);
            variables.push_back(object.variables[i]);
            powers.push_back(object.powers[i]);
        }
    }

    Polynomial(string word) {
        int counter_monom = 0;
        int counter_inside = 0;
        bool negative = 0;
        int i = 0;

        coefficients.push_back(1);
        variables.push_back({});
        powers.push_back({});

        while (i < word.size()) {

            if (word[i] == '-' || word[i] == '+') {

                if (i != 0) {
                    counter_monom++;
                    coefficients.push_back(1);
                    variables.push_back({});
                    powers.push_back({});
                    counter_inside = 0;
                    negative = 0;
                }

                if (word[i] == '-') {
                    coefficients[counter_monom] = -1;
                    negative = 1;
                }

            }

            if ('0' <= word[i] && word[i] <= '9') {

                if (negative == 1)
                    coefficients[counter_monom] = -(word[i] - '0');

                else
                    coefficients[counter_monom] = (word[i] - '0');
                i++;

                while (i < word.size() && '0' <= word[i] && word[i] <= '9') {
                    coefficients[counter_monom] *= 10;

                    if (negative == 1)
                        coefficients[counter_monom] -= (word[i] - '0');

                    else
                        coefficients[counter_monom] += (word[i] - '0');

                    i++;
                }

                negative = 0;
                i--;
            }


            if ('z' >= word[i] && word[i] >= 'a') {

                variables[counter_monom].push_back(word[i]);
                powers[counter_monom].push_back(0);

                if (word[i + 1] == '^') {
                    i += 2;
                    while (i < word.size() && '0' <= word[i] && word[i] <= '9') {
                        powers[counter_monom][counter_inside] *= 10;
                        powers[counter_monom][counter_inside] += word[i] - '0';
                        i++;
                    }
                    i--;
                }

                else
                    powers[counter_monom][counter_inside] = 1;

                counter_inside++;
            }

            i++;
        }

        amount_monom = counter_monom + 1;

        for (int j = 0; j < amount_monom; j++) {
            if(variables[j].size() != 0)
                sort_letters(variables[j], powers[j]);
        }
        
        vector<char> vec_var;
        vector<int> vec_pow;
        int coef;
        
        for (int j = 0; j < amount_monom - 1; j++) {
            for (int v = 0; v < amount_monom - 1 - j; v++) {
                if (variables[v].size() == 0 && v != amount_monom - 1) {

                    variables[v] = variables[amount_monom - 1];
                    variables[amount_monom - 1] = {};

                    powers[v] = powers[amount_monom - 1];
                    powers[amount_monom - 1] = {};

                    coef = coefficients[v];
                    coefficients[v] = coefficients[amount_monom - 1];
                    coefficients[amount_monom - 1] = coef;
                }

                else if (variables[v + 1].size() == 0 && v + 1 != amount_monom - 1) {
          
                    variables[v + 1] = variables[amount_monom - 1];
                    variables[amount_monom - 1] = {};

                    powers[v + 1] = powers[amount_monom - 1];
                    powers[amount_monom - 1] = {};

                    coef = coefficients[v + 1];
                    coefficients[v + 1] = coefficients[amount_monom - 1];
                    coefficients[amount_monom - 1] = coef;
                }
               
                else if (variables[v + 1].size() != 0 && variables[v].size() != 0 && compare_mono(variables[v], variables[v + 1]) == 0) {
                    vec_var = variables[v + 1];
                    variables[v + 1] = variables[v];
                    variables[v] = vec_var;

                    vec_pow = powers[v + 1];
                    powers[v + 1] = powers[v];
                    powers[v] = vec_pow;

                    coef = coefficients[v + 1];
                    coefficients[v + 1] = coefficients[v];
                    coefficients[v] = coef;
                }
            }
        }
    }

    ///<><><><><><><><><>\\\\\
    
    void show() {
        cout << "Amount of monomials: " << amount_monom << "\n";
        for (int i = 0; i < amount_monom; i++) {
            if (coefficients[i] > 0 && i != 0)
                cout << "+";
            if (coefficients[i] == -1 && variables[i].size() != 0)
                cout << "-";

            if ((coefficients[i] != 1 && coefficients[i] != -1) || variables[i].size() == 0)
                cout << coefficients[i];
            for (int k = 0; k < variables[i].size(); k++) {
                cout << variables[i][k];
                if (powers[i][k] > 1)
                    cout << "^" << powers[i][k];
            }
        }
        cout << endl;
    }

    Polynomial& operator = (const Polynomial& object) {

        variables.clear();
        powers.clear();
        coefficients.clear();
        amount_monom = object.amount_monom;
        for (int i = 0; i < amount_monom; i++) {
            coefficients.push_back(object.coefficients[i]);
            variables.push_back(object.variables[i]);
            powers.push_back(object.powers[i]);
        }

        return *this;
    }

    int& operator [] (const int index) {
        return coefficients[index];
    }

    Polynomial& operator - () {
        for (int i = 0; i < amount_monom; i++) {
            coefficients[i] = -coefficients[i];
        }
        return *this;
    }

    Polynomial& operator + () {
        return *this;
    }

    ~Polynomial()
    {
    }

    friend bool operator == (const Polynomial &object_1, const Polynomial &object_2) {
        if(object_1.amount_monom != object_2.amount_monom)
            return false;

        for (int i = 0; i < object_1.amount_monom; i++) {
            if( ( object_1.coefficients[i] != object_2.coefficients[i] ) || ( object_1.variables[i].size() != object_2.variables[i].size() ) )
                return false;

            for (int k = 0; k < object_1.variables[i].size(); k++)
                if ((object_1.variables[i][k] != object_2.variables[i][k]) || (object_1.powers[i][k] != object_2.powers[i][k]))
                    return false;
        }

        return true;
    }

    friend bool operator != (const Polynomial& object_1, const Polynomial& object_2) {
        if (object_1.amount_monom != object_2.amount_monom)
            return true;

        for (int i = 0; i < object_1.amount_monom; i++) {
            if ((object_1.coefficients[i] != object_2.coefficients[i]) || (object_1.variables[i].size() != object_2.variables[i].size()))
                return true;

            for (int k = 0; k < object_1.variables[i].size(); k++)
                if ((object_1.variables[i][k] != object_2.variables[i][k]) || (object_1.powers[i][k] != object_2.powers[i][k]))
                    return true;
        }

        return false;
    }

    Polynomial operator + (const Polynomial& object) {
        Polynomial res;
        bool flag = 1;

        for (int i = 0; i < amount_monom; i++) {
            for (int k = 0; k < object.amount_monom; k++) {
                if (compare_mono(variables[i], object.variables[k]) == -1) {
                    for (int z = 0; z < variables[i].size(); z++) {
                        if (powers[z] != object.powers[z])
                            flag = 0;
                    }
                    if (flag == 1) {
                        res.variables.push_back(variables[i]);
                        res.powers.push_back(powers[i]);
                        res.coefficients.push_back(coefficients[i] + object.coefficients[k])
                    }
                }
            }
        }
    }
};


int main() {
    string word = "1 + a^2 +dc^3e ";
    string word_2 = "a^2 + 1";
    vector<char> vec_1 = { 'a','b', 'c' };
    vector<char> vec_2 = { 'a','b', 'd'};
    //cout << compare_mono(vec_1, vec_2);

    Polynomial a(word);
    a.show();
    Polynomial b(word_2);
    //a = b;
    b.show();
    
    
    //cout << a[5] << endl;

    return 0;
}