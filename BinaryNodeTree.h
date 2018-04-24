/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT binary
 *  tree.
 *
 *  Adapted from pages 480-482 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Rudolf Musika
 *
 *  @date 19 Apr 2018
 *
 *  @version 7.0 */

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_
#include <memory>
#include "BinaryTreeInterface.h"

/** @class BinaryNodeTree BinaryNodeTree.h "BinaryNodeTree.h"
 *
 *  Specification of a link-based ADT binary tree. */
template <typename ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType> {
protected:
    class BinaryNode;
    using BinaryNodePtr = std::shared_ptr<BinaryNode>;
    
private:
    BinaryNodePtr rootPtr;
    long unsigned int indexNum = 0;
    
protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    
    int getHeightHelper(BinaryNodePtr subTreePtr) const;
    
    int getNumberOfNodesHelper(BinaryNodePtr subTreePtr) const;
    
    // Recursively adds a new node to the tree in a left/right fashion to
    // keep the tree balanced.
    BinaryNodePtr balancedAdd(BinaryNodePtr subTreePtr,
                              BinaryNodePtr newNodePtr);
    
    // Removes the target value from the tree by calling moveValuesUpTree
    // to overwrite value with value from child.
    BinaryNodePtr removeValue(BinaryNodePtr subTreePtr,
                              const ItemType& target,
                              bool& success);
    
    // Copies values up the tree to overwrite value in current node until
    // a leaf is reached; the leaf is then removed, since its value is
    // stored in the parent.
    BinaryNodePtr moveValuesUpTree(BinaryNodePtr subTreePtr);
    
    // Recursively searches for target value in the tree by using a
    // preorder traversal.
    BinaryNodePtr findNode(BinaryNodePtr treePtr,
                           const ItemType& target) const;
    
    // Copies the tree rooted at treePtr and returns a pointer to
    // the copy.
    BinaryNodePtr copyTree(const BinaryNodePtr& treePtr) const;
    
    // Recursive traversal helper methods:
    void preorder(void visit(ItemType&),
                  BinaryNodePtr treePtr);
    void inorder(void visit(ItemType&),
                 BinaryNodePtr treePtr);
    void postorder(void visit(ItemType&),
                   BinaryNodePtr treePtr);
    
    // Tools for manipulating BinaryNodes:
    
    bool isLeaf(const BinaryNodePtr nodePtr) const;
    
    BinaryNodePtr getRootPtr() const;
    void setRootPtr(BinaryNodePtr newRootPtr);
    
    //Display
    void display(BinaryNodePtr RootPtrSit);
    //Tree Helper Display
    void treeHelperDisplay(BinaryNodePtr RootPtrSit,int height) const;
    //flip function
    void fliphelper(BinaryNodePtr rootPtr);
    //flip display
    void flipHelperDisplay(BinaryNodePtr RootPtr,ItemType arry[],long unsigned int numFlipCount);
    //BST Helper
    bool BSTHelper(BinaryNodePtr rootPtr,int min,int max);
    //BST GetMaxHelper
    int getMaxHelper(BinaryNodePtr rootPtr, int max);
    //BST GetMinHelper
    int getMinHelper(BinaryNodePtr rootPtr, int min);
    int min(const ItemType& ,const ItemType&);
    int max(const ItemType& , const ItemType&);
    //Print RootLeafHelper
    void printRootHelper(BinaryNodePtr rootPtr, ItemType arry[], long unsigned int indexPrint);
    //doesSomePathHaveSome Helper
    void doesSomePathHaveSumHelper(BinaryNodePtr rootPtr,ItemType arry[],long unsigned int height, int value, bool& statusCheck);
    //doesTestPathArray
    bool testPathArray(ItemType arry[], long unsigned int length, int sum);

public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    BinaryNodeTree() = default;
    BinaryNodeTree(const ItemType& rootItem);
    BinaryNodeTree(const ItemType& rootItem,
                   const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                   const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
    
    virtual ~BinaryNodeTree() = default;
    
    //------------------------------------------------------------
    // Public BinaryTreeInterface Methods Section.
    //------------------------------------------------------------
    bool isEmpty() const override;
    
    int getHeight() const override;
    
    int getNumberOfNodes() const override;
    
    ItemType getRootData() const override;
    
    void setRootData(const ItemType& newData) override;
    
    bool add(const ItemType& newData) override;
    
    bool remove(const ItemType& data) override;
    
    void clear() override;
    
    ItemType getEntry(const ItemType& anEntry) const override;
    
    bool contains(const ItemType& anEntry) const override;
    
    //------------------------------------------------------------
    // Public Traversals Section.
    //------------------------------------------------------------
    void preorderTraverse(void visit(ItemType&) ) override;
    void inorderTraverse(void visit(ItemType&) ) override;
    void postorderTraverse(void visit(ItemType&) ) override;
    
    //------------------------------------------------------------
    // Overloaded Operator Section.
    //------------------------------------------------------------
    BinaryNodeTree& operator=(const BinaryNodeTree& rhs);
    //------------------------------------------------------------
    // Display contents of the Binary Tree
    //------------------------------------------------------------
    void CallDisplay();
    //------------------------------------------------------------
    // Flip contents of the Binary Tree
    //------------------------------------------------------------
    void flip();
    //------------------------------------------------------------
    // Test if this binary tree contains a binary search tree.
    //------------------------------------------------------------
    bool BST();
    //------------------------------------------------------------
    // Find the minimum and maximum values in this binary tree.
    //------------------------------------------------------------
    int getMax();
    int getMin();
    //------------------------------------------------------------
    // Prints all of the root to leaf paths in this binary tree.
    //------------------------------------------------------------
    void printRootLeaf();
    //------------------------------------------------------------
    //PrintArray
    //------------------------------------------------------------
    void printArray(ItemType pathArryP[],long unsigned int& length);
    //------------------------------------------------------------
    // Test If Path Sums to Sum.
    //------------------------------------------------------------
    bool doesSomePathHaveSum(int value);
};

#include "BinaryNode.h"

#include "BinaryNodeTree.cpp"

#endif
