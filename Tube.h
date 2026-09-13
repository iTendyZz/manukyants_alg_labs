#pragma once  // Защита от повторного включения
#include <string>
#include <iostream>
#include <limits>
#include <fstream>



class Tube{
public:
    Tube(std::string name, float length, float diameter, bool inRepair);
    Tube();
    void saveToBinaryFile(std::ofstream& file);
    void loadFromBinaryFile(std::ifstream& file);
    std::string getName() const;
    float getLength() const;
    float getDiameter() const;
    bool getInfo() const;
    void setName();
    void setLength();
    void setDiameter();
    void setInfo();

private:
    std::string name;
    float length;
    float diameter;
    bool inRepair;
};