
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highscores.h"
#include "wordGameLogic.h"

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_menu_button_clicked();
    void on_hscoreMenu_button_clicked();
    void buttonSetChecked(bool var);
    void on_newGame_button_clicked();
    void on_check_button_clicked();

private:
    Ui::MainWindow *ui;
    WordGame myGame;
    Highscore HS;
};

#endif // MAINWINDOW_H
