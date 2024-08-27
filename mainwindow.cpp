
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->highscoreList_textEdit->setVisible(false);
    ui->check_button->setEnabled(false);
    ui->input_lineEdin->setEnabled(false);

    HS.readHS();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::buttonSetChecked(bool var)
{
    ui->hscoreMenu_button->setChecked(var);
    ui->highscoreList_textEdit->setVisible(var);
    ui->menu_button->setChecked(!var);
    ui->newGame_button->setEnabled(!var);

}


void MainWindow::on_menu_button_clicked()
{
    ui->gameLogs_textEdit->clear();
    buttonSetChecked(false);
}


void MainWindow::on_hscoreMenu_button_clicked()
{
    buttonSetChecked(true);
    ui->check_button->setEnabled(false);
    ui->input_lineEdin->setEnabled(false);
    HS.writeHS();
    ui->highscoreList_textEdit->clear();
    for (int i = 0; i < HS.recordList.length(); ++i) {
        ui->highscoreList_textEdit->append(
            QString::number(i+1) + ") " + QString::number(HS.recordList[i].score)+ " б\t"+
            HS.recordList[i].time + " "+ HS.recordList[i].date
        );
    }
}


void MainWindow::on_newGame_button_clicked()
{
    ui->gameLogs_textEdit->clear();
    myGame.startGame();
    ui->gameLogs_textEdit->append(myGame.logMessage());
    myGame.GameFinished(false);
    ui->check_button->setEnabled(true);
    ui->input_lineEdin->setEnabled(true);
}


void MainWindow::on_check_button_clicked()
{
    QString inputWord = ui->input_lineEdin->text();
    if(inputWord.size() != 4 && inputWord != "н" && inputWord != "д"){
        ui->gameLogs_textEdit->append("Введите слово еще раз. \n");
        ui->input_lineEdin->clear();
        return;
    }
    myGame.InputWord(inputWord);
    ui->gameLogs_textEdit->append(myGame.checkGuess());
    ui->input_lineEdin->clear();
    if(HS.getMin() < myGame.score && myGame.GameFinished()){
        HS.addRecord(myGame.score);
    }
}

