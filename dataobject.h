#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QString>
#include <QStringList>
#include <vector>
#include <unordered_map>
#include <set>

class DataObject
{
public:
    DataObject() = default;
    QStringList column_names_;

    std::unordered_map<int, QString> projects_;
    std::unordered_map<std::string, int> rev_projects_;

    std::vector< std::vector<QString> > faq_values_;
    std::set<int> enum_cols;
};

#endif // DATAOBJECT_H
