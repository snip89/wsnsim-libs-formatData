#include "formatData.h"

FormatData::FormatData() :
    QObject()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
}

Format FormatData::load(QString formatFileName, QString *errorMessage)
{
    Format format;

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
    format.type = root_attr.value();

    QDomNode dn_node = de_root.firstChild();

    while (!dn_node.isNull())
    {
        FieldInfo info;

        QDomNamedNodeMap attributes = dn_node.attributes();
        for (uint index = 0; index < attributes.length(); index++) {
            QDomAttr attr = attributes.item(index).toAttr();
            if (attr.name() == "name")
                info.insert(attr.name(), attr.value());
            if (attr.name() == "length")
                info.insert(attr.name(), attr.value());
        }

        format.fieldsInfo.append(info);

        dn_node = dn_node.nextSibling();
    }

    return format;
}

extern "C" MY_EXPORT Format load(QString projectFileName, QString* errorMessage)
{
    FormatData formatData;
    return formatData.load(projectFileName, errorMessage);
}
