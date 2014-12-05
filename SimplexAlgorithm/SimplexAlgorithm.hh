/*
    Author      :   Sreejith Sreekantan
    Date        :   May 2014
    Description :   Simplex algorithm is for linear programming 
*/
#ifndef __SIMPLEXALGORITHM_HH__
#define __SIMPLEXALGORITHM_HH__

#include "SimplexData.hh"
#include <memory>
#include <vector>

using namespace std;

class SimplexAlgorithm {
public:
    virtual bool solve(SimplexData *data, int numOfVariables) = 0;
    virtual void printAnswerPath() = 0;

protected:
	int num_of_variables;
	SimplexData* simplexData;
	std::vector< unique_ptr<SimplexData> > answer_path;
};

#endif // __SIMPLEXALGORITHM_HH__