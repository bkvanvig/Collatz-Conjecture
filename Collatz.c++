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

int collatz_eval (int i, int j) {
    // <your code>
    int max_cycle_length = 0;
    int curr_cycle_length = 0;

    if (i>j){
	   int temp = i;
	   i = j;
	   j = temp;
    }
    
    assert (i<=j);
    assert(i>0);

    for (int bound = i; bound<=j; bound++){
        if (cache[bound]!=0)
            curr_cycle_length=cache[bound];
        else{
            curr_cycle_length= collatz_calc(bound);
            cache[bound] = curr_cycle_length;
        }
            
        if (curr_cycle_length>max_cycle_length){
            max_cycle_length=curr_cycle_length;
        }
    }
    assert(max_cycle_length >0);
    return max_cycle_length;}
// -------------
// collatz_calc
// -------------
int collatz_calc (int i){
    int cycle_length = 0;

    while (i != 1){
        if ((i%2)==1){
            i = 3*i+1;
            cycle_length++;
        }
        else{
            i = i/2;
            cycle_length++;
        }
    }
    return cycle_length+1;
}

// -------------
// collatz_calc
// -------------

void populate_cache (int i, int j){
    assert(i > 0);
    assert(i <= 1000000);
    assert(j > 0);
    assert(j <= 1000000);
    if (i>j){
       int temp = i;
       i = j;
       j = temp;
    }
    
    assert (i<=j);

    for (int i; i<=j; i++){
        cache[i]=collatz_calc(i);
    }
    return;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    if (init==0){
        populate_cache(1, 1000); 
        init = 1;
    }
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
