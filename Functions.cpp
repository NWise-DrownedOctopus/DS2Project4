//
// Created by nicho on 11/11/2024.
//
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Functions.h"

void Graph::loadCities(const string &fileName) {
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        istringstream  iss(line);
        int id;
        string name;
        if (iss >> id && getline(iss, name, ',')) {
            cities[id] = {id, name};
        }
    }
}

void Graph::loadConnections(const string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int source, destination, distance;
        char comma;
        if (iss >> source >> comma >> destination >> comma >> distance) {
            adjacencyList[source].emplace_back(destination, distance);
        }
    }
}

void Graph::displayGraph() {
    for (const auto& [cityId, neighbors] : adjacencyList) {
        std::cout << "City " << cities[cityId].name << " connects to:\n";
        for (const auto& [destId, distance] : neighbors) {
            std::cout << "  - " << cities[destId].name << " with distance " << distance << "\n";
        }
    }
}
