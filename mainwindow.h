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

/*
 * Main class responsible for all operations triggered from GUI.
 *
 * Allows:
 *       - switching modes: alphabet to Morse Code translation and the opposite.
 *       - grabbing events: keyboard pressed in input text edit box
 *       - handling translation in both direction
 *       - clear all button action
 *       - adding instructions for a user
 *       - adding warning in a gui in case of not allowed key being pressed.
 *
 */
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
    void on_modeButton_clicked();
    void on_clearAllButton_clicked();
    bool eventFilter(QObject *object, QEvent *event);

    void on_convertButton_clicked();

private:
    void keyPressedEvent(QEvent *event);
    bool handleASCII2MorseTranslation(QObject *object, QEvent *event);
    bool handleMorse2AlphabetTranslation(QObject *object, QEvent *event);

    Ui::MainWindow *ui;
    char temp_key;
    MorseTranslator *translator;
    enum TRANSLATOR_MODE mode;
    void clearWarningLabel();
    std::string *str_buff; // string buffer for each letter encoded in Morse Code
};
#endif // MAINWINDOW_H
