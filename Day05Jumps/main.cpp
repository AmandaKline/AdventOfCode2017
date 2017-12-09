/*
 * main.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: klineama
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
  string filename = "data.txt";
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()){
    cout << "Error opening file " << filename << endl;
    exit(1);
  }

  vector<int> instructions;
  int in;
  while(fin >> in){
    instructions.push_back(in);
  }

  int position = 0, jumps = 0;
  while(position  >= 0 && position < (int)instructions.size()){
    int moves = instructions[position];
    ++instructions[position];
    position += moves;

    ++jumps;
  }

  cout << "The instructions take " << jumps << " jumps to complete" << endl;
  // Too low: 400
}



