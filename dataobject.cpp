#include "dataobject.h"

QStringList DataObject::return_states_atIndex(int i)
{
    QStringList ret;
    for(auto it : projects_)
    {
        ret.push_back(it.second);
    }
    return ret;
}
