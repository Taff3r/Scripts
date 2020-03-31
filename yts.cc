#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "config.h"
int main (int argc, char** argv) {
    if (argc < 2){
        std::cout << "Missing args" << std::endl;
        return 1;
    }
    std::string number;
    if(argc >= 3){
        number = argv[2];
    } else {
        number = "5";
    }
    std::map<size_t, std::pair<std::string, std::string>> map;
    std::cout << "Searching for top " << number << " results for " << argv[1] << std::endl << "..." << std::endl;
    std::string search;
    search += "youtube-dl -e -g -f \"bestaudio\" \"ytsearch";
    search += number;
    search += ":";
    search += argv[1];
    search += "\" > tmp.txt";
    system(search.c_str());
    std::ifstream results("tmp.txt");
    std::string title;
    size_t k = 0;
    while(std::getline(results, title)){
        std::string url;
        std::getline(results, url);
        map.insert({k++, {title, url}});
    }
    unsigned int i = 0; 
    for(auto it = map.begin(); it != map.end(); ++it){
        std::cout << i++ << ". " <<  (*it).second.first << std::endl;
    }

    unsigned int chosen = 0;
    size_t choice;
    while(!chosen){
        std::cout << "Select download 0-" << map.size()-1 << std::endl;
        std::cin >> choice;
        if(choice < 0 || choice >= map.size()){
            std::cout << "Pick the correct number you git!" << std::endl;
        } else {
            chosen = 1;
        }
    }
    results.close();
    std::cout << "Starting download of: " << map[choice].first << std::endl;
    
    if(remove("tmp.txt") != 0){
        std::cerr << "Failed removing tmp.txt! Please remove manually!" << std::endl;
    }
    std::string dlStr = "youtube-dl -f \"bestaudio\"";
    dlStr += " -o '";
    dlStr += map[choice].first;
    dlStr += "\%(ext)s' \"";
    dlStr += map[choice].second;
    dlStr += "\"";
    system(dlStr.c_str());
    std::string mvStr = "mv '";
    mvStr += map[choice].first;
    mvStr += "' ";
    mvStr += DESTINATION_FOLDER;
    system(mvStr.c_str());
}
