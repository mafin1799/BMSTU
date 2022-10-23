//
// Created by admin on 04.10.2022.
//

#ifndef DEREVO_TREEELEM_H
#define DEREVO_TREEELEM_H

template<typename Type>
class TreeElem {
public:
    Type value;
    TreeElem *left = nullptr;
    TreeElem *right = nullptr;

    explicit TreeElem(Type value) {
        this->value = value;
    }

    void clearChild()
    {
        if(this->left != nullptr) this->left->clearChild();
        delete this->left;
        this->left = nullptr;

        if (this->right != nullptr) this->right->clearChild();
        delete this->right;
        this->right = nullptr;
    }
};
#include "TreeElem.h"
#endif //DEREVO_TREEELEM_H
