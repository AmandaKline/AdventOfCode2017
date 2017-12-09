/*
 * main.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: klineama
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){
  string filename = "data.txt";
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()){
    cout << "Error opening file " << filename << endl;
    return 1;
  }

  vector<int> banks;
  int in;
  while(fin>>in){
    banks.push_back(in);
  }

  int part = 2;
  int times;
  if(part == 1)
    times = 1;
  else if(part == 2)
    times = 2;


  while(times > 0){
    vector<vector<int>> situations;
    int count = 0;
    while(find(situations.begin(), situations.end(), banks) == situations.end()){
      situations.push_back(banks);

      int maxIndex = 0;
      for(int i = 0; i < (int)banks.size(); ++i){
        if(banks[i] > banks[maxIndex])
          maxIndex = i;
      }

      int blocks = banks[maxIndex];
      banks[maxIndex] = 0;
      int i = maxIndex;
      while(blocks > 0){
        i = (i + 1) % banks.size();
        ++banks[i];
        --blocks;
      }

      ++count;
    }

    cout << "It takes " << count << " iterations to encounter a repeat" << endl;
    --times;
  }
}



