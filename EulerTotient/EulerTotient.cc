/*
    Author      :   Sreejith Sreekantan
    Description :   
                    Special Pythagorean triplet
                    Problem 9

                    A Pythagorean triplet is a set of three natural numbers, 
                    a < b < c, for which, a2 + b2 = c2

                    For example, 32 + 42 = 9 + 16 = 25 = 52.

                    There exists exactly one Pythagorean triplet for which 
                    a + b + c = 1000.
                    Find the product abc.

    Eg: for pythagorean triplets:
    (3, 4, 5 )  (5, 12, 13)     (8, 15, 17)     (7, 24, 25)
    (20, 21, 29)    (12, 35, 37)    ( 9, 40, 41)    (28, 45, 53)
    (11, 60, 61)    (16, 63, 65)    (33, 56, 65)    (48, 55, 73)
    (13, 84, 85)    (36, 77, 85)    (39, 80, 89)    (65, 72, 97)
    (20, 99, 101)   (60, 91, 109)   (15, 112, 113)  (44, 117, 125)
    (88, 105, 137)  (17, 144, 145)  (24, 143, 145)  (51, 140, 149)
    (85, 132, 157)  (119, 120, 169)     (52, 165, 173)  (19, 180, 181)
    (57, 176, 185)  (104, 153, 185)     (95, 168, 193)  (28, 195, 197)
    (84, 187, 205)  (133, 156, 205)     (21, 220, 221)  (140, 171, 221)
    (60, 221, 229)  (105, 208, 233)     (120, 209, 241) (32, 255, 257)
    (23, 264, 265)  (96, 247, 265)  (69, 260, 269)  (115, 252, 277)
    (160, 231, 281)     (161, 240, 289)     (68, 285, 293)

*/
#include <iostream>
#include <cmath>


using namespace std;

void pythagoreanTriplet(unsigned long sum)
{
    unsigned long m, n, s=sum;
    s /= 2;
    unsigned long sqrt_s = sqrt(s);
    // cout << "sqrt_s " << sqrt_s << endl;
    for (int m = 1; m <= sqrt_s ; ++m)
    {
        if (s%m==0)
        {
            n = (s/m)-m;
            if (m>n)
            {
                cout << sum << " : " << pow(m,2)-pow(n,2) << " "  
                << 2*m*n << " "  << pow(m,2)+pow(n,2) << endl;
            }
        }
    }

}


int main(int argc, char const *argv[])
{
    unsigned long sums[] = {12, 30, 40, 56, 70, 84, 90, 126, 132, 
                            144, 176, 182, 1000};
    for (int i = 0; i < sizeof(sums)/sizeof(unsigned long); ++i)
    {
            pythagoreanTriplet(sums[i]);
    }

    cout << " the end..." << endl;
    return 0;
}


