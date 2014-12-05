 /*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 

Tips:
 clang++ -g -std=c++11 HuffmanMain.cc HuffmanAlg.cc -o HuffmanMain && ./HuffmanMain

*/
#include "HuffmanAlg.hh"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    HuffmanAlg huff("Ramakrishnan");
    huff.solve();
    cout << huff.code();
    string s = huff.encodedText();
    cout << "Encoded Text : " << s;
    cout << huff.decode(s);
    return 0;
}