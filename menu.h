#ifndef __menu_h__
#define __menu_h__
#include "includes.h"
#include <fstream>
#include <sstream>

class Menu{
protected:
    Manager mng;
    std::ofstream new_passwds;
    std::ifstream passwds;
    void init();
public:
    Manager & manager(){return mng;};
    Menu();
    void refresh();
    int display();
    void handle();
};

#endif
