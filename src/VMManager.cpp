#include "VMManager.hpp"
#include <iostream>

VMManager::VMManager(std::vector<int>& stContents, std::vector<int>& ptContents) {
    int segment, size, ptFrame;
    for (int i = 0; i < stContents.size(); i++) {
        segment = stContents[i];
        size = stContents[i + 1];
        ptFrame = stContents[i + 2];

        pm[2 * segment] = size;
        pm[2 * segment + 1] = ptFrame;
    }

    int page;
    int pageFrame;
    for (int i = 0; i < ptContents.size(); i++) {
        segment = ptContents[i];
        page = ptContents[i + 1];
        pageFrame = ptContents[i + 2];

        pm[pm[2 * segment + 1] * 512 + page] = pageFrame;
    }
}

int VMManager::pmAt(int index) {
    return pm[index];
}