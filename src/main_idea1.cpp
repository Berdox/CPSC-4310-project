#include "../include/Idea1.h"
#include "../include/Timer.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

/*
 * Usage:
 * ./idea1 <filename> <min_sup>
 */

int main(int argc, char* argv[]) {

    // Get filename
    if(argc < 2) {
        std::cerr << "no filename provided" << std::endl;
        return -1;
    }
    std::string filename = argv[1];

    // Get filename
    if(argc < 3) {
        std::cerr << "no min_sup provided" << std::endl;
        return -1;
    }
    double min_sup = std::stod(argv[2]);
    
    // Setup apriori
    Idea1 a(filename, min_sup);
    std::set<itemset> frequent_itemsets;

    // Run algorithm
    Timer t;
    double dbScans = a.aprioriRun(frequent_itemsets);
    auto idea1_time = t.elapsed();

    // Making the output file name
    int posD = filename.find("D");
    int posTxt = filename.find(".txt");
    std::string DBname = filename.substr(posD, posTxt-posD);

    char outputFile[100];
    sprintf(outputFile, "./results/%s_Idea1_%d.freq",
                DBname.c_str(), (int)min_sup*100);

    // Open filestream
    std::ofstream file;
    file.open(outputFile);
    if(!file) {
        std::cerr << "unable to open output file: " << outputFile << std::endl;
        return -1;
    }

    // Write itemsets to file
    for(const itemset &s : frequent_itemsets) {
        file << "{";
        for(auto it = begin(s); it != end(s); ++it) {
            file << it->name;
            if(std::distance(it,end(s)) != 1)
                file << ",";
        }
        file <<"}\n";
    }
    file.close();

    // Stdout information display
    std::cout << frequent_itemsets.size() << " frequent itemsets written to: "
              << outputFile << std::endl;
    std::cout << "Performed " << std::fixed << std::setprecision(1) << dbScans
              << " DB scans in " << std::setprecision(2) << idea1_time 
              << "s" << std::endl;

    return 0;
}
