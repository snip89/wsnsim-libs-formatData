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
};

#endif // FORMATDATA_H
