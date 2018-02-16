#include "newspaperreader.hpp"
#include <QApplication>

//Fix delete bug
//Fix index automatically changing on adding new source
//FIx automatic scrolling up on deletion
//Fix double-opening of addSOurceWIndow

//Der Standard	https://derstandard.at/?page=rss&ressort=Seite1
//Die Presse	http://diepresse.com/rss//home
//The Guardian	https://www.theguardian.com/uk/rss

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewspaperReader w;
    w.show();

    return a.exec();
}
