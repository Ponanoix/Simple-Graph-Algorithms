//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_CSVWRITER_H
#define SDIZO2_CSVWRITER_H

#include<fstream>

using namespace std;

// This is a simple class which is used to write data to .CSV file format
class CSVWriter{
private:
    const string filename;      // Name of the csv file

    const int dataSize;         // Number of data points

    const int columnWidth;      // Amount of data per data point

    double **data;              // Two dimensional array of data

    string *headers;            // Names of the columns

    ofstream stream;            // File output stream

    void writeData();           // Writes data to file
public:
    CSVWriter(const string& fileName, int dataSize, int columnWidth, string *headers, double **data);      // Constructor
};


#endif //SDIZO2_CSVWRITER_H
