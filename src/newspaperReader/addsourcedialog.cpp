#include "addsourcedialog.hpp"
#include "ui_addsourcedialog.h"

#include <QDebug>
#include <QPushButton>

AddSourceDialog::AddSourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSourceDialog)
{
    ui->setupUi(this);
    //Allow translation with QLinguist
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(true);

    connect(ui->sourceNameEdit, &QLineEdit::textEdited, this, &AddSourceDialog::checkEmptyFields);
    connect(ui->sourceAddressEdit, &QLineEdit::textEdited, this, &AddSourceDialog::checkEmptyFields);
}

AddSourceDialog::~AddSourceDialog()
{
    delete ui;
}

void AddSourceDialog::checkEmptyFields(QString text)
{
    if(!(ui->sourceAddressEdit->text().isEmpty()) && !(ui->sourceNameEdit->text().isEmpty()))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(false);

        sourceTitle = ui->sourceNameEdit->text();
        sourceURL = QUrl(ui->sourceAddressEdit->text());
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setDisabled(true);
    }
}
