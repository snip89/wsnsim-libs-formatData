#ifndef FORMATPARAMS_H
#define FORMATPARAMS_H

#include <QMap>
#include <QString>
#include <QList>

typedef QMap<QString, QString> AttrInfo;
typedef AttrInfo FieldInfo;
typedef AttrInfo FormatInfo;
typedef QList<FieldInfo> FieldsInfo;

class Format
{
public:
    FormatInfo formatInfo;
    FieldsInfo fieldsInfo;
    AttrInfo argument;
};

#endif // FORMATPARAMS_H
