#include <iostream>
#include <string> 
#include <sstream>
#include "Polynomial.h"

using namespace std; 

/**
       Jasper Bayani
       CPSC 1160 - 003
       November 20, 2018
       Assignment 8
       
               This program utilizes the Polynomial class to create polynomials using the idea of linked lists
               and does basic addition and multiplication. For easier marking, you can just input your terms like: 
               coefficient degree (ie. 1 4  would be equal to 1x^4). 
               
**/

int main(){
   Polynomial p1, p2, p3, p4; 
   p1 = p1.readPoly(); 
   cerr << endl; 
   cerr << "A: "; 
   printPoly(p1);
   cerr << endl; 
   cerr << "The degree of A is: " << p1.degree(); 
   
   cerr << endl; 
   cerr << endl;     
   p2 = p2.readPoly(); 
   
   cerr <<endl; 
   cerr << "B: "; 
   printPoly(p2); 
   cerr << endl; 
   cerr << "The degree of B is: " << p2.degree(); 
   
   cerr <<endl; 
   cerr <<endl; 
   cerr << "The sum of the first and second polynomial is: "; 
   p3 = p1+p2; 
   printPoly(p3);
   
   
   cerr <<endl; 
   cerr <<endl; 
   cerr << "The product of the first and second polynomial is: "; 
   p4 = p1*p2;
   printPoly(p4); 
   cerr << endl; 
   
   p1.deletePoly(); 
   p2.deletePoly(); 
   p3.deletePoly(); 
   p4.deletePoly(); 
   
   return 0; 
}