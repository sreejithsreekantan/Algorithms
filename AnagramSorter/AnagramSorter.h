//
//  Anagram.h
//  Anagram
//
//  Created by Sreejith Sreekantan03 on 12/12/12.
//  Copyright (c) 2012 . All rights reserved.
//

#ifndef _Anagram_h
#define _Anagram_h
#include <map>

class AnagramSorter {
    std::multimap<long long, std::string> wordsToSort;    
public:
    void push(const std::string wordToPush);
    void printAllWords();
};

#endif
