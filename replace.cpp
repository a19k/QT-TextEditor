#include "replace.h"
#include "ui_replace.h"

Replace::Replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Replace)
{
    ui->setupUi(this);

    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(close()));

}

void Replace::on_fNext_clicked()
{
    QString word=ui->findEdit->text();
    bool caseSensitive=ui->caseSensitivity->isChecked();
    bool matchWholeWords=ui->matchWholeWords->isChecked();

    emit findNext(word,caseSensitive,matchWholeWords);
}

void Replace::on_replace_clicked()
{
    ui->replace->setEnabled(0);

    QString word=ui->findEdit->text();
    QString word2=ui->replaceEdit->text();

    emit replace(word,word2);
}

Replace::~Replace()
{
    delete ui;
}

void Replace::on_findEdit_textEdited()
{
    emit refreshCursor();
}
