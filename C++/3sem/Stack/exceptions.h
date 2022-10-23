//
// Created by admin on 11.09.2022.
//

#ifndef LAB_STACK_EXCEPTIONS_H
#define LAB_STACK_EXCEPTIONS_H

#include <exception>

namespace user {
class bad_stack_capacity : public std::exception {
 public:
    [[nodiscard]] const char *what() const noexcept override {
        return exception::what();
    }
};

class pop_out_of_index : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return exception::what();
    }
};

}
#endif //LAB_STACK_EXCEPTIONS_H
