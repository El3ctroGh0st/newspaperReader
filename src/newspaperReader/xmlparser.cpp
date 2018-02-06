#include "xmlparser.hpp"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QXmlStreamReader>

void XMLParser::downloadXML()
{
    QNetworkRequest qreq(downloadLink);
    QNetworkAccessManager *qmanag = new QNetworkAccessManager(this);

    connect(qmanag, &QNetworkAccessManager::finished, this, XMLParser::readContent);
    connect(this, &XMLParser::downloaded, this, &XMLParser::parseContent);

    qmanag->get(qreq);
}

void XMLParser::readContent(QNetworkReply *qrep)
{
    QByteArray content;
    content = qrep->readAll();
    downloadData = QString(content);
    emit downloaded();
}

void XMLParser::parseContent()
{
    QXmlStreamReader *qxml = new QXmlStreamReader(downloadData);

    while(!(qxml->atEnd()))
    {
        if(qxml->name() == "title" && qxml->tokenType() == QXmlStreamReader::StartElement)
            titles << qxml->readElementText();
        qxml->readNext();
    }

    qDebug() << titles;
}
