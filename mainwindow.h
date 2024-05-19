#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QtGui>
#include <QtCore>
#include <QString>
#include <QSpinBox>

namespace Ui {
class MainWindow;
class FindBox;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionBold_toggled(bool arg1);

    void on_actionItalic_toggled(bool arg1);

    void on_actionUnderline_toggled(bool arg1);

    void on_textEdit_cursorPositionChanged();

    void on_fontWheel_currentFontChanged(const QFont &f);

    void on_fontSizeWheel_valueChanged(int arg1);

    void on_lAllignButton_clicked();

    void on_centerButton_clicked();

    void on_rAllignButton_clicked();

    void on_justifyButton_clicked();

private:
    Ui::MainWindow *ui;
    QString nazivDatoteke;
};

class FindBox: public QWindow
{
    Q_OBJECT



};

#endif // MAINWINDOW_H
