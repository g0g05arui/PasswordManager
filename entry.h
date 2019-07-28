#ifndef __entry_h__
#define __entry_h__
#include <vector>
#include <iostream>
#include <algorithm>

class Entry{
protected:
    std::string _username,_password,_url;
    std::vector< std::string > _tags;
public:
    const std::string & username(){return _username;};
    const std::string & password(){return _password;};
    const std::string & url(){return _url;};
    std::vector< std::string > & tags(){return _tags;};
    Entry(std::string usr,std::string pswd,std::string ur):_username(usr),_password(pswd),_url(ur){}
    void add_tag(std::string tag);
    void remove_tag(std::string tag);
    void change_username(std::string usr);
    void change_password(std::string pswd);
    void change_url(std::string ur);
    void clear_tags();
};

#endif
