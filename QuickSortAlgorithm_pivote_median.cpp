//
//  QuickSort.cpp
//  QuickSortAlgorithm
//
//  Created by Sreejith Sreekantan on 7/13.
//  2013 Sreejith Sreekantan. All rights open.
//
//  Uses divide-n-conquer strategy and promises an O(nlogn) performance.
//  pivot is selected as the median of first,last and middle elements
//  middle element: if even number of elements, then middle element is ((n/2)-1)th element


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

namespace sree {
    using namespace std;
    
    class QuickSort
    {
    public:
        // constructor to read input from terminal.
        QuickSort() {
            unsigned long temp;
            while ( cin >> temp )
            {
                input.push_back(temp);
            }
        }
        
        // constructor to handle input file.
        QuickSort(string filename) {
            unsigned long temp;
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
        unsigned long sort() {
            if (input.size()==0) return 0;
            return sort(0,input.size());
        }
        
        void print() {
            for (auto& a : input) {
                cout << a << " " ;
            }
            cout << endl;
        }
        
        
    private:
        vector<unsigned long> input;
        
        // end is index just after the index of last element. dont try to access index 'end'.
        unsigned long sort(unsigned long start, unsigned long end) {
            // base-condition of array having one element. return 0 as inversion count in this case.
            if (end-start<=1) {
                return 0;
            }
            // number of comparisons = total number of elements - 1 {pivot element compared to all other element}
            unsigned long count = end-start-1; // 'end' is index after the last element, so one more -1
            
            unsigned long pivot_index, i=start+1, j=start+1;
            
            unsigned long temp = end-start, middle;
            middle = start+(temp&1?temp/2:temp/2-1);
            vector<unsigned long> a {input[start], input[middle], input[end-1]};
            std::sort(a.begin(),a.end());
            
            if (a[1]==input[start]) {
                pivot_index = start;
            }
            else if (a[1]==input[middle] ) {
                pivot_index = middle;
            }
            else {
                pivot_index = end-1;
            }
            
            // if pivot_index is not 'start' swap index 'start' with pivot_index and set pivot_index to 'start'
            if (pivot_index != start) {
                swap(input[pivot_index], input[start]);
                pivot_index = start;
            }
            
            for ( ; j<end; j++ ) {
                
                if (input[j]<input[pivot_index]) {
                    swap(input[i], input[j]);
                    //                    print();
                    i++;
                }
            }
            swap(input[pivot_index], input[i-1]); // from now, pivot_index element is at i-1
            //            print();
            
            count += sort( start, i-1);
            
            count += sort( i, end);
            
            return count;
        }
        
        void swap(unsigned long& a, unsigned long& b) {
            unsigned long t=a;
            a=b;
            b=t;
        }
        
    };
}


int main() {
    using namespace std;
    sree::QuickSort qs;
    unsigned long count = qs.sort();
    cout << "Count = " << count << endl;
    qs.print();
    
    
    cout << "main is dying... :( " << endl;
}
