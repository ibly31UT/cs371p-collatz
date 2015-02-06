// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

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

    if(i > j){
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
        int count = 1;

        if(cache[x] != 0)
            return cache[x];

        while(tempX > 1){
            if(tempX < 1000000){
                if(cache[tempX] != 0){
                    count += cache[tempX];
                    break;
                }
            }
            
            if(tempX % 2 == 0){
                tempX /= 2;
            }else if(tempX * 3 + 1 > 0){ // if it doesnt overflow integer, perform step skipping optimization
                tempX = tempX + (tempX >> 1) + 1;
                count++;
            }else{ // otherwise, increment count and break out of loop because overflow occured.
                count++;
                break;
            }
            count++;
            
        }

        if(count > maxCount)
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
