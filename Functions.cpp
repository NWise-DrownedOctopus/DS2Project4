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
    int ogID = startID;
    vector<tuple<int, int, bool>> graphNodes;
    for (int i = 0; i < stations.size(); i++) {
        tuple<int, int, bool> tempNode(stations[i].id, 9999, false);
        graphNodes.push_back(tempNode);
    }

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    // Here we need to set our start node to visited, and set its distance to 0
    get<1>(graphNodes[startID]) = 0;
    while (startID != endID) {
        // Here we update the distance of each adjacent station, and identify the closest that hasn't been visited
        get<2>(graphNodes[startID]) = true;
        cout << "These are the stations within adjacency to our current node (" << stations[startID].name << " )" << endl;
        for (int i = 0; i < adjacencyList[startID].size(); i++) {
            cout << stations[adjacencyList[startID][i].first].name << " with ID : " << stations[adjacencyList[startID][i].first].id << " ";
            cout << "And has weight: " << adjacencyList[startID][i].second << endl;
            if (get<1>(graphNodes[startID]) + adjacencyList[startID][i].second < get<1>(graphNodes[stations[adjacencyList[startID][i].first].id])) {
                cout << get<1>(graphNodes[startID]) << " + " << adjacencyList[startID][i].second << " < " << get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) << endl;
                cout << "New weight is: " << get<1>(graphNodes[startID]) + adjacencyList[startID][i].second << endl;
                get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) = get<1>(graphNodes[startID]) + adjacencyList[startID][i].second;
            }
            else {
                cout << get<1>(graphNodes[startID]) << " + " << adjacencyList[startID][i].second << " < " << get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) << endl;
                cout << "Weight remains: " << get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) << endl;
            }
        }
        // Here we ID our next node to visit
        int nextId = -1, shortestDistance = 9999;
        for (int i = 0; i < adjacencyList[startID].size(); i++) {
            if (get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]) <= shortestDistance && get<2>(graphNodes[stations[adjacencyList[startID][i].first].id]) != 1) {
                nextId = get<0>(graphNodes[stations[adjacencyList[startID][i].first].id]);
                shortestDistance = get<1>(graphNodes[stations[adjacencyList[startID][i].first].id]);
            }
        }
        if (nextId == -1) {
            cout << "ERROR: NO NEXT NODE ID FOUND " << endl;
            bool stationFound = false;
            for (int i = 0; i < stations.size(); i++) {
                if (get<2>(graphNodes[stations[i].id]) == 0 && get<0>(graphNodes[stations[i].id]) != endID) {
                    cout << stations[i].name << " " << get<2>(graphNodes[stations[i].id]) << endl;
                    nextId = get<0>(graphNodes[stations[i].id]);
                    stationFound = true;
                }
            }
            if (stationFound == false) {
                break;
            }
        }
        cout << "The next node should be: " << stations[nextId].name << endl;
        startID = nextId;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    }
    cout << endl << endl << "The Shortest Path to " << stations[endID].name << " from " << stations[ogID].name << ":" << endl;
    cout << get<1>(graphNodes[endID]) << endl;
}

void Graph::displayGraph() {
    for (const auto& [cityId, neighbors] : adjacencyList) {
        cout << "Station " << stations[cityId].name << " connects to:\n";
        for (const auto& [destId, distance] : neighbors) {
            cout << "  - " << stations[destId].name << " with distance " << distance << "\n";
        }
    }
}
