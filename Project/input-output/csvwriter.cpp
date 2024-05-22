//
// Created by Ponanoix on 02.06.2023.
//

#include "csvwriter.h"

CSVWriter::CSVWriter(const string& fileName, int dataSize, int columnWidth, string *headers, double **data) : filename(fileName), dataSize(dataSize), columnWidth(columnWidth), headers(headers), data(data), stream(fileName) {
    writeData();
}

void CSVWriter::writeData() {
    for(int i = 0; i < columnWidth; i++){
        stream<<headers[i];
        if(i + 1 < columnWidth) stream<<",";
    }
    stream<<endl;
    for(int i = 0; i < dataSize; i++){
        for(int j = 0; j < columnWidth; j++){
            stream<<data[i][j];
            if(j + 1 < columnWidth) stream<<",";
        }
        stream<<endl;
    }
}
