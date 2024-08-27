
#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QString>
#include <QList>
#include <QDateTime>

class Highscore
{

public:
    struct Record {
        int score;
        QString time;
        QString date;
    };
    QList<Record> recordList;
    Highscore();
    void addRecord(int scr);
    int getMin();
    void readHS();
    void sotrPlusCut();
    void writeHS();

};
#endif // HIGHSCORES_H
