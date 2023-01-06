#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "bet.h"
using namespace std;

int strSize(const string str){
  int count = 0;
  for(char c: str){
    if(c == ' '){
      count++;
    }
  }
  count++;
  return count;
}

bool operand(const string str){
  int num = 0;
  for(int i = 0; i < str.size(); i++){
    num = str[i];
    if((num > 47 && num < 58) || (num > 64 && num < 91) || (num > 96 && num < 123)){
      continue;
    }else{
      return false;
    }
  }
  return true;
}

int pdt(const string str){
  if(str == "(" || str == ")"){
    return 3;
  } else if(str == "*" || str == "/"){
    return 2;
  } else if(str == "+" || str == "-"){
    return 1;
  } else {
    return 0;
  }
}

void parenthesis(bool & paren){
  if(paren){
    paren = false;
		cout << ") ";
  } 
}

BET::BET(){
  begin = nullptr;
}

BET::BET(const string postfix){
  begin = nullptr;
  buildFromPostfix(postfix);
}

BET::BET(const BET& bet2){
  begin = clone(bet2.begin);
}

BET::~BET(){
  makeEmpty(begin);
}

bool BET::buildFromPostfix(const string postfix){
  string error = "Wrong postfix expression\n";
  
  if(postfix.empty()){
    begin = nullptr;
    //cout << error << " 1" << endl;
    cout << error;
    return false;
  }

  if(!empty()) makeEmpty(begin);

  vector<BinaryNode*> vec;
  string str;
  stringstream stringStream(postfix);
  BinaryNode *tempNode;
  
  for(int i = 0; i < strSize(postfix); i++){
    stringStream >> str;
    tempNode = new BinaryNode(str);
    
    if(operand(str)){
      vec.push_back(tempNode);
    } 
    
    if(pdt(str) > 0){
      if(vec.size() == 1){
        begin = nullptr;
        //cout << error << " 2" << endl;
        cout << error;
        return false;
      }
      (tempNode->left) = vec[vec.size() - 1];
      vec.pop_back();
      (tempNode->right) = vec[vec.size() - 1];
      vec.pop_back();
      vec.push_back(tempNode);
    }
  }

  if(vec.empty()){
    begin = nullptr;
    //cout << error << " 3" << endl;
    cout << error;
    return false;
  }
  
  begin = vec[vec.size() - 1];

  return true;
}

const BET & BET::operator= (const BET & bet2){
  if(this != &bet2){
    makeEmpty(begin);
    begin = clone(bet2.begin);
  }
  return *this;
}

void BET::printInfixExpression(){
  printInfixExpression(begin);
  cout << endl;
}

void BET::printPostfixExpression(){
  printPostfixExpression(begin);
  cout << endl;
}

size_t BET::size(){
  return size(begin);
}

size_t BET::leaf_nodes(){
  return leaf_nodes(begin);
}

bool BET::empty(){
  if(begin == nullptr) return true;
  
  return false;
}

void BET::printInfixExpression(BinaryNode *n){
  if(n == nullptr){
    cout << "BET is empty\n";
    return;
  }
  
  if(((n->left) == nullptr) && ((n->right) == nullptr)){ 
    cout << (n->element) << ' ';
  }else{
    bool paren = false;
    int count = 0, count2 = 0;

    count = pdt(n->element);
    count2 = pdt((n->right)->element);
      
    if(((count > 0) && (count2 > 0)) && (pdt(n->element) >= pdt((n->right)->element))){
			if(pdt(n->element) == 2){
  			cout << "( ";
  			paren = true;
  		}
    }
            
    printInfixExpression(n->right);

    parenthesis(paren);
      
    cout << (n->element) << " ";

    count = pdt(n->element);
    count2 = pdt((n->left)->element);

    if(((count > 0) && (count2 > 0)) && (pdt(n->element) >= pdt((n->left)->element))){
			cout << "( ";
			paren = true;
		}

            
    printInfixExpression(n->left);

    parenthesis(paren);
      
  }
}

void BET::makeEmpty(BinaryNode* &t){
  if(t == nullptr) return;
  else{
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
}

BET::BinaryNode * BET::clone(BinaryNode *t) const{
  if(t == nullptr) return nullptr;

  return new BinaryNode((t->element), clone((t->left)), clone((t->right)));
}

void BET::printPostfixExpression(BinaryNode *n){
  if(size(n) == 0) return;
  
  if(((n->left) != nullptr) && ((n->right) != nullptr)){
    printPostfixExpression((n->right)); 
		printPostfixExpression((n->left)); 
		cout << (n->element) << ' ';
  } else{
    cout << (n->element) << ' ';
  }
}

size_t BET::size(BinaryNode *t){
  if(t == nullptr) return 0; 
  
  return 1 + (size(t->left) + size(t->right));
}

size_t BET::leaf_nodes(BinaryNode *t){
  if(t == nullptr) return 0;
  
  if (((t->left) == nullptr) && ((t->right) == nullptr)) return 1;
  
  return (leaf_nodes(t->left) + leaf_nodes(t->right));
}