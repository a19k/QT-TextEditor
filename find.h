#ifndef FIND_H
#define FIND_H

#include <QDialog>

namespace Ui {
class Find;
}

class Find : public QDialog
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    ~Find();

signals:
    void findNext(QString &word,bool caseSensitive,bool matchWholeWords);

    void refreshCursor();

private slots:
    void on_fNext_clicked();

    void on_lineEdit_textEdited();

private:
    Ui::Find *ui;
};

#endif // FIND_H
