#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "error.hpp"

#define SUBJECT_PRINT 0
#define NORMAL 1
#define END 2
#define LAST_NORMAL 3
#define LAST_END 4
#define FREE_SPACE "    "
#define EMPTY_STRING ""
#define QUTATION '"'
#define ENTER '\n'
#define COMMA ','
#define START1 ": {"
#define START2 ": ["
#define END_1 "    },"
#define END_2 "    }"
#define END_3 "    ],"
#define END_4 "    ]"
#define END_5 ": {}"
#define END_6 ": []"
#define SPACE ": "

class fatherObject
{
    public:
        fatherObject();
        void deleteAll();
        fatherObject(int parentId_,std::string key_);
        fatherObject* searchAndPrint(int id);

        virtual void edit();
        virtual void add(fatherObject* fatherObject_);
        virtual void print(std::string freeSpace = EMPTY_STRING,int mode = NORMAL);        
        virtual int getParentId() { return parentId; }
        virtual int getChildId() { return childId; }
        virtual std::string getKey() { return key; }

        void checkDuplicateKey(fatherObject* fatherObject_);
        void print1(std::string freeSpace= EMPTY_STRING,int mode= NORMAL);

    protected:
        int parentId;
        int childId;
        std::string key;
        std::string freeSpace;
        std::stringstream prettyText;
        std::vector <std::string> allKey;
        std::vector <fatherObject*> childrenClass;
};

class childrenObject : public fatherObject
{
    public:
        childrenObject(int parentId_,std::string key_,std::string value_);
        void print(std::string freeSpace = EMPTY_STRING,int mode = NORMAL);

    private:
        std::string value;
};

class object : public fatherObject
{
    public:
        object(int childId_,int parentId_,std::string key_);
        void print(std::string freeSpace = EMPTY_STRING,int mode = NORMAL);
};

class array : public fatherObject
{
    public:
        array(int childId_,int parentId_,std::string key_);
        void print(std::string freeSpace = EMPTY_STRING,int mode = NORMAL);

    private:
        std::string value;
};

class array_part : public fatherObject
{
    public:
       array_part(int parentId_,std::string value_);
       void print(std::string freeSpace = EMPTY_STRING,int mode = NORMAL);

    private:
        std::string value;
};



#endif