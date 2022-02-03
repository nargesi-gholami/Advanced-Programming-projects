#include "JsonBuilder.hpp"

JsonBuilder::JsonBuilder()
{
    allId.push_back(MOTHER_ID);
    objectId.push_back(MOTHER_ID);
    motherClass = new fatherObject(MOTHER_ID,MOTHER_NAME);
    number = 0;
}

int JsonBuilder::check(int parentId)
{
    for(int i = 0 ; i < allId.size() ; i++)
        if(allId[i] == parentId)
            return allId[i];
    throw invalidId();
}

void JsonBuilder::compose(int parentId, std::string key,std::string value)
{
    int id = check(parentId);
    childrenObject* child_temp = new childrenObject(parentId,key,value);
    motherClass->add(child_temp);
}

void JsonBuilder::addStringToObject(int parentId,std::string key,std::string value)
{
    compose(parentId,key,QUTATION + value + QUTATION);
}

void JsonBuilder:: addIntegerToObject(int parentId, std::string key, int value)
{
    compose(parentId,key,std::to_string(value));
}

int JsonBuilder::addContainerToObject(int parentId, std::string key, std::string type)
{
    int id = check(parentId);
    isObject(parentId);
    number++;
    allId.push_back(number);
    if(!type.compare(OBJECT))
    {
        objectId.push_back(number);
        motherClass->add(new object(number,parentId, key));
    }
    else if(!type.compare(ARRAY))
    {
        arrayId.push_back(number);
        motherClass->add(new array(number,parentId, key));
    }
    else
        throw undifinedType();
    return number;
}

void JsonBuilder::isArray(int id)
{
    for(int i = 0 ; i < arrayId.size() ; i++ )
        if(arrayId[i] == id)
            return ;
    throw invalidId();
}

void JsonBuilder::isObject(int id)
{
    for(int i = 0 ; i < objectId.size() ; i++ )
        if(objectId[i] == id)
            return;
    throw invalidId();
}

int JsonBuilder::addContainerToArray(int parentId, std::string type)
{
    int id = check(parentId);
    isArray(parentId);
    number++;
    allId.push_back(number);
    if(!type.compare(OBJECT)) 
    {
        objectId.push_back(number);
        motherClass->add(new object(number,parentId,EMPTY_STRING));
    }
    else if(!type.compare(ARRAY))
    {
        arrayId.push_back(number);
        motherClass->add(new array(number,parentId,EMPTY_STRING));
    }
    else
        throw undifinedType();
    return number;
}

void JsonBuilder::composeArrayPart(int parentId,std::string value)
{
    int id = check(parentId);
    motherClass->add(new array_part(parentId,value));
}

void JsonBuilder::addStringToArray(int parentId, std::string value)
{
    composeArrayPart(parentId,QUTATION + value + QUTATION);
}

void JsonBuilder::addIntegerToArray(int parentId, int value)
{
    composeArrayPart(parentId,std::to_string(value));
}

void JsonBuilder::print(int id )
{
    check(id);
    std::cout << START << std::endl;
    if(id == MOTHER_ID)
        motherClass->print1();
    else
        fatherObject* child = motherClass->searchAndPrint(id);
        
    std::cout << THE_END << std::endl;
    motherClass->deleteAll();
}