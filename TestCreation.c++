using namespace std;


#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <stdlib.h> //rand()

int main () {
	int num1;
	int num2;
	int bignum = 9;
	for (int i = 0; i <100; ++i){
		if ((i % 50)==0){
			bignum = bignum*10+9;}
		num1 = rand() % bignum + 1;
		num2 = rand() % bignum + 1;
		cout << num1 << " " << num2 << endl;
	}

}
