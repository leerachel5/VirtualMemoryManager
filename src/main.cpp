#include "FileParser.hpp"
#include "VMManager.hpp"
#include <iostream>


const std::string INIT_FILE_PATH = "input/init-no-dp.txt";
const std::string INPUT_FILE_PATH = "input/input-no-dp.txt";


int main() {
    std::vector<int> stContents;
    std::vector<int> ptContents;
    FileParser::GetInitContent(INIT_FILE_PATH, stContents, ptContents);
    VMManager vm(stContents, ptContents);

    std::vector<int> virtualAddrs;
    FileParser::GetVAInput(INPUT_FILE_PATH, virtualAddrs);

    return 0;
}