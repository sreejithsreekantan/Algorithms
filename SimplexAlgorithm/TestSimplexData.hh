/*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/
#ifndef __TESTSIMPLEXDATA_HH__
#define __TESTSIMPLEXDATA_HH__

#include <string>
#include "SimplexData.hh"
#include <sstream>

using namespace std;
class TestSimplexData : public SimplexData
{
public:
    virtual string toString();
    // TestSimplexData(): SimplexData(4, 7,
    // {
    //     1,     -2.5,   -3,     0,      0,      0,       0,
    //     0,     3,      6,      1,      0,      0,       90,
    //     0,     2,      1,      0,      1,      0,       35,
    //     0,     1,      1,      0,      0,      1,       20
    // }) {}
    TestSimplexData(int rowsize, int colsize, initializer_list<double> v_args): SimplexData(rowsize, colsize, v_args) {}
    TestSimplexData(): SimplexData(4, 7,
    {
        1,     -2.5,   -3,     0,      0,      0,       0,
        0,     3,      6,      1,      0,      0,       90,
        0,     2,      1,      0,      1,      0,       35,
        0,     1,      1,      0,      0,      1,       20
    }) {}
    // TestSimplexData(const TestSimplexData& tsdata): SimplexData(tsdata) {}
    virtual ~TestSimplexData() {}
};

string TestSimplexData::toString()
{
    ostringstream output;
    for (int i = 0; i < rowSize(); ++i)
    {
        output << "{\t\t";
        for (int j = 0; j < colSize(); ++j)
        {
            output << get(i, j);
            output << "\t\t";
        }
        output << " }\n";
    }
    return output.str();
}

#endif // __TESTSIMPLEXDATA_HH__