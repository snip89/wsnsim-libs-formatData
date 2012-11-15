#ifndef FORMATPARAMS_H
#define FORMATPARAMS_H

#include <QMap>
#include <QString>
#include <QList>
#include <QFile>

typedef QMap<QString, QString> AttrInfo;
typedef AttrInfo FormatInfo;
typedef AttrInfo LuaInfo;

class Format
{
public:
    QString fileName;
    FormatInfo formatInfo;
    LuaInfo luaInfo;
    AttrInfo argument;
};

#endif // FORMATPARAMS_H
