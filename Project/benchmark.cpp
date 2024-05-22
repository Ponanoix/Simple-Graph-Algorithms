//
// Created by Ponanoix on 04.06.2023.
//

#include "benchmark.h"

Benchmark::Benchmark(AlgType type, bool writeToFile, int initialSize,
                     int step, float multiplier, int testNumber,
                     int maxSize) : type(type), isWriteToFile(writeToFile),
                     initialSize(initialSize), step(step), multiplier(multiplier),
                     testNumber(testNumber), maxSize(maxSize) {
    cout<<"Starting benchmark: "<<endl;
    cout<<"\tWrite to file: "<<writeToFile<<endl;
    cout<<"\tInitial size: "<<initialSize<<endl;
    cout<<"\tStep: "<<step<<endl;
    cout<<"\tMultiplier: "<<multiplier<<endl;
    cout<<"\tTest number: "<<testNumber<<endl;
    cout<<"\tMax size: "<<maxSize<<endl;

    performanceCounter = new LARGE_INTEGER;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(10,100);
    this -> numberDistribution = dist;
    randNumGen = mt;
    calcIterationNumber();
    startTest();
}

void Benchmark::startTimer() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    *performanceCounter = count;
}

double Benchmark::stopTimer() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    uint64_t elapsed = count.QuadPart - (*performanceCounter).QuadPart;
    double timeInS = ((float) 1000 * elapsed) / freq.QuadPart;
    return timeInS;
}

uniform_int_distribution<int> Benchmark::getRandomInRange(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist;
}

int Benchmark::getNextRandom(uniform_int_distribution<int> &dist) {
    return dist(randNumGen);
}

void Benchmark::calcIterationNumber() {
    int size = initialSize;

    int itNumber = 0;

    while (size < maxSize) {
        size *= multiplier;
        size += step;
        itNumber++;
    }
    if (size > maxSize) itNumber--;
    this -> iterationNumber = itNumber;
}

void Benchmark::startTest() {
    MatrixRepresentation *matrixAlg = nullptr;
    ListRepresentation *listAlg = nullptr;
    bool isDirected = false;
    switch (type) {
        case BellmanFord:
            matrixAlg = new BellmanFordMatrix(0, 0, 0);
            listAlg = new BellmanFordList(0, 0, 0);
            isDirected = matrixAlg -> getIsDirected();
            break;
        case Dijkstra:
            matrixAlg = new DijkstraMatrix(0, 0, 0);
            listAlg = new DijkstraList(0, 0, 0);
            isDirected = matrixAlg -> getIsDirected();
            break;
        case FordFulkerson:
            matrixAlg = new FordFulkersonMatrix(0, 0, 0, 0);
            listAlg = new FordFulkersonList(0, 0, 0, 0);
            isDirected = matrixAlg -> getIsDirected();
            break;
        case Kruskal:
            matrixAlg = new KruskalMatrix(0, 0);
            listAlg = new KruskalList(0, 0);
            isDirected = matrixAlg -> getIsDirected();
            break;
        case Prims:
            matrixAlg = new PrimsMatrix(0, 0);
            listAlg = new PrimsList(0, 0);
            isDirected = matrixAlg -> getIsDirected();
            break;
        default:
            cout << "Wrong algorithm type, exiting.." << endl;
            exit(0);
    }
    matrixAlg -> isPrintOut = false;
    listAlg -> isPrintOut = false;
    cout << "Testing chosen algorithm (Max Size: " << maxSize << ", Iterations: " << iterationNumber << ", Step: "
         << step<< ", Multiplier: " << multiplier << ", Starting size: " << initialSize << endl;

    int *sizeArray = new int[iterationNumber];
    auto *resultArrayMatrix25 = new double[iterationNumber];
    auto *resultArrayList25 = new double[iterationNumber];
    auto *resultArrayMatrix50 = new double[iterationNumber];
    auto *resultArrayList50 = new double[iterationNumber];
    auto *resultArrayMatrix75 = new double[iterationNumber];
    auto *resultArrayList75 = new double[iterationNumber];
    auto *resultArrayMatrix99 = new double[iterationNumber];
    auto *resultArrayList99 = new double[iterationNumber];
    //------------------------------25% density---------------------------
    cout << "Testing 25% density... " << endl;
    Sleep(2000);

    int size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avgMatrix = 0;
        double avgList = 0;
        for (int j = 0; j < testNumber; j++) {
            generatePopulation(0.25, matrixAlg, listAlg, isDirected, size);
            startTimer();
            matrixAlg -> start();
            avgMatrix += stopTimer();
            startTimer();
            listAlg -> start();
            avgList += stopTimer();

        }
        avgList /= testNumber;
        avgMatrix /= testNumber;
        sizeArray[i] = size;
        resultArrayMatrix25[i] = avgMatrix;
        resultArrayList25[i] = avgList;
        cout << "Alg. test done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultArrayMatrix25[i] << " μs for matrix and "<<resultArrayList25[i]<<" μs for list." << endl;
        size *= multiplier;
        size += step;
    }
    //------------------------------50% density---------------------------
    cout << "Testing chosen algorithm (Max size: " << maxSize << ", Iterations: " << iterationNumber << ", Step: "
         << step
         << ", Multiplier: " << multiplier << ", Starting size: " << initialSize << endl;
    cout << "Testing 50% density... " << endl;
    Sleep(2000);
    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avgMatrix = 0;
        double avgList = 0;
        for (int j = 0; j < testNumber; j++) {
            generatePopulation(0.50, matrixAlg, listAlg, isDirected, size);
            startTimer();
            matrixAlg -> start();
            avgMatrix += stopTimer();
            startTimer();
            listAlg -> start();
            avgList += stopTimer();

        }
        avgList /= testNumber;
        avgMatrix /= testNumber;
        resultArrayMatrix50[i] = avgMatrix;
        resultArrayList50[i] = avgList;
        cout << "Alg. test done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultArrayMatrix50[i] << " μs for matrix and "<<resultArrayList50[i]<<" μs for list." << endl;
        size *= multiplier;
        size += step;
    }
    //------------------------------75% density---------------------------
    cout << "Testing chosen algorithm (Max size: " << maxSize << ", Iterations: " << iterationNumber << ", Step: "
         << step
         << ", Multiplier: " << multiplier << ", Starting size: " << initialSize << endl;
    cout << "Testing 75% density... " << endl;
    Sleep(2000);

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avgMatrix = 0;
        double avgList = 0;
        for (int j = 0; j < testNumber; j++) {
            generatePopulation(0.75, matrixAlg, listAlg, isDirected, size);
            startTimer();
            matrixAlg -> start();
            avgMatrix += stopTimer();
            startTimer();
            listAlg -> start();
            avgList += stopTimer();

        }
        avgList /= testNumber;
        avgMatrix /= testNumber;
        resultArrayMatrix75[i] = avgMatrix;
        resultArrayList75[i] = avgList;
        cout << "Alg. test done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultArrayMatrix75[i] << "μs for matrix and "<<resultArrayList75[i]<<"μs for list." << endl;
        size *= multiplier;
        size += step;
    }

    //------------------------------99% density---------------------------

    cout << "Testing chosen algorithm (max size: " << maxSize << ", iterations: " << iterationNumber << ", step: "
         << step
         << ", multiplier: " << multiplier << ", starting size: " << initialSize << endl;
    cout << "Testing 99% density... " << endl;
    Sleep(2000);

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avgMatrix = 0;
        double avgList = 0;
        for (int j = 0; j < testNumber; j++) {
            generatePopulation(0.99, matrixAlg, listAlg, isDirected, size);
            startTimer();
            matrixAlg -> start();
            avgMatrix += stopTimer();
            startTimer();
            listAlg -> start();
            avgList += stopTimer();

        }
        avgList /= testNumber;
        avgMatrix /= testNumber;
        sizeArray[i] = size;
        resultArrayMatrix99[i] = avgMatrix;
        resultArrayList99[i] = avgList;
        cout << "Alg. test done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultArrayMatrix99[i] << " μs for matrix and " << resultArrayList99[i] << " μs for list." << endl;
        size *= multiplier;
        size += step;
    }
    string fileName;
    fileName.append(to_string(type));
    writeToFile(fileName, resultArrayMatrix25, resultArrayList25, resultArrayMatrix50,
                resultArrayList50, resultArrayMatrix75, resultArrayList75, resultArrayMatrix99, resultArrayList99,
                sizeArray);
    delete[] sizeArray;
    delete[] resultArrayMatrix25;
    delete[] resultArrayList25;
    delete[] resultArrayMatrix50;
    delete[] resultArrayList50;
    delete[] resultArrayMatrix75;
    delete[] resultArrayList75;
    delete[] resultArrayMatrix99;
    delete[] resultArrayList99;
}

void Benchmark::generatePopulation(double d, MatrixRepresentation *mRepresentation, ListRepresentation *lRepresentation1,
                                   bool directed, int vertSize) {
    int edges = (int)((double)d*vertSize*(vertSize - 1));
    if (!directed) edges /= 2;
    mRepresentation -> setVertexSize(vertSize);
    mRepresentation -> setEdgeSize(edges);
    mRepresentation -> setStartingVertex(0);
    mRepresentation -> setEndingVertex(getRandomInRange(1, vertSize - 1)(randNumGen));
    lRepresentation1 -> setVertexSize(vertSize);
    lRepresentation1 -> setEdgeSize(edges);
    lRepresentation1 -> setStartingVertex(0);
    lRepresentation1 -> setEndingVertex(getRandomInRange(1, vertSize - 1)(randNumGen));
    for (int i = 0; i < edges; i++){
        int v1 = getRandomInRange(0, vertSize - 1)(randNumGen);
        int v2 = getRandomInRange(0, vertSize - 1)(randNumGen);
        while (v2 == v1) {
            v2 = getRandomInRange(0, vertSize - 1)(randNumGen);
        }
        int edge = numberDistribution(randNumGen);
        mRepresentation -> addConnection(v1, v2, edge);
        lRepresentation1 -> addConnection(v1, v2, edge);
    }
}

void Benchmark::writeToFile(string testName, const double *resultArrayMatrix25, const double *resultArrayList25,
                            const double *resultArrayMatrix50, const double *resultArrayList50, const double *resultArrayMatrix75,
                            const double *resultArrayList75, const double *resultArrayMatrix99, const double *resultArrayList99,
                            const int *size) const {
    auto** toWrite = new double *[9];
    toWrite[0] = new double[iterationNumber];
    toWrite[1] = new double[iterationNumber];
    toWrite[2] = new double[iterationNumber];
    toWrite[3] = new double[iterationNumber];
    toWrite[4] = new double[iterationNumber];
    toWrite[5] = new double[iterationNumber];
    toWrite[6] = new double[iterationNumber];
    toWrite[7] = new double[iterationNumber];
    toWrite[8] = new double[iterationNumber];

    for (int i = 0; i < iterationNumber; i++){
        toWrite[0][i] = size[i];
        toWrite[1][i] = resultArrayMatrix25[i];
        toWrite[2][i] = resultArrayList25[i];
        toWrite[3][i] = resultArrayMatrix50[i];
        toWrite[4][i] = resultArrayList50[i];
        toWrite[5][i] = resultArrayMatrix75[i];
        toWrite[6][i] = resultArrayList75[i];
        toWrite[7][i] = resultArrayMatrix99[i];
        toWrite[8][i] = resultArrayList99[i];
    }
    string headers[] = {"Vertex number", "Matrix 25%", "List 25%", "Matrix 50%", "List 50%", "Matrix 75%", "List 75%", "Matrix 99%", "List 99%"};
    CSVWriter writer(testName.append(".csv"), iterationNumber, 9, headers, toWrite);
}