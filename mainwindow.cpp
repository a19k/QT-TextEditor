#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFontComboBox>
#include <QMessageBox>
#include <QPushButton>
#include "find.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f=new Find(this);
    r=new Replace(this);

    //FIND WINDOW KONEKCIJE

    //Find action poziva Find Window
    connect(ui->actionFind,SIGNAL(triggered(bool)),this,SLOT(showFindWindow()));

    //Find Next dugme poziva findNextHandler
    connect(f,SIGNAL(findNext(QString&,bool,bool)),this,SLOT(findNextHandler(QString&,bool,bool)));
    //promjena traženog stringa poziva refreshCursorHandler
    connect(f,SIGNAL(refreshCursor()),this,SLOT(refreshCursorHandler()));




    //REPLACE WINDOW KONEKCIJE

    //Replace action poziva Replace window
    connect(ui->actionReplace,SIGNAL(triggered(bool)),this,SLOT(showReplaceWindow()));

    //Find Next dugme poziva findNextHandler
    connect(r,SIGNAL(findNext(QString&,bool,bool)),this,SLOT(findNextHandler(QString&,bool,bool)));
    //Replace dugme poziva replaceHandler
    connect(r,SIGNAL(replace(QString&)),this,SLOT(replaceHandler(QString&)));
    //promjena traženog stringa poziva refreshCursorHandler
    connect(r,SIGNAL(refreshCursor()),this,SLOT(refreshCursorHandler()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    //otvaranje novog fajla
    nazivDatoteke ="";
    ui->textEdit->setAcceptRichText(1);
    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionOpen_triggered()
{
    //otvaranje postojećeg fajla
    QString datoteka = QFileDialog::getOpenFileName(this,"Otvorite datoteku");
    if(!datoteka.isEmpty()){
        QFile radnaDatoteka(datoteka);
        if(radnaDatoteka.open(QFile::ReadOnly | QFile::Text)){
            nazivDatoteke = datoteka;
            QTextStream upis(&radnaDatoteka);
            QString tekst = upis.readAll();
            radnaDatoteka.close();
            ui->textEdit->setText(tekst);
        }
    }

}

void MainWindow::on_actionSave_triggered()
{
    //spremanje otvorenog fajla
    QFile radnaDatoteka(nazivDatoteke);
    if(radnaDatoteka.open(QFile::WriteOnly | QFile::Text)){
        QTextStream ispis(&radnaDatoteka);
        ispis<<ui->textEdit->toHtml();
        radnaDatoteka.flush();
        radnaDatoteka.close();
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    //Save as komanda na otvorenom fajlu
    QString datoteka = QFileDialog::getSaveFileName(this,"Sacuvaj datoteku");
    if(!datoteka.isEmpty()){
        nazivDatoteke = datoteka;
        on_actionSave_triggered();

    }

}

void MainWindow::on_actionCut_triggered()
{
    // Cut komanda na označenom tekstu
    ui->textEdit->cut();

}

void MainWindow::on_actionCopy_triggered()
{
    //Copy komanda na označenom tekstu
    ui->textEdit->copy();

}

void MainWindow::on_actionPaste_triggered()
{
    //Paste komanda na označenom tekstu
    ui->textEdit->paste();

}

void MainWindow::on_actionUndo_triggered()
{
    //Undo komanda
    ui->textEdit->undo();

}

void MainWindow::on_actionRedo_triggered()
{
    //Redo komanda
    ui->textEdit->redo();


}

void MainWindow::on_actionBold_toggled(bool arg1)
{
    //Bold
    if(arg1)
        ui->textEdit->setFontWeight(QFont::Bold);
    else
        ui->textEdit->setFontWeight(QFont::Normal);
}

void MainWindow::on_actionItalic_toggled(bool arg1)
{
    //Italic
    ui->textEdit->setFontItalic(arg1);

}

void MainWindow::on_actionUnderline_toggled(bool arg1)
{
    //Underline
    ui->textEdit->setFontUnderline(arg1);
}

void MainWindow::on_fontWheel_currentFontChanged(const QFont &f)
{
    //mijenjanje fonta na označenom tekstu uslijed promjene na fontWheel widgetu
    ui->textEdit->setFontFamily(f.family());
}

void MainWindow::on_fontSizeWheel_valueChanged(int arg1)
{
    //mijenjanje veličine fonta na označenom tekstu uslijed promjene na fontSizeWheel widgetu
    ui->textEdit->setFontPointSize(arg1);
}

void MainWindow::on_lAllignButton_clicked()
{
    //lijevo poravnavanje teksta uslijed klika na dugme
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_centerButton_clicked()
{
    //centritranje teksta uslijed klika na dugme
    ui->textEdit->setAlignment(Qt::AlignHCenter);
}

void MainWindow::on_rAllignButton_clicked()
{
    //desno poravnavanje teksta uslijed klika na dugme
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_justifyButton_clicked()
{
    //justify poravnavanje teksta uslijed klika na dugme
    ui->textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    //Pri svakoj promjeni pozicije kursora:

    //Bold dugme update
    if(ui->textEdit->fontWeight()==75)
        ui->actionBold->setChecked(1);
    else
        ui->actionBold->setChecked(0);

    //Italic dugme update
    if(ui->textEdit->fontItalic())
        ui->actionItalic->setChecked(1);
    else
        ui->actionItalic->setChecked(0);

    //Underline dugme update
    if(ui->textEdit->fontUnderline())
        ui->actionUnderline->setChecked(1);
    else
        ui->actionUnderline->setChecked(0);

    //Font Wheel update
    QFont *family=new QFont("MS Shell Dlg 2",14,QFont::Normal);

    if(ui->textEdit->fontFamily()=="")
        ui->fontWheel->setCurrentFont(*family);
    else
        ui->fontWheel->setCurrentFont(ui->textEdit->fontFamily());

    //Font Size Wheel update
    if(ui->textEdit->fontPointSize()==0)
        ui->fontSizeWheel->setValue(14);
    else
        ui->fontSizeWheel->setValue(ui->textEdit->fontPointSize());

}


void MainWindow::showFindWindow(){

    //otvara Find window i postavlja kursor na početak doumenta
    QTextCursor c=ui->textEdit->textCursor();
    c.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(c);
    f->exec();

}

void MainWindow::refreshCursorHandler(){

    //Postavlja kursor na početak dokumenta
    QTextCursor c=ui->textEdit->textCursor();
    c.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(c);

}

void MainWindow::findNextHandler(QString &word,bool caseSensitive,bool matchWholeWords){

    //pretražuje dokument za traženu riječ po postavljenim kriterijima(Case sensitivity i da li je traženi string segment ili cijela riječ)
    bool err=0;

    if((caseSensitive==0) & (matchWholeWords==0))
        err=ui->textEdit->find(word);
    else if(caseSensitive==0 && matchWholeWords==1)
        err=ui->textEdit->find(word,QTextDocument::FindWholeWords);
    else if(caseSensitive==1 && matchWholeWords==0)
        err=ui->textEdit->find(word,QTextDocument::FindCaseSensitively);
    else if(caseSensitive==1 && matchWholeWords==1)
        err=ui->textEdit->find(word,QTextDocument::FindWholeWords|QTextDocument::FindCaseSensitively);

    if(err==0){
        QMessageBox *noMatch=new QMessageBox(f);
        noMatch->setWindowTitle("No match found!");
        noMatch->setText("No match found for your word: "+word);
        noMatch->exec();
    }
    QPushButton *temp=r->findChild<QPushButton*>("replace");
    temp->setEnabled(err);
}

void MainWindow::showReplaceWindow(){

    //otvara Replace Window
    QTextCursor c=ui->textEdit->textCursor();
    c.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(c);

    QPushButton *temp=r->findChild<QPushButton*>("replace");
    temp->setEnabled(0);

    r->exec();

}

void MainWindow::replaceHandler(QString &word){

    ui->textEdit->textCursor().insertText(word);

}
