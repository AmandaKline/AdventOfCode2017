//Amanda Kline
//Dec 2, 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
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
    int sum = 0;
    string line;
    vector<int> nums;

    while(getline(fin, line)){
      istringstream is(line);

      // cout << "Read in line " << line << endl;

      int n, length = 0;;
      while(is >> n){
        nums.push_back(n);
        ++length;
      }

      for(int i = 0; i < length; ++i){
        for(int j = 0; j < length; ++j){
          if(nums[i] != nums[j]){
            if(nums[i]%nums[j] == 0){
              // cout << "Adding " << nums[i] << " / " << nums[j] << " = " << nums[i]/nums[j] << endl;
              sum += nums[i]/nums[j];
              i = length;
              j = length;
            }
          }
        }
      }

      nums.clear();
    }

    cout << "The sum is " << sum << endl;

  }
}
