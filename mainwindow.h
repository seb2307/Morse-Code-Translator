#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <string>
#include "MorseTranslator.h"
#include "MorseBST.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum TRANSLATOR_MODE{
        ASCII_TO_MORSE,
        MORSE_TO_ASCII
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearAll();

private slots:
    void on_pushButton_clicked();
    void on_clearAllButton_clicked();
    bool eventFilter(QObject *object, QEvent *event);

    void on_pushButton_2_clicked();

private:
    void keyPressedEvent(QEvent *event);
    bool handleASCII2MorseTranslation(QObject *object, QEvent *event);
    bool handleMorse2ASCIITranslation(QObject *object, QEvent *event);
    Ui::MainWindow *ui;
    char temp_key;
    MorseTranslator *translator;
    morsebst::MorseBST *morseBst;
    enum TRANSLATOR_MODE mode;
    void clearWarningLabel();
    std::string *str_buff;
};
#endif // MAINWINDOW_H
