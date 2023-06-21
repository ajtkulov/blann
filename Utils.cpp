#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <cstdlib>

using namespace std;

class Utils {
    public:
    static inline char numToChar(char value) {
        return '0' + value;
    }

    static inline char charToNum(char value) {
        return value - '0';
    }


    static std::string int2Str(int value) {
        if (value == 0) {
            return "0";
        }

        int r = value;
        std::vector<char> vec = std::vector<char>();
        while (r > 0) {
            int q = r % 64;
            r = r / 64;
            vec.push_back(numToChar(q));
        }

        std::reverse(vec.begin(), vec.end());

        return std::string(vec.begin(), vec.end());
    }

    static std::string vector2Str(std::vector<bool> vector) {
        int size = vector.size();
        assert(size % 6 == 0);
        std::vector<char> res = std::vector<char>();
        
        for (int i = 0; i < size; i += 6) {
            int r = 0;
            for (int j = 0; j < 6; j++) {
                if (vector[i + j]) {
                    r += 1 << j;
                }
            }
            res.push_back(numToChar(r));            
        }

        return std::string(res.begin(), res.end());
    }
};

class Planes {
    const static int dimensions = 300;
    const static int planes_count = 132;

    public:
        vector<vector<double> > planes;
        Planes() {
            srand(1729);
            planes = vector<vector<double> >();

            for (int p = 0; p < planes_count; p++) {
                vector<double> plane = vector<double>();

                for (int i = 0; i < dimensions; i++) {
                    // double r = ((double) rand() / (RAND_MAX)) + 0.5;
                    float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                    double r = (randomValue * 2.0f) - 1.0f;
                    plane.push_back(r);
                }

                planes.push_back(plane);
            }
        }

        vector<bool> to_bits(vector<double> values) {
            vector<bool> res = vector<bool>();
            for (int p = 0; p < planes_count; p++) {
                double r = 0;
                vector<double> plane = planes[p];
                for (int d = 0; d < dimensions; d++) {
                    r += values[d] * plane[d];
                }

                res.push_back(r >= 0);
            }
            
            return res;
        }
};
