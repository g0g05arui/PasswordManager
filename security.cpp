#include "security.h"
#include <sstream>


static std::string Criptor::encrypt(std::string s){
    std::ostringstream oss;
    for(int i=0;i<s.size();i++){
        int nr=(int)s[i];
        while(nr)
            oss<<nr%2,nr/=2;
        oss<<" ";
    }
    return oss.str();
}

static std::string Criptor::decrypt(std::string s){
    std::ostringstream oss;
    int p2=1,aux=0;
    if(s.back()!=' ')
        s.push_back(' ');
    for(int i=0;i<s.size();i++){
        if(s[i]==' ')
            oss<<(char)aux,aux=0,p2=1;
        else
            aux+=p2*(s[i]-'0'),p2*=2;
    }
    return oss.str();
}
