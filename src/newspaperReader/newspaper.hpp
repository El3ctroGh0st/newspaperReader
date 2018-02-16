#ifndef NEWSPAPER_HPP
#define NEWSPAPER_HPP

#include <QString>
#include <QUrl>

class Newspaper
{
public:
    Newspaper() = default;
    Newspaper(QString name, QUrl url) : name(name), url(url) {}

    QString getName() {return name;}
    QUrl getURL() {return url;}

    void setName(const QString &name) {this->name = name;}
    void setUrl(const QUrl &url) {this->url = url;}

private:
    QString name;
    QUrl url;
};

#endif // NEWSPAPER_HPP
