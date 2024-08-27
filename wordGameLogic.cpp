#include "wordGameLogic.h"
#include <QApplication>
#include <QTextEdit>
#include <QList>
#include <QString>
#include <QTime>
#include <QRandomGenerator>

void WordGame::InputWord (QString val) {
    inputWord = val;
}
bool WordGame::GameFinished(){
    return gameFinished;
}
void WordGame::GameFinished (bool val){
    gameFinished = val;
}


QString WordGame::logMessage()
{
    QString res = "Загаданное слово:  " + guessedWord + "\n"
          + "Введите слово: ";
    return res;
}

void WordGame::generateRandomWord()
{
    QStringList words{
        "мама", "нога", "вилы","стон","слон","нора","жила","крот","стул","гиря","вена",
        "кран", "муха", "барс", "пирс",  "фонд", "курс", "лукс", "кола", "поло","мост",
        "диск", "муза", "порт", "тазь", "роза", "фонд", "порт", "копь", "тазь", "роза",
        "фонд", "киты", "муха", "диск",  "кедр", "гроза", "плот","парк","гора", "рука",
        "дома", "стол", "саду", "улица", "гора", "лука", "книга", "река", "муха", "котя",
        "лужа", "лось", "мухи", "носа", "поле", "песа", "ветр", "дети", "двер", "житы",
        "кода", "прав", "мура", "жукъ", "порт", "терм", "рожь", "сырк", "капк", "карт",
        "перо", "лоно", "шумъ", "гроз", "клуб", "мусь", "киса", "коло", "пись", "пись",
        "лось", "дуда", "мера", "игра", "пере", "мери", "сахк", "дека", "ледь", "золо",
        "крыс", "сека", "дуло", "купа", "пипа", "жаба", "сила", "река", "крым", "госъ",
        "желт", "глав", "суда", "роба", "вера", "тень", "зрим", "горь", "гиля", "снег",
        "бакс", "фонд", "фонъ", "фона", "нови", "русь", "урок", "лиса", "лицо", "коза",
        "левъ", "мыло", "яръ", "леса", "басъ", "луна", "рука", "гоза", "писк", "кура",
        "биты", "гуги", "ялин", "кыры", "цыпа"
    };

    int index = QRandomGenerator::global()->bounded(words.size());
    wordToGuess = words[index];
}

void WordGame::startGame() {
    generateRandomWord();
    guessedWord = "_ _ _ _";
    guessedLetters.clear();
    attempts = 0;
    score = 0;
    GameFinished(false);
}

QString WordGame::showGameLogs()
{
    guessedWord = "";
    for (int i = 0; i < wordToGuess.length(); ++i)
    {
        if (guessedLetters.contains(wordToGuess[i]) &&  wordToGuess[i] == inputWord[i])
        {
            guessedWord += wordToGuess[i];
        }
        else
        {
            guessedWord += "_";
        }
        guessedWord += " ";
    }

    QStringList strList;
    for (const QChar &c : guessedLetters) {
        strList.append(QString(c));
    }
    QString res = "Отгаданные буквы: " + strList.join(", ") + "\n";
    res += guessedWord;
    return res;
}

QString WordGame::gameOver()
{
    QString res =  ("\nВаш общий счет: " + QString::number(score) + " баллов.");
    attempts = 0;
    guessedLetters.clear();
    return res;
}

QString WordGame::checkGuess() {
    QString outputToLogs = " >> " + inputWord + "\n";
    if (inputWord != "н" && inputWord != "д") {
        attempts++;
        if (inputWord == wordToGuess) {
            int tempScore = maxAttempts - attempts + 1;
            attempts = 0;
            outputToLogs += "Вы отгадали слово и заработали " + QString::number(tempScore) + " балла";
            score += tempScore;
            outputToLogs += gameOver();
            outputToLogs += "\nЖелаете продолжить? (д/н)\n";
            return outputToLogs;
        }
    }
    if (inputWord == "н") {
        gameFinished = true;
        outputToLogs += "Игра окончена.";
        outputToLogs += gameOver();
        return outputToLogs;
    }
    if (inputWord == "д") {

        generateRandomWord();
        guessedWord = "_ _ _ _";
        attempts = 0;
        GameFinished(false);
        outputToLogs += logMessage();
        return outputToLogs;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (!guessedLetters.contains(inputWord[i]) && wordToGuess.contains(inputWord[i]))
            {
                QChar buff = inputWord[i];
                guessedLetters.append(buff);
            }
        }
        outputToLogs += showGameLogs();
        outputToLogs += "\nВведите слово. ";
        if (attempts == maxAttempts) {
            outputToLogs += ("Попытки закончились, игра окончена.");
            outputToLogs +=  "\nВаш общий счет: " + QString::number(score) + " баллов.";
            outputToLogs += "\nEсли желаете продолжить нажмите New Game.";
            GameFinished(true);
        }
        return outputToLogs;
    }
}

