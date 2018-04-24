/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT binary
 *  tree.
 *
 *  Adapted from pages 482-491 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Rudolf Musika
 *
 *  @date 19 Apr 2018
 *
 *  @version 7.0 */

#include <algorithm> // For std::max
#include <iostream>
#include <memory>
#include <new>
#include <iomanip>
#include <climits>
#include <iterator>

#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNodePtr subTreePtr) const {
    
    int height(0);
    
    if (subTreePtr) {
        height = 1 + std::max(getHeightHelper(subTreePtr->leftChildPtr),
                              getHeightHelper(subTreePtr->rightChildPtr) );
    }
    return height;
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNodePtr subTreePtr) const {
    
    int numNodes(0);
    
    if (subTreePtr) {
        numNodes = 1 +
        getNumberOfNodesHelper(subTreePtr->leftChildPtr) +
        getNumberOfNodesHelper(subTreePtr->rightChildPtr);
    }
    return numNodes;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::balancedAdd(BinaryNodePtr subTreePtr,
                                      BinaryNodePtr newNodePtr) {
    
    auto returnPtr(newNodePtr);
    
    if (subTreePtr) {
        auto leftPtr(subTreePtr->leftChildPtr);
        auto rightPtr(subTreePtr->rightChildPtr);
        
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr) ) {
            subTreePtr->rightChildPtr = balancedAdd(rightPtr,
                                                    newNodePtr);
        }
        else {
            subTreePtr->leftChildPtr = balancedAdd(leftPtr,
                                                   newNodePtr);
        }
        
        returnPtr = subTreePtr;
    }
    
    return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNodePtr subTreePtr) {
    
    BinaryNodePtr returnPtr;
    
    if (isLeaf(subTreePtr) ) {
        subTreePtr.reset();
    }
    else {
        auto leftPtr(subTreePtr->leftChildPtr);
        auto rightPtr(subTreePtr->rightChildPtr);
        
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr) ) {
            subTreePtr->item =  leftPtr->item;
            subTreePtr->leftChildPtr = moveValuesUpTree(leftPtr);
        }
        else {
            subTreePtr->item = rightPtr->item;
            subTreePtr->rightChildPtr = moveValuesUpTree(rightPtr);
        }
        
        returnPtr = subTreePtr;
    }
    
    return returnPtr;
}

/** Depth-first search of tree for item.
 *
 *  @param subTreePtr The tree to search.
 *
 *  @param target The target item to find.
 *
 *  @param success Communicate to client whether we found the target.
 *
 *  @return A pointer to the node containing the target. */
template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::removeValue(BinaryNodePtr subTreePtr,
                                      const ItemType& target,
                                      bool& success) {
    
    BinaryNodePtr returnPtr;
    
    if(subTreePtr) {
        if (subTreePtr->item == target) {
            subTreePtr = moveValuesUpTree(subTreePtr);
            success = true;
        }
        else {
            subTreePtr->leftChildPtr = removeValue(subTreePtr->leftChildPtr,
                                                   target,
                                                   success);
            if (!success) {
                subTreePtr->rightChildPtr = removeValue(subTreePtr->rightChildPtr,
                                                        target,
                                                        success);
            }
        }
        
        returnPtr = subTreePtr;
    }
    
    return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::findNode(BinaryNodePtr subTreePtr,
                                   const ItemType& target) const {
    
    BinaryNodePtr returnPtr;
    
    if (subTreePtr) {
        if (subTreePtr->item == target) {
            returnPtr = subTreePtr;
        }
        else {
            returnPtr = findNode(subTreePtr->leftChildPtr,
                                 target);
            if (!returnPtr) {
                returnPtr = findNode(subTreePtr->rightChildPtr,
                                     target);
            }
        }
    }
    
    return returnPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::copyTree(const BinaryNodePtr& subTreePtr) const {
    
    BinaryNodePtr newTreePtr;
    
    // Copy tree nodes using a preorder traversal
    if (subTreePtr) {
        newTreePtr = std::make_shared<BinaryNode>(subTreePtr->item,
                                                  copyTree(subTreePtr->leftChildPtr),
                                                  copyTree(subTreePtr->rightChildPtr) );
    }
    
    return newTreePtr;
}

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&),
                                        BinaryNodePtr subTreePtr) {
    
    if (subTreePtr) {
        visit(subTreePtr->item);
        
        preorder(visit, subTreePtr->leftChildPtr);
        preorder(visit, subTreePtr->rightChildPtr);
    }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&),
                                       BinaryNodePtr subTreePtr) {
    
    if (subTreePtr) {
        inorder(visit, subTreePtr->leftChildPtr);
        
        visit(subTreePtr->item);
        
        inorder(visit, subTreePtr->rightChildPtr);
    }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&),
                                         BinaryNodePtr subTreePtr) {
    
    if (subTreePtr) {
        postorder(visit, subTreePtr->leftChildPtr);
        postorder(visit, subTreePtr->rightChildPtr);
        
        visit(subTreePtr->item);
    }
}

//////////////////////////////////////////////////////////////
//      Protected Node Access Sub-Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isLeaf(BinaryNodePtr nodePtr) const {
    
    return !nodePtr->leftChildPtr && !nodePtr->rightChildPtr;
}

template <typename ItemType>
std::shared_ptr<typename BinaryNodeTree<ItemType>::BinaryNode>
BinaryNodeTree<ItemType>::getRootPtr() const {
    
    return rootPtr;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootPtr(BinaryNodePtr newRootPtr) {
    
    rootPtr = newRootPtr;
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
: rootPtr(std::make_shared<BinaryNode>(rootItem) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
: rootPtr(std::make_shared<BinaryNode>(rootItem,
                                       copyTree(leftTreePtr->rootPtr),
                                       copyTree(rightTreePtr->rootPtr)) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr) {
    
    try {
        rootPtr = copyTree(treePtr.rootPtr);
    }
    catch (const std::bad_alloc&) {
        clear();
        throw;
    }
}

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {
    
    return !rootPtr;
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {
    
    return getHeightHelper(rootPtr);
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {
    
    return getNumberOfNodesHelper(rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::clear() {
    
    rootPtr.reset();
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const {
    
    if (isEmpty() ) {
        std::string message("BinaryNodeTree::getRootData: called ");
        message += "on an empty tree.";
        
        throw PrecondViolatedExcep(message);
    }
    
    return rootPtr->item;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem) {
    
    if (isEmpty() ) {
        try {
            rootPtr = std::make_shared<BinaryNode>(newItem);
        }
        catch (const std::bad_alloc&) {
            // What should we do with this? Return something? Throw a
            // different type of exception? Crash?
        }
    }
    else {
        rootPtr->item = newItem;
    }
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData) {
    
    bool canAdd(true);
    try {
        rootPtr = balancedAdd(rootPtr,
                              std::make_shared<BinaryNode>(newData) );
    }
    catch (const std::bad_alloc&) {
        canAdd = false;
    }
    return canAdd;
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target) {
    
    bool isSuccessful(false);
    rootPtr = removeValue(rootPtr, target, isSuccessful);
    return isSuccessful;
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const {
    
    auto binaryNodePtr(findNode(rootPtr, anEntry) );
    
    if (!binaryNodePtr) {
        std::string message("BinaryNodeTree::getEntry: Entry ");
        message += "not found in this tree.";
        throw NotFoundException(message);
    }
    return binaryNodePtr->item;
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const {
    
    return findNode(rootPtr, anEntry) != nullptr;
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&) ) {
    
    preorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&) ) {
    
    inorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&) ) {
    
    postorder(visit, rootPtr);
}

//////////////////////////////////////////////////////////////
//      Overloaded Operator
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>&
BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rhs) {
    
    auto oldTreePtr(rootPtr);
    
    if (this != &rhs) {
        try {
            rootPtr = copyTree(rhs.rootPtr);
            oldTreePtr.reset();
        }
        catch (const std::bad_alloc&) {
            rootPtr.reset();
            rootPtr = oldTreePtr;
            throw;
        }
    }
    
    return *this;
}
//////////////////////////////////////////////////////////////
//      Display contents of the Binary Tree
//////////////////////////////////////////////////////////////
template <typename ItemType>
void BinaryNodeTree<ItemType>::CallDisplay(){
    display(rootPtr);
}
template <typename ItemType>
void BinaryNodeTree<ItemType>::display(BinaryNodeTree::BinaryNodePtr RootPtrSit){
    if (RootPtrSit == nullptr){
        return;
    }
    treeHelperDisplay(rootPtr, 0);
}
template <typename ItemType>
void BinaryNodeTree<ItemType>::treeHelperDisplay(BinaryNodePtr node,int height ) const{
    if (node->leftChildPtr != nullptr){ // is left child
        treeHelperDisplay(node->leftChildPtr, height+1);
    }
    
    for(int i(0); i<=height; i++){
        std::cout<<" ";
    }
        std::cout<< node->item << "\n";
    if (node->rightChildPtr != nullptr){// is right child
        treeHelperDisplay(node->rightChildPtr, height+1);
    }
}

//////////////////////////////////////////////////////////////
// Flip (or mirror) the nodes in this binary tree left-to-right.
//////////////////////////////////////////////////////////////
template <typename ItemType>
void BinaryNodeTree<ItemType>::flip(){
    fliphelper(rootPtr);
}
template<typename ItemType>
void BinaryNodeTree<ItemType>::fliphelper(BinaryNodePtr rootPtr){
    if (rootPtr!= nullptr){// is right child
        BinaryNodePtr temp;
        temp = rootPtr->rightChildPtr;
        rootPtr->rightChildPtr = rootPtr->leftChildPtr;
        rootPtr->leftChildPtr = temp;
        fliphelper(rootPtr->rightChildPtr);
        fliphelper(rootPtr->leftChildPtr);
    }
//    long unsigned int height = getHeight();
//    ItemType pathArray[height];
//    flipHelperDisplay(rootPtr, pathArray, indexNum);
}
template<typename ItemType>
void BinaryNodeTree<ItemType>::flipHelperDisplay(BinaryNodePtr nodePtr,ItemType arry[], unsigned long int numCount){
    arry[indexNum] = nodePtr->item;
    ++indexNum;
    if (nodePtr->leftChildPtr != nullptr){ // is left child
        printArray(arry, indexNum);
        flipHelperDisplay(nodePtr->leftChildPtr, arry,++numCount);
        --numCount;
    }
    for(int i(0); i<=numCount; i++){
        std::cout<<"|";
    }
    if (nodePtr->rightChildPtr != nullptr){ // is right child
        printArray(arry, indexNum);
        flipHelperDisplay(nodePtr->rightChildPtr, arry,++numCount);
        --numCount;
    }
    if(nodePtr->leftChildPtr == nullptr && nodePtr->rightChildPtr == nullptr){
        printArray(arry,indexNum);
    }
}
//////////////////////////////////////////////////////////////
//Test if this binary tree contains a binary search tree.
//////////////////////////////////////////////////////////////
template<typename ItemType>
bool BinaryNodeTree<ItemType>::BST(){
    bool value;
    value = BSTHelper(rootPtr, INT_MIN, INT_MAX);
    return value;
}
template<typename ItemType>
bool BinaryNodeTree<ItemType>::BSTHelper(BinaryNodePtr rootPtr, int min, int max){
    if(rootPtr == NULL){
        return 1;
    }
    else{
        if(rootPtr->item>max || rootPtr->item < min)
            return 0;
        return BSTHelper(rootPtr->leftChildPtr, min, rootPtr->item+1)&&
        BSTHelper(rootPtr->rightChildPtr, rootPtr->item-1, max);
    }
}

//////////////////////////////////////////////////////////////
//Find the minimum and maximum values in this binary tree.
//////////////////////////////////////////////////////////////
template<typename ItemType>
int BinaryNodeTree<ItemType>::min(const ItemType& item1, const ItemType& item2){
    ItemType returnVal = item1;
    if (item2<item1){
        returnVal = item2;
    }
    return returnVal;
}
template<typename ItemType>
int BinaryNodeTree<ItemType>::max(const ItemType& item1, const ItemType& item2){
    ItemType returnVal = item1;
    if (item2>item1){
        returnVal = item2;
    }
    return returnVal;
}
template <typename ItemType>
int BinaryNodeTree<ItemType>::getMax(){
    if (rootPtr==NULL) {
        std::string message("BinaryNodeTree::getRootData: called ");
        message += "on an empty tree.";
        
        throw PrecondViolatedExcep(message);
    }
    int numCheck(rootPtr->item);
    
    return getMaxHelper(rootPtr,numCheck);
}
template <typename ItemType>
int BinaryNodeTree<ItemType>::getMin(){
    if (rootPtr==NULL) {
        std::string message("BinaryNodeTree::getRootData: called ");
        message += "on an empty tree.";
        
        throw PrecondViolatedExcep(message);
    }
    int numCheck(rootPtr->item);
   return getMinHelper(rootPtr,numCheck);
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getMaxHelper(BinaryNodePtr nodePtr, int maxNum){
    if (nodePtr==NULL){
        return maxNum;
    }
    else{
        maxNum = max(nodePtr->item, maxNum);
        maxNum = getMaxHelper(nodePtr->leftChildPtr, maxNum);
        maxNum = getMaxHelper(nodePtr->rightChildPtr, maxNum);
        return maxNum;
    }
}
template <typename ItemType>
int BinaryNodeTree<ItemType>::getMinHelper(BinaryNodePtr nodePtr, int minNum){
    if (nodePtr==NULL){
        return minNum;
    }
    else{
        minNum = min(nodePtr->item, minNum);
        minNum = getMinHelper(nodePtr->leftChildPtr, minNum);
        minNum = getMinHelper(nodePtr->rightChildPtr, minNum);
        return minNum;
    }
}

//////////////////////////////////////////////////////////////
//Prints all of the root to leaf paths in this binary tree.
//////////////////////////////////////////////////////////////
template<typename ItemType>
void BinaryNodeTree<ItemType>::printRootLeaf(){
    if (rootPtr == nullptr) {
        std::string message("Tree can't be empty");
        message += "on an empty tree.";
        throw PrecondViolatedExcep(message);
    }
    
   long unsigned int height = getHeight();
    ItemType pathArray[height];
    printRootHelper(rootPtr, pathArray, indexNum);
}

template<typename ItemType>
void BinaryNodeTree<ItemType>::printRootHelper(BinaryNodePtr nodePtr, ItemType arry[] , long unsigned int indexPrint) {
    arry[indexNum] = nodePtr->item;
    ++indexNum;
    
    if(nodePtr->leftChildPtr != nullptr){// is left child
        printRootHelper(nodePtr->leftChildPtr, arry, indexNum);
        --indexNum;
    }

    if(nodePtr->rightChildPtr!=nullptr ){// is right child
        printRootHelper(nodePtr->rightChildPtr, arry,  indexNum);
        --indexNum;
    }
    if(nodePtr->leftChildPtr == nullptr && nodePtr->rightChildPtr == nullptr){
        printArray(arry,indexNum);
    }
}

template<typename ItemType>
void BinaryNodeTree<ItemType>::printArray(ItemType pathArrayP[], long unsigned int& length){

    for(long unsigned int i(0); i<length; ++i){
        std::cout<<pathArrayP[i]<<" ";
    }
    std::cout<<std::endl;
}

//////////////////////////////////////////////////////////////
//Test to see if the nodes in some path in this binary tree contains a given sum.
//////////////////////////////////////////////////////////////
template<typename ItemType>
bool BinaryNodeTree<ItemType>::doesSomePathHaveSum(int value){
    if (rootPtr==NULL) {
        std::string message("BinaryNodeTree::getRootData: called ");
        message += "on an empty tree.";
        
        throw PrecondViolatedExcep(message);
    }
    bool result(false);
    int start(0);
    long unsigned int height = getHeight();
    ItemType pathArray[height];
    doesSomePathHaveSumHelper(rootPtr,pathArray,start, value,result);
    return result;
}
template<typename ItemType>
bool BinaryNodeTree<ItemType>::testPathArray(ItemType arr[], long unsigned int length, int sum){
    int theSum = 0;
    for(long unsigned int i(0); i<length; i++){
        theSum += arr[i];
    }
    if(theSum==sum){return true;}
    else {return false;}
}

template<typename ItemType>
void BinaryNodeTree<ItemType>::doesSomePathHaveSumHelper(BinaryNodePtr nodePtr,ItemType arry[],long unsigned int length, int valueAdded, bool& statusCheck){
    
    if(nodePtr!= nullptr){
        arry[length] = nodePtr->item;
        ++length;
    }
    else {
        statusCheck = false;
    }
    
    if ((nodePtr->leftChildPtr==nullptr)&&(nodePtr->rightChildPtr==nullptr)){
        if (testPathArray(arry, length, valueAdded)){
        statusCheck = true;
        }
    }
        if(nodePtr->leftChildPtr!=nullptr){
            doesSomePathHaveSumHelper(nodePtr->leftChildPtr, arry, length, valueAdded,statusCheck);
        }
        if(nodePtr->rightChildPtr!=nullptr){
            doesSomePathHaveSumHelper(nodePtr->rightChildPtr, arry, length, valueAdded,statusCheck);
        }
}
//////////////////////////////////////////////////////////////
//Good BYE CS1521 Projects.
//////////////////////////////////////////////////////////////



