#include "VMManager.hpp"
#include <bitset>
#include <iostream>


VMManager::VMManager(std::vector<int>& stContents, std::vector<int>& ptContents) {
    // Add all frames but 0 and 1 (reserved for the ST) to free frames list
    for (int i = 2; i < 1024; i ++ ) {
        freeFrames.emplace_back(i);
    }

    int segment, size, ptFrame;
    for (int i = 0; i < stContents.size(); i++) {
        segment = stContents[i];
        size = stContents[i + 1];
        ptFrame = stContents[i + 2];

        pm[2 * segment] = size;
        pm[2 * segment + 1] = ptFrame;

        if (ptFrame >= 0)
            freeFrames.remove(ptFrame);
    }

    int page;
    int pageFrame;
    for (int i = 0; i < ptContents.size(); i++) {
        segment = ptContents[i];
        page = ptContents[i + 1];
        pageFrame = ptContents[i + 2];

        if (pm[2 * segment + 1] < 0) {
            disk[abs(pm[2 * segment + 1])][page] = pageFrame;
        } else {
            pm[pm[2 * segment + 1] * 512 + page] = pageFrame;
        }

        if (pageFrame >= 0)
            freeFrames.remove(pageFrame);
    }
}

int VMManager::pmAt(int index) {
    return pm[index];
}

int VMManager::translateVAToPA(int va) {
    std::bitset<27> sBitset(va);
    std::bitset<27> sMask("111111111000000000000000000");
    sBitset &= sMask;
    sBitset >>= 18;
    long s = sBitset.to_ulong();

    std::bitset<27> pBitset(va);
    std::bitset<27> pMask("000000000111111111000000000");
    pBitset &= pMask;
    pBitset >>= 9;
    long p = pBitset.to_ulong();

    std::bitset<27> wBitset(va);
    std::bitset<27> wMask("000000000000000000111111111");
    wBitset &= wMask;
    long w = wBitset.to_ulong();

    long pw = p * 512 + w;
    if (pw >= pm[2 * s])
        return -1;

    // PT not resident
    if (pm[2 * s + 1] < 0) {
        int freeFrame = freeFrames.front();
        freeFrames.pop_front();

        copyPageFromDisk(abs(pm[2 * s + 1]), freeFrame);
        pm[2 * s + 1] = freeFrame;
    }

    // Page not resident
    if (pm[pm[2 * s + 1] * 512 + p] < 0) {
        int freeFrame = freeFrames.front();
        freeFrames.pop_front();

        copyPageFromDisk(abs(pm[pm[2 * s + 1] * 512 + p]), freeFrame);
       pm[pm[2 * s + 1] * 512 + p] = freeFrame;
    }

    return pm[pm[2 * s + 1] * 512 + p] * 512 + w;
}

void VMManager::copyPageFromDisk(int diskBlock, int destFrame) {
    for (int i = 0; i < 512; i++)
        pm[destFrame * 512 + i] = disk[diskBlock][i];
}