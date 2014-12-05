/*
    Author      :       Sreejith Sreekantan
    Date        :       May 2014
    Description :       Rabin-Karp Algorithm
                        Monte Carlo version -   return match if hash match
                        Las Vegas version   -   check for substring match if hash match; continue search if false collision
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

// 839, 913

unsigned int calcHash(const string &array, unsigned int prime, size_t startIndex, size_t psize)
{
    unsigned int tmp = 0;
    for (int i = startIndex; i < startIndex + psize; ++i)
    {
     	tmp += ( (static_cast<int>(array[i])-static_cast<int>('A')) * pow(10,(startIndex + psize - i - 1)) );
        cout << array[i]<<  ( (static_cast<int>(array[i])-static_cast<int>('A')) * pow(10,(startIndex + psize - i - 1)) ) << " ";

        // using below two lines instead of above two lines will also work correctly.
        // tmp += ( (static_cast<int>(array[i])-static_cast<int>('A'))  );
        // cout << array[i]<<  ( (static_cast<int>(array[i])-static_cast<int>('A'))  ) << " ";
        
        tmp %= prime;
    }
    return tmp;
}

int main()
{
	// cout << static_cast<int>('N')-static_cast<int>('A') << endl;
	// exit(0);
    string p = "NEEDLE";
    string s = "FINDINAHAYSTACKNEEDLEINA";

    size_t psize = p.size();
    size_t ssize = s.size();
    unsigned int bigPrime = 997;
    unsigned int pHash = 0;
    unsigned int tmpHash = 0;

    pHash = calcHash(p, bigPrime, 0, psize);
    cout << "pHash = " << pHash << endl;

    tmpHash = calcHash(s, bigPrime, 0, psize);
    cout << "tmpHash = " << tmpHash << endl;
    if (pHash == tmpHash)
    {
        cout << "Match at index " << 0 << " of " << s << endl;
    }

    // cout << psize << " " << ssize << endl;

    for (int i = 1; i < ssize - psize; ++i)
    {
    	copy(&s[i], &s[i+psize], ostream_iterator<char>(cout));
    	cout << " : ";
        tmpHash = calcHash(s, bigPrime, i, psize);
        cout << tmpHash << endl; 

        if (pHash == tmpHash)
        {
            cout << "Match at index " << i << " of " << s << endl;
        }

    }
}


