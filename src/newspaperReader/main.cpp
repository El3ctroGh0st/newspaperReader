#include "newspaperreader.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewspaperReader w;
    w.show();

    return a.exec();
}
