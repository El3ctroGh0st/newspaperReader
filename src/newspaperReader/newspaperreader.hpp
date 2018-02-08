#ifndef NEWSPAPERREADER_HPP
#define NEWSPAPERREADER_HPP

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableWidget>
#include <QVBoxLayout>

#include "xmlparser.hpp"

class NewspaperReader : public QMainWindow
{
    Q_OBJECT

public:
    NewspaperReader(QWidget *parent = 0);
    ~NewspaperReader();

    void setupUI();

    void setupRSSBox();
    void updateTable();

public slots:
    void getResult();
    void addSource();

private:
    QString newspaperName;
    QVector<QVector<QString>> titles;

    XMLParser *pars = nullptr;

    QWidget *centralWidget = nullptr;
    QVBoxLayout *centralLayout = nullptr;
    QMenuBar *menuBar = nullptr;

    QGroupBox *rssBox = nullptr;
    QVBoxLayout *rssBoxLayout = nullptr;
    QTableWidget *rssTable = nullptr;

    QHBoxLayout *buttonLayout = nullptr;
    QSpacerItem *buttonSpacer = nullptr;
    QPushButton *refreshButton = nullptr;
    QPushButton *addButton = nullptr;

};

#endif // NEWSPAPERREADER_HPP
