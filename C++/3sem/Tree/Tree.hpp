
#include "Tree.h"
#include <stack>


template<typename Type>
Tree<Type>::Tree() noexcept : root(nullptr){}

template<typename Type>
Tree<Type>::Tree(const Tree<Type> &tree) : Tree(){
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->insert(tree);
}

template<typename Type>
Tree<Type>::Tree(Tree&& tree) noexcept : Tree(){
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->root = tree.root;
    tree.root = nullptr;
}

template<typename Type>
Tree<Type>::~Tree() {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    if (this->root == nullptr) return;

    this->root->clearChild();
    delete this->root;
    this->root = nullptr;
}

template<typename Type>
Tree<Type>::Tree(std::initializer_list<Type> values_list) : Tree() {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    for(const Type& value : values_list){
        this->insert(value);
    }
}

template<typename Type>
TreeElem<Type>* Tree<Type>::deleteElem(TreeElem<Type> *_root, const Type &value) {
    if (_root == nullptr) return _root;

    std::lock_guard<std::recursive_mutex> locker(_mtx);

    if (value < _root->value) {
        _root->left = this->deleteElem(_root->left, value);
    } else if (value > _root->value) {
        _root->right = this->deleteElem(_root->right, value);
    } else {
        if (_root->left == nullptr || _root->right == nullptr) {
            TreeElem<Type>* temp = _root->left ? _root->left : _root->right;

            if (temp == nullptr) {
                temp = _root;
                _root = nullptr;
            } else {
                *_root = *temp;
            }

            delete temp;
        }
    }

    if (_root == nullptr) return _root;
    return _root;
}

template<typename Type>
TreeElem<Type>* Tree<Type>::searchElem(TreeElem<Type> *elem, const Type &value) const {
    if (elem == nullptr) return nullptr;

    std::lock_guard<std::recursive_mutex> locker(_mtx);

    if (value < elem->value) {
        return this->searchElem(elem->left, value);
    } else if (value > elem->value) {
        return this->searchElem(elem->right, value);
    }

    return elem;
}

template<typename Type>
TreeElem<Type>* Tree<Type>::insert(TreeElem<Type> *elem, const Type &value) {
    if (elem == nullptr) return new TreeElem<Type>(value);

    std::lock_guard<std::recursive_mutex> locker(_mtx);

    if (value < elem->value) {
        elem->left = this->insert(elem->left, value);
    } else if (value > elem->value) {
        elem->right = this->insert(elem->right, value);
    } else {
        return elem;
    }

    return elem;
}

template<typename Type>
void Tree<Type>::insert(const Type &value) {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->root = this->insert(this->root, value);
}

template<typename Type>
void Tree<Type>::insert(const Tree<Type> &tree) {
    Tree::LNR(tree.root, [=](const Type& value){
        std::lock_guard<std::recursive_mutex> locker(_mtx);
        this->insert(value);
    });
}
template<typename Type>
void Tree<Type>::NLR(TreeElem<Type> *elem, const std::function<void(const Type &)> &nodeValueHandler) {
    if (elem == nullptr) return;
    nodeValueHandler(elem->value);
    Tree::NLR(elem->left, nodeValueHandler);
    Tree::NLR(elem->right, nodeValueHandler);
}

template<typename Type>
void Tree<Type>::LNR(TreeElem<Type> *elem, const std::function<void(const Type &)> &nodeValueHandler) {
    if (elem == nullptr) { return; }
    Tree::LNR(elem->left, nodeValueHandler);
    nodeValueHandler(elem->value);
    Tree::LNR(elem->right, nodeValueHandler);
}

template<typename Type>
void Tree<Type>::LRN(TreeElem<Type> *elem, const std::function<void(const Type &)> &nodeValueHandler) {
    if (elem == nullptr) { return; }
    Tree::LRN(elem->left, nodeValueHandler);
    Tree::LRN(elem->right, nodeValueHandler);
    nodeValueHandler(elem->value);
}

template<typename Type>
void Tree<Type>::remove(const Type &value) {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->root = this->deleteElem(this->root, value);
}

template<typename Type>
void Tree<Type>::clearTree() {
    if (this->root == nullptr) return;

    this->root->clearChild();
    delete this->root;
    this->root = nullptr;
}

template<typename Type>
bool Tree<Type>::search(const Type &value) const {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    return this->searchElem(this->root, value) != nullptr;
}

template<typename Type>
bool Tree<Type>::isEmpty() const {
    return this->root == nullptr;
}

template<typename Type>
Tree<Type> Tree<Type>::getSubtree(const Type &rootValue) const {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    Tree<Type> result = Tree<Type>();
    TreeElem<Type>* foundNode = this->searchElem(this->root, rootValue);
    if (foundNode == nullptr) return result;
    Tree::LNR(foundNode, [&result](const Type& value) {
        result.insert(value);
    });
    return result;
}

template<typename Type>
void Tree<Type>::NLR(std::ostream &out) const {
    Tree::NLR(this->root, [&out](const Type& value) {
        out << value << ' ';
    });
}

template<typename Type>
void Tree<Type>::LNR(std::ostream &out) const {
    Tree::LNR(this->root, [&out](const Type& value) {
        out << value << ' ';
    });
}

template<typename Type>
void Tree<Type>::LRN(std::ostream &out) const {
    Tree::LRN(this->root, [&out](const Type& value) {
        out << value << ' ';
    });
}

template<typename OutputType>
std::ostream &operator<<(std::ostream &out, const Tree<OutputType> &tree) {
    tree.NLR(out);
    return out;
}

template<typename Type>
Tree<Type> Tree<Type>::operator>>(const Type &add) {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->insert(add);
    return *this;
}


template<typename Type>
Tree<Type> Tree<Type>::operator>>(const Tree<Type> &add) {
    std::lock_guard<std::recursive_mutex> locker(_mtx);
    this->insert(add);
}


template<typename T>
bool operator==(const Tree<T> &n1, const Tree<T> &n2) {
    if(n1->root == nullptr && n2->root == nullptr) {return true;}
    if(n1->root != nullptr && n2->root != nullptr && n1->root->value == n2->root->value) { return (n1->root->left == n2->root->left) && (n1->root->right == n2->root->right);}
    else return false;
}

template<typename T>
bool operator!=(const Tree<T> &left, const Tree<T> &right) {
    return !(left==right);
}

template<typename Type>
Tree<Type> Tree<Type>::operator=(const Tree<Type>& that) {
    if(this != &that){
        this->clearTree();
        Tree<Type>* c = that.root;
        NLR(c);
    }
    return *this;
}

template<typename Type>
Tree<Type> Tree<Type>::operator=(const Tree<Type>&& otherBST) {
    if (this != &otherBST) {
        if (root) {
            std::stack <Tree<Type>*> nodeStack;
            nodeStack.push(root);

            Tree<Type> *currentNode = nullptr;
            while (!nodeStack.empty()) {
                currentNode = nodeStack.top();
                nodeStack.pop();

                if (currentNode->rlink) {
                    nodeStack.push(currentNode->rlink);
                }
                if (currentNode->llink) {
                    nodeStack.push(currentNode->llink);
                }

                delete currentNode;
                currentNode = nullptr;
            }
            std::cout << root << std::endl; // This is where it seems like root is not being deleted correctly/nullptr'd.
        }

        root = move(otherBST.root);
        otherBST.root = nullptr;
    }
    else {
        std::cerr << "ERROR: Cannot assign to self." << std::endl;
    }

    return *this;
}





















