

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
using namespace std;

class TimeSeries {

public:
    const char *CSVfileName;
    TimeSeries(const char *CSVfileName) {
        this->CSVfileName = CSVfileName;
    }
    vector<string> countColumns() const {
        std::ifstream file(CSVfileName);
        std::string line;
        vector<string> namesOfFeatures (1);
        int col = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string result;
            while (std::getline(iss, result, ',')) {
                namesOfFeatures.push_back(result);
            }
            return namesOfFeatures;
        }
    }
    int numOfRows() const{
        std::ifstream file(CSVfileName);
        std::string line;
        int row = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            row++;
        }
        return row;
    }

    float* dataOfFeatures(int index) const{
        int size = numOfRows();
        float* data = new float[size];
        std::ifstream file(CSVfileName);
        std::string line;
        int col = 0;
        int firstRow = 0;
        vector<vector<float>> allData (0);
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string result;
            vector<float> rows (0);
            while (std::getline(iss, result, ',')) {
                if(firstRow != 0) {
                    float num_float = std::stof(result);
                    rows.push_back(num_float);
                }
                firstRow++;
            }
            allData.push_back(rows);
        }
        for (int k = 1; k < allData.size();k++) {
            data[k-1] = allData[k][index];
        }
        return data;
    }
};


#endif /* TIMESERIES_H_ */
