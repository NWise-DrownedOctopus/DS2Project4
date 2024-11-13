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

    cout << "We would like to find the shortest path from: " << graph.stations[3].name << " to " << graph.stations[9].name << endl;
    graph.findShortestPath(3, 9);

    return 0;
}
