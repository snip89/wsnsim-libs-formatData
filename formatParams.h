#ifndef FORMATPARAMS_H
#define FORMATPARAMS_H

#include <QMap>
#include <QString>
#include <QList>

typedef QMap<QString, QString> AttrInfo;
typedef AttrInfo FieldInfo;
typedef QList<FieldInfo> FieldsInfo;

class Format
{
public:
    QString type;
    FieldsInfo fieldsInfo;
};

#endif // FORMATPARAMS_H
