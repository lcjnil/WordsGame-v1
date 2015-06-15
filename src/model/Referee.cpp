//
// Created by NiL on 15/6/3.
//

#include "Referee.h"
#include "Question.h"

bool Referee::addQuestion(QString word, int level) {
    Question * question = new Question(word, level, id);
    int cnt = get("words_count").toInt() + 1;
    set("words_count", QString::number(cnt));
    int lv = get("level").toInt() + level;
    set("level", QString::number(lv));
    update();
    return true;
}
