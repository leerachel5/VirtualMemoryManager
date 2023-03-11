#include "FileParser.hpp"
#include "VMManager.hpp"
#include <iostream>


int main() {
    std::vector<int> stContents;
    std::vector<int> ptContents;

    FileParser::GetInitContent("input/init-no-dp.txt", stContents, ptContents);

    VMManager vm(stContents, ptContents);

    return 0;
}