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
    connect(this, &XMLParser::downloadComplete, this, &XMLParser::parseContent);

    qmanag->get(qreq);
}

void XMLParser::readContent(QNetworkReply *qrep)
{
    QByteArray content;
    content = qrep->readAll();
    downloadData = QString(content);
    emit downloadComplete();
}

void XMLParser::parseContent()
{
    QXmlStreamReader *qxml = new QXmlStreamReader(downloadData);
    bool mainBody = false;
    QStringList items;
    QVector<QString> data;
    items << "title" << "link" << "description" << "pubDate";

    while(!(qxml->atEnd()))
    {
        QString name = qxml->name().toLatin1();
        if(name == "item" && !mainBody)
        {
            mainBody = true;
        }
        if(items.contains(name) && qxml->tokenType() == QXmlStreamReader::StartElement && mainBody)
        {
            if(name == "title")
            {
                //Prevent from being pushed back on first loop
                if(!data.empty())
                    titles.push_back(data);
                data.clear();
                data.push_back(qxml->readElementText());
            }
            else
            {
                data.push_back(qxml->readElementText());
            }
        }
        qxml->readNext();
    }

    emit parsingFinished();
}
