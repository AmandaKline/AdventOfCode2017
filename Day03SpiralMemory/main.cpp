/*
 * main.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: klineama
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

/* Patterns:
 *   The bottom right corner of each level is an odd square
 *     Of level n, (2n - 1)^2 is the bottom right corner
 *   One to the right of the top left corner is an even square
 *     For level n, this number is (2n)^2
 *   Number of moves = (distance from center of side) + n
 */

int main(){
  int data = 368078;

  int rootSquareBefore = (int)sqrt(data);
  int rootSquareAfter = rootSquareBefore + 1;

  int level = 0;

  //to find level, figure out if it comes after or before the odd square
  if((rootSquareBefore % 2) != 0){
    //if it comes after the odd sqrt, it has the same level as the even sqrt
    level = rootSquareAfter / 2;
  }
  else if((rootSquareAfter % 2) != 0){
    //if it comes before the odd sqrt, it has the same level as the odd sqrt
    level = (rootSquareAfter + 1)/2;
    level--;
  }

  cout << "The data " << data << " is on level n = " << level << endl;

  int sideLen = 2*level + 1;
  int movesToMid = 0;
  int mid = 0;

  if((rootSquareBefore % 2) != 0){
    //if it's on the right or top
    if((pow(rootSquareAfter, 2) - data) < sideLen){
      //if it's on the top
      /**/cout << "top" << endl;
      mid = pow(rootSquareAfter, 2) - sideLen/2 - 1;
      movesToMid = abs(data-mid);
    }
    else if((data - pow(rootSquareBefore, 2)) < sideLen){
      //if it's on the right
      /**/ cout << "right" << endl;
      mid = pow(rootSquareBefore, 2) - sideLen/2;
      movesToMid = abs(data-mid);
    }
    else{
      //it's on the corner
      movesToMid = sideLen/2;
    }
  }
  else if((rootSquareAfter % 2) != 0){
    //if it's on the left or bottom
    if((data-pow(rootSquareBefore, 2)) < sideLen){
      //it's on the left
      /**/ cout << "left" << endl;
      mid = pow(rootSquareBefore, 2) + sideLen/2 + 1;
      movesToMid = abs(data-mid);
    }
    else if((pow(rootSquareAfter, 2)-data) < sideLen){
      //it's on the bottom
      /**/ cout << "bottom" << endl;
      mid = pow(rootSquareAfter, 2) - sideLen/2;
      movesToMid = abs(data-mid);
    }
    else{
      //its on the bottom left corner
      movesToMid = sideLen/2;
    }
  }

  cout << "Mid is " << mid << endl;
  cout << "The data " << data << " is " << movesToMid << " units from the middle" << endl;
  cout << "It will take " << level + movesToMid << " moves" << endl;

}








