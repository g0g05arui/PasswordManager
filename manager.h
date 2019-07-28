#ifndef __manager_h__
#define __manager_h__
#include "entry.h"

class Manager{
protected:
    std::vector<Entry> _entries;
public:
    int add_entry(Entry);
    void clear(){_entries.clear();};
    void remove_entry(Entry);
    std::vector<Entry> & entries(){return _entries;};
};

#endif
