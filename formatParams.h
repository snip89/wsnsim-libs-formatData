#ifndef FORMATPARAMS_H
#define FORMATPARAMS_H

#include <QMap>
#include <QString>
#include <QList>

typedef QMap<QString, QString> AttrInfo;
typedef AttrInfo FieldInfo;
typedef AttrInfo ArgumentInfo;
typedef QList<FieldInfo> FieldsInfo;
typedef QList<ArgumentInfo> ArgumentsInfo;

class Format
{
public:
    QString type;
    ArgumentsInfo argumentsInfo;
    FieldsInfo fieldsInfo;
};

#endif // FORMATPARAMS_H
