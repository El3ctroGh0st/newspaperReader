#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject *parent = 0) : QObject(parent) {}
    XMLParser(QUrl link, QObject *parent = 0) : QObject(parent), downloadLink(link) {}

    QString getContent() const { return downloadData; }
    QVector<QVector<QString>> getTitles() const { return titles; }
    void downloadXML();

public slots:
    void readContent(QNetworkReply *);
    void parseContent();

signals:
    void downloadComplete();
    void parsingFinished();

private:
    QUrl downloadLink = QUrl();
    QString downloadData;

    //[0] -> title
    //[1] -> link
    //[2] -> description
    //[3] -> pubDate
    QVector<QVector<QString>> titles;
};

#endif // XMLPARSER_HPP
