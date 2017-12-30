/*
 * main.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: klineama
 */

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "tree.h"

using namespace std;

int main(){
  string filename = "data.txt";
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()){
    cout << "Error opening file " << filename << endl;
    return 1;
  }

  //create a vector of all separate Nodes that will be in the tree
  vector<Node*> nodes; //master of all dynamic memory nodes
  string line;
  while(getline(fin, line)){
    istringstream is(line);

    string name;
    string weight;
    int w;
    vector<string> supporting;

    is >> name;
    is >> weight;

    weight = weight.substr(1, weight.length()-2);
    w = stoi(weight);

    string s;
    if(is >> s){//this will be "-->", if there is one
      while(is >> s){
        if(s.back() == ',')
          s.pop_back();
        supporting.push_back(s);
      }
    }

    nodes.push_back(new Node(name, w, supporting));
  }
  /**/ cout << "Finished reading in data. nodes.size() = " << (int)nodes.size() << endl;

  vector<Node*> tempNodes = nodes;
  Tree tree(tempNodes[0]);
  tempNodes.erase(tempNodes.begin());

  //build up from current root
  //cout << "Building initial tree with " << tree.getRoot()->getName() << " as the root" << endl;
  tree.buildTree(tempNodes, tree.getRoot());
  // cout << "Built initial tree. tempNodes.size() = " << (int)tempNodes.size() << endl;

  //loop until nothing in tempNodes, building the tree along the way
  while(tempNodes.size() > 0){
    //find the next backwards node, add to tree
    for(int i = 0; i < (int)tempNodes.size(); ++i){
      vector<string> unmatchedNextNode = tempNodes[i]->getUnmatchedNext();

      //if i points to root
      for(string next : unmatchedNextNode){
        if(!next.compare(tree.getRoot()->getName())){
          // cout << "Found previous program " << tempNodes[i]->getName() << " supporting current root " << tree.getRoot()->getName() << endl;
          tempNodes[i]->addNext(tree.getRoot());
          tree.getRoot()->setPrev(tempNodes[i]);

          tree.setRoot(tempNodes[i]);
          tempNodes.erase(tempNodes.begin()+i);
          --i;

          //cout << "calling buildTree on program " << tree.getRoot()->getName() << endl;
          //build up again from the new bottom node ...
          tree.buildTree(tempNodes, tree.getRoot());
          //cout << "built tree" << endl;
        }
      }
    }

  }

  cout << "The root of the tree is " << tree.getRoot()->getName() << endl;

  //---------------------Part 2-----------------------
  Node * progUnbalanced = tree.findUnbalanced(tree.getRoot());
  /**/ cout << "found unbalanced program" << endl;
  /**/ if(progUnbalanced == nullptr) cout << "It's nullptr" << endl;
  /**/ else cout << "Program: " << progUnbalanced->getName() << endl;
  Node * supporting = progUnbalanced->getPrev();

  vector<int> weights;
  for(Node *ptr : supporting->getNexts()){
    cout << "Adding weight " << tree.towerWeight(ptr) << " to weights<>" << endl;
    weights.push_back(tree.towerWeight(ptr));
  }

  for(int i = 0; i < (int)weights.size(); ++i){
    if(weights[i] == tree.towerWeight(progUnbalanced)){
      weights.erase(weights.begin()+i);
      i = weights.size();
    }
  }

  int amtLess = weights[0]-tree.towerWeight(progUnbalanced);
  cout << "The program " << progUnbalanced->getName() << " needs to weigh " << amtLess << " less" << endl;
  cout << "It currently weighs " << progUnbalanced->getWeight() << endl;

  //delete dynamic nodes
  for(int i = 0; i < (int)nodes.size(); ++i){
    delete nodes[i];
  }

  return 0;
}

