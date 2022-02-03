#include "object.hpp"

void fatherObject::print(std::string freeSpace,int mode) {}

void fatherObject::print1(std::string freeSpace,int mode)
{
    if(mode == NORMAL)
    for(int i = 0 ; i < childrenClass.size() ; i++)
    {
        if(childrenClass[i]->childrenClass.size() == 0)
        {
            if(i == childrenClass.size() - 1)
                childrenClass[i]->print(freeSpace,LAST_NORMAL);
            else
                childrenClass[i]->print(freeSpace,NORMAL);
        }
        else
        {
            childrenClass[i]->print(freeSpace,SUBJECT_PRINT);
            childrenClass[i]->print1(freeSpace + FREE_SPACE);
            if(i == childrenClass.size() - 1)
                childrenClass[i]->print(freeSpace,LAST_END);
            else
                childrenClass[i]->print(freeSpace,END);
        }
    }
}

fatherObject* fatherObject::searchAndPrint(int id)
{
    for (int i = 0; i < childrenClass.size() ; i++)
    {
        if(childrenClass[i]->getChildId() == id)
             childrenClass[i]->print1();
        else
            childrenClass[i]->searchAndPrint(id);
    }    
}

fatherObject::fatherObject(int parentId_,std::string key_)
{
    parentId = parentId_;
    childId = parentId_;
    key = key_;
    freeSpace = EMPTY_STRING;
}

fatherObject::fatherObject() {}

void fatherObject::checkDuplicateKey(fatherObject* fatherObject_)
{
    for(int i = 0 ; i < allKey.size() ; i++)
        if(!allKey[i].compare(fatherObject_->getKey()))
            if(fatherObject_->getKey().compare(EMPTY_STRING))
                throw duplicateKey();
}

void fatherObject::add(fatherObject* fatherObject_)
{
    checkDuplicateKey(fatherObject_);
    if(this->getChildId() ==  fatherObject_->getParentId())
    {
        this->childrenClass.push_back(fatherObject_);
        allKey.push_back(fatherObject_->getKey());
            return;
    }
    for(int i = 0 ; i < childrenClass.size() ; i++)
    {
        if(childrenClass[i]->getChildId() ==  fatherObject_->getParentId())
        {
            childrenClass[i]->allKey.push_back(fatherObject_->getKey());
            childrenClass[i]->childrenClass.push_back(fatherObject_);
                return;
        }
        else
            childrenClass[i]->add(fatherObject_);
    }
}

void fatherObject::deleteAll()
{
    for(int i = 0 ; i < childrenClass.size() ; i++)
    {
        if(childrenClass[i]->childrenClass.size() == 0)
           delete childrenClass[i];
        else
        {
            childrenClass[i]->deleteAll();   
            delete (childrenClass[i]);
        }      
    }
}

void fatherObject::edit()
{
    std::string current = prettyText.str();
    prettyText.str(EMPTY_STRING);
    current.pop_back();
    current.pop_back();
    current += ENTER;
    prettyText << current;
}

childrenObject::childrenObject(int parentId_,std::string key_,std::string value_) 
    : fatherObject(parentId_ , key_)
    {
        value = value_;
        prettyText << FREE_SPACE << QUTATION+ key + QUTATION + SPACE + value + COMMA +ENTER ;
    }

void childrenObject::print(std::string freeSpace,int mode)
{
    std::cout << freeSpace;
    if(mode == NORMAL)
        std::cout << prettyText.rdbuf();
    else if(mode == LAST_NORMAL)
    {
        this->edit();
        std::cout << prettyText.rdbuf();
    }
}

object::object(int childId_,int parentId_,std::string key_)
    : fatherObject(parentId_,key_)
{
    childId = childId_;
    prettyText << FREE_SPACE << QUTATION + key + QUTATION + END_5 + COMMA + ENTER ;
}

void object::print(std::string freeSpace,int mode)
{
    std::cout << freeSpace;
    if(mode == NORMAL)
        std::cout << prettyText.rdbuf();
    else if(mode== SUBJECT_PRINT)
    {
        if(!key.compare(EMPTY_STRING))
            std::cout << FREE_SPACE << key  << START1 << std::endl;
        else
            std::cout << FREE_SPACE << QUTATION << key << QUTATION << START1 << std::endl;
    }
    else if(mode == END)
        std::cout << END_1 << std::endl;
    else if(mode == LAST_END)
        std::cout << END_2 << ENTER;
    else if(mode == LAST_NORMAL)
    {
        edit();
        std::cout << prettyText.rdbuf();
    }
}

array::array(int childId_,int parentId_,std::string key_)
    : fatherObject(parentId_,key_)
{
    childId = childId_;
    prettyText << FREE_SPACE << QUTATION + key + QUTATION + END_6 + COMMA + ENTER ;
}

void array::print(std::string freeSpace,int mode)
{
    std::cout << freeSpace;
    if(mode == NORMAL)
        std::cout << prettyText.rdbuf();
    else if(mode== SUBJECT_PRINT)
    {
        if(!key.compare(EMPTY_STRING))
            std::cout << FREE_SPACE << key  << START2 << std::endl;
        else
            std::cout << FREE_SPACE << QUTATION << key << QUTATION << START2 << std::endl;
    }
    else if(mode == END)
        std::cout << END_3 << ENTER;
    else if(mode == LAST_END)
        std::cout << END_4 << ENTER;
    else if(mode == LAST_NORMAL)
    {
        edit();
        std::cout << prettyText.rdbuf();
    }
}

array_part::array_part(int parentId_,std::string value_)
{
    parentId = parentId_;
    key = EMPTY_STRING;
    value = value_; 
}

void array_part::print(std::string freeSpace,int mode)
{
    std::cout << freeSpace;
    if(mode == NORMAL)
        std::cout << FREE_SPACE << value << COMMA << std::endl;
    else if(mode == LAST_NORMAL)
        std::cout << FREE_SPACE << value << std::endl;
}