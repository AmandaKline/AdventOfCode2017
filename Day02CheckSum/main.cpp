//Amanda Kline
//Dec 2, 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

int main() {
  string filename = "data.txt";
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()){
    cout << "Error opening file " << filename << endl;
    exit(1);
  }

  int part = 2;

  if(part == 1){  //complete!
    int checkSum = 0;
    string line;

    while(getline(fin, line)){
      istringstream is(line);

      int n;
      is >> n;

      int max = n, min = n;

      while(is >> n){
        if(n > max)
          max = n;
        else if(n < min)
          min = n;
      }

      checkSum += (max-min);
    }

    cout << "The checkSum is " << checkSum << endl;
  }
  else if(part == 2){

  }
}
