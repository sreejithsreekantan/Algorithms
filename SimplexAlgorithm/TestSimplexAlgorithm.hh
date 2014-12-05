/*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/
#ifndef __TESTSIMPLEXALGORITHM_HH__
#define __TESTSIMPLEXALGORITHM_HH__

#include "SimplexAlgorithm.hh"
#include "TestSimplexData.hh"
#include <vector>
#include <limits>
#include <assert.h>

#include <iostream>

using namespace std;


class TestSimplexAlgorithm : public SimplexAlgorithm
{
public:
    virtual bool solve(SimplexData *data, int numOfVariables);
    virtual void printAnswerPath();
    virtual void printAnswer();
private:
    int nextColumnToNormalize() const;
    bool normalize(int pivotRow, int pivotCol) const;
    int pivotRowOfColumn(int col) const;
};

/*
S[1-3]  :   slack variables
L       :   literal values

{       P       X1      X2      X3      S1      S2      S3      L        }
{       1       -1      -3      -4      0       0       0       0        }
{       0       1       0       0       0       0       0       4        }
{       0       0       -1      0       0       0       0       -2       }
{       0       0       0       -1      0       0       0       -3       }
{       0       0       0       1       0       0       0       232      }
{       0       -1      -3      -4      1       0       0       0        }
{       0       0       0       1       0       1       0       1        }
{       0       1       2       0       0       0       1       2        }

*/

void TestSimplexAlgorithm::printAnswer()
{
    int colSize = this->simplexData->colSize();
    cout << "P\t:\t" << this->simplexData->get(0, colSize-1 ) << endl;
    bool isZero;
    int numOfVariables = this->num_of_variables;
    for (int col = 1; col <= colSize-2; ++col)
    {
        isZero = true;
        for (int row = 1; row < this->simplexData->rowSize(); ++row)
        {
            // clog << "row : " << row << " col : " << col << endl; 
            if (this->simplexData->get(row, col) == 1)
            {
                isZero = false;
                if (col <= numOfVariables)
                {
                    cout << "X" << col << "\t:\t" << this->simplexData->get(row, colSize-1 ) << endl;
                }
                else
                {
                    cout << "S" << (col-numOfVariables-1) << "\t:\t" << this->simplexData->get(row, colSize-1 ) << endl;
                }
            }
        }
        if (isZero)
        {
            if (col <= numOfVariables)
            {
                cout << "X" << col << "\t:\t0" << endl;
            }
            else
            {
                cout << "S" << (col-numOfVariables-1) << "\t:\t0" << endl;
            }
        }
    }
}

void TestSimplexAlgorithm::printAnswerPath()
{
    // cout << "this->answer_path.size(): " << this->answer_path.size() << endl;
	for (std::vector<unique_ptr<SimplexData> >::iterator i = this->answer_path.begin(); i != this->answer_path.end(); ++i)
	{
		cout << (*i)->toString() << endl;
	}
}

bool TestSimplexAlgorithm::solve(SimplexData *data, int numOfVariables)
{
    simplexData = data;
    num_of_variables = numOfVariables; 

    
    this->answer_path.push_back(unique_ptr<SimplexData>(new TestSimplexData( *(dynamic_cast<TestSimplexData *>(simplexData)) ) ) );

    int colToNormalize, pivotRow;
    colToNormalize = nextColumnToNormalize();
   

    while ( (colToNormalize = nextColumnToNormalize()) != -1)
    {
    	pivotRow = pivotRowOfColumn(colToNormalize);

        // clog << "pivotRow: " << pivotRow << endl;
        // clog << "colToNormalize: " << colToNormalize << endl;

        // clog << "normalize(pivotRow, colToNormalize): " << normalize(pivotRow, colToNormalize) << endl;
        normalize(pivotRow, colToNormalize);
        this->answer_path.push_back(unique_ptr<SimplexData>(new TestSimplexData( *(dynamic_cast<TestSimplexData *>(simplexData)) ) ) );
        // clog << data->toString() << endl;
    }
    return true;
}

int TestSimplexAlgorithm::pivotRowOfColumn(int col) const
{
    int lCol = simplexData->colSize() - 1;
    int pivotRow = -1;
    double ratioOfPivotElement = numeric_limits<double>::max();
    double rationOfRowTmp;
    for (int rowTmp = 1; rowTmp < simplexData->rowSize(); ++rowTmp)
    {
        // skip the iteration when the ratio is infinity
        if (simplexData->get(rowTmp, col) == 0 && simplexData->get(rowTmp, lCol) != 0)
        {
            // clog << "(skip) ";
            continue;
        }

        rationOfRowTmp = (simplexData->get(rowTmp, lCol) / simplexData->get(rowTmp, col));
        // clog << rationOfRowTmp;
        if (ratioOfPivotElement > rationOfRowTmp )
        {
            // clog << "(yes)";
            pivotRow = rowTmp;
            ratioOfPivotElement = rationOfRowTmp;
        }
        // clog << " ";
    }
    assert(pivotRow != -1);
    return pivotRow;
}

bool TestSimplexAlgorithm::normalize(int pivotRow, int pivotCol) const
{
    const double pivotElement = simplexData->get(pivotRow, pivotCol);
    // clog << "pivotRow: " << pivotRow << " pivotCol: " << pivotCol << endl;
    // clog << "pivotElement: " << pivotElement << endl;
    // clog << simplexData->toString() << endl;
    double multiplyingFactor, tmp;
    for (int i = 0; i < simplexData->rowSize(); ++i)
    {
        if (i == pivotRow) continue; // skip pivot row
        multiplyingFactor = ( simplexData->get(i, pivotCol) / pivotElement );
        // clog << multiplyingFactor << endl;
        for (int j = 0; j < simplexData->colSize(); ++j)
        {
            tmp = simplexData->get(i, j);
            tmp -= (simplexData->get(pivotRow, j) * multiplyingFactor);
            simplexData->set(i, j, tmp);
        }
    }
    // for pivot row, divide through-out with pivot element.
    for (int j = 0; j < simplexData->colSize(); ++j)
    {
        tmp = simplexData->get(pivotRow, j);
        tmp /= pivotElement;
        simplexData->set(pivotRow, j, tmp);
    }
    return true;
}

/*
Return:
    -1  :   no column to normalize
    >=0 :   column number of the column to normalize
*/
int TestSimplexAlgorithm::nextColumnToNormalize() const
{
    int column_to_normalize = -1;   // of row 0
    // possible values: 1 <= column_to_normalize <= num_of_variables
    // set to -1 by default means no column to normalize
    // row is always zero(0)
    for (int col = 1; col <= this->num_of_variables; ++col)
    {
        if (column_to_normalize == -1 && this->simplexData->get(0, col) < 0)
        {
            column_to_normalize = col;
            continue;
        }
        if ( this->simplexData->get(0, col) < 0 &&
                this->simplexData->get(0, col) < this->simplexData->get(0, column_to_normalize) )
        {
            column_to_normalize = col;
        }
    }
    return column_to_normalize;
}

#endif // __TESTSIMPLEXALGORITHM_HH__