//#ifndef BET_H
//#define BET_H
#include <iostream>
using namespace std;

  class BET {
    private:
      struct BinaryNode {
	      string element;
  	    BinaryNode *left;
  	    BinaryNode *right;
  
  	    BinaryNode(const string &theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
        : element{theElement}, left{lt}, right{rt} {}
  	    BinaryNode(string && theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
        : element{std::move(theElement)}, left{lt}, right{rt} {}
  	  };

    public: 
      BET();
      BET(const string postfix);
      BET(const BET&);
      ~BET();
      bool buildFromPostfix(const string postfix);
      const BET & operator= (const BET &);
      void printInfixExpression();
      void printPostfixExpression();
      size_t size();
      size_t leaf_nodes();
      bool empty();

    private:
      BinaryNode * begin;
      void printInfixExpression(BinaryNode *n);
      void makeEmpty(BinaryNode* &t);
      BinaryNode * clone(BinaryNode *t) const;
      void printPostfixExpression(BinaryNode *n);
      size_t size(BinaryNode *t);
      size_t leaf_nodes(BinaryNode *t);
  };

//#include "bet.hpp"
//#endif