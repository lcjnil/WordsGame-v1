//
// Created by NiL on 15/6/3.
//

#include "Referee.h"
#include "Question.h"

int Referee::MAXEXP = 10;

bool Referee::addQuestion(QString word, int level) {
    if (level > 10) {
        level = 10;
    }

    if(Question::findByField("word", word).size()) {
        return false;
    };

    Question * question = new Question(word, level, id);
    int cnt = get("words_count").toInt() + 1;
    set("words_count", QString::number(cnt));

    int exp = get("exp").toInt() + level;
    int lv = get("lv").toInt();

    while (exp >= MAXEXP) {
        exp -= MAXEXP;
        lv++;
    }

    set("exp", QString::number(exp));
    set("level", QString::number(lv));
    update();
    return true;
}
