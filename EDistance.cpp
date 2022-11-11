// Copyright Forrest Boyer 2022

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>

class EDistance {
 public:
    EDistance(std::string str1, std::string str2):
    s1(str1),
    s2(str2),
    n(str1.size()),
    m(str2.size()) {
        std::vector<int> temp(str1.size() + 1, 0);
        for (size_t i = 0; i < str2.size() + 1; i++) {
            matrix.push_back(temp);
        }
    }
    int penalty(char a, char b) {
        return a == b ? 0 : 1;
    }
    int min(int a, int b, int c) {
        return std::min(std::min(a, b), c);
    }
    int OptDistance() {
        for (size_t i = 1; i < n + 1; i++) {
            for (size_t j = 1; j < m + 1; j++) {
                int match = matrix[i - 1][j - 1] + penalty(s1[i], s2[j]);
                int del = matrix[i - 1][j] + 2;
                int insert = matrix[i][j - 1] + 2;
                matrix[i][j] = min(match, del, insert);
            }
        }
        return matrix[n - 1][m - 1];
    }
    std::string Alignment() {
        std::string alignA = "";
        std::string alignB = "";
        int i = n;
        int j = m;
        while (i > 0 || j > 0) {
            if ((i > 0 && j > 0) && matrix[i][j] == matrix[i - 1][j - 1] + penalty(s1[i], s2[j])) {
                alignA = s1[i] + alignA;
                alignB = s2[j] + alignB;
                i--;
                j--;
            } else if (i > 0 && matrix[i][j] == matrix[i - 1][j] + 2) {
                alignA = s1[i] + alignA;
                alignB = "-" + alignB;
                i--;
            } else {
                alignA = "-" + alignA;
                alignB = s2[j] + alignB;
                j--;
            }
        }
        std::string ret;
        for (size_t i = 0; i < alignA.size(); i++) {
            int x;
            if (alignA[i] == alignB[i]) {
                x = 0;
            } else if (alignA[i] || alignB[i] == '-') {
                x = 2;
            } else {
                x = 1;
            }
            std::cout << alignA[i] << " " << alignB[i] << " " << x << std::endl;
        }
        return ret;
    }

 private:
    std::vector<std::vector<int>> matrix;
    std::string s1;
    std::string s2;
    size_t n;
    size_t m;
};

int main() {

    sf::Clock clock;
    sf::Time t;

    // Get input from file
    std::string s1;
    std::string s2;

    std::cin >> s1;
    std::cin >> s2;

    EDistance edi(s1, s2);

    int distance = edi.OptDistance();
    std::cout << "Edit distance = " << distance << std::endl;
    std::cout << edi.Alignment() << std::endl;

    std::cout << "Edit distance = " << distance << std::endl;
    t = clock.getElapsedTime();

    std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;
}
