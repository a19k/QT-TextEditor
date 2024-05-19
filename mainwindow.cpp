#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFontComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setFontPointSize(14);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    // New file
    nazivDatoteke ="";
    ui->textEdit->setAcceptRichText(1);
    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionOpen_triggered()
{
    // Open file
    QString datoteka = QFileDialog::getOpenFileName(this,"Otvorite datoteku");
    if(!datoteka.isEmpty()){
        QFile radnaDatoteka(datoteka);
        if(radnaDatoteka.open(QFile::ReadOnly | QFile::Text)){
            nazivDatoteke = datoteka;
            QTextStream upis(&radnaDatoteka);
            QString tekst = upis.readAll();
            radnaDatoteka.close();
            ui->textEdit->setPlainText(tekst);
        }
    }

}

void MainWindow::on_actionSave_triggered()
{
    //Save file
    QFile radnaDatoteka(nazivDatoteke);
    if(radnaDatoteka.open(QFile::WriteOnly | QFile::Text)){
        QTextStream ispis(&radnaDatoteka);
        ispis<<ui->textEdit->toPlainText();
        radnaDatoteka.flush();
        radnaDatoteka.close();
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    //Save as file
    QString datoteka = QFileDialog::getSaveFileName(this,"Sacuvaj datoteku");
    if(!datoteka.isEmpty()){
        nazivDatoteke = datoteka;
        on_actionSave_triggered();

    }

}

void MainWindow::on_actionCut_triggered()
{
    // Cut tekst
    ui->textEdit->cut();

}

void MainWindow::on_actionCopy_triggered()
{
    //Copy tekst
    ui->textEdit->copy();

}

void MainWindow::on_actionPaste_triggered()
{
    //Paste tekst
    ui->textEdit->paste();

}

void MainWindow::on_actionUndo_triggered()
{
    //Undo
    ui->textEdit->undo();

}

void MainWindow::on_actionRedo_triggered()
{
    //Redo
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
    ui->textEdit->setFontFamily(f.family());
}

void MainWindow::on_fontSizeWheel_valueChanged(int arg1)
{
    ui->textEdit->setFontPointSize(arg1);
}

void MainWindow::on_lAllignButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_centerButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignHCenter);
}

void MainWindow::on_rAllignButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_justifyButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    //Bold button update
    if(ui->textEdit->fontWeight()==75)
        ui->actionBold->setChecked(1);
    else
        ui->actionBold->setChecked(0);

    //Italic button update
    if(ui->textEdit->fontItalic())
        ui->actionItalic->setChecked(1);
    else
        ui->actionItalic->setChecked(0);

    //Underline button update
    if(ui->textEdit->fontUnderline())
        ui->actionUnderline->setChecked(1);
    else
        ui->actionUnderline->setChecked(0);

    //Font Wheel update
    ui->fontWheel->setCurrentFont(ui->textEdit->fontFamily());

    //Font Size Wheel update
    ui->fontSizeWheel->setValue(ui->textEdit->fontPointSize());

}
