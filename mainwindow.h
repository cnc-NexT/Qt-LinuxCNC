#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "QTimer"
#include "QtCore"
#include "QtGui"
#include "QTreeWidget"
#include "QTreeWidgetItem"

#include "emc.hh"
#include "emc_nml.hh"
#include "emcpos.h"

//#include "/home/udos/LLExec_PluginHeaders/LLSymbols/LLSymbols.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void addTreeRoot(QString tagNumber, QString tagName, QString tagType);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QString Description, QString tagType );


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer timer;


public slots:
        void updnmlval();


private slots:
    void updateRandomNumber();

    void on_pbtn_00_MenuBottom_pressed();

    void on_pbtn_00_MenuBottom_released();

    void on_pbtn_09_MenuBottom_pressed();

//    void on_pbtn_00_MenuLeft_pressed();

private:
    Ui::MainWindow *ui;

protected:

//    void timerEvent(QTimerEvent *);

};

#endif // MAINWINDOW_H
