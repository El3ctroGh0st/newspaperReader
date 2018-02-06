#ifndef NEWSPAPERREADER_HPP
#define NEWSPAPERREADER_HPP

#include <QMainWindow>

#include "xmlparser.hpp"

class NewspaperReader : public QMainWindow
{
    Q_OBJECT

public:
    NewspaperReader(QWidget *parent = 0);
    ~NewspaperReader();

public slots:
    void printResult();

private:
    XMLParser *pars = nullptr;
};

#endif // NEWSPAPERREADER_HPP
