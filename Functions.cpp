//
// Created by nicho on 11/11/2024.
//
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Functions.h"
using namespace std;

void Graph::loadStations(const string &fileName) {
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        istringstream  iss(line);
        int id;
        string name, token;
        vector<string> tokens;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        };
        id = stoi(tokens[0]);
        name = tokens[1];
        stations.emplace(id, Station{id, name});
    }
}

void Graph::loadConnections(const string& fileName) {
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int source, destination, distance;
        char comma;
        if (iss >> source >> comma >> destination >> comma >> distance) {
            adjacencyList[source].emplace_back(destination, distance);
        }
    }
}

void Graph::findShortestPath(int startID, int endID) {
    // Makde Node for each station
    // SHould have [int ID, int Distance, bool visitied]
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Finding shortest path from " << stations[startID].name << " to " << stations[endID].name << endl;
    cout << "Start: " << stations[startID].name << " Distance: 0" << endl << endl;
    for (int i = 0; i < adjacencyList[startID].size(); i++) {
        cout << stations[adjacencyList[startID][i].first].name << endl;
    }
}

void Graph::displayGraph() {
    for (const auto& [cityId, neighbors] : adjacencyList) {
        cout << "Station " << stations[cityId].name << " connects to:\n";
        for (const auto& [destId, distance] : neighbors) {
            cout << "  - " << stations[destId].name << " with distance " << distance << "\n";
        }
    }
}
