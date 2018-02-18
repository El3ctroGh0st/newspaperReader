#ifndef NEWSPAPERREADER_HPP
#define NEWSPAPERREADER_HPP

#include <QCloseEvent>
#include <QMainWindow>
#include <QGroupBox>
#include <QListView>
#include <QPoint>
#include <QPushButton>
#include <QSpacerItem>
#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
#include <QVBoxLayout>

#include "xmlparser.hpp"
#include "article.hpp"
#include "newspaper.hpp"

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
    void addSource(const QUrl, const QString);

    void closeEvent(QCloseEvent *event) {emit windowClosed();
                                         event->accept();}
    void loadEntries();

public slots:
    void addSourceDialog();
    void getResult();
    void updateShowList();
    void updateTable();
    void changeFilter();
    void openWebsite(const QModelIndex);
    void rightClickMenuRSSBox();
    void rightCLickMenuSourcesList();
    void sourcesDeletion();
    void manualDeletion();
    void deleteArticle(QItemSelectionModel*);
    void saveEntries();

signals:
    void windowClosed();
    void addedEntries();

private:
    QString currentTag = "All";
    QVector<Article> articleList;
    QVector<Article *> articleShowList;
    QVector<Newspaper *> sourcesVector;
    QString newspaperName;

    //UI SETUP
    XMLParser *pars = nullptr;

    QWidget *centralWidget = nullptr;
    QHBoxLayout *centralLayout = nullptr;
    QMenuBar *menuBar = nullptr;

    QGroupBox *sourcesBox = nullptr;
    QStringList sourcesStringList;
    QStandardItemModel *sourcesListModel = nullptr;
    QListView *sourcesList = nullptr;

    QGroupBox *rssBox = nullptr;
    QStandardItemModel *rssModel = nullptr;
    QVBoxLayout *rssBoxLayout = nullptr;
    QTableView *rssTable = nullptr;

    QHBoxLayout *buttonLayout = nullptr;
    QSpacerItem *buttonSpacer = nullptr;
    QPushButton *refreshButton = nullptr;
    QPushButton *addButton = nullptr;

    bool openSourceWindow = false;

};

#endif // NEWSPAPERREADER_HPP
