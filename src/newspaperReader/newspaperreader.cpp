#include "newspaperreader.hpp"

#include "addsourcedialog.hpp"

#include <QDesktopServices>
#include <QFont>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidgetItem>

NewspaperReader::NewspaperReader(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    connect(addButton, &QPushButton::pressed, this, &NewspaperReader::addSourceDialog);
    connect(sourcesList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NewspaperReader::changeFilter);
    connect(rssTable, &QTableView::doubleClicked, this, &NewspaperReader::openWebsite);
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
    sourcesStringList += newspaperName;
    sourcesStringListModel->setStringList(sourcesStringList);
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
    sourcesStringListModel = new QStringListModel(this);
    sourcesList->setModel(sourcesStringListModel);
    sourcesList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sourcesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sourcesBoxLayout->addWidget(sourcesList);

    sourcesStringList << "All";
    sourcesStringListModel->setStringList(sourcesStringList);

    sourcesBox->setLayout(sourcesBoxLayout);
}

void NewspaperReader::resetTable()
{
    rssModel->clear();
}

void NewspaperReader::setupRSSBox()
{
    QVBoxLayout *rssBoxLayout = new QVBoxLayout;
    rssTable = new QTableView(this);
    rssModel = new QStandardItemModel(this);
    rssTable->setModel(rssModel);

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

void NewspaperReader::openWebsite(const QModelIndex index)
{
    Article *article = articleShowList.at(index.row());
    QDesktopServices::openUrl(article->getLinkAddress());
}
