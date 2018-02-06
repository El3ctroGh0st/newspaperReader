#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject *parent = 0) {}
    XMLParser(QUrl link, QObject *parent = 0) : downloadLink(link) {}

    QString getContent() const { return downloadData; }
    QStringList getTitles() const { return titles; }
    void downloadXML();

public slots:
    void readContent(QNetworkReply *);
    void parseContent();

signals:
    void downloaded();

private:
    QUrl downloadLink;
    QString downloadData;
    QStringList titles;
};

#endif // XMLPARSER_HPP
