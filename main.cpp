#include <iostream>
#include "Functions.h"

int main()
{
    Graph graph;
    ifstream destinationFile, connectionFile;

    destinationFile.open("destination.txt");
    connectionFile.open("connection.txt");

    if (!destinationFile.good() || !connectionFile.good()) {
        cout << "Error opening file " << endl;
        return -1;
    }

    graph.loadCities("destinations.txt");
    graph.loadConnections("connections.txt");
    graph.displayGraph();
    return 0;
}
