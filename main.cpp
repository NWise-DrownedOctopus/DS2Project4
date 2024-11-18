#include <iostream>
#include "Functions.h"

int main()
{
    Graph graph;
    ifstream destinationFile, connectionFile;

    destinationFile.open("destinations.txt");
    connectionFile.open("connections.txt");

    if (!destinationFile.good() || !connectionFile.good()) {
        cout << "Error opening file " << endl;
        return -1;
    }

    graph.loadStations("destinations.txt");
    cout << "We have: " << graph.stations.size() << " cites" << endl;
    graph.loadConnections("connections.txt");
    graph.displayGraph();
    cout << endl << endl;

    int startStation, endStation;
    while (true) {
        cout << "Please enter the ID number for your starting station: ";
        cin >> startStation;
        cout << "Please enter the ID number for your ending station: ";
        cin >> endStation;

        cout << "We would like to find the shortest path from: " << graph.stations[startStation].name << " to " << graph.stations[endStation].name << endl;
        graph.findShortestPath(startStation, endStation);
        char choice;
        cout << "Would you like to check another route?(Y/N)" << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n') {
            break;
        }
    }

    cout << "Thank you for using my program" << endl;
    cout << "Now Exiting" << endl;

    return 0;
}
