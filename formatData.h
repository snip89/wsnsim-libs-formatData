#ifndef FORMATDATA_H
#define FORMATDATA_H

#include <QtXml>
#include <QObject>
#include <QTextCodec>
#include <QFile>
#include <QDebug>

#include "formatParams.h"

class FormatData : public QObject
{
    Q_OBJECT
public:
    FormatData();

    Format* load(QString formatFileName, QString* errorMessage);
    ArgumentsInfo loadArguments(QDomNode dn_node);
    FieldsInfo loadFields(QDomNode dn_node);
};

#ifdef Q_WS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

extern "C" MY_EXPORT Format* load(QString projectFileName, QString* errorMessage);

#endif // FORMATDATA_H
