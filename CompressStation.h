#pragma once  // Защита от повторного включения
#include <string>
#include <iostream>
#include <limits>
#include <fstream>

class CompressStation{
public:
    // CompressStation(std::string name, int total, int working, std::string stationclass);
    CompressStation();

    void saveToBinaryFile(std::ofstream& file);
    void loadFromBinaryFile(std::ifstream& file);
    std::string getName() const;
    int getTotal() const;
    int getWorking() const;
    std::string getStationClass() const;
    void setName();
    void setTotal();
    void setWorking();
    void setStationClass();
    void startWorkshop();
    void stopWorkshop();
private:
    std::string name;
    int total;
    int working;
    std::string stationclass;
};


