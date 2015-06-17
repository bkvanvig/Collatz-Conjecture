// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

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
// collatz_calc
// -------------

/**
 * calculate cycle length of i
 */
int collatz_calc (int i);

// -------------
// populate_cache
// -------------

/**
 * fill in cycle lengths for indicies i-j
 */
void populate_cache (int i, int j);

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

#endif // Collatz_h

using namespace std;
#define CACHE 1

#ifdef CACHE
int init_cache = 0;
unsigned int cache [1000001] = {(unsigned)0};
#endif

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

    if (CACHE && init_cache == 0){
        populate_cache(1, 10000);
        init_cache = 1;
    }

    for (int bound = i; bound<=j; bound++){

        if (CACHE){
           if (cache[bound]!=0)
                curr_cycle_length=cache[bound];
           else {
                curr_cycle_length= collatz_calc(bound);
                cache[bound] = curr_cycle_length;
             } 
        }
        else
            curr_cycle_length = collatz_calc(bound);

        max_cycle_length = curr_cycle_length > max_cycle_length ? curr_cycle_length : max_cycle_length;
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
            i = i + (i>>1) + 1;
            cycle_length+=2;
        }
        else{
            i = i>>1;
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

    while(i<=j){
        cache[i]=collatz_calc(i);
        ++i;
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
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout



// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

/*
% g++-4.8 -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz



% cat RunCollatz.in
1 10
100 200
201 210
900 1000



% RunCollatz < RunCollatz.in > RunCollatz.out



% cat RunCollatz.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/
