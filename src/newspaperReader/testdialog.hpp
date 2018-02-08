#ifndef TESTDIALOG_HPP
#define TESTDIALOG_HPP

#include <QDialog>

namespace Ui {
class testDialog;
}

class testDialog : public QDialog
{
    Q_OBJECT

public:
    explicit testDialog(QWidget *parent = 0);
    ~testDialog();

private:
    Ui::testDialog *ui;
};

#endif // TESTDIALOG_HPP
