#ifndef __security_h__
#define __security_h__
#include <iostream>

class Criptor{
public:
    static std::string encrypt(std::string);
    static std::string decrypt(std::string);
};

#endif
