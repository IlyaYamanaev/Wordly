
#include "highscores.h"
#include <QFile>
#include <QString>
#include <QtAlgorithms>
#include <QTextStream>
#include <QList>
#include <QDebug>


Highscore::Highscore(){}


void Highscore::addRecord(int scr)
{
    Record newrec;
    newrec.score = scr;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    newrec.time = currentDateTime.toString("hh:mm");
    newrec.date = currentDateTime.toString("dd.MM");
    recordList.append(newrec);
}

int Highscore::getMin(){
    if (recordList.isEmpty())
        return 0;
    int minScore = recordList[0].score;
    for (const Record &record : recordList) {
        if (record.score < minScore) {
            minScore = record.score;
        }
    }
    return minScore;
}

void Highscore::readHS(){
    QFile file("SPISOKRECORDOV.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 3) {
            Record newrec;
            newrec.score = parts[0].toInt();
            newrec.time = parts[1];
            newrec.date = parts[2];
            recordList.append(newrec);
        }
    }
    file.close();
}

void Highscore::sotrPlusCut(){
    int n = recordList.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (recordList[j].score < recordList[j + 1].score) {
                Record temp = recordList[j];
                recordList[j] = recordList[j + 1];
                recordList[j + 1] = temp;
            }
        }
    }
    if (recordList.size() > 5) {
        recordList = recordList.mid(0, 5);
    }
}

void Highscore::writeHS(){

    QFile file("SPISOKRECORDOV.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    sotrPlusCut();
    QTextStream out(&file);
    for (Record &recc : recordList) {
        out << QString::number(recc.score) << " " << recc.time << " " << recc.date << "\n";
    }
    file.close();
    return;
}








