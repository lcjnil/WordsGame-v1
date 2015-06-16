//
// Created by NiL on 15/6/3.
//

#ifndef WORDSGAME_QUESTION_H
#define WORDSGAME_QUESTION_H

#include <vector>
#include "Model.h"

using namespace std;

class Question : public Model<Question> {
public:
    Question(){};
    Question(QString word, int level, int userId);

    QString getWord() {
        return get("word");
    }

    int getLevel() {
        return get("level").toInt();
    }


    // 随机获取题目
    static vector<Question> getQuestion(int level);
    static vector<Question> getAllQuestion();

    static vector<Question> findQuestionByUser(int userId);
    static bool addQuestion(QString word, int level, int userId);
};


#endif //WORDSGAME_QUESTION_H
