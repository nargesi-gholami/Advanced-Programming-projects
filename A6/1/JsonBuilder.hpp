#ifndef __JSON_BUILDER_H__
#define __JSON_BUILDER_H__

#include <iostream>
#include <string>
#include <vector>
#include "object.hpp"
#include "error.hpp"

#define ARRAY "array"
#define OBJECT "object"
#define QUTATION '"'
#define EMPTY_STRING ""
#define MOTHER_NAME "motherObject"
#define START "{"
#define THE_END "}"

#define  MOTHER_ID 0

class JsonBuilder
{
    public:
        JsonBuilder();
        void print(int id);
        void isArray(int id);
        void isObject(int id);
        int check(int parentId);
        void addIntegerToArray(int parentId, int value);
        void composeArrayPart(int parentId,std::string value);
        void addStringToArray(int parentId, std::string value);
        int addContainerToArray(int parentId, std::string type);
        void compose(int parentId, std::string key,std::string value);
        void addIntegerToObject(int parentId, std::string key, int value);
        void addStringToObject(int parentId, std::string key, std::string value);
        int addContainerToObject(int parentId, std::string key, std::string type);

    private:
        fatherObject* motherClass;
        std::vector<int> allId;
        std::vector<int> arrayId;
        std::vector<int> objectId;
        int number;
};

#endif 