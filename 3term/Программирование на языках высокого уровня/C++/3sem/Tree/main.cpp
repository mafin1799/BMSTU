#include <iostream>
#include <thread>
#include "Tree.h"

template<typename Type>
void Test(Tree<Type>& tree, int randAdd = 10)
{
    srand(std::time(nullptr) + randAdd);
    for (int i = 0; i <= 200; i++) {
        if (std::rand() % 2) {
            tree.insert(i / 5);
        } else {
            tree.remove(i / 5);
        }
    }
}


int main() {
    const Tree<int> tree_int{1, 2, 4, 3, 0};
    std::cout << "tree_int:    " << tree_int << std::endl;
    std::cout << std::endl;
    const int i = 5;
    //tree_int >> 4 >> 7 >> 9;

    //std::cout << tree_int;

    const Tree<int> tree{};
    const Tree<int> tree1{};
    //tree_int >> tree;
    std::cout << std::boolalpha;

    // ищем элемент
    if (!tree_int.search(23)) {
        std::cout << "The value is not found" << std::endl;
    } else {
        std::cout << "The value is found" << std::endl;
    }
    std::cout << std::endl;

    // удаление элемента
    //tree_int.remove(8);
    std::cout << "tree_int:    " << tree_int << std::endl;

    // удаление несуществующего элемента
    //tree_int.remove(45784);
    std::cout << "tree_int:    " << tree_int << std::endl;
    std::cout << std::endl;

    // вывод элементов в различном порядке
    std::cout << "PreOrder:    ";
    tree_int.LNR(std::cout);
    std::cout << std::endl;
    std::cout << "InOrder:     ";
    tree_int.NLR(std::cout);
    std::cout << std::endl;
    std::cout << "PostOrder:   ";
    tree_int.LRN(std::cout);
    std::cout << std::endl;
    std::cout << std::endl;

    // добавление дерева в дерево, очистка дерева
    Tree<int> subtree_int{6, 8, 45, 23};
    std::cout << "subtree_int: " << subtree_int << std::endl;
    //tree_int.insert(subtree_int);
    std::cout << "tree_int:    " << tree_int << std::endl;
    subtree_int.clearTree();
    std::cout << "subtree_int (after clear): " << subtree_int << std::endl;
    std::cout << std::endl;

    // получение поддерева
    Tree<int> subtree = tree_int.getSubtree(1);
    if (!subtree.isEmpty()) {
        std::cout << "Tree: " << subtree << std::endl;
    } else {
        std::cout << "Tree is not found" << std::endl;
    }
    std::cout << std::endl;

    // проверка типа double
    Tree<double> tree_double{6, 54.34, 9};
    std::cout << "tree_double: " << tree_double << std::endl;
    std::cout << std::endl;


    // проверка на thread-safe
    Tree<int> tree_;

    std::thread thread_1([&tree_]() { Test(tree_, 50); });
    std::thread thread_2([&tree_]() { Test(tree_, 100); });
    std::thread thread_3([&tree_]() { Test(tree_, 150); });
    std::thread thread_4([&tree_]() { Test(tree_, 200); });

    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();

    std::cout << "tree_th1: " << tree_ << std::endl;
    std::cout << std::endl;

    return 0;
}
