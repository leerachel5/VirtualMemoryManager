#include "VMManager.hpp"
#include <bitset>
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

    return pm[pm[2 * s + 1] * 512 + p] * 512 + w;
}