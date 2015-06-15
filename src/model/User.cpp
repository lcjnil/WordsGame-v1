//
// Created by NiL on 15/4/8.
//

#include "User.h"

#include <QDebug>

template <> QString Model<User>::tableName = "Users";
template <> QString Model<User>::primaryKey = "userId";

template <> QMap<QString, QString> Model<User>::fields{
    {"name", "VARCHAR(255)"},
    {"password", "VARCHAR(255)"},
    {"type", "VARCHAR(255)"},
    {"stage_obtained", "INTEGER"},
    {"exp", "INTEGER"},
    {"level", "INTEGER"},
    {"words_count", "INTEGER"}
};

User User::findByName(QString name) {
    vector<User> users = User::findByField("name", name);
    if (users.size() != 0) {
        return users[0];
    } else {
        return User();
    }
}

QString User::auth(QString name, QString password) {
    User user = User::findByName(name);

    if (!user.isEmpty()) {
        return (user.get("password") == password ? user.get("type") : "");
    } else {
        return "";
    }
}

bool User::reg(QString name, QString password, QString type) {
    User udb;
    if (!User::findByName(name).isEmpty()) {
        return false;
    }
    udb.set("name", name);
    udb.set("password", password);
    udb.set("type", type);
    return udb.save();
}
