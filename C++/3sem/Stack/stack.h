///
/// Created by admin on 11.09.2022.
///

#ifndef LAB_STACK_STACK_H
#define LAB_STACK_STACK_H

#include <cstddef>
#include <memory>
#include <iostream>
#include "exceptions.h"

namespace user {
    template<typename Type>
    class Stack {
    protected:
        std::size_t capacity = 0;
        std::size_t numElements = 0;
        std::unique_ptr<Type[]> array;
        void resize(std::size_t capacity);

    public:
        Stack() = default;
        ~Stack() = default;

        explicit Stack(std::size_t _capacity);
        Stack(std::initializer_list<Type> list);
        Stack(const Stack& stack);
        //Stack(Stack&& stack);
        //копирование и перемещение

        void push(Type value);
        Type pop();
        [[nodiscard]] Type check_pop() const;
        [[nodiscard]] std::size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        void clear() noexcept;
        ///копирование и перемещение
        //Stack& operator= (const Stack&);
        //Stack& operator= (const Stack&&);
        ///перенаправление вывода
        template<typename U> friend std::ostream& operator<< (std::ostream& out, const Stack<U>& stack);

        /// >> добавление push pop
        template<typename T> friend Stack<T>& operator<< (Stack<T>&, T);//push
        template<typename T> friend Stack<T>& operator>> (Stack<T>&, T&);//pop

        // stack << a << b << c


        ///Сравнение == и !=
        template<typename T> friend bool operator == (const Stack <T>& left, const Stack <T>& right);
        template<typename T> friend bool operator != (const Stack <T>& left, const Stack <T>& right);

        ///метод top
        void swap(Type &a);
        void top(Type i);
    };




}
#endif //LAB_STACK_STACK_H
