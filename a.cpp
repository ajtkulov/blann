#include <iostream>
#include <string>
#include <sstream>
#include "bloom_filter/bloom_filter.hpp"
#include "Utils.cpp"
#include <fstream>
#include <stdlib.h>

using namespace std;


class LshTrie {
    private:
        bloom_filter filter;
        bloom_filter final_filter;

    public:
        LshTrie(int word_count) {
            bloom_parameters parameters;
            
            parameters.projected_element_count = word_count * 27;
            parameters.false_positive_probability = 0.0001;
            parameters.compute_optimal_parameters();

            filter = bloom_filter(parameters);

            bloom_parameters final_parameters;
            final_parameters.projected_element_count = word_count;
            final_parameters.false_positive_probability = 0.0001;
            final_parameters.compute_optimal_parameters();
            final_filter = bloom_filter(final_parameters);
        }

        void add_word(std::string str, int id) {
            std::string to_add = str + Utils::int2Str(id);

            final_filter.insert(to_add);

            for (int i = 1; i <= to_add.length(); i++) {
                // std::cout << to_add.substr(0, i) << "\n";
                filter.insert(to_add.substr(0, i));
            }         
        }  

        void serialize() {
            // cout << final_filter.size();
            final_filter.serializeVectorToFile("final_filter.bloom");
            filter.serializeVectorToFile("main_filter.bloom");
        }

        bool check(std::string str, int id) {
            std::string to_add = str + Utils::int2Str(id);
            return final_filter.contains(to_add);
        }
};

int main()
{
    LshTrie *t = new LshTrie(400000);

    Planes planes = Planes();
    
    std::ifstream infile("glove.6B.300d.txt");

    int idx = 0;
    for (string line = ""; getline(infile, line); )
    {
        istringstream ss(line);
        string del;
        getline(ss, del, ' ');
        std::string word = del;
        vector<double> v = vector<double>();
        while(getline(ss, del, ' ')) {
             double vv = atof(del.c_str());
             v.push_back(vv);
        }
        std::vector<bool> bits = planes.to_bits(v);

        t->add_word(Utils::vector2Str(bits), idx);

        if (idx % 10000 == 0) {
            cout << idx << "\n";
        }

        idx++;
   }

    t->serialize();

   return 0;
}