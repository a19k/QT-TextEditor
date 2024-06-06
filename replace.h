#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = 0);
    ~Replace();

signals:
    void findNext(QString &word,bool caseSensitive,bool matchWholeWords);

    void replace(QString &word,QString &word2);

    void refreshCursor();

public slots:
    void on_findEdit_textEdited();

private slots:
    void on_fNext_clicked();

    void on_replace_clicked();

public:
    Ui::Replace *ui;
};

#endif // REPLACE_H
