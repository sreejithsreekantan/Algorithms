//
//  main.cpp
//  Anagram
//
//  Created by Sreejith Sreekantan on 12/12/12.
//  Copyright (c) 2012. All rights reserved.
//

#include <iostream>
#include "AnagramSorter.h"

int main (int argc, const char * argv[])
{
    AnagramSorter as;
    as.push("cat");
    as.push("tac");
    as.push("dog");
    as.push("dgo");
    as.push("143");
    as.push("314");
    as.push("879");
    as.push("789");
    as.printAllWords();
    return 0;
}

