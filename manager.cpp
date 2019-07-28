#include "manager.h"

int Manager::add_entry(Entry ent){
    bool ok=1;
    for(int i=0;i<_entries.size();i++)
        if(_entries[i].url()==ent.url() && _entries[i].username()==ent.username()){
            ok=0;
            break;
        }
    if(ok)
        _entries.push_back(ent);
    return ok;
}

void Manager::remove_entry(Entry ent){
    for(int i=0;i<_entries.size();i++)
        if(_entries[i].url()==ent.url() && _entries[i].username()==ent.username()){
            _entries.erase(_entries.begin()+i);
            break;
    }
}
