//
//  LIBStringUtils.h
//  Librelio
//
//  Created by Geert on 17/08/14.
//
//

#ifndef __Librelio__LIBStringUtils__
#define __Librelio__LIBStringUtils__

#include <iostream>

class LIBStringUtils
{
public:
    std::vector<std::string> split(const std::string &s, char delim);

private:
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
};

#endif /* defined(__Librelio__LIBStringUtils__) */
