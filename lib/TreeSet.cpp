#ifndef TREE_SET_CPP
#define TREE_SET_CPP

#include "TreeSet.hpp"

template <typename T>
TreeSet<T>::TreeSet() : _root(nullptr), _size(0) {
    _comparator = [](T left, T right) {
        if (left < right)
        {
            return -1;
        }
        else if (left > right)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    };
}

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items) {
    _root = nullptr;
    _size = 0;
    _comparator = [](T left, T right) {
        if (left < right)
            return -1;
        else if (left > right)
            return 1;
        else
            return 0;
    };

    
    for (int i = 0; i < items.size(); i++) {
        add(items[i]);
    }
}

template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items, std::function<int(T, T)> comparator) : _comparator(comparator) {
    _root = nullptr;
    _size = 0;
    
    // Iterate thoguh loop and add each item to the tree
    for (int i = 0; i < items.size(); i++) {
        add(items[i]);
    }
}

template <typename T>
TreeSet<T>::TreeSet(std::function<int(T, T)> comparator){

    _root = nullptr;
    _size = 0;
    _comparator = comparator;
}

//derived from both pseudocode from the book and the discussion pseudocode
template <typename T>
void TreeSet<T>::fix_violation(BinaryTreeNode<T> *z) {
    
    //while loops checks if z and its parent are both red to correct violation
    //it also makes sure to omit the case in which z is the root node thus having null parent and grandparent
    while((z->_parent && z->_parent->_parent) && (z->_parent->_color == Red)){
        
        //Scenario 1 : z's parent is a left child therefore set the y ptr (uncle) as 
        ////the right child of grandparent
        if(z->_parent == z->_parent->_parent->_left){
            BinaryTreeNode<T> * y = z->_parent->_parent->_right;

            //Scenario A: Uncle of z is red, thus change parent and uncle to black, and grandparent to red
            if(y != nullptr && y->_color == Red){
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;   
                //Set z to grandparent which will check if grnadparent is now causing a violation
                z = z->_parent->_parent;
            }
            else{  //Scenario B: Uncle of z is black 

                //if z is a right child rotate z's parent left
                if(z == z->_parent->_right){
                    z = z->_parent;
                    this->rotate_left(z);
                    //z.parent and z have reversed parent-child roles
                }

                //set z's parent black and grandparent to red
                z->_parent->_color = Black; 
                z->_parent->_parent->_color = Red;
                //rotate z's grandparent to right
                this->rotate_right(z->_parent->_parent);
            }   
        }
        else{ //same steps as above with right and left reversed
            BinaryTreeNode<T> * y = z->_parent->_parent->_left;

            //Scenario A: Uncle of z is red, thus change parent and uncle to black, and grandparent to red
            if(y != nullptr && y->_color == Red){
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;   
                //Set z to grandparent which will check if grnadparent is now causing a violation
                z = z->_parent->_parent;
            }
            else{  //Scenario B: Uncle of z is black 

                //if z is a left child rotate z's parent right
                if(z == z->_parent->_left){
                    z = z->_parent;
                    this->rotate_right(z);
                    //z.parent and z have reversed parent-child roles
                }

                //set z's parent black and grandparent to red
                z->_parent->_color = Black; 
                z->_parent->_parent->_color = Red;
                //rotate z's grandparent to left
                this->rotate_left(z->_parent->_parent);
            }   
        }
    }
    //set root to be black
    if(this->_root != nullptr)
        this->_root->_color = Black;
}

//derived using pseudocode from the book
template <typename T>
void TreeSet<T>::rotate_left(BinaryTreeNode<T> *x) {
    
    //create a vriable to hold node x's right ptr
    BinaryTreeNode<T> * y = x->_right;
    // x's right ptr inherits y's left subtree
    x->_right = y->_left;

    //Check if y's left subtree exists if it does
    ////if it des then set y's left to accept x as its parent
    if(y->_left != nullptr){
        y->_left->_parent = x;
    }

    //x's parent now becomes y's parent
    y->_parent = x->_parent;
    //verify if x was originally the root then make the y the new root
    if(x->_parent == nullptr){
        this->_root = y;
    }
    //verify if x was the left child  or right child of its parent and modify y accordingly
    else if(x == x->_parent->_left){
        x->_parent->_left = y;
    }
    else{
        x->_parent->_right = y;
    }

    //x becomes y's left child
    y->_left = x;
    //x's parent is now y
    x->_parent = y;
}

//derived using the same exact steps in the book pseudocode for rotate_left
template <typename T>
void TreeSet<T>::rotate_right(BinaryTreeNode<T> *y) {
    
    //create a variable to hold y's left pointer
    BinaryTreeNode<T> * x = y->_left;
    //x's right subtree now belongs to y's left ptr
    y->_left = x->_right;

    //Check if x's right subtree exists,
    ////if it does then set it to accept y as its parent
    if(x->_right != nullptr){
        x->_right->_parent = y;
    }
    
    //y's parent gets assigned to become x's parent
    x->_parent = y->_parent;

    //verify if y was originally the root, if so, make x the new root
    if(y->_parent == nullptr){
        this->_root = x;
    }
    //else if y was a left or right child, make x a left or right child accordingly
    else if(y->_parent->_left == y){
        y->_parent->_left = x;
    }
    else{
        y->_parent->_right = x;
    }

    //y should now be x's right child and it should point its parent variable to x
    x->_right = y;
    y->_parent = x;
}

template <typename T>
size_t TreeSet<T>::size() const {
    return _size;  
}

//derived from the book pseudocode chapter 13.3
template <typename T>
void TreeSet<T>::add(T value) {

    //Create a node with the value passed
    BinaryTreeNode<T> * z = new BinaryTreeNode<T>(value);
    //save the tree's root in a pointer to traverse the tree
    BinaryTreeNode<T> * x = this->_root;
    //Create a ptr that would point to x'parent which will eventually be z's parent too
    BinaryTreeNode<T> * y = nullptr;

    //Check if x has traversed down to the end of the tree or has found a node of equivalent 
    while(x != nullptr ){
         //set y to become x because we will move x down
        y = x;
        //use the comparator to see if z's vlue is smaller or greater than
        if( this->_comparator(z->value, x->value) < 0)
            x = x->_left; // x is moved to thr left
        else if(this->_comparator(z->value, x->value) == 0){
            //checks for case where value alrready exists
            //x holds the pointer to the node to be replaced so use it to transfer ownership

            //handle the transfer of parent transfer
            //if x's parent is null then make z the root of the tree since that's what x was to begin with
            if(x->_parent == nullptr){
                this->_root = z;
            }
            else{
                //if paent of x non null update z to accept x's parent as its parent
                z->_parent = x->_parent;
                //if x was a left child make z a left child
                if(x->_parent->_left == x) 
                    x->_parent->_left = z;
                //if x was a right child make z a left child
                if(x->_parent->_right == x) 
                    x->_parent->_right = z;
            }
            
            //transfer x's memeber variables
            z->_left = x->_left;
            z->_right = x->_right;
            z->_color = x->_color;

            //if children of x were not null have them point to z
            if(x->_left != nullptr)
                x->_left->_parent = z;
            if(x->_right != nullptr)
                x->_right->_parent = z;
            //delete node x and return
            delete x;
            return;
        }
        else
            x = x->_right; // x is moved to the right
    }
    // set z's parent to be y
    z->_parent = y;
    // handle case where tree is empy
    if(y == nullptr)
        this->_root = z;
    else if (this->_comparator(z->value, y->value) < 0){
        //if z is smaller than y place it as its left child
        y->_left = z;
    } 
    else{
        //if z is greater than y place it as its right child
        y->_right = z;
    }
    //set z's children to be nullptr and its color to be red
    z->_left = nullptr;
    z->_right = nullptr;
    z->_color = Red;
    //call the fix violation method and increment size;
    this->fix_violation(z);
    this->_size++;
}

template <typename T>
bool TreeSet<T>::contains(T value) const {

    //set a pointer that holds the root of the tree
    BinaryTreeNode<T> * checkValue = this->_root;

    //if root is nullptr (meaning tree is empty, return false
    if(this->_root == nullptr){
        return false;
    }
    
    //traverse the treee until a nullptr is reachedd
    while(checkValue != nullptr){
        //if the current node's valu matches the value we are looking for return true
        if(this->_comparator(value, checkValue->value) == 0){
            return true;
        }
        else if(this->_comparator(value, checkValue->value) < 0){
            //if value we are looking for  is smaller than the value of the current node,
            //// make the current checkValue ptr become its left child
            checkValue = checkValue->_left;
        }
        else{
            //if value we a re looking for is greater, then traverse on the right child of the 
            ////current node
            checkValue = checkValue ->_right;
        }      
    }
    //return false if traversed entire list and not found
    return false;  
}

template <typename T>
bool TreeSet<T>::is_empty() const {
    
    if(_root == nullptr)
        return true;  
    else
        return false;
}

template <typename T>
std::optional<T> TreeSet<T>::min() const {
    //return nullopt if tree is empty
    if(this->_root == nullptr)
        return std::nullopt;  
    
    //create a node ptr to hold the parent of the node because it will eventually reach nullptr
    ////and we need the node right before nullptr
    BinaryTreeNode<T> * parent = nullptr;
    //create a node ptr to hold root node
    BinaryTreeNode<T> * findMin = this->_root;
    
    //traverse tree until nullptr is reached
    while(findMin != nullptr){
        //make parent point to node findMin  as findMin will continue to go left
        parent = findMin;
        //traverse always left because values get smaller and smaller
        findMin = findMin->_left;
    }
    // findMin must have reached nullptr by now which means parent holds the node right before nullptr
    return parent->value;
}

template <typename T>
std::optional<T> TreeSet<T>::max() const {
     //return nullopt if tree is empty
    if(this->_root == nullptr)
        return std::nullopt;  
    
    //create a node ptr to hold the parent of the node because it will eventually reach nullptr
    ////and we need the node right before nullptr
    BinaryTreeNode<T> * parent = nullptr;
    //create a node ptr to hold root node
    BinaryTreeNode<T> * findMax = this->_root;
    
    //traverse tree until nullptr is reached
    while(findMax != nullptr){
        //make parent point to node findMax as findMax will continue to go right
        parent = findMax;
        //traverse always right because values get bigger and bigger
        findMax = findMax->_right;
    }
    // findMax must have reached nullptr by now which means parent holds the node right before nullptr
    return parent->value;
}

//based on discussion pseudocode and book pseudocode section 12.1
//in-order algorithm helper function
template <typename T>
std::vector<T> InOrderAlgorithm(BinaryTreeNode<T> * rootNode, std::vector<T> & sortedList){
    //check if tree is empty
    if(rootNode == nullptr)
        return sortedList;
    else{
        //recursivelly access left subtrees
        InOrderAlgorithm(rootNode->left(), sortedList);
        //push element into vector
        sortedList.push_back(rootNode->value);
        //recursively access right subtrees
        InOrderAlgorithm(rootNode->right(), sortedList);
        //return the vector
        return sortedList;
    }
}

//call the helper function above
template <typename T>
std::vector<T> TreeSet<T>::to_vector() const {
    std::vector<T> toVector;
    return InOrderAlgorithm(this->_root, toVector);
}

template <typename T>
std::optional<T> TreeSet<T>::get(T value) const {
     //set a pointer that holds the root of the tree
    BinaryTreeNode<T> * checkValue = this->_root;

    //if root is nullptr (meaning tree is empty, return nullopt
    if(this->_root == nullptr){
        return std::nullopt;
    }
    
    //traverse the treee until a nullptr is reachedd
    while(checkValue != nullptr){
        //if the current node's valu matches the value we are looking for return true
        if(this->_comparator(value, checkValue->value) == 0){
            return checkValue;
        }
        else if(this->_comparator(value, checkValue->value) < 0){
            //if value we are looking for  is smaller than the value of the current node,
            //// make the current checkValue ptr become its left child
            checkValue = checkValue->_left;
        }   
        else{
            //if value we a re looking for is greater, then traverse on the right child of the 
            ////current node
            checkValue = checkValue ->_right;
        }      
    }
    //return nullopt if traversed entire list and not found
    return std::nullopt;
}


template <typename T>
TreeSet<T> TreeSet<T>::operator+(const TreeSet &other) {
    //Initialize new TreeSet object that will take the union of both sets
    TreeSet<T> unionOfSets;

    //call the to_vector method to sort all values into a vecor
    std::vector<T> thisVector = this->to_vector();
    //append each value into unionOfSets
    for(int i = 0; i < thisVector.size(); i++){
        unionOfSets.add(thisVector[i]);
    }

    //repeat same steps but with object other
    std::vector<T> otherVector = other.to_vector();
    for(int i = 0; i < otherVector.size(); i++){
        unionOfSets.add(otherVector[i]);
    }

    //in both cases add() Will handle duplicates

    return unionOfSets;  
}

template <typename T>
TreeSet<T>& TreeSet<T>::operator+=(const TreeSet &other) {
    
    //put all the elements of other into a vector
    std::vector<T> otherVector = other.to_vector();
    //itirate to place each element into this object
    for(int i = 0; i < otherVector.size(); i++){
        this->add(otherVector[i]);
    }
    return *this;
}

template <typename T>
TreeSet<T> TreeSet<T>::operator&(const TreeSet &other) {
    //operator returns only common values
     
    //call the to_vector method to sort all of this's values into a vector
    std::vector<T> thisVector = this->to_vector();
  
    //Initialize new TreeSet object with default constructor that will take the union of both sets
    TreeSet<T> intersectionOfSets;

    //itirate through thisVector's elements and append other's elements into intersectionOfsets if it
    ////contains the elements in thisVector
    for(int i = 0; i < thisVector.size(); i++){
        
        if(other.contains(thisVector[i])){
            intersectionOfSets.add(thisVector[i]);
        }
    }

    return intersectionOfSets;
}

template <typename T>
bool TreeSet<T>::operator==(const TreeSet &other) const {
    // operator returns bool based on if elements are equal

    //call the to_vector method to sort all of this's values into a vector
    std::vector<T> thisVector = this->to_vector();
    //call the to_vector method to sort all of other'svalues into a vector
    std::vector<T> otherVector = other.to_vector();

    //if vectors are not equal in size it implies that they aren't equal
    if(otherVector.size() != thisVector.size())
        return false;

    //ititrate trhough thisVector
    for(int i = 0; i < thisVector.size(); i++){

        //if any of thisVectors's elements are not present in otherVector, return false
        if(otherVector[i] != thisVector[i]){
            return false;
        }
    }
    
    //if scrrening processes above are passed, return true
    return true;  
}

template <typename T>
bool TreeSet<T>::operator!=(const TreeSet &other) const {
    //opposite of == operator above

    //call the to_vector method to sort all of this's values into a vector
    std::vector<T> thisVector = this->to_vector();
    //call the to_vector method to sort all of other'svalues into a vector
    std::vector<T> otherVector = other.to_vector();

    //if vectors are not equal in size it implies that they aren't equal
    if(otherVector.size() != thisVector.size())
        return true;

    //ititrate trhough thisVector
    for(int i = 0; i < thisVector.size(); i++){

        if(otherVector[i] != thisVector[i]){
            return true;
        }
    }
    
    return false;  

}

//Derived with inspiration from discussion pseudocode
//define function that allows parameters and uses post-order traversal as shown in discussion
template <typename T>
BinaryTreeNode<T>* deallocate(BinaryTreeNode<T>* subTree) {
   
   if (subTree == nullptr) 
        return nullptr;
    deallocate(subTree->left());
    deallocate(subTree->right());
    delete subTree;
    return nullptr;  
}

template <typename T>
void TreeSet<T>::clear() {

//call the above function here to delete all nodes using post-order traversal
    deallocate(_root);
    _root = nullptr;
    _size = 0;
    
}

template <typename T>
TreeSet<T>::~TreeSet() {
    this->clear();
}

#endif
