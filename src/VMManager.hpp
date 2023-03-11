#ifndef VM_MANAGER_HPP
#define VM_MANAGER_HPP

#include <vector>
#include <list>


class VMManager {
public:
    VMManager(std::vector<int>& stContents, std::vector<int>& ptContents);

    int pmAt(int index);
    int translateVAToPA(int va);
    void copyPageFromDisk(int diskBlock, int destFrame);

private:
    int pm[524288] = {0};
    int disk[1024][512] = {0};
    std::list<int> freeFrames;
};


#endif