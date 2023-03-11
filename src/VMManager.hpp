#ifndef VM_MANAGER_HPP
#define VM_MANAGER_HPP

#include <vector>


class VMManager {
public:
    VMManager(std::vector<int>& stContents, std::vector<int>& ptContents);

    int pmAt(int index);
    int translateVAToPA(int va);

private:
    int pm[524288] = {0};
};


#endif