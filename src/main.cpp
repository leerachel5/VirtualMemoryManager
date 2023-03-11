#include "FileParser.hpp"
#include "VMManager.hpp"
#include <iostream>
#include <fstream>


const std::string INIT_FILE_PATH = "input/init-no-dp.txt";
const std::string INPUT_FILE_PATH = "input/input-no-dp.txt";
const std::string OUTPUT_FILE_PATH = "output/output-no-dp.txt";


int main() {
    std::vector<int> stContents;
    std::vector<int> ptContents;
    FileParser::GetInitContent(INIT_FILE_PATH, stContents, ptContents);
    VMManager vm(stContents, ptContents);

    std::vector<int> virtualAddrs;
    FileParser::GetVAInput(INPUT_FILE_PATH, virtualAddrs);

    std::ofstream outputFile(OUTPUT_FILE_PATH);
    for (int i = 0; i < virtualAddrs.size(); i++) {
        outputFile << vm.translateVAToPA(virtualAddrs[i]);
        if (i < virtualAddrs.size() - 1)
            outputFile << " ";
    }
    outputFile.close();

    return 0;
}