//
// Created by NiL on 15/6/3.
//

#include "Question.h"

template <> QString Model<Question>::tableName = "Questions";
template <> QString Model<Question>::primaryKey = "questionId";

template <> QMap<QString, QString> Model<Question>::fields{
        {"word", "VARCHAR(255)"},
        {"level", "INTEGETR"},
        {"userId", "INTEGER"}
};

Question::Question(QString word, int level, int userId) {
    set("word", word);
    set("level", level);
    set("userId", userId);

    save();
}

vector<Question> Question::getQuestion(int level) {
    return findByField("level", QString::number(level));
}

vector<Question> Question::getAllQuestion() {
    return findAll();
}

vector<Question> Question::findQuestionByUser(int userId) {
    return findByField("userId", QString::number(userId));
}
