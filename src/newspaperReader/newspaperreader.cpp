#include "newspaperreader.hpp"

#include "addsourcedialog.hpp"

#include <QFont>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidgetItem>

NewspaperReader::NewspaperReader(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    connect(addButton, &QPushButton::pressed, this, &NewspaperReader::addSource);
}

NewspaperReader::~NewspaperReader()
{

}

void NewspaperReader::getResult()
{
    QVector<QVector<QString>> parsedTitles = pars->getTitles();

    for(int i = 0; i < parsedTitles.size(); ++i)
    {
        parsedTitles[i].push_back(newspaperName);
    }

    for(int i = 0; i < parsedTitles.size(); ++i)
    {
        titles.push_back(parsedTitles.at(i));
    }

    updateTable();
}

void NewspaperReader::addSource()
{
    QUrl url;
    newspaperName = "";

    AddSourceDialog *sdialog = new AddSourceDialog(this);
    sdialog->show();

    if(sdialog->exec() == QDialog::Accepted)
    {
        url = sdialog->getSourceURL();
        newspaperName = sdialog->getSourceTitle();
        delete sdialog;
    }
    pars = new XMLParser(url, this);
    pars->downloadXML();
    qDebug() << url;

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
    centralLayout->addLayout(buttonLayout);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    this->resize(800, 900);
}

void NewspaperReader::updateTable()
{
    QStringList headers;
    headers << tr("Title") << tr("Newspaper");

    rssTable->setRowCount(titles.size());
    rssTable->setColumnCount(2);
    rssTable->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < titles.size(); ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(j == 0)
                rssTable->setItem(i, 0, new QTableWidgetItem(titles.at(i).at(0)));
            if(j == 4)
                rssTable->setItem(i, 1, new QTableWidgetItem(titles.at(i).at(4)));
        }
        rssTable->setColumnWidth(i, 600);
    }

    QFont tableFont = rssTable->horizontalHeader()->font();
    tableFont.setPointSize(10);
    rssTable->setFont(tableFont);
}

void NewspaperReader::setupSourcesBox()
{
    QVBoxLayout *sourcesBoxLayout = new QVBoxLayout;
    sourcesList = new QListView(this);
    sourcesList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sourcesBoxLayout->addWidget(sourcesList);

    sourcesBox->setLayout(sourcesBoxLayout);
}

void NewspaperReader::setupRSSBox()
{
    QVBoxLayout *rssBoxLayout = new QVBoxLayout;
    rssTable = new QTableWidget(this);

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
