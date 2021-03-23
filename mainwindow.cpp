#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

using namespace morsebst;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mode(ASCII_TO_MORSE)
{
    ui->setupUi(this);
    ui->inputTextEdit->installEventFilter(this);
    translator = new MorseTranslator();
    ui->warningLabel->clear();

    str_buff = new std::string();
    ui->modeButton->setText("ASCII TO MORSE");
    ui->clearAllButton->setText("Clear All");
    ui->inputTextEdit->setPlainText("");
    ui->outputText->setPlainText("");
    ui->instructionLabel->setText("Instruction:\nASCII TO MORSE mode:  Insert normal text\nMORSE TO ASCII mode:  Write morse code \".\" or \"-\" separating\nletters by spaces and words by slash \"/\"\nUse Convert Button: it is possible to right mouse click and paste longer text\nand translate the whole input text by pressing convert button.");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete translator;
    delete str_buff;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{    
    if (mode == TRANSLATOR_MODE::ASCII_TO_MORSE && object == ui->inputTextEdit && event->type() == QEvent::KeyPress) {
        return handleASCII2MorseTranslation(object, event);
    }
    else if (mode == TRANSLATOR_MODE::MORSE_TO_ASCII && object == ui->inputTextEdit && event->type() == QEvent::KeyPress) {
        return handleMorse2AlphabetTranslation(object, event);
    }
    else
        return QObject::eventFilter(object, event);
}

bool MainWindow::handleASCII2MorseTranslation(QObject *object, QEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if ((keyEvent->key() >= Qt::Key_A && keyEvent->key() <= Qt::Key_Z) || (keyEvent->key() >= Qt::Key_0 && keyEvent->key() <= Qt::Key_9)) {
        qDebug() << keyEvent->key();

        // HANDLING CONVERTING LETTER
        clearWarningLabel();
        const char* morse_code;
        morse_code = translator->translate2Morse(keyEvent->key());
        ui->outputText->setPlainText(ui->outputText->toPlainText() + morse_code + ' ');
        return QObject::eventFilter(object, event);;
    }
    else if(keyEvent->key() ==  Qt::Key_Space)
    {
        ui->outputText->setPlainText(ui->outputText->toPlainText() + "/ ");
        return QObject::eventFilter(object, event);;
    }
    else if(keyEvent->key() ==  Qt::Key_Backspace)
    {
        clearAll();
        return QObject::eventFilter(object, event);;
    }
    else
    {
        ui->warningLabel->setText("<font color='red'>Invalid parameter. accepted a-z and 0-9 only</font>");

        qDebug() << "Invalid parameter. accepted a-z and 0-9 only";
        return true; // true bool prevents from passing event further to print text in a text box
    }
}

void MainWindow::clearWarningLabel()
{
    if( ui->warningLabel->isEnabled())
        ui->warningLabel->setDisabled(true);
    ui->warningLabel->clear();
}

bool MainWindow::handleMorse2AlphabetTranslation(QObject *object, QEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    // Pressing space or slash indicate that letter is complete to be decoded from Morse to Alphabet
    if (keyEvent->key() == Qt::Key_Space || keyEvent->key() == Qt::Key_Slash) {
        qDebug() << keyEvent->key();
        // HANDLING CONVERTING LETTER
        clearWarningLabel();
        if(str_buff->size() > 0)
        {
            const char* decoded_ascii_ptr = translator->getMorseBst()->get(str_buff->c_str());

            if(decoded_ascii_ptr != nullptr)
            {
                char dec_ascii = *decoded_ascii_ptr;
                QString d_ascii = QString::fromLatin1(&dec_ascii, sizeof(char));
                ui->outputText->setPlainText(ui->outputText->toPlainText() + d_ascii);
                str_buff->clear();
            }
        }

        if(keyEvent->key() == Qt::Key_Slash)
            ui->outputText->setPlainText(ui->outputText->toPlainText() + ' ');
        return QObject::eventFilter(object, event);
    }
    else if(keyEvent->key() == '.' || keyEvent->key() == '-')
    {
        str_buff->append(sizeof(char),static_cast<char>(keyEvent->key()));
        return QObject::eventFilter(object, event);
    }
    else if(keyEvent->key() ==  Qt::Key_Backspace)
    {
        clearAll(); // should be improved by numbers of dit and dahs
        return false;
    }
    else
    {
        ui->warningLabel->setText("<font color='red'>Invalid parameter. accepted '.' , '-' space and '/'</font>");
        qDebug() << "Invalid parameter. accepted '.' , '-' space and '/'";
        return true; // this will stop going to print text in a text box
    }
}

void MainWindow::clearAll()
{
    str_buff->clear();
    ui->inputTextEdit->clear();
    ui->outputText->clear();
}

void MainWindow::on_modeButton_clicked()
{
    if(mode == ASCII_TO_MORSE)
    {

        mode = MORSE_TO_ASCII;
        ui->modeButton->setText("MORSE TO ASCII");
    }
    else {
        mode = ASCII_TO_MORSE;
        ui->modeButton->setText("ASCII TO MORSE");
    }
    clearAll();

}

void MainWindow::on_clearAllButton_clicked()
{
    clearAll();

}

void MainWindow::on_convertButton_clicked()
{
    std::string whole_text = ui->inputTextEdit->toPlainText().toStdString();
    std::string out_str;

    if(mode == MORSE_TO_ASCII)
        translator->getMorseBst()->decodeWholeText(&whole_text, &out_str);
    else
    {
        QChar search_dot('.');
        QChar search_dah('-');
        QChar search_slash('/');
        if(ui->inputTextEdit->toPlainText().contains(search_dot) || ui->inputTextEdit->toPlainText().contains(search_dah) || ui->inputTextEdit->toPlainText().contains(search_slash))
            ui->warningLabel->setText("<font color='red'>Invalid parameter. accepted a-z and 0-9 only</font>");
        else
            translator->translate2MorseWholeString(&whole_text, &out_str);
    }


    ui->outputText->setPlainText(ui->outputText->toPlainText() + out_str.c_str());
    str_buff->clear();
}
