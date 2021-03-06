#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <QString>
#include <QStringList>
#include <QUrl>

class Article
{
public:
    Article() = default;
    Article(QString title, QString pubDate, QUrl linkAddress, QString newspaper) : title(title), pubDate(pubDate), linkAddress(linkAddress), newspaper(newspaper), show(true) {tags << newspaper << "All";}

    void setTitle (const QString& title) {this->title = title;}
    void setPubDate(const QString& pubDate) {this->pubDate = pubDate;}
    void setNewspaper (const QString &newspaper) {this->newspaper = newspaper;}
    void setLinkAddress(const QUrl& linkAddress) {this->linkAddress = linkAddress;}
    void addTag(const QString& tag) {this->tags << tag;}
    void setShow(const bool show) {this->show = show;}

    QString getTitle() const {return title;}
    QString getPubDate() const {return pubDate;}
    QString getNewspaper() const {return newspaper;}
    QUrl getLinkAddress() const {return linkAddress;}
    QStringList getTags() const {return tags;}
    bool getShow() const {return show;}

private:
    QString title;
    QString pubDate;
    QUrl linkAddress;
    QString newspaper;
    QStringList tags;
    bool show;
};

#endif // ARTICLE_HPP
