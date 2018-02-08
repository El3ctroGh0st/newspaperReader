#include "newspaperreader.hpp"

#include "addsourcedialog.hpp"

#include <QFormLayout>
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

    connect(pars, &XMLParser::parsingFinished, this, NewspaperReader::getResult);
}

void NewspaperReader::setupUI()
{
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle(tr("RSS Reader"));

    centralLayout = new QVBoxLayout;

    rssBox = new QGroupBox(this);
    rssBox->setTitle(tr("RSS Feed"));
    setupRSSBox();

    buttonLayout = new QHBoxLayout;
    buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    refreshButton = new QPushButton(this);
    addButton = new QPushButton(this);
    refreshButton->setText(tr("Refresh"));
    addButton->setText(tr("Add"));

    buttonLayout->addItem(buttonSpacer);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(addButton);


    centralLayout->addWidget(rssBox);
    centralLayout->addLayout(buttonLayout);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    this->resize(500, 600);
}

void NewspaperReader::updateTable()
{
    rssTable->setRowCount(titles.size());
    rssTable->setColumnCount(5);

    for(int i = 0; i < titles.size(); ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
                rssTable->setItem(i, j, new QTableWidgetItem(titles.at(i).at(j)));
        }
    }
}

void NewspaperReader::setupRSSBox()
{
    QVBoxLayout *rssBoxLayout = new QVBoxLayout;
    rssTable = new QTableWidget(this);
    rssBoxLayout->addWidget(rssTable);

    rssBox->setLayout(rssBoxLayout);
}
