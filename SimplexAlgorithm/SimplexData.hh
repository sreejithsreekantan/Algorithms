/*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/
#ifndef __SIMPLEXDATA_HH__
#define __SIMPLEXDATA_HH__

#include <initializer_list>
#include <vector>
#include <string>

using namespace std;

class SimplexData
{
public:
    typedef initializer_list<double>::iterator v_args_iter;
    SimplexData(int rowsize, int colsize, initializer_list<double> v_args): row_size(rowsize), col_size(colsize)
    {
        int i, j;
        v_args_iter it;
        std::vector<double> tmp;
        v.push_back(tmp);
        for ( i = 0, j = 0, it = v_args.begin(); it != v_args.end(); ++it, ++j)
        {
            if (j == col_size)
            {
                i++; j = 0;
                v.push_back(tmp);
                // cout << "\n";
            }
            v[i].push_back(*it);
            // cout << *it << "\t\t";
        }
    }
    // SimplexData(const SimplexData& sdata): row_size(sdata.row_size), col_size(sdata.col_size), v(sdata.v) { }
    virtual ~SimplexData() {};
    virtual string toString()=0;
    int rowSize() {return row_size;}
    int colSize() {return col_size;}
    virtual bool set(const int row, const int col, const double val);
    virtual double get(const int row, const int col);

private:
    int row_size;
    int col_size;

    std::vector<std::vector<double> > v;
};

bool SimplexData::set(const int row, const int col, const double val) 
{
    // cout << " " << row << " " << col << " " << row_size << " " << col_size << " " << v.size() << " " << v[row].size() << endl;
    if (row>=0 && row<row_size && col>=0 && col<col_size && row<v.size() && col<v[row].size())
    {
        v[row][col] = val;
        return true;
    }
    return false;
}

double SimplexData::get(const int row, const int col)
{
    // cout << " " << row << " " << col << " " << row_size << " " << col_size << " " << v.size() << " " << v[row].size() << endl;
    if (row>=0 && row<row_size && col>=0 && col<col_size && row<v.size() && col<v[row].size())
    {
        return v[row][col];
    }
    // throw exception("invalid row("+ row + ") and col(" + col + ")");
    // cout << "row: " << row << " col: " << col << endl;
    throw "invalid row and col";
}
#endif // __SIMPLEXDATA_HH__