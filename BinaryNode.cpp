//
//  BinaryNode.cpp
//  Project7
//
//  Created by Rudolf Musika on 4/17/18.
//  Copyright © 2018 Rudolf Musika. All rights reserved.
//


template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNode::BinaryNode(const ItemType& anItem,
                                                 BinaryNodePtr leftPtr,
                                                 BinaryNodePtr rightPtr ){
    this->item = anItem;
    this->leftChildPtr = leftPtr;
    this->rightChildPtr = rightPtr;
}
