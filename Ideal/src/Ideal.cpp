#include "../include/Ideal.h"
#include <iostream>
#include <fstream>

std::map<std::string, int> Ideal::readDataBase(std::string dataBaseName, int& count) {
    std::map<std::string, int> collection;
    std::fstream file;
    file.open(dataBaseName);

    if(!file.is_open()) {
        std::cout << "not open" << std::endl;
    }

    std::string line;
    while (getline (file, line)) {

        while(line.size() != 0) {

            int pos = line.find(",");

            if(pos == -1) {

                if(collection.find(line) != collection.end()) {
                    collection[line] += 1;
                } else {
                    collection.insert(std::make_pair(line, 1));
                }

                line.clear();

            } else {
                std::string sub = line.substr(0, pos);

                if(collection.find(sub) != collection.end()) {
                    collection[sub] += 1;
                } else {
                    collection.insert(std::make_pair(sub, 1));
                }

                line.erase(0, sub.length()+1);
            }
        }
        count++;
    }

    for(auto i : collection) {
        std::cout << "key " << i.first << " Value " << i.second << std::endl;
    }

    file.close();

    return collection;
}



std::map<std::string, int> Ideal::idealRun(std::string db, float minSup) {
    int transactionNum = 0;
    std::map<std::string, int> collection = readDataBase(db, transactionNum);
}