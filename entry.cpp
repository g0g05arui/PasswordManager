#include "entry.h"

void Entry::add_tag(std::string tag){
    if(std::find(_tags.begin(),_tags.end(),tag)==_tags.end())
        _tags.push_back(tag);
}

void Entry::change_password(std::string pswd){
    _password=pswd;
}

void Entry::change_username(std::string usr){
    _username=usr;
}

void Entry::change_url(std::string ur){
    _url=ur;
}

void Entry::clear_tags(){
    _tags.clear();
}

void Entry::remove_tag(std::string tag){
    auto it=std::find(_tags.begin(),_tags.end(),tag);
    if(it!=_tags.end())
        _tags.erase(it);
}
