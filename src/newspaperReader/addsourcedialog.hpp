#ifndef ADDSOURCEDIALOG_HPP
#define ADDSOURCEDIALOG_HPP

#include <QDialog>
#include <QUrl>

namespace Ui {
class AddSourceDialog;
}

class AddSourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSourceDialog(QWidget *parent = 0);
    ~AddSourceDialog();

    QString getSourceTitle() const { return sourceTitle; }
    QUrl getSourceURL() const { return sourceURL; }

public slots:
    void checkEmptyFields(QString text);

private:
    Ui::AddSourceDialog *ui;

    QString sourceTitle;
    QUrl sourceURL;
};

#endif // ADDSOURCEDIALOG_HPP
