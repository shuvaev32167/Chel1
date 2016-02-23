#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextBrowser>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

#include "Trigon.h"
#include "Weight.h"
#include "Settings.h"

#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButtonRabb_clicked();

};

#endif // MAINWINDOW_H
