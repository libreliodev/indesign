//
//  LIBStringUtils.cpp
//  Librelio
//
//  Created by Geert on 17/08/14.
//
//

#include "LIBStringUtils.h"

std::vector<std::string>& LIBStringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> LIBStringUtils::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}