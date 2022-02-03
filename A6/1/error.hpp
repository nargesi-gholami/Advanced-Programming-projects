#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>

#define DUPLICATE "Duplicate key.\n"
#define UNDEFINED "Undefined type.\n"
#define INVALID "invalid id.\n"

class duplicateKey : public std::exception
{
    public:
        virtual const char* what() const throw() { return DUPLICATE;};
};

class undifinedType : public std::exception
{
    public:
        virtual const char* what() const throw() { return UNDEFINED;};
};

class invalidId: public std::exception
{
    public:
        virtual const char* what()  const throw() { return INVALID;};
};

#endif 