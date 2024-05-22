//
// Created by Ponanoix on 04.06.2023.
//

#include <windows.h>
#include "menu.h"
#include "input-output/file-reader.h"
#include "utility/adjacency-list.h"
#include "graph-representations/list-representation.h"

Menu::Menu() {
    printMainMenu();
}

void Menu::printMainMenu() {
    while(matrixRep == nullptr && listRep == nullptr){
        printReadFromFileMenu();
    }
    while(true){
        cout<<"Choose the action: " << endl;
        cout<<"\t1. Reload a graph from a file & show it"<<endl;
        cout<<"\t2. Generate a random graph"<<endl;
        cout<<"\t3. Kruskal's algorithm"<<endl;
        cout<<"\t4. Prim's algorithm"<<endl;
        cout<<"\t5. Dijkstra's algorithm"<<endl;
        cout<<"\t6. Bellman-Ford's algorithm"<<endl;
        cout<<"\t7. Ford-Fulkerson's algorithm"<<endl;
        cout<<"\t0. Turn off the program"<<endl;
        int input = getIntegerInput("\nYour choice:\n");
        switch(input){
            case 1:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                printReadFromFileMenu();
                break;
            }
            case 2:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                generateRandomGraph(matrixRep, listRep);
                break;
            }
            case 3:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                kruskal();
                break;
            }
            case 4:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                prims();
                break;
            }
            case 5:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                dijkstra();
                break;
            }
            case 6:{
                cout<<endl<<">--------------------------------------------------------------------|"<<endl;
                bellmanFord();
                break;
            }
            case 7:{
                fordFulkerson();
                break;
            }
            case 0:{
                cout<<"Shutting down..."<<endl;
                exit(0);
            }
            default:{
                cout<<"Unknown input"<<endl;
                break;
            }
        }
    }
}

int Menu::getIntegerInput(const string& message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    int val;
    while(!isNum){
        cout<<message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try{
            val = stoi(input);
            if(val > 0) isPositive = true;
            if(!mustPositive || isPositive) isNum = true;
            else isNum = false;
        } catch (invalid_argument &e){
            cout<<"Entered data is not numerical"<<endl;
            continue;
        }
        catch(out_of_range &e){
            cout<<"Entered number is too large"<<endl;
            continue;
        }
    }
    return val;
}

float Menu::getFloatInput(const string& message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    float val;
    while(!isNum){
        cout<<message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try{
            val = stof(input);
            if(val > 0) isPositive = true;
            if(!mustPositive || isPositive) isNum = true;
            else isNum = false;
        } catch(invalid_argument &e){
            cout<<"Entered data is not numerical"<<endl;
            continue;
        }
        catch(out_of_range &e){
            cout<<"Entered number is too large"<<endl;
            continue;
        }
    }
    return val;
}

void Menu::printException(exception &e) {
    cout<<"X-----------------------------X\n";
    cout<<"WARNING: An error has occurred:\n";
    cerr << e.what()<<"\n";
    cout<<"X-----------------------------X\n";
}

void Menu::printReadFromFileMenu() {
    string fileName;
    cout << "Please enter the file's name:\n";
    cin >> fileName;
    cout << "\n";
    cout << "Loading data from the file..."<<endl;
    cout << "\n";
    try{
        FileReader reader(fileName);
        cout<<"...Data loaded successfully. Both data types:"<<endl;
        cout<<endl<<endl;
        cout<<"List:\t";
        reader.showData();
        listRep = new ListRepresentation(0, 0, 0, 0, true);
        reader.readToAdjList(listRep);
        cout<<endl<<endl;

        FileReader reader2(fileName);
        cout<<"Matrix:\t";
        reader2.showData();
        matrixRep = new MatrixRepresentation(0, 0, 0, 0, true);
        reader2.readToIncMatrix(matrixRep);
        cout<<"...Both data types loaded successfully"<<endl<<endl;
        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch (runtime_error &e){
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}

uniform_int_distribution<int> Menu::getRandomInRange(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist;
}

void Menu::generateRandomGraph(MatrixRepresentation *matrixAlg, ListRepresentation *listAlg) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(10,100);
    this -> numberDistribution = dist;
    randNumGen = mt;
    cout << "Please enter the density (0.01 - 1.00):" << endl;
    double density;
    cin >> density;
    if(density > 1 || density < 0.01) throw invalid_argument("Invalid density (0.01 - 1.00");
    cout << "Please enter 1 if you wish for the graph to be directed. Enter 0 otherwise." << endl;
    bool directed;
    cin >> directed;
    if(directed == 1) directed = true;
    if(directed == 0) directed = false;
    cout << "Please enter the number of vertices:" << endl;
    int numberOfVertices;
    cin >> numberOfVertices;
    if(numberOfVertices <= 0) throw invalid_argument("Invalid number of vertices (greater than 0)");
    int edges = (int)((double)density * numberOfVertices * (numberOfVertices - 1));
    if(!directed) edges /= 2;
    matrixAlg -> setVertexSize(numberOfVertices);
    matrixAlg -> setEdgeSize(edges);
    matrixAlg -> setStartingVertex(0);
    matrixAlg -> setEndingVertex(getRandomInRange(1, numberOfVertices - 1)(randNumGen));
    listAlg -> setVertexSize(numberOfVertices);
    listAlg -> setEdgeSize(edges);
    listAlg -> setStartingVertex(0);
    listAlg -> setEndingVertex(getRandomInRange(1, numberOfVertices - 1)(randNumGen));
    int *begin = new int[edges];
    int *end = new int[edges];
    int *weights = new int[edges];
    for (int i = 0; i < edges; i++){
        int v1 = getRandomInRange(0, numberOfVertices - 1)(randNumGen);
        int v2 = getRandomInRange(0, numberOfVertices - 1)(randNumGen);
        while (v2 == v1) {
            v2 = getRandomInRange(0, numberOfVertices - 1)(randNumGen);
        }
        int edge = numberDistribution(randNumGen);
        matrixAlg -> addConnection(v1, v2, edge);
        listAlg -> addConnection(v1, v2, edge);
        begin[i] = v1;
        end[i] = v2;
        weights[i] = edge;
    }

    cout<<endl;
    for(int i = 0; i < edges; i++){
        cout << "From " << begin[i] << ":\n";
        cout<<"\tTo: " << end[i]<<", weight: " << weights[i] << endl;
    }

    std::cout<<std::endl;
    std::cout<<"V\\E | ";
    for(int v = 0; v < edges; v++){
        std::cout<<"\t"<<v;
    }
    std::cout<<std::endl;
    std::cout<<"----|-------";
    for(int v2 = 0; v2 < edges; v2++){
        std::cout<<"-------";
    }
    std::cout<<std::endl;
    for(int i = 0; i < numberOfVertices; i++) {
        std::cout<<" "<<i<<"  |";
        for (int j = 0; j < edges; j++) {
            if(directed){
                if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1){
                    if(begin[0] == i) std::cout <<"\tX";
                    else std::cout << "\t0";
                } else {
                    if (begin[j] == i) std::cout << "\t-1";
                    else if (end[j] == i) std::cout << "\t1";
                    else std::cout << "\t0";
                }
            }
            if(!directed){
                if(begin[j] == i || end[j] == i) std::cout << "\t1";
                else std::cout << "\t0";
            }
        }
        std::cout << std::endl;
    }
    if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1) cout<<"(Single vertex graph. Vertex -> "<<begin[0]<<")";
    std::cout<<std::endl;
    std::cout<<std::endl;

    delete[] begin;
    delete[] end;
    delete[] weights;
}

void Menu::kruskal() {
    try {
        KruskalList kList(0, 0);
        kList.clone(listRep);
        kList.seekErrors();
        kList.start();

        KruskalMatrix kMatrix(0, 0);
        kMatrix.clone(matrixRep);
        kMatrix.start();
        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch (logic_error &e){
        cout<<endl;
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}

void Menu::prims() {
    try {
        PrimsList pList(0, 0);
        pList.clone(listRep);
        pList.seekErrors();
        pList.start();

        PrimsMatrix pMatrix(0, 0);
        pMatrix.clone(matrixRep);
        pMatrix.start();
        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch (logic_error &e) {
        cout<<endl;
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}

void Menu::dijkstra() {
    try {
        DijkstraList dList(0, 0, 0);
        dList.clone(listRep);
        dList.seekErrors();

        int startVertex;
        int endVertex;
        cout<<"Please enter the starting vertex:\n";
        cin >> startVertex;
        cout<<"Please enter the ending vertex:\n";
        cin >> endVertex;

        dList.assignVertices(startVertex, endVertex);
        dList.start();

        DijkstraMatrix dMatrix(0, 0, 0);
        dMatrix.clone(matrixRep);
        dMatrix.assignVertices(startVertex, endVertex);
        dMatrix.start();

        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch(logic_error &e) {
        cout<<endl;
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}

void Menu::bellmanFord() {
    try {
        BellmanFordList bfList(0, 0, 0);
        bfList.clone(listRep);

        int startVertex;
        cout << "Please enter the starting vertex:\n";
        cin >> startVertex;

        bfList.assignVertices(startVertex);
        bfList.start();

        BellmanFordMatrix bfMatrix(0, 0, 0);
        bfMatrix.clone(matrixRep);

        bfMatrix.assignVertices(startVertex);
        bfMatrix.start();
        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch(invalid_argument &e) {
        cout<<endl;
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}

void Menu::fordFulkerson() {
    try {
        FordFulkersonList ffList(0, 0, 0, 0);
        ffList.clone(listRep);
        ffList.seekErrors();

        int startVertex;
        int endVertex;
        cout << "Please enter the starting vertex:\n";
        cin >> startVertex;
        cout << "Please enter the ending vertex:\n";
        cin >> endVertex;

        ffList.assignVertices(startVertex, endVertex);
        ffList.start();


        FordFulkersonMatrix ffMatrix(0, 0, 0, 0);
        ffMatrix.clone(matrixRep);

        ffMatrix.assignVertices(startVertex, endVertex);
        ffMatrix.start();
        cout<<">--------------------------------------------------------------------|"<<endl;
    } catch(logic_error &e) {
        cout<<endl;
        printException(e);
        cout<<endl;
        Sleep(200);
        return;
    }
}
