#ifndef WORDGAMELOGIC_H
#define WORDGAMELOGIC_H

#include <QString>
#include <QList>

class WordGame {
    int maxAttempts = 5;
    QString wordToGuess ;
    QString guessedWord;
    QList<QChar> guessedLetters;
    int attempts;
    bool gameFinished = true;
    QString inputWord;

public:
    int score = 0;
    bool GameFinished();
    void GameFinished (bool val);
    void InputWord (QString val);
    void startGame();
    void generateRandomWord();
    QString checkGuess();
    QString logMessage();
    QString gameOver();
    QString showGameLogs();
};

#endif // WORDGAMELOGIC_H
