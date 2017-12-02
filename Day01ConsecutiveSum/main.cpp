/*
 * main.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: klineama
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

int main(){
  string filename = "data.txt";
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()){
    cout << "Error opening file " << filename << endl;
    exit(1);
  }

  string in;
  fin >> in;

  int puzzle = 2;


  if(puzzle == 1){ //correct!
    int sum = 0;
    int prev = in[0], cur = in[1]; //will these convert from chars to ascii values?
    //the ascii value for '1' is 49, for '2' is 50, ...

    for(int i = 1; i < (int)in.length(); ++i){
      cur = in[i];
      if(prev == cur){
        sum += (cur-48);
      }

      prev = cur;
    }

    if(prev == in[0])
      sum += (in[0]-48);

    cout << "The captcha is " << sum << endl;
  }
  else if(puzzle == 2){
    int sum = 0;
    int length = in.length();

    for(int i = 0; i < length/2; ++i){
      if(in[i] == in[i+length/2])
        sum += 2*(in[i]-48);
    }

    cout << "The captcha is " << sum << endl;
  }
}


