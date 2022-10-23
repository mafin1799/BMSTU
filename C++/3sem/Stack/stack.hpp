#include "stack.h"

namespace user {
    template<typename Type>
    void Stack<Type>::resize(std::size_t _capacity) {
        this->capacity = _capacity;

        if (this->numElements > this->capacity) {
            this->numElements = this->capacity;
        }

        auto tmp = std::move(this->array);
        this->array = std::make_unique<Type[]>(this->capacity);
        std::copy(tmp.get(), tmp.get()+this->numElements, this->array.get());
    }

    template<typename Type>/// Конструктор с указанием вместительности стека.
    Stack<Type>::Stack(std::size_t _capacity) : capacity(_capacity) {
        if (_capacity <= 0) throw bad_stack_capacity();
        this->array = std::make_unique<Type[]>(_capacity);
    }

    template<typename Type>/// Конструктор со списком инициализации.
    Stack<Type>::Stack(std::initializer_list<Type> list) : Stack(list.size()) {
        for(Type item : list) this->push(item);
    }

    template<typename Type> /// Конструктор с параметром
    Stack<Type>::Stack(const Stack &stack) : Stack(stack.capacity) {
        for (std::size_t i = 0; i < stack.numElements; i++){
            this->push(stack.array[i]);
        }
    }

    template<typename Type> /// Добавляет значение в стек.
    void Stack<Type>::push(Type value) {
        if (this->numElements >= this->capacity) this->resize(this->capacity + 16);
        this->array[this->numElements] = value;
        this->numElements += 1;
    }

    template<typename Type> ///pop
    Type Stack<Type>::pop() {
        if(this->empty()) throw pop_out_of_index();

        this->numElements -= 1;
        Type tmp = this->array[this->numElements];
        if (this->numElements == 0) this->clear();
        return tmp;
    }

    template<typename Type>
    bool Stack<Type>::empty() const noexcept {
        return !static_cast<bool>(this->array);
    }

    template<typename Type>
    void Stack<Type>::clear() noexcept{
        //if(this->empty()) return;
        this->numElements = 0;
    }

    template<typename Type>
    Type Stack<Type>::check_pop() const {
        if(this->empty()) throw pop_out_of_index();
        return this->array[this->numElements];
    }

    template<typename Type>
    std::size_t Stack<Type>::size() const noexcept {
        return this->numElements;
    }

    template<typename Type>
    std::ostream &operator<<(std::ostream &out, const Stack<Type>& stack) {
        out << stack.numElements << " of " << stack.capacity << ": ";
        for(std::size_t i = 0; i < stack.size(); i++){
            out << stack.array[i] << " ";
        }
        return out;
    }




    template<typename T>
    bool operator==(const Stack<T> &left, const Stack<T> &right) {
        int count = 0;
        //if(left.size() != right.size()) throw bad_stack_capacity();
        if(left.size() == right.size()) {
            for(size_t i = 0; i < left.size(); i++){
                if(left.array[i] == right.array[i]) count++;
                else return false;
            }
            if(count == left.size()) {
                return true;
            }

        }
        return false;
    }

    template<typename T>
    bool operator!=(const Stack<T> &left, const Stack<T> &right) {
        if (left == right) return false;
        else return true;
    }

    template<typename Type>
    void Stack<Type>::swap(Type &a) {
        Type tmp;
        tmp = a;
        a = this->pop();
        this->push(tmp);

    }

    template<typename Type>
    void Stack<Type>::top(Type i) {
        if(this->empty()) throw pop_out_of_index();
        this->pop();
        this->push(i);
    }

    template<typename T>
    Stack<T> &operator<<(Stack<T> &s, T x) {
        s.push(x);
        return s;
    }

    template<typename T>
    Stack<T> &operator>>(Stack<T> &s, T &x) {
        x = s.pop();
        return s;
    }
    /* template<typename T>
       std::istream &operator>>(Stack<T>& s, T x) {

       }

       template<typename T>
       std::ostream &operator<<(Stack<T> & s, T &x) {

       }*/


    /*template<typename Type>///возвращает не удаляя
    Type Stack<Type>::top() {

        Type tmp = this->array[this->numElements - 1];
        return tmp;
    }*/

    /*template<typename Type>
    void Stack<Type>::swap(Stack<Type> &init) {
        //std::cout << *this << std::endl;
        //std::cout << init << std::endl;
        Stack<Type> temp;

        temp = *this;
        *this->clear();
        *this = init;
        init.clear();
        &init = temp;
        //std::cout << temp << std::endl;

        /*for(std::size_t i = 0; i < this->size(); i++){
            temp.push(this->array[i]);

        }
        this->clear();

        //std::cout << temp << std::endl;
        //std::cout << *this << std::endl;
        //this->resize(init.capacity);
        for(std::size_t i = 0; i < init.size(); i++){
            this->push(init.array[i]);

        }
        init.clear();
        //init.resize(temp.capacity);
        //std::cout << *this << std::endl;
        for(std::size_t i = 0; i < this->size(); i++){
            init.push(temp.array[i]);
        }
        //std::cout << init << std::endl;*/

    /*template<typename Type>
    void Stack<Type>::top(Type i) {

    }

    template<typename Type>
    void Stack<Type>::swap(Type &a) {

    }*/

    }




