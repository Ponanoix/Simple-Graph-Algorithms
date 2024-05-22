//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_MENU_H
#define SDIZO2_MENU_H

#include "graph-representations/list-representation.h"
#include "graph-representations/matrix-representation.h"
#include "input-output/file-reader.h"
#include <string>
#include <random>

using namespace std;

class Menu{
private:
    mt19937 randNumGen;

    uniform_int_distribution<int> numberDistribution;

    ListRepresentation *listRep = nullptr;                                                  // Graph list representation read from file

    MatrixRepresentation *matrixRep = nullptr;                                              // Graph matrix representation read from file

    FileReader *fileReader = nullptr;

    void printMainMenu();                                                                   // Prints main menu

    static int getIntegerInput(const string& message, bool mustPositive = false);           // Prompts the user with message to input integer value and returns it

    static float getFloatInput(const string& message, bool mustPositive = false);           // Prompts the user with message to input float value and returns it

    static void printException(exception &e);                                               // Nicely prints thrown exception on stdout

    static uniform_int_distribution<int> getRandomInRange(int a, int b);
public:
    Menu();

    void printReadFromFileMenu();

    void generateRandomGraph(MatrixRepresentation *matrixAlg, ListRepresentation *listAlg);

    void kruskal();

    void dijkstra();

    void bellmanFord();

    void fordFulkerson();

    void prims();

};

#endif //SDIZO2_MENU_H
