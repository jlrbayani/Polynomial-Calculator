#ifndef Polynomial_H
#define Polynomial_H

#include <iostream>
#include <cctype> 
#include <string> 
#include <sstream>

using namespace std; 

/**
       Jasper Bayani
       November 20, 2018

       
               This is the header file for the Polynomial class. This holds both the predefined structs Term and Node
               utilized in the Polynomial class. This also contains all the prototyping for all the methods making up    
               the Polynomial class. 
               
**/

/**
      Term -
      A data type which represents a term and holds its coefficient and degree.
**/ 
struct Term{
   int coeff; 
   int degree; 
}; 

/**
      Node -
      A data type which is used to create a linked list for the Polynomial class. It has a
      Term which serves as the node's data and a Node *next which points to the next node 
       for the linked list. 
**/
struct Node {
   Term *term; 
   Node *next; 
}; 

class Polynomial{
   public:
      Polynomial(); 
      Polynomial(int c); 
      Polynomial(int c, int n); 
      int degree() const; 
      int coeff(int n) const; 
      Polynomial readPoly(); 
      friend void printPoly(const Polynomial &p); 
      void deletePoly(); 
      friend const Polynomial operator +(const Polynomial &a, const Polynomial &b);
      friend const Polynomial operator *(const Polynomial &a, const Polynomial &b); 
   
   private:
      Node *poly; 
      friend Node* deleteNode(Node *p); 
      friend void print(Node *p); 
      friend Node* insert(Term t, Node *p); 
      friend Polynomial copyPoly(const Polynomial p); 
      friend Node* copy(Node *p);   
      friend Node* sumPoly(Node *a, Node *b); 
      int getDegree(Node *p) const; 
      int getCoeff(Node *p, int n) const; 
}; 

#endif