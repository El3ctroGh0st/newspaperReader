#include "newspaperreader.hpp"

#include "xmlparser.hpp"

NewspaperReader::NewspaperReader(QWidget *parent)
    : QMainWindow(parent)
{
    XMLParser *pars = new XMLParser(QUrl("https://derstandard.at/?page=rss&ressort=seite1"), this);
    pars->downloadXML();

}

NewspaperReader::~NewspaperReader()
{

}
