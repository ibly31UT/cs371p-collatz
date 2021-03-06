// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
pair<int, int> collatz_read (const string& s);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

// Cache size of 1 million, holds all values that will be given in test cases on SPOJ

int cache[1000000];

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);

    if(i > j){ // if numbers are in descending order, reverse them
        int temp = i;
        i = j;
        j = temp;
    }

    // optimization, skip all prior to j/2
    if(i < j / 2){
        i = j / 2;
    }

    int maxCount = 0;
    for(int x = i; x <= j; x++){
        int tempX = x;
        int count = 1; // initialize at 1 so that we guarantee a minimum count of 1 to replace the maxCount of 0

        if(cache[x] != 0) // if we've calculated it already, return
            return cache[x];

        while(tempX > 1){
            if(tempX < 1000000){
                if(cache[tempX] != 0){ // cache hit
                    count += cache[tempX];
                    break;
                }
            }
            
            if(tempX % 2 == 0){ // if even
                tempX /= 2;
            }else if(tempX * 3 + 1 > 0){ // if odd and it doesnt overflow integer, perform step skipping optimization
                tempX = tempX + (tempX >> 1) + 1;
                count++;
            }else{ // otherwise, increment count and break out of loop because overflow occured.
                count++;
                break;
            }
            count++;
            
        }

        if(count > maxCount) // replace maxCount if necessary
            maxCount = count;
    }

    assert(maxCount > 0);

    return maxCount;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}


// ----
// main
// ----

int main () {
    collatz_solve(cin, cout);
    return 0;}