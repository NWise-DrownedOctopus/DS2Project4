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



struct Station {
    int id;
    string name;
};

class Graph {
public:
    unordered_map<int, Station> stations;
    unordered_map<int, std::vector<std::pair<int, int>>> adjacencyList;
    void loadStations(const string& fileName);
    void loadConnections(const string& fileName);
    void displayGraph();
    void findShortestPath(int startID, int endID);
};


#endif //FUNCTIONS_H
