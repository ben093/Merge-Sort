// CSC 325 - Spring 2015 - Homework 1

// Complete this program where indicated so that it solves Problem 2-4
// on page 41. Do not modify any of the other code. The program reads
// zero or more integers from standard input into a vector, then
// counts the number of inversions using a modified mergesort. So the
// vector is sorted at the end, but we really care about the number of
// inversions. Your program must run in worst-case time O(n log n).
//
// If you test your program by entering numbers from the keyboard (the
// default standard input), remember that <Ctrl-Z><Enter> signals EOF
// from the keyboard on Windows and <Ctrl-D> signals EOF from the
// keyboard on Mac and Linux. Or create files of numbers and use the
// redirection operators. See the links on my web page for a reminder.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using count_t = uint64_t;

vector<int> A;                  // the ints read from standard input
vector<int> B;                  // temporary vector used for merging

//g++ -std=c++11 -Wall h1.cpp

count_t mergesortAndCountInversions(int p, int r) {
    // note: r is an inclusive upper bound

    if (p >= r)
        // subarray has length at most 1: already sorted, no inversions
        return 0;
    else {
        int q = (p + r)/2;
        auto a = mergesortAndCountInversions(p, q);
        auto c = mergesortAndCountInversions(q + 1, r);
        count_t b = 0;  // inversions *between* the two sorted halves

        // copy the subarray from A into B
        copy(begin(A) + p, begin(A) + r + 1, begin(B) + p);

        // Merge the two halves from B back into A, also counting the
        // inversions *between* the two halves, where one element is
        // in the left half and the other is in the right half. (The
        // inversions within each half have already been counted via
        // the recursive calls.) You must count the inversions between
        // the halves in linear time, i.e., O(r - p + 1). You can
        // exploit the fact that the two halves are sorted.

        // YOUR CODE HERE!		
		int left_end = q;
		int right_end = r;
		
		//going from B[p...q] and B[q+1...r]. Iterate q once to start the right side in the correct location.
		q += 1;
		
		//k will be the index of A[].
		int k = p;
		
		//cout << "A[" << k << "]" << endl;
		
		//loop while p isn't to the end of the left 'side' and q isn't to the end of the right 'side'
		while( p <= left_end && q <= right_end )
		{	//if the value at index p is less than or equal to value at q
			if(B[p] <= B[q])
			{
				//assign the value at index p in B[] to the index k in A[]
				A[k] = B[p];
				p++;
			}
			else
			{
				//assign the value at index q in B[] to the index k in A[]
				A[k] = B[q];
				q++;
				
				//add inversions, this will only be hit when B[p] > B[q], and q will always be greater than p.
				b += left_end - p + 1;
			}
			
			//iterate k on each loop
			k++;
		}
		
		//add remainder of left side to A[]
		while( p <= left_end )
		{
			A[k] = B[p];
			p++;
			k++;
		}
		//add remainder of right side to A[]
		while( q <= right_end )
		{
			A[k] = B[q];
			q++;
			k++;
		}
		
        return a + b + c;
    }
}


int main () {
    int number;

    while (cin >> number) {
        A.push_back(number);
    }

    // B is a copy of A; all that really matters is that it's the same size
    B = A;

    cout << mergesortAndCountInversions(0, A.size() - 1) << endl;

    for (size_t i = 1; i < A.size(); ++i) 
	{
        if (A[i - 1] > A[i]) {
            cout << "Array is NOT sorted!" << endl;
            break;
        }
    }
}