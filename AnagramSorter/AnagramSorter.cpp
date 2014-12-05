//
//  AnagramSorter.cpp
//  Anagram
//
//  Created by Sreejith Sreekantan03 on 12/12/12.
//  Copyright (c) 2012 . All rights reserved.
//

#include <iostream>
#include <map>
#include "AnagramSorter.h"

long long getKeyForWord(const std::string word);

long long getKeyForWord(const std::string word) {
    long long hashValue=0;
    const char *iter = word.c_str();
    for (int i=0; i<word.length(); i++,iter++) {
        hashValue += ((int)*iter - 65);
    }
    return hashValue;
}

void AnagramSorter::push(const std::string wordToPush) {
    wordsToSort.insert(std::pair<long long,std::string>(getKeyForWord(wordToPush),wordToPush));
}

void AnagramSorter::printAllWords() {
    std::cout << "Anagram-Sorted list:" << std::endl;
    for (std::multimap<long long, std::string>::iterator iter = wordsToSort.begin(); iter != wordsToSort.end(); iter++) {
        std::cout << "\"" << iter->second << "\" ";
    }
    std::cout << std::endl;
}
