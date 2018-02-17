#include "newspaperreader.hpp"
#include <QApplication>

//Fix index automatically changing on adding new source
//FIx automatic scrolling up on deletion

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewspaperReader w;
    w.show();

    return a.exec();
}
