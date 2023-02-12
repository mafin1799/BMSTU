//
// Created by admin on 30.09.2022.
//

#ifndef DEREVO_TREE_H
#define DEREVO_TREE_H

#include <iostream>
#include <mutex>
#include "TreeElem.h"
template<typename Type>
class Tree {
protected:


    mutable std::recursive_mutex _mtx;
    TreeElem<Type> *root = nullptr;

    TreeElem<Type>* insert(TreeElem<Type>* elem, const Type& value);
    TreeElem<Type>* deleteElem(TreeElem<Type>* root, const Type& value);
    TreeElem<Type>* searchElem(TreeElem<Type>* elem, const Type& value) const;

    static void NLR(TreeElem<Type>* elem, const std::function<void(const Type&)>& nodeValueHandler);
    static void LNR(TreeElem<Type>* elem, const std::function<void(const Type&)>& nodeValueHandler);
    static void LRN(TreeElem<Type>* elem, const std::function<void(const Type&)>& nodeValueHandler);

public:

    Tree() noexcept;
    Tree(const Tree<Type>& tree);
    Tree(Tree&& tree) noexcept;
    ~Tree();
    Tree(std::initializer_list<Type> values_list);

    void insert(const Type& value);
    void insert(const Tree<Type>& tree);
    void remove(const Type& value);
    void clearTree();
    bool search(const Type& value) const;
    bool isEmpty() const;
    Tree<Type> getSubtree(const Type& rootValue) const;
    void NLR(std::ostream& out) const;
    void LNR(std::ostream& out) const;
    void LRN(std::ostream& out) const;

    template<typename OutputType>
    friend std::ostream& operator<<(std::ostream& out, const Tree<OutputType>& tree);

    Tree<Type> operator>> (const Tree<Type>&); //cin
    Tree<Type> operator>> (const Type&); //cin

    Tree<Type> operator=(const Tree<Type>&);
    Tree<Type> operator=(const Tree<Type>&&);


    template<typename T> friend bool operator == (const Tree<T>& n1, const Tree<T>& n2);
    template<typename T> friend bool operator != (const Tree<T>& left, const Tree<T>& right);
};



#include "Tree.hpp"
#endif //DEREVO_TREE_H
