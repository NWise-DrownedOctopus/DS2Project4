//
// Created by nicho on 11/11/2024.
//
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <tuple>
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
    // Make Node for each station
    // Should have [int ID, int Distance, bool visited]
    vector<tuple<int, int, bool>> graphNodes;
    for (int i = 0; i < stations.size(); i++) {
        tuple<int, int, bool> tempNode(stations[i].id, 9999, false);
        graphNodes.push_back(tempNode);
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Finding shortest path from " << stations[startID].name << " to " << stations[endID].name << endl;

    // Here we need to set our start node to visited, and set its distance to 0
    get<1>(graphNodes[startID]) = 0;
    get<2>(graphNodes[startID]) = true;

    // No we must update the distance of each adjacent station
    for (int i = 0; i < adjacencyList[startID].size(); i++) {
        cout << stations[adjacencyList[startID][i].first].name << " with ID : " << stations[adjacencyList[startID][i].first].id << endl;
        cout << "And has weight: " << adjacencyList[startID][i].second << endl;
        get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) = adjacencyList[startID][i].second;
        cout << stations[adjacencyList[startID][i].first].name << " with ID: " << get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) << " now has " << adjacencyList[startID][i].second << " distance" << endl;
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
