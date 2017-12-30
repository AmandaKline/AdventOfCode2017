/*
 * tree.h
 *
 *  Created on: Dec 10, 2017
 *      Author: klineama
 */

#ifndef TREE_H_
#define TREE_H_

#include <string>
#include <vector>

using namespace std;

class Node{
  private:
    string name;
    int weight;
    Node* prev;
    vector<string> unmatchedNext;
    vector<Node*> next;

  public:
    Node(string n, int w, vector<string> v)
      : name(n), weight(w), prev(nullptr), unmatchedNext(v){ }

    string getName() {return name;}
    int getWeight() {return weight;}
    Node* getPrev() {return prev;}
    vector<string> & getUnmatchedNext() {return unmatchedNext;}
    vector<Node*> getNexts() {return next;}


    void setName(string n) {name = n;}
    void setWeight(int w) {weight = w;}
    void setPrev(Node* n) {prev = n;}
    void addNext(Node* n) {
      next.push_back(n);
      for(int i = 0; i < (int)unmatchedNext.size(); ++i){
        if(unmatchedNext[i] == n->getName()){
          unmatchedNext.erase(unmatchedNext.begin()+i);
          i = unmatchedNext.size() + 1;
        }
      }
    }

  };

class Tree{
private:
  Node *root;

  bool isBalanced(Node * n){
    int weight = 0;
    for(Node * ptr : n->getNexts()){
      if(weight == 0)
        weight = towerWeight(ptr);
      else if(weight != towerWeight(ptr))
        return false;
    }

    return true;
  }

public:
  Tree() : root(nullptr) {}

  Tree(Node* n) : root(n) {}

  Node* getRoot(){ return root; }

  //If the current root is pointed to by n, n becomes the new root
  bool setRoot(Node *n){
    //make sure root is pointed to by n
    vector<Node*> nexts = n->getNexts();
    for(Node* next : nexts){
      if(next == root){
        root = n;
        vector<string> unmatchedNexts = n->getUnmatchedNext();
        for(int i = 0; i < (int)unmatchedNexts.size(); ++i){
          if(unmatchedNexts[i] == next->getName()){
            unmatchedNexts.erase(unmatchedNexts.begin()+i);
            i = unmatchedNexts.size() + 1;
          }
        }
        return true;
      }
    }

    return false;
  }

  void buildTree(vector<Node*> & nodes, Node* cur){
    //find all matches for current node
    for(int i = 0; i < (int)cur->getUnmatchedNext().size(); ++i){
      for(int j = 0; j < (int)nodes.size(); ++j){
        if(nodes[j]->getName() == (cur->getUnmatchedNext())[i]){
          nodes[j]->setPrev(cur);
          cur->addNext(nodes[j]);

          Node * temp = nodes[j];
          nodes.erase(nodes.begin()+j);
          //find all matches for newly added node
          buildTree(nodes, temp);

          //reset loop variables because changed size
          j = nodes.size() + 1;
          --i;
        }
      }
    }

    return; //once all unmatchedNexts are matched, return.
  }

  int towerWeight(Node * n){
    if(n->getNexts().empty()){
      return n->getWeight();
    }
    else{
      int sum = 0;
      for(Node * ptr : n->getNexts()){
        sum += towerWeight(ptr);
      }
      return sum + n->getWeight(); //everything on top plus own
    }
  }

  Node * findUnbalanced(Node * n){
    vector<Node*> nexts = n->getNexts();
    for(int i = 0; i < (int)nexts.size(); ++i){
      /**/cout << nexts[i]->getName() << " isBalanced = " << isBalanced(nexts[i]) << endl;
      if(!isBalanced(nexts[i])){
        Node * result = findUnbalanced(nexts[i]);
        if(result == nullptr){
          cout << "unbalanced node: " << n->getName() << endl;
          return n;
        }
        else
          return result;
      }
    }

    //if the current disk isn't unbalanced
    return n;
  }
};

#endif /* TREE_H_ */

//too high: 449
//Too low: 123
