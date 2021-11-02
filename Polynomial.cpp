#include <iostream>
#include <string> 
#include <sstream> 
#include <cctype> 
#include "Polynomial.h"

using namespace std; 

/**
       Jasper Bayani
       November 20, 2018

       
               This is the source file of the Polynomial class. This holds all the implementation for the functions
               within the header file. 
               
**/

/**
      Polynomial()
      input: 
      - none
      output: 
      - creates the zero Polynomial object
**/
Polynomial::Polynomial(){
   poly = new Node{new Term{0, 0}, nullptr}; 
} 

/**
      Polynomial(int c)
      input: 
      c - the value of the coefficient for the constant Polynomial
      output: 
      - creates the constant Polynomial object
**/
Polynomial::Polynomial(int c){
   poly = new Node{new Term{c, 0}, nullptr}; 
} 

/**
      Polynomial(int c, int n)
      input: 
      c - the value of the coefficient for the term of Polynomial
      n - the degree of the term of the Polynomial
      output: 
      - creates a polynomial with a single term containing coefficient with value c and degree with value n
**/   
Polynomial::Polynomial(int c, int n){
   poly = new Node{new Term{c, n}, nullptr}; 
}

/**
      getDegree - a helper function, finds the highest degree of the Polynomial object
                           The Running Time Complexity of this algorithm is O(n)
      input: 
      p - the starting Node of the Polynomial object to be searched through to find the highest degree
      output: 
      - returns -1 if the Node passed in to begin with was a nullptr, otherwise, returns the degree value of the last
         non-nullptr Node within the linked list
**/
int Polynomial::getDegree(Node *p) const{
   if(p == nullptr)
      return -1; 
   if(p->next == nullptr)
      return p->term->degree;
   
   return getDegree(p->next); 
}

/**
      degree - find the highest degree of the Polynomial object
                     The Running Time Complexity of this algorithm is O(n)
      input: 
      - none
      output: 
      - returns the highest degree of the Polynomial or returns -1 if the poly is nullptr 
**/
int Polynomial::degree() const{ 
   return getDegree(poly);  
}

/**
      getCoeff - a helper function, finds the coeffcient of the given degree
      input: 
      p - the starting Node to be used to travaerse the linked list
      n - the degree that needs to be checked
      output: 
      - returns an int which represents the coefficent of the degree being searched for, if the degree does not exist, a 0 is returned instead
**/
int Polynomial::getCoeff(Node *p, int n) const{
   if(p == nullptr)
      return 0; 
   if(p->term->degree == n)
      return p->term->coeff; 
   
   return getCoeff(p->next, n); 
}

/**
      coeff - finds the coeff of the given degree n
      input: 
      n - the degree to be searched for in the linked list
      output: 
      - returns an int which represents the coefficient of the term with the degree n being sarched for, if the degree
      doesn't exist, then 0 is returned 
**/
int Polynomial::coeff(int n) const{
   return getCoeff(poly, n); 
}

/**
      insert - inserts a node into a linked list at the right place at time complexity O(n)
      input: 
      t - the term holding both the coefficient and degree
      p - the starting node to be used to tracerse the linked list
      output: 
      - returns a the same original node but now has the new Node inserted into it 
**/
Node* insert(Term *t, Node *p){
   //add term to end
   if(p == nullptr)
      return new Node{t, p}; 
   //add term to head
   if(t->degree < p->term->degree){
      Node *temp = p; 
      p = new Node{t, temp}; 
      return p;  
   } 
   //add the value of t->coeff to the current p->coeff
   else if(t->degree == p->term->degree){
      p->term->coeff += t->coeff; 
      if(p->term->coeff == 0){
         Node *temp = p->next; 
         delete p; 
         return temp; 
      }
      return p; 
   }
   
   //go through list
   p->next = insert(t, p->next); 
   
   return p; 
}

/**
      readPoly - creates a Polynomial object given user input
      input: 
      - none, it is called by an empty instance of the object caller
      output: 
      - returns a newly created Polynomial from user input
**/
Polynomial Polynomial::readPoly(){
   int numTerms, c, n; 
   string numInput, input = "", values = "";
   Polynomial head;
   Node *p;    
   stringstream ss; 
   
   cerr << "Enter number of terms of the Polynomial: " << endl; 
   cin >> numInput; 
   cin.ignore(); 
   cerr << "            coefficient    degree " << endl; 
   
   numTerms = stoi(numInput); 
   
   for(int i = 1; i <= numTerms; i++){
      cerr << "Enter term " << i << ":"; 
      getline(cin, input);    
      ss << input; 
      ss >> c; 
      ss >> n; 
      ss.clear(); 
      ss.str(""); 
      
      if(i == 1){
         head = Polynomial(c, n);
         p = head.poly;  
      }         
      else{
         Term *t = new Term{c, n}; 
         p = insert(t, p); 
         head.poly = p; 
      }  
   }      
   
   return head; 
}

/**
      print - a helper function, prints all the terms within the linked list of a Polynomial object
      input: 
      p - the starting node to be used to traverse the linked list
      output: 
      - prints out the linked list Polynomial object in the corecct polynomial format
**/
void print(Node *p){
   if(p == nullptr)
      return; 
   
   if(p->term->degree == 0)
      cerr << p->term->coeff << " "; 
   else
      cerr << p->term->coeff << "*x^" << p->term->degree;
   
   if(p->next != nullptr && p->next->term->coeff > 0)
      cerr << " + ";  
   
   print(p->next); 
}

/**
      printPoly - prints the Polynomial object using function print
      input: 
      p - a constant Polynomial whose values will be printed out
      output: 
      - prints the polynomial equation of the Polynomial object onto the console
**/
void printPoly(const Polynomial &p){
   print(p.poly); 
}

/**
      deleteNode - a helper function, deletes the linked list of nodes
      input: 
      p - the starting Node of the linked list
      output: 
      - returns a nullptr
**/
Node* deleteNode(Node *p){
   if(p == nullptr)
      return p; 
   
   p->next = deleteNode(p->next); 
   
   delete p->term;
   p->term = nullptr; 
   delete p;    
   p = nullptr; 
   
   return p; 
}

/**
      deletePoly - deletes the linked list of nodes within the Polynomial object
      input: 
      - none
      output: 
      - sets the poly value of the Polynomial object to nullptr and deletes all nodes and terms within it
**/
void Polynomial::deletePoly(){
   poly = deleteNode(poly); 
}

/**
      copy - a helper function, creates a new linked list of nodes which copies from the passed starting node
      input: 
      p - the starting node of the linked list to be copied 
      output: 
      - returns a Node which is the starting node of the new copied linked list
**/
Node* copy(Node *p){
   if(p == nullptr)
      return nullptr; 
   return new Node{new Term{p->term->coeff, p->term->degree}, copy(p->next)}; 
}

/**
      copyPoly - a function which copies the Polynomial passed in as a parameter
      input: 
      p - the Polynomial to be copied
      output: 
      - returns a  new Polynomial which is an exact copy of p
**/
Polynomial copyPoly(const Polynomial p){
   Polynomial newPoly; 
   newPoly.poly = copy(p.poly); 
   return newPoly; 
}

/**
      sumPoly - a helper function which merges 2 linked lists of nodes from Polynomial objects to mimic addition, 
                       this also deletes unnecessary nodes
                      The Running Time Complexity of this algorithm is O(n + m)
      input: 
      a - the first starting Node to be used to merge
      b - the second starting Node to be used to merge
      output: 
      - returns the linked list of Nodes which now comprises a merge of a and b nodes
**/
Node* sumPoly(Node *a, Node *b){
   if(a == nullptr || (a->term->coeff == 0 && a->term->degree == 0))
      return b; 
   if(b == nullptr || (b->term->coeff == 0 && b->term->degree == 0))
      return a; 
   if(a->term->degree < b->term->degree){
      a->next = sumPoly(a->next, b); 
      return a; 
   }
   else if(a->term->degree > b->term->degree){
      b->next = sumPoly(a, b->next); 
      return b; 
   }
   else{
      int newCoeff = a->term->coeff + b->term->coeff; 
      int tempDegree = a->term->degree; 
      Node *tempA = a->next; 
      Node *tempB = b->next; 
      delete a; 
      delete b; 
      if(newCoeff == 0){
         return sumPoly(tempA, tempB); 
      }
      else{
         Node *n = new Node{new Term{newCoeff, tempDegree}, sumPoly(tempA, tempB)}; 
         return n; 
      }
   }
}

/**
      operator+  -  overloads the operator + to add two Polynomial objects to create a new Polynomial object as the sum
                              The Running Time Complexity of this algorithm is O(n + m)
      input: 
      a - the first Polynomial object to be added
      b - the second Polynomial object to be added to a
      output: 
      sum - returns a new Polynomial object representing the Polynomial sum of a and b
**/
const Polynomial operator +(const Polynomial &a, const Polynomial &b){  
   Polynomial copyA = copyPoly(a); 
   Polynomial copyB = copyPoly(b); 
   Polynomial sum; 
   sum.poly = nullptr; 
   sum.poly = sumPoly(copyA.poly, copyB.poly); 
   
   return sum;  
}

/**
      operator* - this overloads the operator * such that it finds the polynomial product (and creates a Polynomial object for it), 
                           from the two Polynomial objects passed in as parameters and using the Nodes within each object, utilizes the insert function
                           when creating the new product Polynomial
                           The Running Time Complexity of this algorithm is O((n*m)log(n*m))
      input: 
      a - the first Polynomial to be multiplied
      b - the second Polynomial to be multiplied to a
      output: 
      p - the product Polynomial object that is found from multiplying a by b
**/
const Polynomial operator*(const Polynomial &a, const Polynomial &b){
   
   Polynomial p;
   p.poly = nullptr;    
   Node *tempA = a.poly; 
   Node *tempB = b.poly; 
   
   if(tempA != nullptr && (tempA->term->coeff == 0 && tempA->term->degree == 0))
      return Polynomial(); 
   if(tempB != nullptr && (tempB->term->coeff == 0 && tempB->term->degree == 0))
      return Polynomial(); 
   
   while(tempB != nullptr){
      while(tempA != nullptr){
         Term *t = new Term{tempA->term->coeff*tempB->term->coeff, tempA->term->degree + tempB->term->degree}; 
         p.poly = insert(t, p.poly); 
         tempA = tempA->next; 
      }
      tempB = tempB->next; 
      tempA = a.poly; 
   }
   
   return p; 
}











