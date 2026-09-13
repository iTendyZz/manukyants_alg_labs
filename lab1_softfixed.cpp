#include <iostream>
#include <fstream>
#include <string>
#include "limits"
#include "Tube.h"
#include "CompressStation.h"
#include "utils.h"


// void clearInputBuffer() {
//     std::cin.clear();
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }

Tube main_tube{};
CompressStation main_cs{};

void menu();

void CreateTube(Tube *main_v){
    Tube tube{};
    tube.setName();
    tube.setLength();
    tube.setDiameter();
    tube.setInfo();
    *main_v = tube;
}

void CreateCS(CompressStation *main_v){
    CompressStation cs{};
    cs.setName();
    cs.setTotal();
    cs.setWorking();
    cs.setStationClass();
    *main_v = cs;
}

void ExploreObjects(Tube *t_val, CompressStation *c_val){
    std::string result;
    if (!t_val->getName().empty()){
        std::string status = t_val->getInfo() ? "in repairing" : "working";
        result += std::to_string(1) + ") " + "\"" + t_val->getName() + "\"" + " Tube(Length: " + std::to_string(t_val->getLength()) + " km, Diameter: " + std::to_string(t_val->getDiameter()) + " mm, Status: " + status + ")" + "\n";
    }
    if (!c_val->getName().empty()){
        result += std::to_string(2) + ") " + "\"" + c_val->getName() + "\"" + " CS(" + "Total: " + std::to_string(c_val->getTotal()) + ", Working: " + std::to_string(c_val->getWorking()) + ", Station Class: " + c_val->getStationClass() + ")" + "\n";
    }
    if (result.empty()) {
        std::cout << "No objects found" << std::endl;
    }
    else {
        std::cout << result;
    }
}

void EditTube(Tube *object){
    int choice;
    std::cout << "What to edit:\n1) Name\n2) Length\n3) Diameter\n4) Repair status\n0) Back \n\n ";
    std::cin >> choice;
    clearInputBuffer();
    if (choice == 1) {object->setName();}
    else if (choice == 2) {object->setLength();}
    else if (choice == 3) {object->setDiameter();}
    else if (choice == 4) {object->setInfo();}
    else if (choice == 0) {return;}
}

void EditCs(CompressStation *object){
    int choice;
    std::cout << "What to edit:\n1) Name\n2) Total\n3) Set working\n4) Start one workshop\n5) Stop one workshop\n6) Station class\n0) Back \n\n ";
    std::cin >> choice;
    clearInputBuffer();
    if (choice == 1) {object->setName();}
    else if (choice == 2) {object->setTotal();}
    else if (choice == 3) {object->setWorking();}
    else if (choice == 4) {object->startWorkshop();}
    else if (choice == 5) {object->stopWorkshop();}
    else if (choice == 6) {object->setStationClass();}
    else if (choice == 0) {return;}
}

void SaveBinaryData() {
    std::ofstream file("data.bin", std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: Cannot open binary file for writing!" << std::endl;
        return;
    }

    const char* header = "TUBE_CS_DATA";
    file.write(header, 12);

    int version = 2;
    file.write(reinterpret_cast<char*>(&version), sizeof(version));

    main_tube.saveToBinaryFile(file);
    main_cs.saveToBinaryFile(file);

    file.close();
    std::cout << "Data saved successfully to binary file 'data.bin'" << std::endl;
}

void LoadBinaryData() {
    std::ifstream file("data.bin", std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: Cannot open binary file for reading!" << std::endl;
        std::cout << "File may not exist yet." << std::endl;
        return;
    }

    char header[13];
    file.read(header, 12);
    header[12] = '\0';

    if (std::string(header) != "TUBE_CS_DATA") {
        std::cout << "Error: Invalid file format!" << std::endl;
        file.close();
        return;
    }

    int version;
    file.read(reinterpret_cast<char*>(&version), sizeof(version));

    if (version != 2) {
        std::cout << "Error: Unsupported file version!" << std::endl;
        file.close();
        return;
    }

    main_tube.loadFromBinaryFile(file);
    main_cs.loadFromBinaryFile(file);

    file.close();
    std::cout << "Data loaded successfully from binary file 'data.bin'" << std::endl;
}

void menu(){
    while(true){
        int choice;
        std::cout << "What to do?\n1) Create Tube\n2) Create CS\n3) Show all objects\n4) Edit tube\n5) Edit CS\n6) Save Data\n7) Load Data\n0) Exit\n\n";
        std::cin >> choice;
        clearInputBuffer();
        if (choice == 1) {CreateTube(&main_tube);}
        else if (choice == 2) {CreateCS(&main_cs);}
        else if (choice == 3) {ExploreObjects(&main_tube, &main_cs);}
        else if (choice == 4) {
            if (!main_tube.getName().empty()) {EditTube(&main_tube);} 
            else {std::cout << "Tube not found" << std::endl;}
        }
        else if (choice == 5) {
            if (!main_cs.getName().empty()) {EditCs(&main_cs);} 
            else {std::cout << "CS not found" << std::endl;}
        }
        else if (choice == 6) {SaveBinaryData();}
        else if (choice == 7) {LoadBinaryData();}
        else if (choice == 0) {
            std::cout << "BYE!\n";
            break;
        }
        else {
            std::cout << "Incorrect menu item" << std::endl;
        }
    }
}

int main() {
    menu();
    return 0;
};
