/*
 * main.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: klineama
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
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

  int part = 2;

  string line;
  int numIncorrect = 0;
  int numPhrases = 0;
  while(getline(fin, line)){
    numPhrases++;

    istringstream is(line);

    vector<string> words;
    int index = 0;
    bool incorrect = false;
    string in;

    while(is >> in){
      if(part == 1)
        words.push_back(in);
      else if(part == 2){
        char *temp = const_cast<char*>(in.c_str());
        std::sort(temp, temp+in.length());
        words.push_back(in);
      }

      for(int i = 0; i < index; ++i){
        if(words[index] == words[i] && !incorrect){
          ++numIncorrect;
          incorrect = true;
        }
      }
      ++index;
    }
  }

  cout << "The number of invalid passphrases is " << numIncorrect << endl;
  cout << "The total number of passphrases is " << numPhrases << endl;
  cout << "The number of correct passphrases is " << numPhrases - numIncorrect << endl;

  //Too high: 401    Too low: 110

}


