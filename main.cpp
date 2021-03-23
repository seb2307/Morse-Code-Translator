#include "mainwindow.h"
#include "MorseBST.h"

#include <QApplication>
int morsebst::MorseBST::Node::N = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
