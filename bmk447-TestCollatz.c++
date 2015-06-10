// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_EXPECTions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}
TEST(CollatzFixture, read_2) {
    string s("100000 1000000\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 100000, p.first);
    ASSERT_EQ(1000000, p.second);}
TEST(CollatzFixture, read_3) {
    string s("999999 1000000\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 999999, p.first);
    ASSERT_EQ(1000000, p.second);}
TEST(CollatzFixture, read_4) {
    string s("827599 977399\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(827599, p.first);
    ASSERT_EQ(977399, p.second);}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

// ----
// calc
// ----
TEST(CollatzFixture, calc_1) {
    const int v = collatz_calc(5);
    ASSERT_EQ(6, v);}

TEST(CollatzFixture, calc_2) {
    const int v = collatz_calc(10);
    ASSERT_EQ(7, v);}

TEST(CollatzFixture, calc_3) {
    const int v = collatz_calc(27);
    ASSERT_EQ(112, v);}

TEST(CollatzFixture, calc_4) {
    const int v = collatz_calc(999);
    ASSERT_EQ(50, v);}
TEST(CollatzFixture, calc_5) {
    const int v = collatz_calc(999999);
    ASSERT_EQ(259, v);}

// -----
// print
// -----

TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}
TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 10, 100, 2000);
    ASSERT_EQ("10 100 2000\n", w.str());}
TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 1000000, 1000000, 1000000);
    ASSERT_EQ("1000000 1000000 1000000\n", w.str());}

TEST(CollatzFixture, print_4) {
    ostringstream w;
    collatz_print(w, 999999, 999999, 999999);
    ASSERT_EQ("999999 999999 999999\n", w.str());}


// -----
// solve
// -----

TEST(CollatzFixture, solve_1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    EXPECT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(CollatzFixture, solve_2) {
    istringstream r("1 1\n11 11\n555555 555555\n999999 999999\n");
    ostringstream w;
    collatz_solve(r, w);
    EXPECT_EQ("1 1 1\n11 11 15\n555555 555555 147\n999999 999999 259\n", w.str());}
TEST(CollatzFixture, solve_3) {
    istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    ostringstream w;
    collatz_solve(r, w);
    EXPECT_EQ("10 1 20\n200 100 125\n210 201 89\n1000 900 174\n", w.str());}
TEST(CollatzFixture, solve_4) {
    istringstream r("1 100000\n333331 333332\n333333 333335\n666666 666667\n");
    ostringstream w;
    collatz_solve(r, w);
    EXPECT_EQ("1 100000 351\n333331 333332 154\n333333 333335 154\n666666 666667 155\n", w.str());}

/*
% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.8 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz        >  TestCollatz.out 2>&1
% gcov-4.8 -b Collatz.c++     >> TestCollatz.out
% gcov-4.8 -b TestCollatz.c++ >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
...
*/
