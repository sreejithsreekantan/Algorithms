/*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include "TestSimplexData.hh"
#include "TestSimplexAlgorithm.hh"

using namespace std;

int main(int argc, char const *argv[])
{

    cout << "started..\n";
    // TestSimplexData data;
    TestSimplexData data(4, 7,
    {
        1,     -13,   -23,      0,      0,      0,       0,
        0,     5,      15,      1,      0,      0,       480,
        0,     4,      4,       0,      1,      0,       160,
        0,     35,     20,      0,      0,      1,       1190
    });
    TestSimplexAlgorithm algorithm;

    cout << "algorithm.solve(&data) : " << algorithm.solve(&data, 2) << endl;
    algorithm.printAnswerPath();
    algorithm.printAnswer();
    // cout << endl; 
    // cout << data.toString() << endl;

    return 0;
}
