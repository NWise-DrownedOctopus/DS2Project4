//
// Created by nicho on 11/11/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//
// Created by nicho on 11/11/2024.
//
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;



struct City {
    int id;
    string name;
};

class Graph {
private:
    unordered_map<int, City> cities;
    unordered_map<int, std::vector<std::pair<int, int>>> adjacencyList;

public:
    void loadCities(const string& fileName);
    void loadConnections(const string& fileName);
    void displayGraph();
};


#endif //FUNCTIONS_H
