using namespace std;


#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <stdlib.h> //rand()

int main () {
	int num1;
	int num2;
	int bignum = 9;
	int smallnum = 7;
	for (int i = 1; i <101; ++i){
		if ((i % 20)==0){
			bignum = bignum*10+9;
			smallnum = smallnum*10+1;
		}
		num1 = rand() % bignum + smallnum;
		num2 = rand() % bignum + smallnum;
		cout << num1 << " " << num2 << endl;
	}

}
