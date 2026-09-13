#include "CompressStation.h"
#include "utils.h"

// CompressStation::CompressStation(std::string name = "", int total = 0, int working = 0, std::string stationclass = "unknown"){
//     this->name = name;
//     this->total = total;
//     this->working = working;
//     this->stationclass = stationclass;
// }

CompressStation::CompressStation() : name(""), total(0), working(0), stationclass("unknown") {}

void CompressStation::saveToBinaryFile(std::ofstream& file) {
    size_t nameSize = name.size();
    file.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    file.write(name.c_str(), nameSize);

    file.write(reinterpret_cast<char*>(&total), sizeof(total));
    file.write(reinterpret_cast<char*>(&working), sizeof(working));

    size_t classSize = stationclass.size();
    file.write(reinterpret_cast<char*>(&classSize), sizeof(classSize));
    file.write(stationclass.c_str(), classSize);
}

void CompressStation::loadFromBinaryFile(std::ifstream& file) {
    size_t nameSize;
    file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    name.resize(nameSize);
    file.read(&name[0], nameSize);

    file.read(reinterpret_cast<char*>(&total), sizeof(total));
    file.read(reinterpret_cast<char*>(&working), sizeof(working));

    size_t classSize;
    file.read(reinterpret_cast<char*>(&classSize), sizeof(classSize));
    stationclass.resize(classSize);
    file.read(&stationclass[0], classSize);
}

std::string CompressStation::getName() const {return this->name;}
int CompressStation::getTotal() const {return this->total;}
int CompressStation::getWorking() const {return this->working;}
std::string CompressStation::getStationClass() const {return this->stationclass;}

void CompressStation::setName(){
    std::string value;
    std::cout << "Enter name for a CS" << std::endl;
    std::getline(std::cin, value);
    this->name = value;
}

void CompressStation::setTotal(){
    int value;
    while (true) {
        std::cout << "Enter total for a CS" << std::endl;
        std::cin >> value;
        if (!std::cin.fail() && value > 0) {
            clearInputBuffer();
            this->total = value;
            if (this->working > this->total) {
                this->working = this->total;
            }
            break;
        }
        clearInputBuffer();
        std::cout << "Incorrect value. Try again" << std::endl;
    }
}

void CompressStation::setWorking(){
    int value;
    while (true) {
        std::cout << "Enter working for a CS" << std::endl;
        std::cin >> value;
        if (!std::cin.fail() && value >= 0 && value <= this->total) {
            clearInputBuffer();
            this->working = value;
            break;
        }
        clearInputBuffer();
        std::cout << "Incorrect value. Try again" << std::endl;
    }
}

void CompressStation::setStationClass(){
    std::string value;
    std::cout << "Enter station class for a CS" << std::endl;
    std::getline(std::cin, value);
    this->stationclass = value;
}

void CompressStation::startWorkshop(){
    if (working < total) {
        working++;
        std::cout << "One workshop started" << std::endl;
    }
    else {
        std::cout << "All workshops are already working" << std::endl;
    }
}

void CompressStation::stopWorkshop(){
    if (working > 0) {
        working--;
        std::cout << "One workshop stopped" << std::endl;
    }
    else {
        std::cout << "There are no working workshops" << std::endl;
    }
}