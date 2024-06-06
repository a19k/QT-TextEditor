#include "find.h"
#include "ui_find.h"
#include <QApplication>
#include <QDialog>



Find::Find(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
    setFixedSize(400,200);



    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(close()));

}

Find::~Find()
{
    delete ui;
}

void Find::on_fNext_clicked()
{
    QString word=ui->lineEdit->text();
    bool caseSensitive=ui->caseSensitivity->isChecked();
    bool matchWholeWords=ui->matchWholeWords->isChecked();

    emit findNext(word,caseSensitive,matchWholeWords);
}

void Find::on_lineEdit_textEdited()
{
    emit refreshCursor();
}
