/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a node in the pointer-based implementation of the
 *  ADT binary tree.
 *
 *  Adapted from page 478 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 27 Mar 2018
 *
 *  @version 7.0 */

#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>
#include "BinaryNodeTree.h"

/** @class BinaryNode BinaryNode.h "BinaryNode.h"
 *
 *  Specification of the nested node type for a linked-chain based ADT
 *  binary tree. */
template <typename ItemType>
class BinaryNodeTree<ItemType>::BinaryNode {

public:
    ItemType item;
    
    using BinaryNodePtr = std::shared_ptr<BinaryNode>;
    
    BinaryNodePtr leftChildPtr;
    BinaryNodePtr rightChildPtr;
    
    BinaryNode(const ItemType& anItem,
               BinaryNodePtr leftPtr = nullptr,
               BinaryNodePtr rightPtr = nullptr);
    
#ifdef DTOR_TEST
    virtual ~BinaryNode();
#else
    virtual ~BinaryNode() = default;
#endif
};

#include "BinaryNode.cpp"

#endif
