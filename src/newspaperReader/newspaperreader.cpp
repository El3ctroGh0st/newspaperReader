#include "newspaperreader.hpp"

#include "addsourcedialog.hpp"

#include <QDesktopServices>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QFont>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMenu>

NewspaperReader::NewspaperReader(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    loadEntries();

    connect(addButton, &QPushButton::pressed, this, &NewspaperReader::addSourceDialog);
    connect(sourcesList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NewspaperReader::changeFilter);
    connect(this, &NewspaperReader::windowClosed, this, &NewspaperReader::saveEntries);
}

NewspaperReader::~NewspaperReader()
{
}

void NewspaperReader::getResult()
{
    QVector<QVector<QString>> parsedTitles = pars->getTitles();

    for(int i = 0; i < parsedTitles.size(); ++i)
    {
        QString name = parsedTitles.at(i).at(0);
        QUrl link = parsedTitles.at(i).at(1);
        QString pubDate = parsedTitles.at(i).at(2);
        QString newspaper = newspaperName;
        Article article(name, pubDate, link, newspaper);
        articleList.push_back(article);
    }
    updateShowList();
}

void NewspaperReader::addSourceDialog()
{
    QUrl dialogURL;
    QString dialogNewspaperName;

    AddSourceDialog *sdialog = new AddSourceDialog(this);
    sdialog->show();

    if(sdialog->exec() == QDialog::Accepted)
    {
        dialogURL = sdialog->getSourceURL();
        dialogNewspaperName = sdialog->getSourceTitle();
        delete sdialog;
        addSource(dialogURL, dialogNewspaperName);
    }
}

void NewspaperReader::addSource(QUrl url, QString name)
{
    newspaperName = name;
    sourcesVector.push_back(new Newspaper(name, url));
    sourcesListModel->appendRow(new QStandardItem(sourcesVector[sourcesVector.size() - 1]->getName()));

    pars = new XMLParser(url, this);
    pars->downloadXML();
    connect(pars, &XMLParser::parsingFinished, this, NewspaperReader::getResult);
}

void NewspaperReader::setupUI()
{
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle(tr("RSS Reader"));

    centralLayout = new QHBoxLayout;

    sourcesBox = new QGroupBox(this);
    sourcesBox->setTitle(tr("Sources"));

    rssBox = new QGroupBox(this);
    rssBox->setTitle(tr("RSS Feed"));
    setupSourcesBox();
    setupRSSBox();

    centralLayout->addWidget(sourcesBox);
    centralLayout->addWidget(rssBox);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    resize(1200, 900);
}

void NewspaperReader::updateTable()
{
    resetTable();
    QStringList headers;
    headers << tr("Title") << tr("Newspaper");

    rssTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rssModel->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < articleShowList.size(); ++i)
    {
        QList<QStandardItem *> items;
        items << new QStandardItem(articleShowList.at(i)->getTitle()) << new QStandardItem(articleShowList.at(i)->getNewspaper());
        rssModel->appendRow(items);
    }
    rssTable->resizeColumnsToContents();
    rssTable->resizeRowsToContents();

    emit addedEntries();
}

void NewspaperReader::updateShowList()
{
    articleShowList.clear();
    for(auto i = articleList.begin(); i != articleList.end(); ++i)
    {
        if(i->getTags().contains(currentTag))
        {
            articleShowList.push_back(&(*i));
        }
    }
    updateTable();
}

void NewspaperReader::changeFilter()
{
    QModelIndex index = sourcesList->currentIndex();
    currentTag = index.data(Qt::DisplayRole).toString();
    updateShowList();
}

void NewspaperReader::setupSourcesBox()
{
    QVBoxLayout *sourcesBoxLayout = new QVBoxLayout;
    sourcesList = new QListView(this);
    sourcesListModel = new QStandardItemModel(this);
    sourcesList->setModel(sourcesListModel);
    sourcesList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sourcesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sourcesBoxLayout->addWidget(sourcesList);

    QStandardItem *allTag = new QStandardItem("All");
    sourcesListModel->appendRow(allTag);
//    QModelIndex allRow = sourcesListModel->index(1, 1);
//    sourcesList->selectionModel()->select(allRow, QItemSelectionModel::Select);
    sourcesBox->setLayout(sourcesBoxLayout);
}

void NewspaperReader::resetTable()
{
    rssModel->clear();
}

void NewspaperReader::deleteArticle()
{
    QItemSelectionModel *select = rssTable->selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList indexes = select->selectedIndexes();

        for(int i = 0; i < indexes.size(); ++i)
            articleShowList.erase(articleShowList.begin() + indexes.at(i).row());
        updateTable();
    }
}

void NewspaperReader::rightClickMenu()
{
    QMenu *contextMenu = new QMenu(this);

    QAction *deleteAction = new QAction("Delete", this);
    connect(deleteAction, &QAction::triggered, this, &NewspaperReader::deleteArticle);
    contextMenu->addAction(deleteAction);


    contextMenu->exec(QCursor::pos());
}

void NewspaperReader::setupRSSBox()
{
    QVBoxLayout *rssBoxLayout = new QVBoxLayout;
    rssTable = new QTableView(this);
    rssModel = new QStandardItemModel(this);
    rssTable->setModel(rssModel);
    rssTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(rssTable, &QTableView::doubleClicked, this, &NewspaperReader::openWebsite);
    connect(rssTable, &QTableView::customContextMenuRequested, this, &NewspaperReader::rightClickMenu);

    buttonLayout = new QHBoxLayout;
    buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    refreshButton = new QPushButton(this);
    addButton = new QPushButton(this);
    refreshButton->setText(tr("Refresh"));
    addButton->setText(tr("Add"));

    buttonLayout->addItem(buttonSpacer);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(addButton);

    rssBoxLayout->addWidget(rssTable);
    rssBoxLayout->addLayout(buttonLayout);

    rssBox->setLayout(rssBoxLayout);
}

void NewspaperReader::saveEntries()
{
    QFile file("sources.txt");

    if(!file.open(QIODevice::WriteOnly))
        qWarning() << "Failed to save entries!";

    QTextStream out(&file);

    for(int i = 0; i < sourcesVector.size(); ++i)
    {
        out << sourcesVector.at(i)->getName() << "\t" << sourcesVector.at(i)->getURL().toString();
        if(i != sourcesVector.size() - 1)
            out << "\n";
    }

    file.close();
}

void NewspaperReader::loadEntries()
{
    QFile file("sources.txt");

    if(!file.open(QIODevice::ReadOnly))
        qWarning() << "Failed to load entries!";

    QTextStream inputStream(&file);
    QString text = inputStream.readAll();
    QStringList textList = text.split('\n');
    QVector<QPair<QString, QUrl>> entries;

    for(int i = 0; i < textList.size(); ++i)
    {
        QString temp = textList.at(i);
        temp.remove(QRegExp("\\r"));
        QStringList entryList = temp.split('\t');
        qDebug() << entryList.at(0) << " " << entryList.at(1);
        entries.push_back(qMakePair(entryList.at(0), QUrl(entryList.at(1))));
    }

    for(int i = 0; i < entries.size(); ++i)
    {
        addSource(QUrl(entries.at(i).second), entries.at(i).first);

        QEventLoop pauseLoop;
        connect(this, &NewspaperReader::addedEntries, &pauseLoop, &QEventLoop::quit);
        pauseLoop.exec();
    }
}

void NewspaperReader::openWebsite(const QModelIndex index)
{
    Article *article = articleShowList.at(index.row());
    QDesktopServices::openUrl(article->getLinkAddress());
}
