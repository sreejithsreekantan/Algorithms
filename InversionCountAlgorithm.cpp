//
//  InversionCount.cpp
//  InversionCountAlgorithm
//
//  Created by Sreejith Sreekantan on 7/13.
//  2013 Sreejith Sreekantan. All rights open.
//
// Uses divide-n-conquer strategy and promises an O(nlogn) performance.

#include "InversionCount.h"

#include <vector>
#include <string>
#include <fstream>

namespace sree {
    using namespace std;
    
    class InversionCount
    {
    public:
        // constructor to read input from terminal.
        InversionCount() {
            int temp;
            while ( cin >> temp )
            {
                input.push_back(temp);
            }
        }
        
        // constructor to handle input file.
        InversionCount(string filename) {
            int temp;
            ifstream ifile(filename.c_str());
            if (!ifile.is_open()) {
                clog << "ERROR: failed to open. " << filename << endl;
            }
            while ( ifile >> temp )
            {
                input.push_back(temp);
            }
            if (input.size()==0) {
                clog << "ERROR: no input found. " << endl;
            }
        }
        
        // assumption: 'input' vector is already populated with input-values to start processing
        //              function doesn't raise any error and returns '0' if assumption is not satisfied
        uint getTotalNumOfInvCounts() {
            if (input.size()==0) return 0;
            return getNumOfInvCounts(0,(uint)input.size());
        }
        
        
    private:
        vector<int> input;
        
        int mergeAndCount(uint start1, uint end1, uint start2, uint end2) {
            uint count = 0;
        
            uint i = start1, j = start2; //indexes to iterate over two sub arrays; initialized both to start of two sub-arrays.
            vector<int> temp_v; // temporary vector to store the sorted elements, will be copied back to 'input' before leaving this function.
            
            // go through both the sub-arrays to check inversions across them.
            for (; i<end1 && j<end2; ) {
                // if an element of first sub-array is greater than that of second, it means all the sub-sequent elements
                // of first sub-array will also make inversions with that element of second sub-array.
                if (input[i]>input[j]) {
                    count += (end1-i);
                    // to print out the inversion pairs.
                    for (int k = i; k<end1; k++) {
                        cout << "( " << input[k] << ", " << input[j] << ") ";
                    }
                    temp_v.push_back(input[j]);
                    j++;
                }
                else { //(input[i]<=input[j])
                    temp_v.push_back(input[i]);
                    i++;
                }
            }
            // Iterate over the rest of first-array-elements if any and add it to 'temp_v'.
            for (; i<end1; ) {
                temp_v.push_back(input[i]);
                i++;
            }
            
            // Iterate over the rest of second-array-elements if any and add it to 'temp_v'.
            for (; j<end2; ) {
                temp_v.push_back(input[j]);
                j++;
            }
            
            // copying 'temp_v' to 'input' vector.
            i = start1; // starting index to put elements from.
            for (vector<int>::const_iterator iter = temp_v.begin(),end_iter = temp_v.end(); iter!=end_iter; iter++) {
                input[i++] = *iter;
            }
            return count;
        }
        
        // end is index just after the index of last element. dont try to access index 'end'.
        int getNumOfInvCounts(uint start, uint end) {
            // base-condition of array having one element. return 0 as inversion count in this case.
            if (end-start <= 1) {
                return 0;
            }
            
            //  if array have more than one element, go for a divide-n-conquer strategy.
            uint x=0,y=0,z=0;
            
            // finding the middle of two arrays.
            uint temp = start+(end-start)/2;
            
            // get inversion count for left sub-array.
            x=getNumOfInvCounts(start,temp);
            // get inversion count for left sub-array.
            y=getNumOfInvCounts(temp, end);
            // merge the left and right sub-arrays and return the inversions across two sub-arrays.
            z = mergeAndCount(start, temp, temp, end);
            
            return x+y+z;
        }

    };
}


int main() {
    using namespace std;
    sree::InversionCount ic("/Users/Sreejith_S03/Desktop/sreejith/workspace/xcode4.6/testBoostLib1/testBoostLib1/inp1.txt");
    cout << "Inversion Pairs = "; 
    int inv_count = ic.getTotalNumOfInvCounts();
    cout << endl;
    cout << "Inversion Count = " << inv_count << endl;
    cout << "main is dying... :( " << endl;
}
