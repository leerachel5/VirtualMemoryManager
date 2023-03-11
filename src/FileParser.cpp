#include "FileParser.hpp"
#include <fstream>
#include <sstream>


void FileParser::GetInitContent(std::string initFilePath, std::vector<int>& stContents, std::vector<int>& ptContents) {
    std::ifstream initFile(initFilePath);
    std::string buffer;
    int intBuffer;

    // Read first line of file and get ST contents
    getline(initFile, buffer);
    std::stringstream ss(buffer);

    while (ss >> intBuffer) {
        stContents.push_back(intBuffer);
    }

    // Read second line of file and get PT contents
    getline(initFile, buffer);
    ss.str(buffer);
    ss.clear();
    
    while(ss >> intBuffer) {
        ptContents.push_back(intBuffer);
    }
}