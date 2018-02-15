#ifndef NEWSPAPERREADER_HPP
#define NEWSPAPERREADER_HPP

#include <QMainWindow>
#include <QGroupBox>
#include <QListView>
#include <QPushButton>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
#include <QVBoxLayout>

#include "xmlparser.hpp"

#include "article.hpp"

class NewspaperReader : public QMainWindow
{
    Q_OBJECT

public:
    NewspaperReader(QWidget *parent = 0);
    ~NewspaperReader();

    void resetTable();

    void setupUI();
    void setupRSSBox();
    void setupSourcesBox();

public slots:
    void getResult();
    void addSource();
    void updateShowList();
    void updateTable();
    void changeFilter();
    void openWebsite(const QModelIndex);

private:
    QString currentTag = "All";
    QVector<Article> articleList;
    QVector<Article *> articleShowList;
    QString newspaperName;

    //UI SETUP
    XMLParser *pars = nullptr;

    QWidget *centralWidget = nullptr;
    QHBoxLayout *centralLayout = nullptr;
    QMenuBar *menuBar = nullptr;

    QGroupBox *sourcesBox = nullptr;
    QStringList sourcesStringList;
    QStringListModel *sourcesStringListModel = nullptr;
    QListView *sourcesList = nullptr;

    QGroupBox *rssBox = nullptr;
    QStandardItemModel *rssModel = nullptr;
    QVBoxLayout *rssBoxLayout = nullptr;
    QTableView *rssTable = nullptr;

    QHBoxLayout *buttonLayout = nullptr;
    QSpacerItem *buttonSpacer = nullptr;
    QPushButton *refreshButton = nullptr;
    QPushButton *addButton = nullptr;

};

#endif // NEWSPAPERREADER_HPP
