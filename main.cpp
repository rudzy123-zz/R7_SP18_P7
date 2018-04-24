//
//  main.cpp
//  Project7
//
//  Created by Rudolf Musika on 4/17/18.
//  Copyright © 2018 Rudolf Musika. All rights reserved.
//

#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include <algorithm>
#include <iterator>
int main() {
    BinaryNodeTree<int> Tree;
    Tree.add(5);
    Tree.add(8);
    Tree.add(4);
    Tree.add(3);
    Tree.add(7);
    Tree.add(1);
    Tree.add(2);
    Tree.add(6);
    std::cout<<"To simply display the contents of the Binary Tree\n"<<std::endl;
    Tree.CallDisplay();
   
    std::cout<<"\n------------------------------\n"<<std::endl;
    std::cout<<"\nTo flip the contents of the Binary Tree\n"<<std::endl;
    Tree.flip();
    Tree.CallDisplay();
    std::cout<<"\n------------------------------\n"<<std::endl;
    
    std::cout<<"\nTest if this binary tree contains a binary search tree\n"<<std::endl;
    if (Tree.BST() == true){
        std::cout<<"\nThis is a binary tree that contains a binary search"<<std::endl;
    }
    else{
        std::cout<<"\nThis is a binary tree that does not contain a binary search "<< Tree.BST()<<std::endl;
    }
    
    std::cout<<"\n------------------------------\n"<<std::endl;
    std::cout<<"\nTo find the maximum and minimum values onf Binary Tree\n"<<std::endl;
    std::cout<<"\nTo find the maximum value is \n"<<Tree.getMax()<<std::endl;
    std::cout<<"\nTo find the minimum value is \n"<<Tree.getMin()<<std::endl;
    
    std::cout<<"\n------------------------------\n"<<std::endl;
    std::cout<<"\nPrints all of the root to leaf paths in this binary tree.\n"<<std::endl;
    Tree.flip();
    Tree.CallDisplay();
     std::cout<<"\n------We are looking at that above---\n"<<std::endl;
    Tree.printRootLeaf();
    std::cout<<"\n------------------------------\n"<<std::endl;
    
    std::cout<<"\nTest if this binary tree contains a binary search tree\n"<<std::endl;
    std::cout<<"\nEnter Number you wish to check for sum : ";
    int num;
    std::cin>>num;

    if (Tree.doesSomePathHaveSum(num) == true){
        std::cout<<"\nThis is a binary tree that contains  the sum for the number "<<num<<std::endl;
    }
    else{
        std::cout<<"\nThis is a binary tree that does not contain sum for the number "<< num<<std::endl;
    }
    return EXIT_SUCCESS;
    
}
