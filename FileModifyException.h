//
// Created by erik on 2/3/21.
//

#ifndef INC_21S_CS3377_PROJECT_FILEMODIFYEXCEPTION_H
#define INC_21S_CS3377_PROJECT_FILEMODIFYEXCEPTION_H

#include <exception>
#include <string>


class FileModifyException : public std::exception {
public:
    explicit FileModifyException(const std::string& message) noexcept
    : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


#endif //INC_21S_CS3377_PROJECT_FILEMODIFYEXCEPTION_H
