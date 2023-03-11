#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include <vector>


class FileParser {
public:
    static void GetInitContent(std::string initFilePath, std::vector<int>& stContents, std::vector<int>& ptContents);
    static void GetVAInput(std::string inputFilePath, std::vector<int>& virtualAddrs);
};


#endif