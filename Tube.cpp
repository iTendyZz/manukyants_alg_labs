#include "Tube.h"
#include "utils.h"


Tube::Tube(std::string name = "", float length = 0.0, float diameter = 0.0, bool inRepair = false){
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->inRepair = inRepair;
}

Tube::Tube() : name(""), length(0.0f), diameter(0.0f), inRepair(false) {}

void Tube::saveToBinaryFile(std::ofstream& file) {
    size_t nameSize = name.size();
    file.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    file.write(name.c_str(), nameSize);

    file.write(reinterpret_cast<char*>(&length), sizeof(length));
    file.write(reinterpret_cast<char*>(&diameter), sizeof(diameter));
    file.write(reinterpret_cast<char*>(&inRepair), sizeof(inRepair));
}

void Tube::loadFromBinaryFile(std::ifstream& file) {
    size_t nameSize;
    file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    name.resize(nameSize);
    file.read(&name[0], nameSize);

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(reinterpret_cast<char*>(&diameter), sizeof(diameter));
    file.read(reinterpret_cast<char*>(&inRepair), sizeof(inRepair));
}

std::string Tube::getName() const {return this->name;}
float Tube::getLength() const {return this->length;}
float Tube::getDiameter() const {return this->diameter;}
bool Tube::getInfo() const {return this->inRepair;}

void Tube::setName(){
    std::string value;
    std::cout << "Enter name for a tube" << std::endl;
    std::getline(std::cin, value);
    this->name = value;
}

void Tube::setLength(){
    float value;
    while (true) {
        std::cout << "Enter length for a tube (km)" << std::endl;
        std::cin >> value;
        if (!std::cin.fail() && value > 0) {
            clearInputBuffer();
            this->length = value;
            break;
        }
        clearInputBuffer();
        std::cout << "Incorrect value. Try again" << std::endl;
    }
}

void Tube::setDiameter(){
    float value;
    while (true) {
        std::cout << "Enter diameter for a tube (mm)" << std::endl;
        std::cin >> value;
        if (!std::cin.fail() && value > 0) {
            clearInputBuffer();
            this->diameter = value;
            break;
        }
        clearInputBuffer();
        std::cout << "Incorrect value. Try again" << std::endl;
    }
}

void Tube::setInfo(){
    int value;
    while (true) {
        std::cout << "Is tube in repairing? (1 - yes, 0 - no)" << std::endl;
        std::cin >> value;
        if (!std::cin.fail() && (value == 0 || value == 1)) {
            clearInputBuffer();
            this->inRepair = value;
            break;
        }
        clearInputBuffer();
        std::cout << "Incorrect value. Try again" << std::endl;
    }
}
