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

    morseBst = new MorseBST();
    str_buff = new std::string();
    ui->pushButton->setText("ASCII TO MORSE");
    ui->clearAllButton->setText("Clear All");
    ui->inputTextEdit->setPlainText("");
    ui->outputText->setPlainText("");
    ui->instructionLabel->setText("Instruction:\nASCII TO MORSE mode:  Insert normal text\nMORSE TO ASCII mode:  Write morse code \".\" or \"-\" separating\nletters by spaces and words by slash \"/\"");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete translator;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{    
    if (mode == TRANSLATOR_MODE::ASCII_TO_MORSE && object == ui->inputTextEdit && event->type() == QEvent::KeyPress) {
        return handleASCII2MorseTranslation(object, event);
    }
    else if (mode == TRANSLATOR_MODE::MORSE_TO_ASCII && object == ui->inputTextEdit && event->type() == QEvent::KeyPress) {
        return handleMorse2ASCIITranslation(object, event);
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
        // qDebug() << "cursor for inputTextEdit: " << ui->inputTextEdit->cursorForPosition);
        morse_code = translator->translate2Morse(keyEvent->key());
        qDebug() << "inputTextEdit->pos(): " << ui->inputTextEdit->pos();
        qDebug() << "outputText->pos(): " << ui->outputText->pos();
        //        ui->outputText->textCursor().insertText(morse_code);
        ui->outputText->setPlainText(ui->outputText->toPlainText() + morse_code + ' ');
        // qDebug() << "cursor for outputText: " << ui->outputText->cursorForPosition();
        //        return QObject::eventFilter(object, event);
        return QObject::eventFilter(object, event);;
    }
    else if(keyEvent->key() ==  Qt::Key_Space)
    {
        ui->outputText->setPlainText(ui->outputText->toPlainText() + "/ ");
        return QObject::eventFilter(object, event);;
    }
    else if(keyEvent->key() ==  Qt::Key_Backspace)
    {
        //            QKeyEvent * evt = new QKeyEvent(QEvent::Type::KeyPress, keyEvent->key(), Qt::ControlModifier);
        //            QCoreApplication::postEvent(ui->outputText, evt);
        clearAll();
        //  ui->outputText->textCursor().deletePreviousChar(); // should be improved by numbers of dit and dahs
        return QObject::eventFilter(object, event);;
    }
    else
    {
        ui->warningLabel->setText("Invalid parameter. accepted a-z and 0-9 only");

        qDebug() << "Invalid parameter. accepted a-z and 0-9 only";
        return true; // this will stop going to print text in a text box
    }
}

void MainWindow::clearWarningLabel()
{
    if( ui->warningLabel->isEnabled())
        ui->warningLabel->setDisabled(true);
    ui->warningLabel->clear();
}

bool MainWindow::handleMorse2ASCIITranslation(QObject *object, QEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Space || keyEvent->key() == Qt::Key_Slash) {
        qDebug() << keyEvent->key();
        // HANDLING CONVERTING LETTER
        clearWarningLabel();
        if(str_buff->size() > 0)
        {
            const char* decoded_ascii_ptr = morseBst->get(str_buff->c_str());

            if(decoded_ascii_ptr != nullptr)
            {
                char dec_ascii = *decoded_ascii_ptr;
                QString d_ascii = QString::fromLatin1(&dec_ascii, sizeof(char));
                ui->outputText->setPlainText(ui->outputText->toPlainText() + d_ascii);
                str_buff->clear();
            }
        }

        if(keyEvent->key() == Qt::Key_Slash)
            ui->outputText->setPlainText(ui->outputText->toPlainText() + "/");
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
        ui->warningLabel->setText("Invalid parameter. accepted a-z and 0-9 only");
        qDebug() << "Invalid parameter. accepted a-z and 0-9 only";
        return true; // this will stop going to print text in a text box
    }
}

void MainWindow::clearAll()
{
    str_buff->clear();
    ui->inputTextEdit->clear();
    ui->outputText->clear();
}

void MainWindow::on_pushButton_clicked()
{
    if(mode == ASCII_TO_MORSE)
    {

        mode = MORSE_TO_ASCII;
        ui->pushButton->setText("MORSE TO ASCII");
    }
    else {
        mode = ASCII_TO_MORSE;
        ui->pushButton->setText("ASCII TO MORSE");
    }
    clearAll();

}

void MainWindow::on_clearAllButton_clicked()
{
    clearAll();

}

void MainWindow::on_pushButton_2_clicked()
{
    std::string whole_text = ui->inputTextEdit->toPlainText().toStdString();
    std::string out_str;

    if(mode == MORSE_TO_ASCII)
        morseBst->decodeWholeText(&whole_text, &out_str);
    else
        translator->translate2MorseWholeString(&whole_text, &out_str);

    ui->outputText->setPlainText(ui->outputText->toPlainText() + out_str.c_str());
    str_buff->clear();
}
