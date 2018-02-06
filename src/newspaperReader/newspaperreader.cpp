#include "newspaperreader.hpp"

NewspaperReader::NewspaperReader(QWidget *parent)
    : QMainWindow(parent)
{
    pars = new XMLParser(QUrl("https://derstandard.at/?page=rss&ressort=seite1"), this);
    pars->downloadXML();

    connect(pars, &XMLParser::parsingFinished, this, NewspaperReader::printResult);
}

NewspaperReader::~NewspaperReader()
{

}

void NewspaperReader::printResult()
{
    QVector<QVector<QString>> titles = pars->getTitles();

    for(int i = 0; i < titles.size(); ++i)
    {
        QStringList items;
        for(int j = 0; j < titles.at(i).size(); ++j)
            items << titles.at(i).at(j);
        qDebug() << QString::number(i + 1) + ": " << items;
    }
}
