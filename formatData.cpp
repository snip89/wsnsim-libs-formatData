#include "formatData.h"

FormatData::FormatData() :
    QObject()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
}

Format* FormatData::load(QString formatFileName, QString *errorMessage)
{
    Format* format = new Format();

    QFile file(formatFileName);

    QDomDocument dd_doc;

    int errorLine;
    int errorColumn;

    if (!file.open(QFile::ReadOnly))
    {
        qDebug("Error open file: %s", qPrintable(file.error()));
        *errorMessage = QString::number(file.error());

        return format;
    }

    QString content = file.readAll();
    file.close();

    if (!dd_doc.setContent(content, true, errorMessage, &errorLine, &errorColumn)) {

        qDebug("Error in xml structure file: %s\n line %x\n column %x ",
               qPrintable(*errorMessage), errorLine, errorColumn);

        return format;
    }

    QDomElement de_root = dd_doc.documentElement();

    QDomNamedNodeMap root_attributes = de_root.attributes();
    QDomAttr root_attr = root_attributes.item(0).toAttr();
    format->type = root_attr.value();

    QDomNode dn_node = de_root.firstChild();

    while (!dn_node.isNull())
    {
        if(dn_node.nodeName() == "arguments")
            format->argumentsInfo = loadArguments(dn_node);

        if(dn_node.nodeName() == "fields")
            format->fieldsInfo = loadFields(dn_node);

        dn_node = dn_node.nextSibling();
    }

    return format;
}

ArgumentsInfo FormatData::loadArguments(QDomNode dn_node)
{
    QDomNode dn_nextNode = dn_node.firstChild();

    ArgumentsInfo argumentsInfo;

    while (!dn_nextNode.isNull())
    {
        ArgumentInfo argumentInfo;

        QDomNamedNodeMap attributes = dn_nextNode.attributes();
        for (uint index = 0; index < attributes.length(); index++) {
            QDomAttr attr = attributes.item(index).toAttr();
            if (attr.name() == "event")
                argumentInfo.insert(attr.name(), attr.value());
            if (attr.name() == "ID")
                argumentInfo.insert(attr.name(), attr.value());
        }

        argumentsInfo.append(argumentInfo);

        dn_nextNode = dn_nextNode.nextSibling();
    }

    return argumentsInfo;
}

FieldsInfo FormatData::loadFields(QDomNode dn_node)
{
    QDomNode dn_nextNode = dn_node.firstChild();

    FieldsInfo fieldsInfo;

    while (!dn_nextNode.isNull())
    {
        FieldInfo fieldInfo;

        QDomNamedNodeMap attributes = dn_nextNode.attributes();
        for (uint index = 0; index < attributes.length(); index++) {
            QDomAttr attr = attributes.item(index).toAttr();
            if (attr.name() == "name")
                fieldInfo.insert(attr.name(), attr.value());
            if (attr.name() == "length")
                fieldInfo.insert(attr.name(), attr.value());
        }

        fieldsInfo.append(fieldInfo);

        dn_nextNode = dn_nextNode.nextSibling();
    }

    return fieldsInfo;
}

extern "C" MY_EXPORT Format* load(QString formatFileName, QString* errorMessage)
{
    FormatData formatData;
    return formatData.load(formatFileName, errorMessage);
}
